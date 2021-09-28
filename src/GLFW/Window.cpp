#include <GL/glew.h>

#include "GLFW/Error.hpp"
#include "GLFW/Window.hpp"

namespace GLFW {

Window::Window(int const width, int const height, char const* const name) {
	handle = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (handle == nullptr) {
		throw GLFW::Error{};
	}
}
Window::~Window() {
	glfwDestroyWindow(handle);
}
void Window::set_key_callback(GLFWkeyfun cb) {
	glfwSetKeyCallback(handle, cb);
}
void Window::make_current() {
	glfwMakeContextCurrent(handle);
}
void Window::set_opengl_version(int major, int minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}
void Window::run() {
	while (!glfwWindowShouldClose(handle)) {
		int width, height;
		glfwGetFramebufferSize(handle, &width, &height);
		glViewport(0, 0, width, height);

		renderer();

		glfwSwapBuffers(handle);
		glfwPollEvents();
	}
}

}  // namespace GLFW
