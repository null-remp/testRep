#include <iostream>

#define GLEW_STATIC
#include <glew/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Camera.hpp"

#include "Loader/stb_image.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

void updatePolygonMode();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
void process_input(GLFWwindow* window);
unsigned int load_texture(const char* path);

glm::vec3 light_pos(2.0f, -1.0f, 0.0f);

bool mouse;

bool mode = true;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

float coordinates[] = {
	 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3  
};

glm::vec3 cube_positions[] = {	
	glm::vec3(13.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-5.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -2.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(7.5f,  2.0f, -2.5f),
	glm::vec3(-3.5f,  1.2f, -1.5f),
	glm::vec3(1.9f,  4.0f, -1.5f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(3.0f, -2.0f, 0.0f)
};

float transparency = 0.5f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float last_x = WINDOW_WIDTH / 2.0f;
float last_y = WINDOW_HEIGHT / 2.0f;

float delta_time = 0.0f;
float last_frame = 0.0f;

int main()
{
#pragma region MAIN_INITIALIZATION
	if (!glfwInit())
	{
		std::cerr << "GLFW didn't initialize success." << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW." << std::endl;
		glfwTerminate();
		return -1;
	}
#pragma endregion This is initialization of the window and and other libraries.

	Shader* shader = new Shader("Res/Mainv.glsl", "Res/Mainf.glsl");
	Shader* lamp_shader = new Shader("Res/Lampv.glsl", "Res/Lampf.glsl");

#pragma region BUFFERS_INITIALIZATION 
	unsigned int VBO, cube_VAO;

	glGenVertexArrays(1, &cube_VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(cube_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Coords
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);

	unsigned int light_VAO;
	glGenVertexArrays(1, &light_VAO);
	glBindVertexArray(light_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

#pragma endregion There are buffers initialization.

#pragma region TEXTURE_INITIALIZATION
	
	//Texture* diffuse_map = new Texture("Res/Imgs/wooden_container_2.png", true);
	unsigned int diffuse_map = load_texture("Res/Imgs/wooden_container_2.png");
	unsigned int specular_map = load_texture("Res/Imgs/container_2_specular.png");
	unsigned int emission_map = load_texture("Res/Imgs/em_map.jpg");

	shader->use();

	shader->set_vector("object_color", 1.0f, 0.5f, 0.31f);
	shader->set_vector("light_color", 1.0f, 0.31f, 0.3f);

	shader->set_primitive_type("material.diffuse", 0);
	shader->set_primitive_type("material.specular", 1);
	shader->set_primitive_type("material.emission", 2);


#pragma endregion Initialize the texture

	glEnable(GL_DEPTH_TEST);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);

	shader->use();
	shader->set_vector("material.specular", 0.0f, 0.0f, 0.0f);
	shader->set_primitive_type("material.shininess", 128.0f);
	
	shader->set_vector("light.position", light_pos);
	shader->set_vector("light.ambient", 0.2f, 0.2f, 0.2f);
	shader->set_vector("light.diffuse", 1.0f, 1.0f, 1.0f);
	shader->set_vector("light.specular", 1.0f, 1.0f, 1.0f);

	shader->set_primitive_type("light.constant", 1.0f);
	shader->set_primitive_type("light.linear", 0.09f);
	shader->set_primitive_type("light.quadratic", 0.032f);

	//std::cout << glm::cos(glm::radians(360.0f)) << std::endl;

	//shader->set_vector("light.direction", -0.2f, -4.0f, -0.3f);

	while (!glfwWindowShouldClose(window))
	{
		updatePolygonMode();
		float current_time = glfwGetTime();

		delta_time = current_time - last_frame;
		last_frame = current_time;

		process_input(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse_map);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular_map);

		/*glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emission_map);*/

		/*light_color.x = sin(glfwGetTime() * 2.0f);
		light_color.y = sin(glfwGetTime() * 0.7f);
		light_color.z = sin(glfwGetTime() * 1.3f);

		diffuse_color = light_color * glm::vec3(0.5f);
		ambient_color = diffuse_color * glm::vec3(0.2f);*/

		//light_pos.x = sin(glfwGetTime()) * 2.0f;
		//light_pos.z = cos(glfwGetTime()) * 2.0f; 

		shader->use();
		shader->set_vector("light_pos", light_pos);

		shader->set_vector("light.position", camera.position);
		shader->set_vector("light.direction", camera.front);
		shader->set_primitive_type("light.cut_off", glm::cos(glm::radians(12.5f)));
		shader->set_primitive_type("light.outer_cut_off", glm::cos(glm::radians(17.5f)));



		/*shader->set_vector("light.ambient", ambient_color);
		shader->set_vector("light.diffuse", diffuse_color);*/

		projection = glm::perspective(glm::radians(camera.zoom), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 100.0f);
		view = camera.get_view_matrix();


		shader->set_matrix("view", view);
		shader->set_matrix("projection", projection);
		shader->set_primitive_type("transparency", transparency);
		
		

		for (size_t i = 0; i < 12; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cube_positions[i]);
			
			if (!(i % 3))
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
			
			shader->set_matrix("model", model);
			glBindVertexArray(cube_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(1.5f));

		shader->set_matrix("model", model);
		shader->set_vector("view_pos", camera.position);
		
		glBindVertexArray(cube_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lamp_shader->use();
		lamp_shader->set_matrix("projection", projection);
		lamp_shader->set_matrix("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, light_pos);
		model = glm::scale(model, glm::vec3(0.2f));
		lamp_shader->set_matrix("model", model);

		glBindVertexArray(light_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &light_VAO);
	glDeleteVertexArrays(1, &cube_VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;
	delete lamp_shader;

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	if (mouse)
	{
		last_x = x_pos;
		last_y = y_pos;

		mouse = false;
	}
	
	float x_offset = x_pos - last_x;
	float y_offset = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;

	camera.process_mouse_movement(x_offset, y_offset);
}

void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	camera.process_mouse_scroll(y_offset);
}

void updatePolygonMode()
{
	if (mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (!mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		mode = !mode;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.process_keyboard(Camera_Movment::FORWARD, delta_time);
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.process_keyboard(Camera_Movment::BACKWARD, delta_time);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.process_keyboard(Camera_Movment::LEFT, delta_time);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.process_keyboard(Camera_Movment::RIGHT, delta_time);	
}

unsigned int load_texture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}