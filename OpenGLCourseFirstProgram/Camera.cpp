#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera()
{
	projection = glm::mat4(1.0f);
	uniformProjectionLocation = 0;
}

Camera::~Camera()
{
	std::cout << "+++++++++++Destroyin Camera++++++++" << std::endl;
}

void Camera::Update()
{
	glUniformMatrix4fv(uniformProjectionLocation,1,GL_FALSE,glm::value_ptr(projection));
}

void Camera::SetProjection(GLuint &shader_ID,ProjectionArgs projArgs)
{
	projection = glm::perspective(
		projArgs.pointOfView,
		projArgs.aspectRatio,
		projArgs.nearPlaneDistance,
		projArgs.farPlaneDistance
	);

	uniformProjectionLocation = glGetUniformLocation(shader_ID, "projection");
}
