#pragma once

#define GLEW_STATIC
#include <glew/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	unsigned int program_id;

	void check_compile_errors(unsigned int shader, std::string type);

public:
	Shader(const char* vertex_path, const char* fragment_path);

	unsigned int get_id() const;
	void set_id(unsigned int id);

	void use();

	void set_primitive_type(const std::string &name, bool value) const;
	void set_primitive_type(const std::string& name, int value) const;
	void set_primitive_type(const std::string& name, float value) const;

	void set_matrix(const std::string& name, glm::mat4& m) const;

	void set_vector(const std::string& name, glm::vec3 v) const;
	void set_vector(const std::string& name, float x, float y, float z) const;
};

