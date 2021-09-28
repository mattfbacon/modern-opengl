#pragma once

#include <GL/glew.h>
#include <stdexcept>
#include <vector>

#include "GL/Attribute.hpp"
#include "GL/Shader.hpp"

namespace GL {

class Program {
protected:
	GLuint handle;
public:
	struct LinkError : public std::exception {
		std::vector<char> log_data;
		char const* what() const noexcept override;
	protected:
		LinkError(GLuint handle);
		friend class Program;
	};
public:
	Program(std::initializer_list<Shader> shaders);
	template <typename T>
	Attribute<T> lookup_attribute(char const* name) {
		return Attribute<T>{ glGetAttribLocation(handle, name) };
	}
	template <typename T, size_t E>
	VertexAttribute<T, E> lookup_vertex_attribute(char const* name) {
		return VertexAttribute<T, E>{ glGetAttribLocation(handle, name) };
	}
	void use() {
		glUseProgram(handle);
	}
protected:
	void check_for_link_error();
};

}  // namespace GL
