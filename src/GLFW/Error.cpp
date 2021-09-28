#include "GLFW/Error.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GLFW {

Error::Error() {
	code = glfwGetError(&msg);
}
char const* Error::what() const noexcept {
	return "GLFW error";
}

}  // namespace GLFW
