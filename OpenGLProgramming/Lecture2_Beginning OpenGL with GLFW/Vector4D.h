#pragma once
#include <iostream>

template<class T>
class Vector4D
{
public:
	union 
	{
		struct { T x_, y_, z_, w_; };
		T data[4];
	};

public:
	Vector4D()
		:x_(T()), y_(T()), z_(T()), w_(T()){}

	Vector4D(const T& _x, const T& _y, const T& _z, const T& _w)
		: x_(_x), y_(_y), z_(_z), w_(_w)
	{}

	void set(const T& v0, const T& v1, const T& v2, const T& v3)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
		data[3] = v3;
	}

	void operator *= (const T s)
	{
		x_ *= s;
		y_ *= s;
		z_ *= s;
		w_ *= s;
	}

	friend std::ostream& operator << (std::ostream& stream, const Vector4D<T>& vector)
	{
		stream << vector.x_ << " " << vector.y_ << " " << vector.z_ << " " << vector.w_;

		return stream;
	}
};