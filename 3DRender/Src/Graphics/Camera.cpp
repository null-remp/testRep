#include "Camera.hpp"

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::process_mouse_movement(float x_offset, float y_offset, bool constrain_pitch)
{
	x_offset *= mouse_sensitivity;
	y_offset *= mouse_sensitivity;

	yaw += x_offset;
	pitch += y_offset;

	if (constrain_pitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;

		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	update_vectors();
}

void Camera::process_mouse_scroll(float y_offset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= y_offset;

	if (zoom <= 1.0f)
		zoom = 1.0f;

	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::process_keyboard(Camera_Movment dir, float delta_time)
{
	float velocity = movement_speed * delta_time;

	if (dir == Camera_Movment::FORWARD)
		position += front * velocity;

	else if (dir == Camera_Movment::BACKWARD)
		position -= front * velocity;

	else if (dir == Camera_Movment::LEFT)
		position -= right * velocity;

	else if (dir == Camera_Movment::RIGHT)
		position += right * velocity;

	//position.y = 0.0f;
}

glm::mat4 Camera::create_own_lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 world_up)
{
	glm::vec3 z_axis = glm::normalize(pos - target);
	glm::vec3 x_axis = glm::normalize(glm::cross(glm::normalize(world_up), z_axis));
	glm::vec3 y_axis = glm::cross(z_axis, x_axis);

	glm::mat4 translation = glm::mat4(1.0f);

	translation[3][0] = -pos.x;
	translation[3][1] = -pos.y;
	translation[3][2] = -pos.z;

	glm::mat4 rotation = glm::mat4(1.0f);

	rotation[0][0] = x_axis.x;
	rotation[1][0] = x_axis.y;
	rotation[2][0] = x_axis.z;
	rotation[0][1] = y_axis.x;
	rotation[1][1] = y_axis.y;
	rotation[2][1] = y_axis.z;
	rotation[0][2] = z_axis.x; 
	rotation[1][2] = z_axis.y;
	rotation[2][2] = z_axis.z;


	return rotation * translation;
}

void Camera::update_vectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}
