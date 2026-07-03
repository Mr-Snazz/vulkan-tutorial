#include "vulkan/queue-family-indices.hpp"

inline bool SNZ::QueueFamilyIndices::IsComplete() const
{
    return this->GraphicsFamily.has_value() && this->PresentFamily.has_value();
}