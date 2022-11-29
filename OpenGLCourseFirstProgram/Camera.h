#include <glm/glm.hpp>
#include <GL/glew.h>
#pragma once

struct ProjectionArgs {
	float pointOfView;
	float aspectRatio;
	float nearPlaneDistance;
	float farPlaneDistance;

	ProjectionArgs(float pov,float ar,float npd,float fpd):
		pointOfView(pov),aspectRatio(ar),nearPlaneDistance(npd),farPlaneDistance(fpd){}
};

class Camera
{
public:
	Camera();
	~Camera();

	void Update();
	void SetProjection(GLuint &shader_ID,ProjectionArgs projArgs);
	glm::mat4 GetProjection() { return projection; }

private:
	glm::mat4 projection;
	GLuint uniformProjectionLocation;
};

