#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix3X3.h"

int main()
{
	// extend Vector2D to Vector 3D
	// implement crossproduct between two vector
	/*{
		Vector3D<float> v0(1, 0, 0), v1(0, 1, 0);

		for (int d = 0; d < 3; d++)
			std::cout << crossProduct(v0, v1).values_[d] << " ";
		std::cout << std::endl;
	}*/
	
	// add Matrix 3 by 3
	{
		Matrix3X3 m;

		float input_value = 0.0f;

		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				m.value_[row][col] = input_value;
				++input_value;
			}
		}

		m.print();

	}

	return 0;
}