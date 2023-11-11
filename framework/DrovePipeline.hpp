#pragma once


#include <vulkan/vulkan.h>

#include <functional>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <vulkan/vulkan_core.h>


namespace Drove {
    class Pipeline{
    private:

        VkDevice* device;


        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;

        VkPipeline graphicsPipeline;

        std::vector<VkFramebuffer> swapChainFramebuffers;

        static std::vector<char> readFile(const std::string& filename){
            std::ifstream file(filename, std::ios::ate | std::ios::binary);

            if(!file.is_open()){
                throw std::runtime_error("failed to open file.");
            }
            size_t fileSize = static_cast<size_t>(file.tellg());
            std::vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(),fileSize);

            file.close();

            return buffer;


        }
        VkShaderModule createShaderModule(const std::vector<char>& code);

    public:
        Pipeline(VkDevice* device, std::function<void(int*, int*)> getWindowExtent,
                std::string fragPath, std::string vertPath);
        ~Pipeline();

    };

}
