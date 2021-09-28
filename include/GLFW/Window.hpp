#pragma once

#include <functional>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GLFW {

class Window {
public:
	explicit Window(int width, int height, char const* name);
	~Window();
	void set_key_callback(GLFWkeyfun cb);
	void make_current();
	static void set_opengl_version(int major, int minor);
	void set_renderer(std::function<void(void)> new_renderer) {
		renderer = new_renderer;
	}
	void run();
protected:
	std::function<void(void)> renderer;
	GLFWwindow* handle;
};

}  // namespace GLFW
