#version 430

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;

layout(location = 0) out vec4 outColor;

void main() {
	gl_Position = pos;
	outColor = color;
}