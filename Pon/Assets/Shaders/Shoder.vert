#version 330 core

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 colors;
layout(location = 2) in vec3 normals;
layout(location = 3) in vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main() {
    FragPos = vec3(transform * vec4(Pos, 1.0));
    Normal = mat3(transpose(inverse(transform))) * normals;  
    TexCoords = texCoord;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}