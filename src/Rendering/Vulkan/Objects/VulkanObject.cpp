#include "VulkanObject.hpp"

void VulkanObject::printObjectDetails() {
	std::cout << "Overriden Object doesn't supply any details!" << std::endl;
}

const std::type_info& VulkanObject::getUnderlyingType() {
	return typeid(VulkanObject);
}
const std::string VulkanObject::getObjectName() {
	return this->getUnderlyingType().name();
}