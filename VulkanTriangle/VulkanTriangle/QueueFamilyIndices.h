#pragma once

struct QueueFamilyIndices
{
	int GraphicsFamily = -1;
	int PresetFamily = -1;

	bool IsComplete()
	{
		return GraphicsFamily >= 0 && PresetFamily >= 0;
	}
};