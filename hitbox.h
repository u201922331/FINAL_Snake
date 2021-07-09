#pragma once

#ifndef _HITBOX_
#define _HITBOX_

enum class Axes { X, Y, Z, ALL };

class Hitbox {
public:
	glm::vec3 pos;
private:
	glm::vec3 scale;

public:
	Hitbox(glm::vec3 pos, glm::vec3 scale) :
		pos(pos), scale(scale)  {}

	void Update(glm::vec3 meshPos, glm::vec3 newScale) { pos = meshPos; scale = newScale; }
	bool IntersectsWith(Hitbox _htb, Axes ax = Axes::ALL) {
		switch (ax) {
		case Axes::ALL:
			return
				(this->min().x <= _htb.max().x && this->max().x >= _htb.min().x) &&
				(this->min().y <= _htb.max().y && this->max().y >= _htb.min().y) &&
				(this->min().z <= _htb.max().z && this->max().z >= _htb.min().z);
		case Axes::X:
			return (this->min().x <= _htb.max().x && this->max().x >= _htb.min().x);
		case Axes::Y:
			return (this->min().y <= _htb.max().y && this->max().y >= _htb.min().y);
		case Axes::Z:
			return (this->min().z <= _htb.max().z && this->max().z >= _htb.min().z);
		}
	}

	glm::vec3 min() { return pos - scale / 2.0f; }
	glm::vec3 max() { return pos + scale / 2.0f; }
};

#endif