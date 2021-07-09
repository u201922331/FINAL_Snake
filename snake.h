#pragma once

#ifndef _SNAKE_
#define _SNAKE_

#define _USE_MATH_DEFINES
#include <files.hpp>
#include <model.hpp>
#include <cam.hpp>

#include "hitbox.h"

#define SNAKE_INIT 4

typedef glm::vec3 v3;
const v3 U = {  0, 0, -1 };
const v3 D = {  0, 0,  1 };
const v3 L = { -1, 0,  0 };
const v3 R = {  1, 0,  0 };

class Game {
	Files* files;
	Shader* gameShader;

	// Muros
	Model* block;
	std::vector<v3> wall_pos;

	// Serpiente
	std::vector<v3> snake;
	
public:
	std::vector<Hitbox*> wall_htb;
	std::vector<Hitbox*> snake_body;
public:
	v3 direction = L;

	Game(i32 w = 10, i32 h = 10) :
		files(new Files("resources/shaders", "resources/textures", "resources/objects"))
	{
		gameShader = new Shader(files, "shader.vert", "shader.frag");

		block = new Model(files, "box/box.obj");
		for (u32 i = 0; i < w; i++) for (u32 j = 0; j < h; j++) {
			if (i == 0 || i == w - 1 || j == 0 || j == h - 1) {
				wall_pos.push_back({ 2 * i, 0, 2 * j });
				wall_htb.push_back(new Hitbox({ 2 * i, 0, 2 * j }, v3(2.0f)));
			}
		}
		for (u32 i = 0; i < SNAKE_INIT; i++) {
			snake.push_back({ 2 * (w - 1 - SNAKE_INIT + i), 0,  2 * 1 });
			snake_body.push_back(new Hitbox({ 2 * (w - 1 - SNAKE_INIT + i), 0,  2 * 1 }, v3(1.95f)));
		}
	}

	void Update(f32 frame) {
		if (i32(frame * 10000) % 10 == 0) {
			for (u32 i = 0; i < snake.size(); i++) {
				snake[i] += 2.0f * direction;
				snake_body[i]->Update(snake[i], v3(1.95f));
			}
			//snake[0] += 2.0f * direction;
			
			/*for (u32 i = 0; i < wall_htb.size(); i++) {
				std::cout << snake_body[0]->IntersectsWith(*wall_htb[i]) << '\n';
			}*/
		}

	}

	void Display(Cam camera, f32 aspect) {
		// Muros
		gameShader->use();
		gameShader->setI32("mode", 0);
		for (u32 i = 0; i < wall_pos.size(); i++) {
			block->Draw(gameShader, camera, aspect, wall_pos[i]);
		}

		// Serpiente
		gameShader->use();
		gameShader->setI32("mode", 1);
		for (u32 i = 0; i < snake.size(); i++) {
			gameShader->setI32("num", i);
			block->Draw(gameShader, camera, aspect, snake[i]);
		}
	}
};

#endif
