#include "Triangle.h"

void Triangle::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
}

void Triangle::MainLoop()
{
	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();
		DrawFrame();
	}
	vkDeviceWaitIdle(Device);
}

void Triangle::DrawFrame()
{
	uint32_t ImageIndex;
	VkResult Result = vkAcquireNextImageKHR(Device, SwapChain, std::numeric_limits<uint64_t>::max(),
											ImageAvailableSemaphore, VK_NULL_HANDLE, &ImageIndex);

	if (Result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapChain();
		return;
	}
	else if (Result != VK_SUCCESS && Result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("Failed to acquire Swap Chain Image!");
	}

	VkSubmitInfo SubmitInfo = {};
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore WaitSemaphores[] = { ImageAvailableSemaphore };
	VkPipelineStageFlags WaitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = WaitSemaphores;
	SubmitInfo.pWaitDstStageMask = WaitStages;
	SubmitInfo.commandBufferCount = 1;
	SubmitInfo.pCommandBuffers = &CommandBuffers[ImageIndex];

	VkSemaphore SignalSemaphore[] = { RenderFinishedSemaphore };
	SubmitInfo.signalSemaphoreCount = 1;
	SubmitInfo.pSignalSemaphores = SignalSemaphore;

	if (vkQueueSubmit(GraphicsQueue, 1, &SubmitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to submit Draw Command Buffer!");
	}

	VkPresentInfoKHR PresentInfo = {};
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.waitSemaphoreCount = 1;
	PresentInfo.pWaitSemaphores = SignalSemaphore;

	VkSwapchainKHR SwapChains[] = { SwapChain };
	PresentInfo.swapchainCount = 1;
	PresentInfo.pSwapchains = SwapChains;
	PresentInfo.pImageIndices = &ImageIndex;
	PresentInfo.pResults = nullptr;

	Result = vkQueuePresentKHR(PresentQueue, &PresentInfo);

	if (Result == VK_ERROR_OUT_OF_DATE_KHR || Result == VK_SUBOPTIMAL_KHR)
	{
		RecreateSwapChain();
	}
	else if (Result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to present Swap Chain Image!");
	}
}

void Triangle::InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(Window, this);
	glfwSetWindowSizeCallback(Window, Triangle::OnWindowResized);
}

void Triangle::InitVulkan()
{
	CreateInstance();
	SetupDebugCallback();
	CreateSurface();
	PickPhysicalDevice();
	CreateLogicalDevice();
	CreateSwapChain();
	CreateImageViews();
	CreateRenderPass();
	CreateGraphicsPipeline();
	CreateFramebuffers();
	CreateCommandPool();
	CreateVertexBuffers();
	CreateCommandBuffers();
	CreateSemaphores();
}

void Triangle::CreateInstance()
{
	if (EnableValidationLayers && !CheckValidationLayerSupport())
	{
		throw std::runtime_error("Validation Layers requested, but not available!");
	}

	VkApplicationInfo AppInfo = {};
	AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.pApplicationName = "Hello Triangle";
	AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	AppInfo.pEngineName = "Solus Engine";
	AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	AppInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	CreateInfo.pApplicationInfo = &AppInfo;

	auto Extensions = GetRequiredExtensions();

	CreateInfo.enabledExtensionCount = Extensions.size();
	CreateInfo.ppEnabledExtensionNames = Extensions.data();
	if (EnableValidationLayers)
	{
		CreateInfo.enabledLayerCount = ValidationLayers.size();
		CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
	}
	else
	{
		CreateInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&CreateInfo, nullptr, Instance.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance!");
	}
}

