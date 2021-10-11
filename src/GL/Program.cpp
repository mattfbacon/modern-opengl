#include <cassert>

#include "GL/Program.hpp"

namespace GL {

char const* Program::LinkError::what() const noexcept {
	return "GL program link error";
}
Program::LinkError::LinkError(GLuint handle) {
	GLsizei log_length = 0;
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
	log_data.reserve(log_length);
	glGetProgramInfoLog(handle, log_length, &log_length, log_data.data());
}

Program::Program(std::initializer_list<Shader> shaders) {
	handle = glCreateProgram();
	assert(handle != 0);
	for (Shader const& shader : shaders) {
		glAttachShader(handle, shader.handle);
	}
	glBindFragDataLocation(handle, 0, "frag_color");
	glLinkProgram(handle);
	check_for_link_error();
}
void Program::check_for_link_error() {
	GLint link_status = GL_TRUE;
	glGetProgramiv(handle, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		throw LinkError{ handle };
	}
}
}  // namespace GL
