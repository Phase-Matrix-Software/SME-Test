#version 430

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec4 inColor;

void main() {
	outColor = inColor;
}