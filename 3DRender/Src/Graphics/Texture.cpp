#include "Texture.hpp"

#define GLEW_STATIC
#include <glew/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../Loader/stb_image.h"

#include <iostream>

Texture::Texture(const char* texture_path, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);

	glGenTextures(1, &id_texture[0]);
	glBindTexture(GL_TEXTURE_2D, id_texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->data = stbi_load(texture_path, &width, &height, &count_channels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cerr << "Faild to load texture." << std::endl;

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Texture::Texture(const char* texture_path, const char* second_texture_path, bool flip) : Texture(texture_path, flip)
{
	glGenTextures(1, &id_texture[1]);
	glBindTexture(GL_TEXTURE_2D, id_texture[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(second_texture_path, &width, &height, &count_channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cerr << "Faild to load texture." << std::endl;

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

unsigned int Texture::get_id_texture(int idx) const
{
	return id_texture[idx];
}
