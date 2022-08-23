#include "Shader.hpp"

void Shader::check_compile_errors(unsigned int program_id, std::string type)
{
	int succes;
	char info_log[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(program_id, GL_COMPILE_STATUS, &succes);

		if (!succes)
		{
			glGetShaderInfoLog(program_id, 512, nullptr, info_log);
			std::cerr << "ERROR::SHADER::COMPILATION_FAILD of type: " << type << ": " << info_log << std::endl;
		}
	}
	else
	{
		glGetProgramiv(program_id, GL_LINK_STATUS, &succes);

		if (!succes)
		{
			glGetProgramInfoLog(program_id, 512, nullptr, info_log);
			std::cerr << "ERROR::SHADER::LINKING_FAILD of type: "<< type << ": " << info_log << std::endl;
		}
	}
}

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;

    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        v_shader_file.open(vertex_path);
        f_shader_file.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << v_shader_file.rdbuf();
        fShaderStream << f_shader_file.rdbuf();

        v_shader_file.close();
        f_shader_file.close();

        vertex_code = vShaderStream.str();
        fragment_code = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();

	unsigned int vertex_shader_id;
	unsigned int fragment_shader_id;

	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader_id, 1, &v_shader_code, nullptr);
	glCompileShader(vertex_shader_id);

	check_compile_errors(vertex_shader_id, "VERTEX");

	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment_shader_id, 1, &f_shader_code, nullptr);
	glCompileShader(fragment_shader_id);

	check_compile_errors(fragment_shader_id, "FRAGMENT");

	this->program_id = glCreateProgram();

	glAttachShader(this->program_id, vertex_shader_id);
	glAttachShader(this->program_id, fragment_shader_id);

	glLinkProgram(this->program_id);

	check_compile_errors(this->program_id, "PROGRAM");

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

unsigned int Shader::get_id() const
{
    return this->program_id;
}

void Shader::set_id(unsigned int program_id)
{
    this->program_id = program_id;
}

void Shader::use()
{
	glUseProgram(program_id);
}

void Shader::set_primitive_type(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), static_cast<int>(value));
}

void Shader::set_primitive_type(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void Shader::set_primitive_type(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void Shader::set_matrix(const std::string& name, glm::mat4& m) const
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::set_vector(const std::string& name, glm::vec3 v) const
{
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), v[0], v[1], v[2]);
}

void Shader::set_vector(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), x, y, z);
}
