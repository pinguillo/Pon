#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 colors;// I forgor
layout(location = 2) in vec3 normals;
layout(location = 3) in vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main() {
	FragPos = vec3(transform * vec4(pos, 1.0));
	Normal = mat3(transpose(inverse(transform))) * normals;
	UV = vec2( texCoord.x, texCoord.y);// texCoord;

	gl_Position = projection * view * vec4(FragPos, 1.0);
}