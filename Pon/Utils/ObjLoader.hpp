#pragma once
#include "../Engine/Log.hpp"
#include "../Engine/Types/Math.hpp"
#include "Utils.hpp"

#include <fstream>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\hash.hpp>

#include <unordered_map>

namespace std {
	template <>
	struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			size_t seed = 0;
			hashCombine(seed, vertex.position, vertex.color, vertex.texCoord);
			return seed;
		}
	};
}

bool KeyCheck(std::string& line, const char* text)
{
	ui32 textLength = strlen(text);
	if (line.size() < textLength)
	{
		return false;
	}

	for (ui32 i = 0; i < textLength; i++)
	{
		if (line[i] == text[i])
		{
			continue;
		}
		else 
		{
			return false;
		}
		return true;
	}
}

static ModelVectors loadOBJ(const char* filePath) {
	ModelVectors meshData;
	std::unordered_map<Vertex, ui32> uniqueVerts{};

	std::ifstream file(filePath);
	if (file)
	{
		std::vector<std::string> mats;
		std::string line;
		char mtlName[256]{};


		while (std::getline(file,line))
		{
			Vertex v;

			if (KeyCheck(line, "v "))
			{
				float x, y, z;
				sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);
				//meshData.positions.push_back(glm::vec3(x, y, z));
				v.position = glm::vec3(x, y, z);
			}
			if (KeyCheck(line, "vn "))
			{
				float x, y, z;
				sscanf_s(line.c_str(), "vn %f %f %f", &x, &y, &z);
				//meshData.normals.push_back(glm::vec3(x, y, z));
				v.normals = glm::vec3(x, y, z);
			}
			if (KeyCheck(line, "vt "))
			{
				float x, y;
				sscanf_s(line.c_str(), "vt %f %f", &x, &y);
				//meshData.textureCoords.push_back(glm::vec2(x, y));
				v.texCoord = glm::vec2(x, y);
			}

			if (KeyCheck(line, "usemtl"))
			{
				(void) sscanf_s(line.c_str(), "usemtl %s", mtlName, sizeof(mtlName));

				if (std::find(mats.begin(), mats.end(), mtlName) != mats.end())
				{
					mats.push_back(mtlName);
				}
			}
			if (KeyCheck(line, "f "))
			{
				ui32 v1, v2, v3, v4;
				ui32 n1, n2, n3, n4;
				ui32 vt1, vt2, vt3, vt4;
				int found = sscanf_s(
					line.c_str(),
					"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
					&v1, &vt1, &n1,
					&v2, &vt2, &n2,
					&v3, &vt3, &n3,
					&v4, &vt4, &n4
				);
				
				meshData.indices.push_back(v1);
				meshData.indices.push_back(v2);
				meshData.indices.push_back(v3);
				if (found > 9)
				{
					meshData.indices.push_back(v4);
				}
				//meshData.faceIndices.push_back(glm::ivec3(v1, vt1, n1));
				//meshData.faceIndices.push_back(glm::ivec3(v2, vt2, n2));
				//meshData.faceIndices.push_back(glm::ivec3(v3, vt3, n3));
				
			}

			meshData.vertex.push_back(v);
		}

		return meshData;
	}
	else
	{
		PIN_WARNING("Failed to load \"" << filePath << "\"");
	}
	return meshData;
}