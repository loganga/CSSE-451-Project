#version 330

in vec3 pos;
in vec3 colorIn;

smooth out vec4 smoothColor;

void main() {
	smoothColor = vec4(colorIn, 1);
}