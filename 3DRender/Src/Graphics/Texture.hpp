#pragma once

class Texture
{
private:
	unsigned int id_texture[2];
	int width, height, count_channels;
	unsigned char* data;

public:
	Texture(const char* texture_path, bool set_flip_vertically);
	Texture(const char* texture_path, const char* second_texture_path, bool set_flip_vertically);

	unsigned int get_id_texture(int idx) const;
};

