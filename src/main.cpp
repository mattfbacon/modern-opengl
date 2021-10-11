#include <GL/glew.h>
#include <cassert>
#include <iostream>
#include <limits>
#include <span>
#include <vector>

#include "GL/Buffer.hpp"
#include "GL/Program.hpp"
#include "GL/Shader.hpp"
#include "GLEW/Error.hpp"
#include "GLEW/Init.hpp"
#include "GLFW/Error.hpp"
#include "GLFW/Init.hpp"
#include "GLFW/Window.hpp"
#include "MappedFile.hpp"

void error_callback(int, char const* const description) {
	std::clog << "Error! " << description << std::endl;
}

void key_callback(GLFWwindow* const window, int key, int, int action, int) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

std::array<float const, 3 * 2> const vertices{
	-0.6, -0.4,  // 1
	+0.6, -0.4,  // 2
	+0.0, +0.6,  // 3
};

int main() {
	try {
		GLFW::Init glfw_global;

		GLFW::Window::set_opengl_version(4, 6);
		GLFW::Window window{ 640, 480, "Test window" };
		window.set_key_callback(key_callback);
		window.make_current();

		GLEW::Init glew_global;
		glfw_global.set_parameters(error_callback);

		GL::Buffer vertex_buffer{ GL::Buffer::Type::array_buffer };
		vertex_buffer.set_data(vertices, GL::Buffer::DataUsage::static_draw);

		GL::Program program{ { "vertex.glsl", GL::Shader::Type::vertex }, { "fragment.glsl", GL::Shader::Type::fragment } };
		auto vertices_attrib = program.lookup_vertex_attribute<float, 2>("vertex_pos");
		// start at 0; stride of 2
		vertices_attrib.set(0, 2);

		window.set_renderer([&program, &vertex_buffer]() {
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			program.use();
			vertex_buffer.bind();
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);
		});
		window.run();
		return EXIT_SUCCESS;
	} catch (GL::Shader::CompilationError const& e) {
		std::clog << e.what() << '\n';
		std::clog << std::string_view{ e.log_data.data(), e.log_data.size() } << std::endl;
	} catch (GL::Program::LinkError const& e) {
		std::clog << e.what() << '\n';
		std::clog << std::string_view{ e.log_data.data(), e.log_data.size() } << std::endl;
	} catch (GLEW::Error const& e) {
		std::clog << e.what() << ": " << glewGetErrorString(e.code) << std::endl;
		return EXIT_FAILURE;
	} catch (GLFW::Error const& e) {
		std::clog << e.what() << " (code " << e.code << "): " << e.msg << std::endl;
	} catch (...) {
		throw;
	}
}
