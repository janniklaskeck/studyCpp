#pragma once

#include <vector>
#include <stdint.h>
#include "Vector3D.h"


class Face {
public:
	int32_t vertex_indices[3];
};

class Model
{
public:
	std::vector<Vector3D> vertices;
	std::vector<Face> faces;

	Model(const char* filename);
};