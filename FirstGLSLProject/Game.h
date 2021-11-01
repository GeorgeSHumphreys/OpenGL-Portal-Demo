#pragma once
#include <Windows.h>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "Structs.h"
#include "SceneObject.h"
#include "LightCube.h"
#include "LightIncludes.h"
#include "TestLight.h"
#include "MaterialIncludes.h"
#include "MeshLoader.h"
#include "Definitions.h"
#include "Portal.h"


class Game
{
public:
	Game(int argc, char* argv[]);

	void InitGL();
	void InitOthers();
	void SetupLights();
	void SetupFrameBuffer();

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void KeyboardUp(unsigned char key, int x, int y);

	void MouseMove(int x, int y);

	~Game(void);

private:
	void PortalCalculations(float deltaTime);
	std::vector<SceneObject*> _hierarchy;
	std::vector<Portal*> _portals;
	Camera* camera;
	Camera* camera2;
	Camera* mainCamera;
	float _oldT;
	SceneLights _sceneLights;

	unsigned int _frameBuffer;
	GLuint _textureColourBuffer;
	unsigned int _rbo;
};

