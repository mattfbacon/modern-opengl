#include "GLFW/Error.hpp"
#include "GLFW/Init.hpp"

namespace GLFW {

Init::Init() {
	if (glfwInit() != GLFW_TRUE) {
		throw GLFW::Error{};
	}
}
void Init::set_parameters(GLFWerrorfun error_callback) {
	glfwSetErrorCallback(error_callback);
	glfwSwapInterval(1);
}
Init::~Init() {
	glfwTerminate();
}

}  // namespace GLFW
