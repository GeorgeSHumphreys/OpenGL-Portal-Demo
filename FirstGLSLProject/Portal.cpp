#include "Portal.h"

Portal::Portal(std::string name, Mesh* mesh, Material* mat, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : SceneObject(name, mesh, mat, position, scale, rotation)
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


	_material = (Material*)(new FrameBufferMaterial("Portal", _textureColourBuffer));

	_camera = new Camera();
}

void Portal::Update(float deltaTime)
{
	_camera->Update(deltaTime);
	_camera->UpdateViewMatrix();
}