#pragma once
#include <iostream>

class Vector2D
{
public:
	float x_, y_;

	Vector2D()
		: x_(0.0f), y_(0.0f)
	{}

	void assign(const float& x_input, const float& y_input)
	{
		x_ = x_input;
		y_ = y_input;
	}

	void print()
	{
		std::cout << x_ << " " << y_ << std::endl;
	}

	Vector2D& operator +=(const Vector2D& rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;

		return *this;
	}

	float dotProduct(const Vector2D& rhs)
	{
		return x_ * rhs.x_ + y_ * rhs.y_;
	}
};