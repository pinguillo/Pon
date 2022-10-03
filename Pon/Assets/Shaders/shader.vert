#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 colors;
layout(location = 2) in vec3 normals;
layout(location = 3) in vec2 texCoord;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec2 outTexCoord;
layout(location = 3) out vec3 FragPos;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main(){
	outColor = vec4(colors, 1.0);
	outNormals = mat3(transpose(inverse(transform))) * normals;
	outTexCoord = texCoord;

	gl_Position = projection * view * transform * vec4(pos, 1.0);
}