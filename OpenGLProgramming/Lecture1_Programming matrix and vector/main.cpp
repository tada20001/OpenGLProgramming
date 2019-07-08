#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"

int main()
{
	Vector3D<float> v0, v1;

	v0.x_ = 1.0f;
	v0.y_ = 0.0f;
	v0.z_ = 0.0f;

	v1.x_ = 0.0f;
	v1.y_ = 1.0f;
	v1.z_ = 0.0f;

	for (int d = 0; d < 3; d++)
		std::cout << crossProduct(v0, v1).values_[d] << " ";
	std::cout << std::endl;

	return 0;
}