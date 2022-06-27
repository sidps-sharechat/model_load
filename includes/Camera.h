#ifndef CAMERA_H
#define CAMERA_H

// Header declarations
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <iostream>

// Camera movement directions
enum CAMERA_MOVE_DIR
{
	FORWARD_DIR,
	BACKWARD_DIR,
	LEFT_DIR,
	RIGHT_DIR,
	UP_DIR,
	DOWN_DIR
};

// Camera Class
class Camera
{
public:
	// DATA SETUP

	// VECTOR DATA
	glm::vec3 position; // World POS of camera
	glm::vec3 front;	// Forward Direction from camera
	glm::vec3 right;	// Right from Camera
	glm::vec3 up;		// Up from Camera
	glm::vec3 worldUp;	// Direction of world Up

	// ANGLE DATA
	float yaw;	 // angle from top
	float pitch; // angle from side

	// MOTION DATA
	float moveSpeed;		// Movement speed of the Camera
	float mouseSensitivity; // Mouse sensitivity of the Camera
	float fovZoom;			// Field of View of the Camera

	// Vector constructor
	Camera(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw_ = -90.0f, float pitch_ = 0.0f);
	// Returns view matrix
	glm::mat4 get_view_matrix();
	// Processes camera movement from keyboard
	void process_keyboard(CAMERA_MOVE_DIR direction, float deltaTime);
	// Process Camera rotation from mouse
	void process_mouse(float xoffset, float yoffset, float deltaTime, GLboolean constrainPitch = true);
	// Processes Camera Zoom from scroll wheel
	void process_scroll(float yoffset);
	// Updates front, right and up vectors from angles
	void update_camera_vectors();

private:
};

#endif // !CAMERA_H
