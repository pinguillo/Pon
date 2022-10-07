#include "Model.hpp"
#include "Log.hpp"
//#include "../Utils/Utils.hpp"
#include "../Utils/ObjLoader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

/*
namespace std
{
	template <>
	struct hash<Vertex>
	{
		size_t operator()(Vertex const& vertex) const
		{
			size_t seed = 0;
			hashCombine(seed, vertex.position, vertex.color, vertex.texCoord);
			return seed;
		}
	};
}*/

Model::Model()
{
	//Loadmdl("Assets/Models/cube.obj");
}

Model::Model(const std::string& filePath)
{
	//Loadmdl(filePath);
}

Model::~Model()
{
}

void Model::Draw(glm::mat4& proj, glm::mat4& view)
{
	UpdateTransform();
	
	for (Mesh& m : meshes)
	{
		m.mat.shader->Bind();
		m.mat.shader->setMat4("projection", proj);
		m.mat.shader->setMat4("view", view);
		m.Draw(transformMatrix);
	}
}

void Model::Loadmdl(const std::string& filePath)
{
	/*
	// Clear previous data
	meshes.clear();
	std::vector<ui32> indices;
	std::vector<Vertex> vertexList;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str()))
	{
		PIN_ERROR(warn + err);
	}

	std::unordered_map<Vertex, ui32> uniqueVerts{};
	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			Vertex vert{};

			if (index.vertex_index >= 0)
			{
				vert.position =
				{
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};
				vert.color =
				{
					attrib.colors[3 * index.vertex_index + 0],
					attrib.colors[3 * index.vertex_index + 1],
					attrib.colors[3 * index.vertex_index + 2]
				};
			}

			if (index.normal_index >= 0)
			{
				vert.normals =
				{
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};
			}

			if (index.texcoord_index >= 0)
			{
				vert.texCoord =
				{
					attrib.texcoords[2 * index.texcoord_index + 0],
					attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}
			
			if (uniqueVerts.count(vert) == 0)
			{
				uniqueVerts[vert] = static_cast<ui32>(vertexList.size());
				vertexList.push_back(vert);
			}
			indices.push_back(uniqueVerts[vert]);
		}
	}*/

	mdl = loadOBJ(filePath.c_str());
	Mesh m;

	m.vertexList = mdl.vertex;
	m.indices = mdl.indices;
	//m.mat = Material();

	m.CreateGL();
	meshes.push_back(m);

	UpdateTransform();
}

void Model::setScale(Vec3 _scale)
{
	scale = _scale;
}

void Model::setRotation(Vec3 rot)
{
	rotation = rot;
}

void Model::setPosition(Vec3 pos)
{
	position = pos;
}

void Model::UpdateTransform()
{
	glm::mat4 temp, transform;
	temp = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	transform = temp;

	temp = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
	transform *= temp;

	temp = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	temp = glm::rotate(temp, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::rotate(temp, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	transform *= temp;
	
	transformMatrix = transform;
}
