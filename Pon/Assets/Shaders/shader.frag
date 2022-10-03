#version 410 core

layout(location = 0) in vec4 colors;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 FragPos; 

out vec4 FragColor;

uniform sampler2D text;
uniform vec3 viewPos; 
uniform vec3 lightPos;
uniform vec3 lightColor;

void main(){
	// Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(normals);
	vec3 lightDir = normalize( lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

	vec3 result = (ambient + diffuse + specular) * colors.xyz;

	FragColor = vec4(result, 1.0) * texture(text, texCoord);
}