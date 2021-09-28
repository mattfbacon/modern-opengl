#pragma once

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GLFW {
struct Init {
	explicit Init();
	void set_parameters(GLFWerrorfun error_callback);
	~Init();
};
}  // namespace GLFW
