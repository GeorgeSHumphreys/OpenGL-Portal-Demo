#include "Game.h"
#include "GLUTCallbacks.h"
#include "Shader.h"


Game::Game(int argc, char* argv[])
{
	glutInit(&argc, argv);
	InitGL();
	InitOthers();

	glutMainLoop();
}

void Game::InitGL()
{
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	GLUTCallbacks::Init(this);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("Portal Demo");
	glewInit();
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutPassiveMotionFunc(GLUTCallbacks::mouse_callback);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

void Game::SetupLights()
{
	Mesh* Cube = MeshLoader::LoadObj((char*)"Cube.obj");
	Material* lightMaterialWhite = (Material*)(new UnlitMaterial("LightCubeShader", { 1.0, 1.0, 1.0 }));
	Material* lightMaterialBlue = (Material*)(new UnlitMaterial("LightCubeShader", { 0.0, 0.0, 1.0 }));
	Material* lightMaterialRed = (Material*)(new UnlitMaterial("LightCubeShader", { 1.0, 0.0, 0.0 }));
	Material* lightMaterialGreen = (Material*)(new UnlitMaterial("LightCubeShader", { 0.0, 1.0, 0.0 }));
	SceneObject* lightCube;

	// DirectionalLight(Name, Direction, Ambient, Diffuse, Specular)
	DirectionalLight* DirectionLight = new DirectionalLight("Direction", { -0.2f, -1.0f, -0.3f }, { 1.0, 1.0, 1.0 }, 0.5f);
	// PointLight(Name, Position, Ambient, Diffuse, Specular, Constant, Linear, Quadratic
	PointLight* pointLight1 = new PointLight("Point1", glm::vec3(0.7f, -4.0f, 2.0f), { 1.0, 1.0, 1.0 }, 0.8f, 1.0, 0.09, 0.032);
	lightCube = new SceneObject("lightCube1", Cube, lightMaterialWhite, pointLight1->position, { 0.3, 0.3, 0.3 });
	_hierarchy.push_back(lightCube);

	PointLight* pointLight2 = new PointLight("Point2", glm::vec3(2.3f, -3.3f, -4.0f), { 0.0, 0.0, 1.0 }, 0.8f, 1.0, 0.09, 0.032);
	lightCube = new SceneObject("lightCube2", Cube, lightMaterialBlue, pointLight2->position, { 0.3, 0.3, 0.3 });
	_hierarchy.push_back(lightCube);

	PointLight* pointLight3 = new PointLight("Point3", glm::vec3(46.0f, 0.0f, -4.0f), { 1.0, 1.0, 1.0 }, 0.8f, 1.0, 0.09, 0.032);
	lightCube = new SceneObject("lightCube3", Cube, lightMaterialWhite, pointLight3->position, { 0.3, 0.3, 0.3 });
	_hierarchy.push_back(lightCube);

	PointLight* pointLight4 = new PointLight("Point4", glm::vec3(0.0f, 0.0f, -3.0f), { 0.0, 1.0, 0.0 }, 0.8f, 1.0, 0.09, 0.032);
	lightCube = new SceneObject("lightCube4", Cube, lightMaterialGreen, pointLight4->position, { 0.3, 0.3, 0.3 });
	_hierarchy.push_back(lightCube);

	// Test Light
	TestLight* testLight = new TestLight("TestLight", { 1.2, 1.0, 2.0 }, { 0.2, 0.2, 0.2 }, { 0.5, 0.5, 0.5 }, { 1.0, 1.0, 1.0 });

	_sceneLights.directionalLight = DirectionLight;
	_sceneLights.pointLights[0] = pointLight1;
	_sceneLights.pointLights[1] = pointLight2;
	_sceneLights.pointLights[2] = pointLight3;
	_sceneLights.pointLights[3] = pointLight4;
	_sceneLights.testLight = testLight;
}

void Game::InitOthers()
{
	_oldT = glutGet(GLUT_ELAPSED_TIME);
	Mesh* Bomb = MeshLoader::LoadObj((char*)"Cube.obj");
	Mesh* Plane = MeshLoader::LoadObj((char*)"Plane.obj");
	Mesh* CameraMesh = MeshLoader::LoadObj((char*)"Bomb.obj");
	Mesh* PortalMesh = MeshLoader::LoadObj((char*)"Portal.obj");
	
	Material* litMaterial = (Material*)(new LightingMaterial("MultipleLightingShaderTextured"));
	litMaterial->SetMaterialProperties({ 1.0, 0.5, 0.31 }, { 1.0, 0.5, 0.31 }, { 0.5, 0.5, 0.5 }, 32);
	Texture2D* litMatTex = new Texture2D();
	litMatTex->LoadTextureTGA("Images/BombTexture.tga");
	litMaterial->SetTexture(litMatTex);

	Material* litMaterialPlane = (Material*)(new LightingMaterial("MultipleLightingShaderTextured"));
	Texture2D* litMatTexPlane = new Texture2D();
	litMatTexPlane->LoadTextureTGA("Images/Orange.tga");
	litMaterialPlane->SetTexture(litMatTexPlane);

	Material* litMaterialPlane2 = (Material*)(new LightingMaterial("MultipleLightingShaderTextured"));
	Texture2D* litMatTexPlane2 = new Texture2D();
	litMatTexPlane2->LoadTextureTGA("Images/Green.tga");
	litMaterialPlane2->SetTexture(litMatTexPlane2);

	Material* grassMaterial = (Material*)(new LightingMaterial("MultipleLightingShaderTextured"));
	Texture2D* grassTex = new Texture2D();
	grassTex->LoadTextureTGA("Images/grass.tga");
	grassMaterial->SetTexture(grassTex);

	Material* depthBufferMat = (Material*)(new LightingMaterial("MultipleLightingDepthBuffer"));
	Texture2D* GreenTex = new Texture2D();
	GreenTex->LoadTextureTGA("Images/Green.tga");
	depthBufferMat->SetTexture(GreenTex);

	

	Material* frameBufferMaterial = (Material*)(new FrameBufferMaterial("FrameBufferShader", _textureColourBuffer));
	
	SceneObject* cube = new SceneObject("Capsule", Bomb, depthBufferMat, { 0.0, -2.0, -7.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.0, 0.0 });
	_hierarchy.push_back(cube);

	SceneObject* bomb = new SceneObject("Bomb", CameraMesh, litMaterial, { 45.0, -3.0, -5.0 });
	_hierarchy.push_back(bomb);

	SceneObject* plane = new SceneObject("Plane", Plane, litMaterialPlane, { 0.0, -5.0, 0.0 }, { 15.0, 1.0, 15.0 });
	_hierarchy.push_back(plane);
	plane = new SceneObject("Plane", Plane, litMaterialPlane2, { 45.0, -5.0, 0.0 }, { 15.0, 1.0, 15.0 });
	_hierarchy.push_back(plane);

	SceneObject* grass = new SceneObject("Grass", Plane, grassMaterial, { -3.0, -4.0, 0.0 }, { 1.0, 1.0, 1.0 }, { 90.0, 0.0, 0.0 });
	_hierarchy.push_back(grass);

	

	// Portal Setup
	Portal* portal1 = new Portal("%Portal1", PortalMesh, nullptr, { 0.0, -3.0, 0.0 }, { 2.0, 2.0, 2.0 }, { 0.0, 0.0, 0.0 });
	portal1->SetCameraPosition(glm::vec3(0.0, 0.0, -4.0));
	_portals.push_back(portal1);

	Portal* portal2 = new Portal("%Portal2", PortalMesh, nullptr, { 45.0, -3.0, 0.0 }, { 2.0, 2.0, 2.0 }, { 0.0, 45.0, 0.0 });
	portal2->SetCameraPosition(glm::vec3(0.0, 2.0, 3.0));
	_portals .push_back(portal2);

	camera = new Camera();
	camera2 = new Camera();
	mainCamera = camera;

	

	SetupLights();
}

void Game::SetupFrameBuffer()
{
	// Generate Frame Buffer
	glGenFramebuffers(1, &_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	// Generate the Texture
	glGenTextures(1, &_textureColourBuffer);
	glBindTexture(GL_TEXTURE_2D, _textureColourBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREENWIDTH, SCREENHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureColourBuffer, 0);

	// Generate RBO
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREENWIDTH, SCREENHEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Game::Display()
{
	for (int i = 0; i < _portals.size(); i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _portals[i]->GetFrameBuffer());
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int j = 0; j < _hierarchy.size(); j++)
		{
			_hierarchy[j]->Draw(_portals[i]->GetCamera(), &_sceneLights);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glEnable(GL_DEPTH_TEST);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < _hierarchy.size(); i++)
	{
		_hierarchy[i]->Draw(mainCamera, &_sceneLights);
	}

	for (int i = 0; i < _portals.size(); i++)
	{
		_portals[i]->Draw(mainCamera, &_sceneLights);
	}

	glFlush(); // Flush to the graphics card
	glutSwapBuffers();
}

void Game::PortalCalculations(float deltaTime)
{
	glm::mat4 cameraView = mainCamera->GetModelMatrix(); // Get Camera Model
	glm::mat4 offsetmat = glm::inverse(_portals[0]->GetModelMatrix()) * cameraView; // Calculate offset from camera to portal
	glm::mat4 otheroffset = _portals[1]->GetModelMatrix() * offsetmat; // Apply offset to second portal
	glm::vec3 portalcam = glm::vec3(otheroffset[3][0], otheroffset[3][1], otheroffset[3][2]); // Grab vec3 position from matrix

	_portals[0]->GetCamera()->SetPosition(portalcam); // Set position of portal 1's camera to found location
	_portals[0]->GetCamera()->SetPitch(mainCamera->GetPitch()); // Set pitch to cameras
	_portals[0]->GetCamera()->SetYaw((mainCamera->GetYaw() - _portals[0]->GetRotation().y) + _portals[1]->GetRotation().y); // Calculate needed rotation based on portals rotations

	// Repeat for second portal
	offsetmat = glm::inverse(_portals[1]->GetModelMatrix()) * cameraView;
	otheroffset = _portals[0]->GetModelMatrix() * offsetmat;
	portalcam = glm::vec3(otheroffset[3][0], otheroffset[3][1], otheroffset[3][2]);
	_portals[1]->GetCamera()->SetPosition(portalcam);
	_portals[1]->GetCamera()->SetYaw((mainCamera->GetYaw() - _portals[1]->GetRotation().y) + _portals[0]->GetRotation().y);
	_portals[1]->GetCamera()->SetPitch((mainCamera->GetPitch()));

	for (int i = 0; i < _portals.size(); i++)
	{
		_portals[i]->Update(deltaTime);
	}
}

void Game::Update()
{
	int t = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (t - _oldT);
	deltaTime = deltaTime / 1000.0f;
	_oldT = t;

	mainCamera->Update(deltaTime);

	camera2->UpdateViewMatrix();
	mainCamera->UpdateViewMatrix();
	



	for (int i = 0; i < _hierarchy.size(); i++)
	{
		_hierarchy[i]->Update(deltaTime);
		if (_hierarchy[i]->GetName() == "Capsule")
		{
			_hierarchy[i]->SetPosition(glm::vec3(1.0f + sin(t * 0.001) * 2.0f, -2.0f, -7.0));
		}
	}

	PortalCalculations(deltaTime);

	glutPostRedisplay();
}

void Game::Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // ESC
		glutLeaveMainLoop();
	if (key == 'z')
		mainCamera = camera;
	if (key == 'x')
		mainCamera = camera2;
	mainCamera->CameraInput(key, x, y);
}

void Game::KeyboardUp(unsigned char key, int x, int y)
{
	mainCamera->CameraInputUp(key, x, y);
}

void Game::MouseMove(int x, int y)
{
	mainCamera->CameraMouse(x, y);
}

Game::~Game(void)
{

}