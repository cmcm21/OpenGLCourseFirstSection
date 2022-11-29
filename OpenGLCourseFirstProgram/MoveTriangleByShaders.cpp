#include "MoveTriangleByShaders.h"
#include <cmath>

void MoveTriangleByShaders::Update()
{
	if (direction)
		triangleOffset += triangleIncrement;
	else
		triangleOffset -= triangleIncrement;

	if (abs(triangleOffset) >= triangleOffsetMax)
		direction = !direction;

	glUniform1f(uniformVarLocation, triangleOffset);
}
