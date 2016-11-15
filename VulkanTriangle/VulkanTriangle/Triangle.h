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
	VkDeleter<VkDevice> Device{ vkDestroyDevice };
	VkDeleter<VkSurfaceKHR> Surface{ Instance, vkDestroySurfaceKHR };
	VkDeleter<VkSwapchainKHR> SwapChain{ Device, vkDestroySwapchainKHR };
	VkDeleter<VkRenderPass> RenderPass{ Device, vkDestroyRenderPass };
	VkDeleter<VkPipelineLayout> PipelineLayout{ Device, vkDestroyPipelineLayout };
	VkDeleter<VkPipeline> GraphicsPipeline{ Device, vkDestroyPipeline };
	VkDeleter<VkCommandPool> CommandPool{ Device, vkDestroyCommandPool };
	VkDeleter<VkSemaphore> ImageAvailableSemaphore{ Device, vkDestroySemaphore };
	VkDeleter<VkSemaphore> RenderFinishedSemaphore{ Device, vkDestroySemaphore };
	VkDeleter<VkBuffer> VertexBuffer{ Device, vkDestroyBuffer };
	VkDeleter<VkDeviceMemory> VertexBufferMemory{ Device, vkFreeMemory };


	std::vector<VkDeleter<VkFramebuffer>> SwapChainFramebuffers;

	std::vector<VkCommandBuffer> CommandBuffers;

	std::vector<VkImage> SwapChainImages;
	VkFormat SwapChainImageFormat;
	VkExtent2D SwapChainExtent;

	std::vector<VkDeleter<VkImageView>> SwapChainImageViews;

	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;

	VkQueue GraphicsQueue;
	VkQueue PresentQueue;

	const std::vector<Vertex> Vertices = {
		{ {0.0f, -0.5f}, {1.0f, 0.0f, 0.0f} },
		{ {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f} },
		{ {-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f} }
	};

	void MainLoop();
	void DrawFrame();

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
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateVertexBuffers();
	void CreateCommandBuffers();
	void CreateSemaphores();

	void RecreateSwapChain();

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

