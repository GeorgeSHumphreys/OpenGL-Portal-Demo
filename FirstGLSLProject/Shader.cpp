#include "Shader.h"


Shader::Shader(std::string Name)
{
	std::string type[] = { ".frag", ".vert" };
	GLuint vs;
	GLuint fs;
	for (int i = 0; i < 2; i++)
	{
		std::string path = "Shaders/" + Name + type[i];
		std::ifstream file(path);
		std::string buffer((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		GLuint s;

		if(i == 0)
			s = glCreateShader(GL_FRAGMENT_SHADER);
		else
			s = glCreateShader(GL_VERTEX_SHADER);

		const char* src = buffer.c_str();
		glShaderSource(s, 1, &src, nullptr);
		glCompileShader(s);


		GLint isCompiled = 0;
		glGetShaderiv(s, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(s, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(s, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			for (int i = 0; i < errorLog.size(); i++)
			{
				std::cout << errorLog[i];
			}
			return;
		}
		if (i == 0)
			fs = s;
		else
			vs = s;
	}


	progID = glCreateProgram();
	glAttachShader(progID, vs);
	glAttachShader(progID, fs);

	glLinkProgram(progID);

	int success;
	char infoLog[512];
	glGetProgramiv(progID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(progID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::Use()
{
	// Apply Shader to the bind
	glUseProgram(progID);
}

// These work by finding the Number location for that specific uniform, then changing the value. Needs to be done each frame its changed.
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(progID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(progID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(progID, name.c_str()), value);
}
void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(progID, name.c_str()), value.x, value.y, value.z);
}
void Shader::setVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(progID, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(progID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}