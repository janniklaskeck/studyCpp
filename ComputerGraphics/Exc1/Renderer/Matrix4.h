#pragma once

#include "Vector3D.h"

/**
 * A 4x4 matirx. Data is strored in column-major layout:
 *   [ 0] [ 4] [ 8] [12]
 *   [ 1] [ 5] [ 9] [13]
 *   [ 2] [ 6] [10] [14]
 *   [ 3] [ 7] [11] [15]
 */
class Matrix4
{
public:
	// Initialize with unit matrix
	Matrix4();
	// Initialize matrix with a copy of the data
	Matrix4(const float data[16]);

	const Matrix4 operator*(const Matrix4 rhs);


	// TODO:
    // create rotation and translation matrices


	// Transform methods
	const Vector3D transformPosition(const Vector3D& v) const;
	const Vector3D transformDirection(const Vector3D& v) const;

	// Returns a transposed version of the matrix
	const Matrix4 transpose() const;

	static const Matrix4 projection(float viewAngle, float aspectRatio, float near, float far);
	static const Matrix4 orthogonal(float left, float right, float bottom, float top, float near, float far);
	static const Matrix4 lookAt(const Vector3D& eye, const Vector3D& point_of_interest, const Vector3D& up);
	static const Matrix4 lookDir(const Vector3D& dir, const Vector3D& up);

	float data[16];
};