#version 330 core

out vec4 frag_color;

in vec3 res_normal;
in vec3 res_frag_pos;
in vec3 res_light_pos;

in vec2 tex_coords;

uniform vec3 object_color;
uniform vec3 light_color;

//uniform vec3 light_pos;
uniform vec3 view_pos;

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cut_off;
	float outer_cut_off;
};


struct Dir_Light
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Point_Light
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Spot_Light 
{
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cutt_off;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Dir_Light dir_light;
vec3 calc_dir_light(Dir_Light light, vec3 normal, vec3 view_dir);

#define NR_POINT_LIGHTS 4
uniform Point_Light point_lights[NR_POINT_LIGHTS];
vec3 calc_point_light(Point_Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);

uniform Spot_Light spot_light;
vec3 calc_spot_light(Spot_Light light, vec3 normal, vec3 frag_pos, vec3 view_dir);

uniform Material material;
uniform Light light;

void main()
{

	vec3 light_dir = normalize(light.position - res_frag_pos);


	//	Ambient lighting
	vec3 res_ambient = light.ambient * texture(material.diffuse, tex_coords).rgb; 

	//	Diffuse lighting
	vec3 norm = normalize(res_normal);

	float diff_angle = max(dot(norm, light_dir), 0.0f);
	vec3 res_diffuse = light.diffuse * diff_angle * texture(material.diffuse, tex_coords).rgb; 

	//	Specular lighting	
	vec3 view_dir = normalize(view_pos - res_frag_pos);
	vec3 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
	vec3 res_specular = light.specular * spec * texture(material.specular, tex_coords).rgb;

	float theta = dot(light_dir, normalize(-light.direction));
	float epsilon = light.cut_off - light.outer_cut_off;
	float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
	
	//res_ambient *= intensity;
	res_diffuse *= intensity;
	
	
	float res_distance = length(light.position - res_frag_pos);
	float attenuation = 1.0f / (light.constant + light.linear * res_distance + light.quadratic * pow(res_distance, 2));

	res_ambient *= attenuation;
	res_diffuse *= attenuation;
	res_specular *= attenuation;

	vec3 result_phong_shading = res_ambient + res_diffuse + res_specular;
	frag_color = vec4(result_phong_shading, 1.0);
}

vec3 calc_dir_light(Dir_Light light, vec3 normal, vec3 view_dir)
{
	vec3 light_dir = normalize(-light.direction);
	float diff_angle = max(dot(normal, light_dir), 0.0f);

	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse = light.diffuse * diff_angle * vec3(texture(material.diffuse, tex_coords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));

    return (ambient + diffuse + specular);
}

vec3 calc_point_light(Point_Light light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
	vec3 light_dir = normalize(light.position - frag_pos);
 
    float diff_angle = max(dot(normal, light_dir), 0.0);
 
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
 
    float res_distance = length(light.position - frag_pos);
	float attenuation = 1.0f / (light.constant + light.linear * res_distance + light.quadratic * pow(res_distance, 2));    
 
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse = light.diffuse * diff_angle * vec3(texture(material.diffuse, tex_coords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
};

vec3 calc_spot_light(Spot_Light light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
	vec3 light_dir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
	
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}