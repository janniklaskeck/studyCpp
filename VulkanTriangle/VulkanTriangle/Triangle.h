#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <fstream>

#include "VkDeleter.h"
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "Vertex.h"
#include "UniformBufferObject.h"

class Triangle
{
public:

	const uint32_t WINDOW_WIDTH = 1280;
	const uint32_t WINDOW_HEIGHT = 720;

	const std::vector<const char*> ValidationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> DeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool EnableValidationLayers = false;
#else
	const bool EnableValidationLayers = true;
#endif

	void Run();

private:

	GLFWwindow* Window;

	VkDeleter<VkInstance> Instance{ vkDestroyInstance };
	VkDeleter<VkDebugReportCallbackEXT> Callback{ Instance, DestroyDebugReportCallbackEXT };
	VkDeleter<VkDevice> device{ vkDestroyDevice };
	VkDeleter<VkSurfaceKHR> Surface{ Instance, vkDestroySurfaceKHR };
	VkDeleter<VkSwapchainKHR> swapChain{ device, vkDestroySwapchainKHR };
	VkDeleter<VkRenderPass> RenderPass{ device, vkDestroyRenderPass };
	VkDeleter<VkDescriptorSetLayout> DescriptorSetLayout{ device, vkDestroyDescriptorSetLayout };
	VkDeleter<VkPipelineLayout> PipelineLayout{ device, vkDestroyPipelineLayout };
	VkDeleter<VkPipeline> GraphicsPipeline{ device, vkDestroyPipeline };
	VkDeleter<VkCommandPool> CommandPool{ device, vkDestroyCommandPool };
	VkDeleter<VkSemaphore> imageAvailableSemaphore{ device, vkDestroySemaphore };
	VkDeleter<VkSemaphore> RenderFinishedSemaphore{ device, vkDestroySemaphore };
	VkDeleter<VkBuffer> VertexBuffer{ device, vkDestroyBuffer };
	VkDeleter<VkDeviceMemory> VertexBufferMemory{ device, vkFreeMemory };
	VkDeleter<VkBuffer> IndexBuffer{ device, vkDestroyBuffer };
	VkDeleter<VkDeviceMemory> IndexBufferMemory{ device, vkFreeMemory };

	VkDeleter<VkBuffer> uniformStagingBuffer{ device, vkDestroyBuffer };
	VkDeleter<VkDeviceMemory> uniformStagingBufferMemory{ device, vkFreeMemory };
	VkDeleter<VkBuffer> uniformBuffer{ device, vkDestroyBuffer };
	VkDeleter<VkDeviceMemory> UniformBufferMemory{ device, vkFreeMemory };

	VkDeleter<VkDescriptorPool> DescriptorPool{ device, vkDestroyDescriptorPool };
	VkDescriptorSet DescriptorSet;

	std::vector<VkDeleter<VkFramebuffer>> SwapChainFramebuffers;

	std::vector<VkCommandBuffer> CommandBuffers;

	std::vector<VkImage> SwapChainImages;
	VkFormat SwapChainImageFormat;
	VkExtent2D SwapChainExtent;

	std::vector<VkDeleter<VkImageView>> SwapChainImageViews;

	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	const std::vector<Vertex> vertices = {
		{ { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f } },
		{ { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f } },
		{ { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f } },
		{ { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f } }
	};

	const std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0
	};

	void MainLoop();
	void DrawFrame();

	void UpdateUniformBuffer();

	void InitWindow();
	void InitVulkan();

	void CreateInstance();
	void SetupDebugCallback();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateDescriptorSetLayout();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateUniformBuffer();
	void CreateDescriptorPool();
	void CreateDescriptorSet();
	void CreateCommandBuffers();
	void CreateSemaphores();

	void RecreateSwapChain();

	void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkDeleter<VkBuffer>& Buffer, VkDeleter<VkDeviceMemory>& BufferMemory);

	void CopyBuffer(VkBuffer SrcBuffer, VkBuffer DstBuffer, VkDeviceSize Size);

	bool CheckValidationLayerSupport();
	std::vector<const char*> GetRequiredExtensions();

	bool IsDeviceSuitable(VkPhysicalDevice Device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice Device);

	void CreateShaderModule(const std::vector<char>& Code, VkDeleter<VkShaderModule>& ShaderModule);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice Device);

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> AvailablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device);

	uint32_t FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties);

private:
	static VkResult CreateDebugReportCallbackEXT(VkInstance Instance,
												 const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
												 const VkAllocationCallbacks* pAllocator,
												 VkDebugReportCallbackEXT* pCallback);

	static void DestroyDebugReportCallbackEXT(VkInstance Instance,
											  VkDebugReportCallbackEXT Callback,
											  const VkAllocationCallbacks* pAllocator);

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugReportFlagsEXT Flags,
														VkDebugReportObjectTypeEXT ObjType,
														uint64_t Obj,
														size_t Location,
														int32_t Code,
														const char* LayerPrefix,
														const char* Msg,
														void* UserData);

	static std::vector<char> ReadFile(const std::string& Filename);

	static void OnWindowResized(GLFWwindow* Window, int Width, int Height);

};

