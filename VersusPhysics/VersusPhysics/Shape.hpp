#pragma once
#include "Vector2.hpp"

enum ShapeType
{
	NONE,
	AABB,
	CIRCLE
};

struct Shape
{
	Shape()
	{
	}
	Shape(const Shape& Other)
	{
		if (this != &Other)
		{
			this->Type = Other.Type;
			this->Radius = Other.Radius;
			this->Size = Other.Size;
		}
	}
	~Shape()
	{
	}

	ShapeType Type;
	union
	{
		float Radius;
		Vector2 Size;
	};

	Shape& operator=(const Shape& Other)
	{
		if (this != &Other)
		{
			this->Type = Other.Type;
			this->Radius = Other.Radius;
			this->Size = Other.Size;
		}
		return *this;
	}
};
