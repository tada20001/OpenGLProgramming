#pragma once

class Vector3D
{
public:
	union
	{
		struct { float x_, y_, z_; };
		struct { float r_, g_, b_; };
		float data[3];
	};

	Vector3D(const float & x_input, const float& y_input, const float& z_input)
		: x_(x_input), y_(y_input), z_(z_input)
	{}

};