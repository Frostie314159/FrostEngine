#include "ErrorHandler.hpp"


std::string ErrorHandler::getVulkanErrorCodeAsString(VkResult t_errorCode) {
    switch (t_errorCode)
    {
    case VK_SUCCESS:
        return "Success";
    case VK_NOT_READY:
        return "NotReady";
    case VK_TIMEOUT:
        return "Timeout";
    case VK_EVENT_SET:
        return "EventSet";
    case VK_EVENT_RESET:
        return "EventReset";
    case VK_INCOMPLETE:
        return "Incomplete";
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        return "ErrorOutOfHostMemory";
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        return "ErrorOutOfDeviceMemory";
    case VK_ERROR_INITIALIZATION_FAILED:
        return "ErrorInitializationFailed";
    case VK_ERROR_DEVICE_LOST:
        return "ErrorDeviceLost";
    case VK_ERROR_MEMORY_MAP_FAILED:
        return "ErrorMemoryMapFailed";
    case VK_ERROR_LAYER_NOT_PRESENT:
        return "ErrorLayerNotPresent";
    case VK_ERROR_EXTENSION_NOT_PRESENT:
        return "ErrorExtensionNotPresent";
    case VK_ERROR_FEATURE_NOT_PRESENT:
        return "ErrorFeatureNotPresent";
    case VK_ERROR_INCOMPATIBLE_DRIVER:
        return "ErrorIncompatibleDriver";
    case VK_ERROR_TOO_MANY_OBJECTS:
        return "ErrorTooManyObjects";
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
        return "ErrorFormatNotSupported";
    case VK_ERROR_FRAGMENTED_POOL:
        return "ErrorFragmentedPool";
    case VK_ERROR_UNKNOWN:
        return "ErrorUnknown";
    case VK_ERROR_OUT_OF_POOL_MEMORY:
        return "ErrorOutOfPoolMemory";
    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
        return "ErrorInvalidExternalHandle";
    case VK_ERROR_FRAGMENTATION:
        return "ErrorFragmentation";
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        return "ErrorInvalidOpaqueCaptureAddress";
    case VK_ERROR_SURFACE_LOST_KHR:
        return "ErrorSurfaceLostKHR";
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        return "ErrorNativeWindowInUseKHR";
    case VK_SUBOPTIMAL_KHR:
        return "SuboptimalKHR";
    case VK_ERROR_OUT_OF_DATE_KHR:
        return "ErrorOutOfDateKHR";
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        return "ErrorIncompatibleDisplayKHR";
    case VK_ERROR_VALIDATION_FAILED_EXT:
        return "ErrorValidationFailedEXT";
    case VK_ERROR_INVALID_SHADER_NV:
        return "ErrorInvalidShaderNV";
    case VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        return "ErrorIncompatibleVersionKHR";
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        return "ErrorInvalidDrmFormatModifierPlaneLayoutEXT";
    case VK_ERROR_NOT_PERMITTED_EXT:
        return "ErrorNotPermittedEXT";
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        return "ErrorFullScreenExclusiveModeLostEXT";
    case VK_THREAD_IDLE_KHR:
        return "ThreadIdleKHR";
    case VK_THREAD_DONE_KHR:
        return "ThreadDoneKHR";
    case VK_OPERATION_DEFERRED_KHR:
        return "OperationDeferredKHR";
    case VK_OPERATION_NOT_DEFERRED_KHR:
        return "OperationNotDeferredKHR";
    case VK_PIPELINE_COMPILE_REQUIRED_EXT:
        return "PipelineCompileRequiredEXT";
    default: return "invalid";
    }
}
std::string ErrorHandler::getGLFWErrorCodeAsString(int t_errorCode) {
    switch (t_errorCode) {
    case GLFW_NOT_INITIALIZED:
        return "ErrorNotInitialized";
    case GLFW_NO_CURRENT_CONTEXT:
        return "ErrorNoCurrentContext";
    case GLFW_INVALID_ENUM:
        return "ErrorInvalidEnum";
    case GLFW_INVALID_VALUE:
        return "ErrorInvalidValue";
    case GLFW_OUT_OF_MEMORY:
        return "ErrorOutOfMemory";
    case GLFW_API_UNAVAILABLE:
        return "ErrorAPIUnavailable";
    case GLFW_VERSION_UNAVAILABLE:
        return "ErrorVersionUnavailable";
    case GLFW_PLATFORM_ERROR:
        return "ErrorPlatformError";
    case GLFW_FORMAT_UNAVAILABLE:
        return "ErrorFormatUnavailable";
    case GLFW_NO_WINDOW_CONTEXT:
        return "ErrorNoWindowContext";
    default:
        return "Invalid Error Code";
    }
}
std::string ErrorHandler::getOpenGLErrorCodeAsString(GLenum t_errorCode) {
    switch (t_errorCode) {
    case GL_INVALID_ENUM:
        return "ErrorInvalidEnum";
    case GL_INVALID_VALUE:
        return "ErrorInvalidValue";
    case GL_INVALID_OPERATION:
        return "ErrorInvalidOperation";
    case GL_STACK_OVERFLOW:
        return "ErrorStackOverflow";
    case GL_STACK_UNDERFLOW:
        return "ErrorStackUnderflow";
    case GL_OUT_OF_MEMORY:
        return "ErrorOutOfMemory";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "ErrorInvalidFramebufferOperation";
    case GL_CONTEXT_LOST:
        return "ErrorContextLost";
    case GL_TABLE_TOO_LARGE:
        return "ErrorTableTooLarge";
    default:
        return "InvalidErrorCode";
    }
    return "";
}
std::string ErrorHandler::getOpenALErrorCodeAsString(int t_errorCode) {
    return "";
}
void ErrorHandler::glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void ErrorHandler::handleVulkanErrorCode(VkResult t_errorCode) {
    if (t_errorCode > 0)
        std::cout << "[Vulkan][WARN][" + Time::getTimeAsString() + "] " + getVulkanErrorCodeAsString(t_errorCode) << std::endl;
    else if (t_errorCode < 0)
        std::cout << "[Vulkan][ERROR][" + Time::getTimeAsString() + "] " + getVulkanErrorCodeAsString(t_errorCode) << std::endl;
}
void ErrorHandler::handleGLFWErrorCode(int t_errorCode) {
    if (t_errorCode != GLFW_NO_ERROR)
        std::cout << "[GLFW][ERROR][" + Time::getTimeAsString() + "] " + getGLFWErrorCodeAsString(t_errorCode) << std::endl;
}
void ErrorHandler::handleOpenGLErrorCode(GLenum t_errorCode) {
    if (t_errorCode != GL_NO_ERROR) {
        std::cout << "[OpenGL][ERROR][" + Time::getTimeAsString() + "] " + getOpenGLErrorCodeAsString(t_errorCode) << std::endl;
        glClearError();
    }
}
void ErrorHandler::handleOpenALErrorCode(int t_errorCode) {}