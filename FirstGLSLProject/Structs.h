#pragma once
#include <Windows.h>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include "LightIncludes.h"
#include "Definitions.h"

struct Vertex
{
	GLfloat x, y, z;
};

struct Normal
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct InterlacedVertex
{
	Vertex Vertices;
	Normal Normals;
	TexCoord TexCoords;
};

struct SceneLights
{
	DirectionalLight* directionalLight = nullptr;
	PointLight* pointLights[MAXPOINTLIGHTS] = { nullptr, nullptr, nullptr, nullptr };
	SpotLight* spotLight = nullptr;
	TestLight* testLight = nullptr;

	void DeletePointLight(std::string lightName)
	{
		for (int i = 0; i < 4; i++)
		{
			if (pointLights[i] != nullptr && pointLights[i]->GetName() == lightName)
			{
				delete pointLights[i];
				pointLights[i] = nullptr;
				break;
			}
		}
	}

	void AddPointLight(PointLight* light)
	{
		for (int i = 0; i < 4; i++)
		{
			if (pointLights[i] == nullptr)
			{
				pointLights[i] = light;
				break;
			}
		}
	}
};

struct Mesh
{
	std::vector<float> vertices;


	TexCoord* TexCoords;
	int IndexCount;

	std::vector<InterlacedVertex> InterVertex;
};