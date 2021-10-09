#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <iostream>
#include <vector>
#include <memory>

#include "vulkan/vulkan.h"
#include "ErrorHandler.hpp"
#include "Config.hpp"

namespace Layer {

	enum class LayerLevel {
		LAYER_LEVEL_INSTANCE,
		LAYER_LEVEL_DEVICE
	};

	std::vector<VkLayerProperties> enumerateLayers(VkPhysicalDevice t_physicalDevice = VkPhysicalDevice{});

	std::vector<VkLayerProperties> getRequieredLayersFromConfig(LayerLevel t_layerLevel, Config t_engineConfig);

	std::vector<const char*> getLayerPropertiesAsCStrVector(std::vector<VkLayerProperties> t_layerProperties);
}


#endif