#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

struct Vertex
{
	glm::vec2 Pos;
	glm::vec3 Color;

	static VkVertexInputBindingDescription GetBindingDescription()
	{
		VkVertexInputBindingDescription BindingDescription = {};
		BindingDescription.binding = 0;
		BindingDescription.stride = sizeof(Vertex);
		BindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return BindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescription()
	{
		std::array<VkVertexInputAttributeDescription, 2> AttributeDescription = {};
		AttributeDescription[0].binding = 0;
		AttributeDescription[0].location = 0;
		AttributeDescription[0].format = VK_FORMAT_R32G32_SFLOAT;
		AttributeDescription[0].offset = offsetof(Vertex, Pos);

		AttributeDescription[1].binding = 0;
		AttributeDescription[1].location = 1;
		AttributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		AttributeDescription[1].offset = offsetof(Vertex, Color);

		return AttributeDescription;
	}
};