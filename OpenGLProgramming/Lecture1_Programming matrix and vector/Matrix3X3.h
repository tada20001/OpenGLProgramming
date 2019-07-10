#pragma once
#include "Vector3D.h"
#include <iostream>

class Matrix3X3
{
public:
	// recommanded for fixed size of matrix
	float value_[3][3];

	// recommand for M by N matrix(arbitray sized matrix)
	//float* values_ = new float[3 * 3];  

	void print()
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				std::cout << value_[row][col] << " ";
			}

			std::cout << std::endl;
		}
	}
	
	Vector3D<float> multiply(const Vector3D<float>& v)
	{
		return Vector3D<float>(value_[0][0] * v.v0_ + value_[0][1] * v.v1_ + value_[0][2] * v.v2_,
								value_[1][0] * v.v0_ + value_[1][1] * v.v1_ + value_[1][2] * v.v2_,
								value_[2][0] * v.v0_ + value_[2][1] * v.v1_ + value_[2][2] * v.v2_);
	}
};

// 3X3 multiply 3 X1 (vector) = 3X1 matrix(vector)
//MatrixMN multiply(const MatrixMN& m1, const MatirxMN&m2
//{}

Vector3D<float> multiply(const Matrix3X3& m, const Vector3D<float>& v)
{
	return Vector3D<float>(m.value_[0][0] * v.x_ + m.value_[0][1] * v.y_ + m.value_[0][2] * v.z_,
							m.value_[1][0] * v.x_ + m.value_[1][1] * v.y_ + m.value_[1][2] * v.z_,
							m.value_[2][0] * v.x_ + m.value_[2][1] * v.y_ + m.value_[2][2] * v.z_);
}

