#include <iostream>
#include <GLFW/glfw3.h> 
extern GLFWwindow* window;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controls.hpp"


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

// position
glm::vec3 position = glm::vec3(0, 0, 5);
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 90.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.05f;
bool tabPressed = false;

void computeMatricesFromInputs()
{

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);


	double xpos = 0, ypos = 0;
	int windowHeight, windowWidth;
	//glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	std::cout << tabPressed << std::endl;
	if (!tabPressed)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		horizontalAngle += mouseSpeed * deltaTime * float(windowWidth / 2 - xpos);
		verticalAngle += mouseSpeed * deltaTime * float(windowHeight / 2 - ypos);
	}

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	//Tab Pressed
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		tabPressed = !tabPressed;
		glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float FoV = initialFoV;// -5 * glfwGetMouseWheel();
		
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
