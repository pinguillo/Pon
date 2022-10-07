#pragma once
#include "Types\Math.hpp"
#include "Mesh.hpp"

#include <string>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>//Some is not needed
#include <glm\gtx\hash.hpp>

class Model
{
public:
	Model();
	Model(const std::string& filePath);
	~Model();

	void Loadmdl(const std::string& filePath);
	void setScale(Vec3 scale);
	void setRotation(Vec3 rot);
	void setPosition(Vec3 pos);
	void UpdateTransform();


	void Draw(glm::mat4& proj, glm::mat4& view);

private:

	glm::mat4 transformMatrix = glm::mat4(1.0f);
	Vec3 position{};
	Vec3 scale = Vec3().identity();
	Vec3 rotation{};

	ModelVectors mdl;

	std::vector<Mesh> meshes;
};