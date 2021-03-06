#version 330 core
in vec2 fragUVs;
out vec4 finalColor;

uniform sampler2D texture_diffuse1;

uniform int mode;
uniform int num;

void main() {
	vec4 color;
	switch(mode) {
	case 1:  // Serpiente
		if (num == 0)
			color = vec4(0.75f, 0.0f, 0.0f, 1.0f);
		else
			if (num % 2 == 0)
				color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
			else
				color = vec4(0.0f, 0.5f, 0.0f, 1.0f);
		break;
	case 2: // Comida
		color = vec4(1.0f, 0.6f, 0.0f, 1.0f); break;
	case 0:  // Default: Paredes
		color = vec4(1.0f); break;
	}

	finalColor = texture(texture_diffuse1, fragUVs) * color;
}