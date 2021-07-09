#include "snake.h"

const u32 SCR_WIDTH = 1200;
const u32 SCR_HEIGHT = 675;
const f32 ASPECT = (f32)SCR_WIDTH / (f32)SCR_HEIGHT;

const u32 FSIZE = sizeof(f32);
const u32 ISIZE = sizeof(i32);

Cam* cam;

f32 deltaTime = 0.0f;
f32 lastFrame = 0.0f;
bool wireframe = false;

Game* snake;

void key_callback(GLFWwindow* window, int key, int, int act, int) {
	wireframe ^= key == GLFW_KEY_E && act == GLFW_PRESS;

	if (act == GLFW_PRESS) {
		// Cambiar direccion de la serpiente
		if (key == GLFW_KEY_UP    && snake->direction != -1.0f * U) snake->direction = U;
		if (key == GLFW_KEY_LEFT  && snake->direction != -1.0f * L) snake->direction = L;
		if (key == GLFW_KEY_DOWN  && snake->direction != -1.0f * D) snake->direction = D;
		if (key == GLFW_KEY_RIGHT && snake->direction != -1.0f * R) snake->direction = R;
	}

	// AUTO: Detectar si la cabeza chocó con algo
	for (u32 i = 0; i < snake->wall_htb.size(); i++)
		if (snake->snake_body[0]->IntersectsWith(*snake->wall_htb[i])) glfwSetWindowShouldClose(window, true);

	for (u32 i = 1; i < snake->snake_body.size(); i++)
		if (snake->snake_body[0]->IntersectsWith(*snake->snake_body[i]))  glfwSetWindowShouldClose(window, true);
}
void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		cam->movePov(xpos, ypos);
	}
	else {
		cam->stopPov();
	}
}
void scroll_callback(GLFWwindow*, f64, f64 yoffset) {
	cam->processScroll((f32)yoffset);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam->processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam->processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam->processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam->processKeyboard(RIGHT, deltaTime);
	}
}

i32 main() {
	GLFWwindow* window = glutilInit(3, 3, SCR_WIDTH, SCR_HEIGHT, "Snake");

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	i32 w = 10;
	i32 h = 10;

	cam = new Cam({ w, 30.0f, h }, { 0.0f, 1.0f, 0.0f }, glm::radians(-90.0f), glm::radians(-89.0f)); cam->speed = 5.0f;
	snake = new Game(w, h);

	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(window)) {
		f32 currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.1 * sin(currentFrame) + 0.05, 0.1 * sin(currentFrame) + 0.05, 0.1 * sin(currentFrame) + 0.05, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

		snake->Display(*cam, ASPECT);
		snake->Update(currentFrame);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete cam;

	return 0;
}