void Triangle::SetupDebugCallback()
{
	if (!EnableValidationLayers)
	{
		return;
	}

	VkDebugReportCallbackCreateInfoEXT CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	CreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	CreateInfo.pfnCallback = DebugCallback;

	if (CreateDebugReportCallbackEXT(Instance, &CreateInfo, nullptr, Callback.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to set up debug callback!");
	}
}

void Triangle::CreateSurface()
{
	if (glfwCreateWindowSurface(Instance, Window, nullptr, Surface.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Window Surface!");
	}
}

void Triangle::PickPhysicalDevice()
{
	uint32_t DeviceCount = 0;
	vkEnumeratePhysicalDevices(Instance, &DeviceCount, nullptr);
	if (DeviceCount == 0)
	{
		throw std::runtime_error("Failed to find GPUs with Vulkan support!");
	}
	std::vector<VkPhysicalDevice> Devices(DeviceCount);
	vkEnumeratePhysicalDevices(Instance, &DeviceCount, Devices.data());

	for (const auto& Device : Devices)
	{
		if (IsDeviceSuitable(Device))
		{
			PhysicalDevice = Device;
			break;
		}
	}
	if (PhysicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to find a suitable GPU!");
	}
}

void Triangle::CreateLogicalDevice()
{
	QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice);

	std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
	std::set<int> UniqueQueueFamilies = { Indices.GraphicsFamily, Indices.PresetFamily };

	float QueuePriority = 1.0f;
	for (int QueueFamily : UniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo QueueCreateInfo = {};
		QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfo.queueFamilyIndex = QueueFamily;
		QueueCreateInfo.queueCount = 1;
		QueueCreateInfo.pQueuePriorities = &QueuePriority;
		QueueCreateInfos.push_back(QueueCreateInfo);
	}

	VkPhysicalDeviceFeatures DeviceFeatures = {};

	VkDeviceCreateInfo CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	CreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
	CreateInfo.queueCreateInfoCount = (uint32_t)QueueCreateInfos.size();
	CreateInfo.pEnabledFeatures = &DeviceFeatures;
	CreateInfo.enabledExtensionCount = DeviceExtensions.size();
	CreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();
	if (EnableValidationLayers)
	{
		CreateInfo.enabledLayerCount = ValidationLayers.size();
		CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
	}
	else
	{
		CreateInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(PhysicalDevice, &CreateInfo, nullptr, Device.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create logical Device!");
	}

	vkGetDeviceQueue(Device, Indices.GraphicsFamily, 0, &GraphicsQueue);
	vkGetDeviceQueue(Device, Indices.PresetFamily, 0, &PresentQueue);
}

void Triangle::CreateSwapChain()
{
	SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(PhysicalDevice);

	VkSurfaceFormatKHR SurfaceFormat = ChooseSwapSurfaceFormat(SwapChainSupport.Formats);
	VkPresentModeKHR PresentMode = ChooseSwapPresentMode(SwapChainSupport.PresentModes);
	VkExtent2D Extent = ChooseSwapExtent(SwapChainSupport.Capabilities);

	uint32_t ImageCount = SwapChainSupport.Capabilities.minImageCount + 1;
	if (SwapChainSupport.Capabilities.minImageCount > 0 && ImageCount > SwapChainSupport.Capabilities.maxImageCount)
	{
		ImageCount = SwapChainSupport.Capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.surface = Surface;
	CreateInfo.minImageCount = ImageCount;
	CreateInfo.imageFormat = SurfaceFormat.format;
	CreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
	CreateInfo.imageExtent = Extent;
	CreateInfo.imageArrayLayers = 1;
	CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	SwapChainImageFormat = SurfaceFormat.format;
	SwapChainExtent = Extent;

	QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice);
	uint32_t QueueFamilyIndicesArray[] = { (uint32_t)Indices.GraphicsFamily, (uint32_t)Indices.PresetFamily };
	if (Indices.GraphicsFamily != Indices.PresetFamily)
	{
		CreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		CreateInfo.queueFamilyIndexCount = 2;
		CreateInfo.pQueueFamilyIndices = QueueFamilyIndicesArray;
	}
	else
	{
		CreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount = 0;
		CreateInfo.pQueueFamilyIndices = nullptr;
	}

	CreateInfo.preTransform = SwapChainSupport.Capabilities.currentTransform;
	CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode = PresentMode;
	CreateInfo.clipped = VK_TRUE;
	VkSwapchainKHR OldSwapchain = SwapChain;
	CreateInfo.oldSwapchain = OldSwapchain;

	VkSwapchainKHR NewSwapChain;
	if (vkCreateSwapchainKHR(Device, &CreateInfo, nullptr, &NewSwapChain) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create SwapChain!");
	}

	SwapChain = NewSwapChain;

	vkGetSwapchainImagesKHR(Device, SwapChain, &ImageCount, nullptr);
	SwapChainImages.resize(ImageCount);
	vkGetSwapchainImagesKHR(Device, SwapChain, &ImageCount, SwapChainImages.data());
}

void Triangle::CreateImageViews()
{
	SwapChainImageViews.resize(SwapChainImages.size(), VkDeleter<VkImageView>{Device, vkDestroyImageView});

	for (uint32_t i = 0; i < SwapChainImages.size(); i++)
	{
		VkImageViewCreateInfo CreateInfo = {};
		CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		CreateInfo.image = SwapChainImages[i];
		CreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		CreateInfo.format = SwapChainImageFormat;
		CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		CreateInfo.subresourceRange.baseMipLevel = 0;
		CreateInfo.subresourceRange.levelCount = 1;
		CreateInfo.subresourceRange.baseArrayLayer = 0;
		CreateInfo.subresourceRange.layerCount = 1;
		if (vkCreateImageView(Device, &CreateInfo, nullptr, SwapChainImageViews[i].replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create image views!");
		}
	}

}

void Triangle::CreateRenderPass()
{
	VkAttachmentDescription ColorAttachment = {};
	ColorAttachment.format = SwapChainImageFormat;
	ColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	ColorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	ColorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	ColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	ColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	ColorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	ColorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference ColorAttachmentRef = {};
	ColorAttachmentRef.attachment = 0;
	ColorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription SubPass = {};
	SubPass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	SubPass.colorAttachmentCount = 1;
	SubPass.pColorAttachments = &ColorAttachmentRef;

	VkSubpassDependency Dependecy = {};
	Dependecy.srcSubpass = VK_SUBPASS_EXTERNAL;
	Dependecy.dstSubpass = 0;
	Dependecy.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	Dependecy.srcAccessMask = 0;
	Dependecy.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	Dependecy.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT
		| VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo RenderPassInfo = {};
	RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	RenderPassInfo.attachmentCount = 1;
	RenderPassInfo.pAttachments = &ColorAttachment;
	RenderPassInfo.subpassCount = 1;
	RenderPassInfo.pSubpasses = &SubPass;
	RenderPassInfo.dependencyCount = 1;
	RenderPassInfo.pDependencies = &Dependecy;

	if (vkCreateRenderPass(Device, &RenderPassInfo, nullptr, RenderPass.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Render pass!");
	}
}

void Triangle::CreateGraphicsPipeline()
{
	auto VertexShaderCode = ReadFile("../shaders/vert.spv");
	auto FragmentShaderCode = ReadFile("../shaders/frag.spv");

	VkDeleter<VkShaderModule> VertexShaderModule{ Device, vkDestroyShaderModule };
	VkDeleter<VkShaderModule> FragmentShaderModule{ Device, vkDestroyShaderModule };

	CreateShaderModule(VertexShaderCode, VertexShaderModule);
	CreateShaderModule(FragmentShaderCode, FragmentShaderModule);

	VkPipelineShaderStageCreateInfo VertexShaderCreateInfo = {};
	VertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	VertexShaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	VertexShaderCreateInfo.module = VertexShaderModule;
	VertexShaderCreateInfo.pName = "main";

	VkPipelineShaderStageCreateInfo FragmentShaderCreateInfo = {};
	FragmentShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	FragmentShaderCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	FragmentShaderCreateInfo.module = FragmentShaderModule;
	FragmentShaderCreateInfo.pName = "main";

	VkPipelineShaderStageCreateInfo ShaderStages[] = { VertexShaderCreateInfo, FragmentShaderCreateInfo };

	auto BindingDescription = Vertex::GetBindingDescription();
	auto AttributeDescriptions = Vertex::GetAttributeDescription();

	VkPipelineVertexInputStateCreateInfo VertexInputInfo = {};
	VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputInfo.vertexBindingDescriptionCount = 1;
	VertexInputInfo.pVertexBindingDescriptions = &BindingDescription;
	VertexInputInfo.vertexAttributeDescriptionCount = AttributeDescriptions.size();
	VertexInputInfo.pVertexAttributeDescriptions = AttributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo InputAssembly = {};
	InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport Viewport = {};
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width = (float)SwapChainExtent.width;
	Viewport.height = (float)SwapChainExtent.height;
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	VkRect2D Scissor = {};
	Scissor.offset = { 0,0 };
	Scissor.extent = SwapChainExtent;

	VkPipelineViewportStateCreateInfo ViewportState = {};
	ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportState.viewportCount = 1;
	ViewportState.pViewports = &Viewport;
	ViewportState.scissorCount = 1;
	ViewportState.pScissors = &Scissor;

	VkPipelineRasterizationStateCreateInfo Rasterizer = {};
	Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	Rasterizer.depthClampEnable = VK_FALSE;
	Rasterizer.rasterizerDiscardEnable = VK_FALSE;
	Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	Rasterizer.lineWidth = 1.0f;
	Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	Rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	Rasterizer.depthBiasEnable = VK_FALSE;
	Rasterizer.depthBiasConstantFactor = 0.0f;
	Rasterizer.depthBiasClamp = 0.0f;
	Rasterizer.depthBiasSlopeFactor = 0.0f;

	VkPipelineMultisampleStateCreateInfo Multisampling = {};
	Multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	Multisampling.sampleShadingEnable = VK_FALSE;
	Multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	Multisampling.minSampleShading = 1.0f;
	Multisampling.pSampleMask = nullptr;
	Multisampling.alphaToCoverageEnable = VK_FALSE;
	Multisampling.alphaToOneEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState ColorBlendAttachment = {};
	ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
		| VK_COLOR_COMPONENT_G_BIT
		| VK_COLOR_COMPONENT_B_BIT
		| VK_COLOR_COMPONENT_A_BIT;
	ColorBlendAttachment.blendEnable = VK_TRUE;
	ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	// GLOBAL COLOR BLENDING
	VkPipelineColorBlendStateCreateInfo ColorBlending = {};
	ColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlending.logicOpEnable = VK_FALSE;
	ColorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	ColorBlending.attachmentCount = 1;
	ColorBlending.pAttachments = &ColorBlendAttachment;
	ColorBlending.blendConstants[0] = 0.0f; // Optional
	ColorBlending.blendConstants[1] = 0.0f; // Optional
	ColorBlending.blendConstants[2] = 0.0f; // Optional
	ColorBlending.blendConstants[3] = 0.0f; // Optional


	VkDynamicState DynamicStates[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	VkPipelineDynamicStateCreateInfo DynamicState = {};
	DynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicState.dynamicStateCount = 2;
	DynamicState.pDynamicStates = DynamicStates;

	VkPipelineLayoutCreateInfo PipelineLayoutInfo = {};
	PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	PipelineLayoutInfo.setLayoutCount = 0;
	PipelineLayoutInfo.pSetLayouts = nullptr;
	PipelineLayoutInfo.pushConstantRangeCount = 0;
	PipelineLayoutInfo.pPushConstantRanges = 0;

	if (vkCreatePipelineLayout(Device, &PipelineLayoutInfo, nullptr, PipelineLayout.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Pipeline Layout!");
	}

	VkGraphicsPipelineCreateInfo PipelineInfo = {};
	PipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	PipelineInfo.stageCount = 2;
	PipelineInfo.pStages = ShaderStages;
	PipelineInfo.pVertexInputState = &VertexInputInfo;
	PipelineInfo.pInputAssemblyState = &InputAssembly;
	PipelineInfo.pViewportState = &ViewportState;
	PipelineInfo.pRasterizationState = &Rasterizer;
	PipelineInfo.pMultisampleState = &Multisampling;
	PipelineInfo.pDepthStencilState = nullptr;
	PipelineInfo.pColorBlendState = &ColorBlending;
	PipelineInfo.pDynamicState = nullptr;
	PipelineInfo.layout = PipelineLayout;
	PipelineInfo.renderPass = RenderPass;
	PipelineInfo.subpass = 0;
	PipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	PipelineInfo.basePipelineIndex = -1;

	if (vkCreateGraphicsPipelines(Device, VK_NULL_HANDLE, 1, &PipelineInfo, nullptr, GraphicsPipeline.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Graphics Pipeline!");
	}

}

void Triangle::CreateFramebuffers()
{
	SwapChainFramebuffers.resize(SwapChainImageViews.size(), VkDeleter<VkFramebuffer>{Device, vkDestroyFramebuffer});
	for (size_t i = 0; i < SwapChainImageViews.size(); i++)
	{
		VkImageView Attachments[] = {
			SwapChainImageViews[i]
		};

		VkFramebufferCreateInfo FramebufferInfo = {};
		FramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		FramebufferInfo.renderPass = RenderPass;
		FramebufferInfo.attachmentCount = 1;
		FramebufferInfo.pAttachments = Attachments;
		FramebufferInfo.width = SwapChainExtent.width;
		FramebufferInfo.height = SwapChainExtent.height;
		FramebufferInfo.layers = 1;

		if (vkCreateFramebuffer(Device, &FramebufferInfo, nullptr, SwapChainFramebuffers[i].replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Frame buffers!");
		}
	}
}
void Triangle::CreateCommandPool()
{
	QueueFamilyIndices QueueFamilyIndex = FindQueueFamilies(PhysicalDevice);
	VkCommandPoolCreateInfo PoolInfo = {};
	PoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	PoolInfo.queueFamilyIndex = QueueFamilyIndex.GraphicsFamily;
	PoolInfo.flags = 0;

	if (vkCreateCommandPool(Device, &PoolInfo, nullptr, CommandPool.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Command Pool!");
	}
}

void Triangle::CreateVertexBuffers()
{
	VkBufferCreateInfo BufferInfo = {};
	BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferInfo.size = sizeof(Vertices[0]) * Vertices.size();
	BufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(Device, &BufferInfo, nullptr, VertexBuffer.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Vertex Buffer!");
	}

	VkMemoryRequirements MemRequirements;
	vkGetBufferMemoryRequirements(Device, VertexBuffer, &MemRequirements);

	VkMemoryAllocateInfo AllocInfo = {};
	AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	AllocInfo.allocationSize = MemRequirements.size;
	AllocInfo.memoryTypeIndex = FindMemoryType(MemRequirements.memoryTypeBits,
											   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
											   | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	if (vkAllocateMemory(Device, &AllocInfo, nullptr, VertexBufferMemory.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate Vertex Buffer Memory!");
	}
	vkBindBufferMemory(Device, VertexBuffer, VertexBufferMemory, 0);

	void* Data;
	vkMapMemory(Device, VertexBufferMemory, 0, BufferInfo.size, 0, &Data);
	memcpy(Data, Vertices.data(), (size_t)BufferInfo.size);
	vkUnmapMemory(Device, VertexBufferMemory);
}

void Triangle::CreateCommandBuffers()
{
	if (CommandBuffers.size() > 0)
	{
		vkFreeCommandBuffers(Device, CommandPool, CommandBuffers.size(), CommandBuffers.data());
	}
	CommandBuffers.resize(SwapChainFramebuffers.size());

	VkCommandBufferAllocateInfo AllocInfo = {};
	AllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	AllocInfo.commandPool = CommandPool;
	AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	AllocInfo.commandBufferCount = (uint32_t)CommandBuffers.size();

	if (vkAllocateCommandBuffers(Device, &AllocInfo, CommandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate Command Buffers!");
	}

	for (size_t i = 0; i < CommandBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo BeginInfo = {};
		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		BeginInfo.pInheritanceInfo = nullptr;

		vkBeginCommandBuffer(CommandBuffers[i], &BeginInfo);

		VkRenderPassBeginInfo RenderPassInfo = {};
		RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		RenderPassInfo.renderPass = RenderPass;
		RenderPassInfo.framebuffer = SwapChainFramebuffers[i];
		RenderPassInfo.renderArea.offset = { 0,0 };
		RenderPassInfo.renderArea.extent = SwapChainExtent;
		VkClearValue ClearColor = { 0.0f,0.0f,0.0f,1.0f };
		RenderPassInfo.clearValueCount = 1;
		RenderPassInfo.pClearValues = &ClearColor;

		vkCmdBeginRenderPass(CommandBuffers[i], &RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(CommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);

		VkBuffer VertexBuffers[] = { VertexBuffer };
		VkDeviceSize Offsets[] = { 0 };
		vkCmdBindVertexBuffers(CommandBuffers[i], 0, 1, VertexBuffers, Offsets);

		vkCmdDraw(CommandBuffers[i], Vertices.size(), 1, 0, 0);

		vkCmdEndRenderPass(CommandBuffers[i]);

		if (vkEndCommandBuffer(CommandBuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to record Command Buffer!");
		}
	}

}

void Triangle::CreateSemaphores()
{
	VkSemaphoreCreateInfo SemaphoreInfo = {};
	SemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if (vkCreateSemaphore(Device, &SemaphoreInfo, nullptr, ImageAvailableSemaphore.replace()) != VK_SUCCESS
		|| vkCreateSemaphore(Device, &SemaphoreInfo, nullptr, RenderFinishedSemaphore.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Semaphores!");
	}
}

void Triangle::RecreateSwapChain()
{
	vkDeviceWaitIdle(Device);
	CreateSwapChain();
	CreateImageViews();
	CreateRenderPass();
	CreateGraphicsPipeline();
	CreateFramebuffers();
	CreateCommandBuffers();
}

bool Triangle::CheckValidationLayerSupport()
{
	uint32_t LayerCount;
	vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);

	std::vector<VkLayerProperties> AvailableLayers(LayerCount);
	vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());

	for (const char* LayerName : ValidationLayers)
	{
		bool LayerFound = false;
		for (const auto& LayerProperties : AvailableLayers)
		{
			if (strcmp(LayerName, LayerProperties.layerName) == 0)
			{
				LayerFound = true;
				break;
			}
		}
		if (!LayerFound)
		{
			return false;
		}
	}

	return true;
}

std::vector<const char*> Triangle::GetRequiredExtensions()
{
	std::vector<const char*> Extensions;
	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (uint32_t i = 0; i < glfwExtensionCount; i++)
	{
		Extensions.push_back(glfwExtensions[i]);
	}

	if (EnableValidationLayers)
	{
		Extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return Extensions;
}

bool Triangle::IsDeviceSuitable(VkPhysicalDevice Device)
{
	QueueFamilyIndices Indices = FindQueueFamilies(Device);

	bool ExtensionSupported = CheckDeviceExtensionSupport(Device);

	bool SwapChainAdequate = false;
	if (ExtensionSupported)
	{
		SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(Device);
		SwapChainAdequate = !SwapChainSupport.Formats.empty() && !SwapChainSupport.PresentModes.empty();
	}

	return Indices.IsComplete() && ExtensionSupported && SwapChainAdequate;
}

bool Triangle::CheckDeviceExtensionSupport(VkPhysicalDevice Device)
{
	uint32_t ExtensionCount;
	vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, nullptr);

	std::vector<VkExtensionProperties> AvailableExtensions(ExtensionCount);
	vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, AvailableExtensions.data());

	std::set<std::string> RequiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

	for (const auto& Extension : AvailableExtensions)
	{
		RequiredExtensions.erase(Extension.extensionName);
	}

	return RequiredExtensions.empty();
}

void Triangle::CreateShaderModule(const std::vector<char>& Code, VkDeleter<VkShaderModule>& ShaderModule)
{
	VkShaderModuleCreateInfo CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.codeSize = Code.size();
	CreateInfo.pCode = (uint32_t*)Code.data();

	if (vkCreateShaderModule(Device, &CreateInfo, nullptr, ShaderModule.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Shader Module!");
	}
}

SwapChainSupportDetails Triangle::QuerySwapChainSupport(VkPhysicalDevice Device)
{
	SwapChainSupportDetails Details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Device, Surface, &Details.Capabilities);

	uint32_t FormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(Device, Surface, &FormatCount, nullptr);

	if (FormatCount > 0)
	{
		Details.Formats.resize(FormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(Device, Surface, &FormatCount, Details.Formats.data());
	}

	uint32_t PresentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(Device, Surface, &PresentModeCount, nullptr);

	if (PresentModeCount > 0)
	{
		Details.PresentModes.resize(PresentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(Device, Surface, &PresentModeCount, Details.PresentModes.data());
	}

	return Details;
}

VkSurfaceFormatKHR Triangle::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats)
{
	if (AvailableFormats.size() == 1 && AvailableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& AvailableFormat : AvailableFormats)
	{
		if (AvailableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && AvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return AvailableFormat;
		}
	}

	return AvailableFormats[0];
}

VkPresentModeKHR Triangle::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> AvailablePresentModes)
{
	for (const auto& AvailablePresentMode : AvailablePresentModes)
	{
		if (AvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return AvailablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Triangle::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR & Capabilities)
{
	if (Capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return Capabilities.currentExtent;
	}
	else
	{
		VkExtent2D ActualExtent = { WINDOW_WIDTH, WINDOW_HEIGHT };
		ActualExtent.width = std::max(Capabilities.minImageExtent.width, std::min(Capabilities.maxImageExtent.width, ActualExtent.width));
		ActualExtent.height = std::max(Capabilities.minImageExtent.height, std::min(Capabilities.maxImageExtent.height, ActualExtent.height));
		return ActualExtent;
	}
}

QueueFamilyIndices Triangle::FindQueueFamilies(VkPhysicalDevice Device)
{
	QueueFamilyIndices Indices;

	uint32_t QueueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());

	int i = 0;
	for (const auto& QueueFamily : QueueFamilies)
	{
		VkBool32 PresetSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(Device, i, Surface, &PresetSupport);
		if (QueueFamily.queueCount > 0 && PresetSupport)
		{
			Indices.PresetFamily = i;
		}
		if (QueueFamily.queueCount > 0 && QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			Indices.GraphicsFamily = i;
		}
		if (Indices.IsComplete())
		{
			break;
		}
		i++;
	}

	return Indices;
}

uint32_t Triangle::FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties)
{
	VkPhysicalDeviceMemoryProperties MemProperties;
	vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &MemProperties);

	for (uint32_t i = 0; i < MemProperties.memoryTypeCount; i++)
	{
		if (TypeFilter & (1 << i)
			&& (MemProperties.memoryTypes[i].propertyFlags & Properties) == Properties)
		{
			return i;
		}
	}
	throw std::runtime_error("Failed to find suitable Memory Type!");
}

VkResult Triangle::CreateDebugReportCallbackEXT(VkInstance Instance,
												const VkDebugReportCallbackCreateInfoEXT * pCreateInfo,
												const VkAllocationCallbacks * pAllocator,
												VkDebugReportCallbackEXT * pCallback)
{
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(Instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr)
	{
		return func(Instance, pCreateInfo, pAllocator, pCallback);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void Triangle::DestroyDebugReportCallbackEXT(VkInstance Instance, VkDebugReportCallbackEXT Callback, const VkAllocationCallbacks * pAllocator)
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(Instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr)
	{
		func(Instance, Callback, pAllocator);
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL Triangle::DebugCallback(VkDebugReportFlagsEXT Flags,
													   VkDebugReportObjectTypeEXT ObjType,
													   uint64_t Obj,
													   size_t Location,
													   int32_t Code,
													   const char * LayerPrefix,
													   const char * Msg,
													   void * UserData)
{
	std::cerr << "Validation Layer: " << Msg << std::endl;
	return VK_FALSE;
}

std::vector<char> Triangle::ReadFile(const std::string & Filename)
{
	std::ifstream File(Filename, std::ios::ate | std::ios::binary);

	if (!File.is_open())
	{
		throw std::runtime_error("Failed to open File!");
	}
	size_t FileSize = (size_t)File.tellg();
	std::vector<char> buffer(FileSize);
	File.seekg(0);
	File.read(buffer.data(), FileSize);
	File.close();

	return buffer;
}

void Triangle::OnWindowResized(GLFWwindow * Window, int Width, int Height)
{
	if (Width == 0 || Height == 0)
	{
		return;
	}
	Triangle* App = reinterpret_cast<Triangle*>(glfwGetWindowUserPointer(Window));
	App->RecreateSwapChain();
}
