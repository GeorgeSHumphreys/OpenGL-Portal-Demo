#pragma once
#include <iostream>
#include <Windows.h>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Structs.h"

class Shader
{
public:
	Shader(std::string Name);
	void Use();
	GLuint GetProgID() { return progID; }
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec4(const std::string& name, glm::vec4 value) const;
	void setMatrix4(const std::string& name, glm::mat4 value) const;
private:
	GLuint progID;
};

