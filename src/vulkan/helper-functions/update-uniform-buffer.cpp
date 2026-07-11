#include <chrono>
#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vulkan/helper-functions/update-uniform-buffer.hpp"
#include "vulkan/uniform-buffer-object.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::UpdateUniformBuffer(uint32_t CurrentImage)
{
    static auto StartTime = std::chrono::high_resolution_clock::now();

    auto CurrentTime = std::chrono::high_resolution_clock::now();
    float Delta = std::chrono::duration<float, std::chrono::seconds::period>(CurrentTime - StartTime).count();

    SNZ::UniformBufferObject UBO
    (   
        glm::rotate(glm::mat4(1.0f), Delta * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        glm::perspective(glm::radians(45.0f), SNZ::SwapChainExtent.width / static_cast<float>(SNZ::SwapChainExtent.height), 0.1f, 10.0f)
    );

    UBO.ProjectionMatrix[1u][1u] *= -1;

    std::memcpy(SNZ::UniformbuffersMapped[CurrentImage], &UBO, sizeof(UBO));
}