// We need this macro to get constants like M_PI from cmath
#define _USE_MATH_DEFINES
#include <cmath>
#include "Matrix4.h"


Matrix4::Matrix4()
{
	for (size_t i = 0; i < 16; i++)
		data[i] = 0;

	data[0] = 1;
	data[5] = 1;
	data[10] = 1;
	data[15] = 1;
}

Matrix4::Matrix4(const float data[16])
{
	for (size_t i = 0; i < 16; i++)
		this->data[i] = data[i];
}

const Matrix4 Matrix4::operator*(const Matrix4 rhs)
{
	float data[16];
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			int colMajor = 4 * x + y;
			int rowMajor = 4 * y + x;
			data[colMajor] = this->data[colMajor] * rhs.data[rowMajor];
		}
	}
	return Matrix4(data);
}


const Vector3D Matrix4::transformPosition(const Vector3D& v) const
{
	Vector3D result;
	float w;

	result.x = data[0] * v.x + data[4] * v.y + data[8] * v.z + data[12];
	result.y = data[1] * v.x + data[5] * v.y + data[9] * v.z + data[13];
	result.z = data[2] * v.x + data[6] * v.y + data[10] * v.z + data[14];
	w = data[3] * v.x + data[7] * v.y + data[11] * v.z + data[15];

	if (w != 0.0f && w != 1.0f)
		result /= w;

	return result;
}

const Vector3D Matrix4::transformDirection(const Vector3D& v) const
{
	Vector3D result;
	float w;

	result.x = data[0] * v.x + data[4] * v.y + data[8] * v.z;
	result.y = data[1] * v.x + data[5] * v.y + data[9] * v.z;
	result.z = data[2] * v.x + data[6] * v.y + data[10] * v.z;
	w = data[3] * v.x + data[7] * v.y + data[11] * v.z;

	return result;
}

const Matrix4 Matrix4::transpose() const
{
	Matrix4 result;

	result.data[0] = data[0];
	result.data[1] = data[4];
	result.data[2] = data[8];
	result.data[3] = data[12];
	result.data[4] = data[1];
	result.data[5] = data[5];
	result.data[6] = data[9];
	result.data[7] = data[13];
	result.data[8] = data[2];
	result.data[9] = data[6];
	result.data[10] = data[10];
	result.data[11] = data[14];
	result.data[12] = data[3];
	result.data[13] = data[7];
	result.data[14] = data[11];
	result.data[15] = data[15];

	return result;
}

const Matrix4 Matrix4::projection(float viewAngle, float aspectRatio, float near, float far)
{
	Matrix4 result;

	viewAngle = viewAngle / 180 * (float)M_PI;

	// x axis
	result.data[0] = 1 / tan(viewAngle / 2) * aspectRatio;
	result.data[1] = 0;
	result.data[2] = 0;
	result.data[3] = 0;

	// y axis
	result.data[5] = 1 / tan(viewAngle / 2);
	result.data[4] = 0;
	result.data[6] = 0;
	result.data[7] = 0;

	// z axis
	result.data[10] = (far + near) / (near - far);
	result.data[11] = -1;
	result.data[8] = 0;
	result.data[9] = 0;

	// w axis
	result.data[14] = (2 * far * near) / (near - far);
	result.data[12] = 0;
	result.data[13] = 0;
	result.data[15] = 0;

	return result;
}

const Matrix4 Matrix4::orthogonal(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4 result;

	// x axis
	result.data[0] = 2 / (right - left);
	result.data[1] = 0;
	result.data[2] = 0;
	result.data[3] = 0;

	// y axis
	result.data[4] = 0;
	result.data[5] = 2 / (top - bottom);
	result.data[6] = 0;
	result.data[7] = 0;

	// z axis
	result.data[8] = 0;
	result.data[9] = 0;
	result.data[10] = -2 / (far - near);
	result.data[11] = 0;

	// w axis
	result.data[12] = -(right + left) / (right - left);
	result.data[13] = -(top + bottom) / (top - bottom);
	result.data[14] = -(far + near) / (far - near);
	result.data[15] = 1;

	return result;
}


const Matrix4 Matrix4::lookAt(const Vector3D& eye, const Vector3D& point_of_interest, const Vector3D& up)
{
	Vector3D x, y, z;
	Matrix4 result;

	z = Vector3D(point_of_interest.x - eye.x, point_of_interest.y - eye.y, point_of_interest.z - eye.z).normalized();
	x = z.cross(up.normalized()).normalized();
	y = x.cross(z);
	z = z * -1;

	// x axis
	result.data[0] = x.x;
	result.data[4] = x.y;
	result.data[8] = x.z;
	result.data[12] = -x.dot(eye);

	// y axis
	result.data[1] = y.x;
	result.data[5] = y.y;
	result.data[9] = y.z;
	result.data[13] = -y.dot(eye);

	// z axis
	result.data[2] = z.x;
	result.data[6] = z.y;
	result.data[10] = z.z;
	result.data[14] = -z.dot(eye);

	// w axis
	result.data[3] = 0;
	result.data[7] = 0;
	result.data[11] = 0;
	result.data[15] = 1;

	return result;
}


const Matrix4 Matrix4::lookDir(const Vector3D& dir, const Vector3D& up)
{
	Matrix4 result;
	Vector3D x, y, z;

	z = dir.normalized();
	x = z.cross(up.normalized()).normalized();
	y = x.cross(z);
	z = z * -1;

	// x axis
	result.data[0] = x.x;
	result.data[4] = x.y;
	result.data[8] = x.z;
	result.data[12] = 0;

	// y axis
	result.data[1] = y.x;
	result.data[5] = y.y;
	result.data[9] = y.z;
	result.data[13] = 0;

	// z axis
	result.data[2] = z.x;
	result.data[6] = z.y;
	result.data[10] = z.z;
	result.data[14] = 0;

	// w axis
	result.data[3] = 0;
	result.data[7] = 0;
	result.data[11] = 0;
	result.data[15] = 1;

	return result;
}


// TODO:
// create rotation and translation matrices