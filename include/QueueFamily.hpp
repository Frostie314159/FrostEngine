#ifndef QUEUE_FAMILY_HPP_
#define QUEUE_FAMILY_HPP_

#include "PhysicalDevice.hpp"

class QueueFamily
{
private:
	VkQueueFamilyProperties m_queueFamilyProperties;
	uint32_t m_queueFamilyIndex;
public:
	static const std::vector<QueueFamily> enumerateQueueFamilies();

	QueueFamily(VkQueueFamilyProperties t_queueFamilyProperties, uint32_t t_queueFamilyIndex);
	QueueFamily(const QueueFamily&);
	QueueFamily();
	~QueueFamily();
	
	const std::tuple<VkQueueFamilyProperties, uint32_t> getQueueFamilyDetails();
};

#endif