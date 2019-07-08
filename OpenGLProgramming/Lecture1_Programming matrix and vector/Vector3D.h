#pragma once

template <class TT>
class Vector3D
{
public:
	union
	{
		struct { TT x_, y_, z_; };
		struct { TT v0_, v1_, v2_; };
		TT values_[3];
	};
	

	Vector3D()
		: x_(0.0f), y_(0.0f), z_(0.0f)
	{}

	Vector3D(const TT& x_input, const TT& y_input, const TT& z_input)
	{
		x_ = x_input;
		y_ = y_input;
		z_ = z_input;
	}

	//Vector3D<TT> crossProduct(const Vector3D<TT>& v0, const Vector3D<TT>& v1)  // outer product
	//{
	//	return Vector3D<TT>((TT)(v0.y_ * v1.z_ - v0.z_ * v1.y_),
	//						(TT)(v0.z_ * v1.x_ - v0.x_ * v1.z_),
	//						(TT)(v0.x_ * v1.y_ - v0.y_ * v1.x_));
	//}
};

template<class TT> Vector3D<TT> crossProduct(const Vector3D<TT>& v0, const Vector3D<TT>& v1)
{
	return Vector3D<TT>((TT)(v0.y_ * v1.z_ - v0.z_ * v1.y_),
						(TT)(v0.z_ * v1.x_ - v0.x_ * v1.z_),
						(TT)(v0.x_ * v1.y_ - v0.y_ * v1.x_));
}