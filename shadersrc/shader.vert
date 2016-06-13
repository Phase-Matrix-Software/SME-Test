#version 430

layout(location = 0) out vec4 outColor;

void main() {
	vec4 color[3] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0));
	vec2 pos[3] = vec2[3](vec2(-1, 1), vec2(1, 1), vec2(0, -1));
	gl_Position = vec4(pos[gl_VertexIndex], 0.0, 1.0);
	outColor = color[gl_VertexIndex];
}