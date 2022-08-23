#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 in_tex_coords;
//layout (location = 1) in vec3 a_color;
//layout (location = 1) in vec2 a_texture;

out vec3 res_color;
out vec3 res_normal;
//out vec2 res_texture_coords;
out vec3 res_light_pos;
out vec3 res_frag_pos;

out vec2 tex_coords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_pos;

void main()
{
	//res_texture_coords = a_texture;
	
	res_frag_pos = vec3(model * vec4(a_pos, 1.0f));
	res_normal = mat3(transpose(inverse(model))) * a_normal;
	//res_light_pos = vec3(view * vec4(light_pos, 1.0f));
	tex_coords = in_tex_coords;
	
	gl_Position = projection * view * model * vec4(a_pos, 1.0f);
}