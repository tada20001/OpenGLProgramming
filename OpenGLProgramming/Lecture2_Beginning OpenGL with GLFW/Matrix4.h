#pragma once
#include "Vector4D.h"

template<class T>
class Matrix4
{
public:
	T data[4][4];   // [row][column] notation

	void setIndentity()  // set the indentity matrix
	{
		for (int r=0; r < 4; ++r)
			for (int c = 0; c < 4; ++c)
			{
				data[r][c] = r == c ? (T)1 : (T)0;
			}
	}

	void setRow(const int& row, const T& v0, const T& v1, const T& v2, const T& v3)
	{
		data[row][0] = v0;
		data[row][1] = v1;
		data[row][2] = v2;
		data[row][3] = v3;
	}

	void multiply(const Vector4D<T>& vec, Vector4D<T>& out)
	{
		multiply(vec.data, out.data);
	}

	void multiply(const T vec[4], T out[4])
	{
		for (int r = 0; r < 4; ++r)
		{
			out[r] = (T)0;

			for (int c = 0; c < 4; ++c)
			{
				out[r] += data[r][c] * vec[c];
			}
		}
	}

	void multiply(const T a[4][4], const T b[4][4])
	{
		for (int r = 0; r < 4; r++)  // row number of output
			for (int c = 0; c < 4; c++)  // column number of output
			{
				data[r][c] = 0;
				for (int z = 0; z < 4; z++)   // four elements are added for the data
					data[r][c] += a[r][z] * b[z][c];
			}
	}

	friend std::stream& operator << (std::ostream& stream, const Matrix4<T>& matrix)
	{
		for(int r = 0; r < 4; r++)
			for (int c = 0; c < 4; c++)
			{
				ostream << matrix.data[r][c] << " ";
			}
		ostream << std::endl;

		return ostream;
	}
};