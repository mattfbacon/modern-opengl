#include <cassert>
#include <limits>

#include "GL/Shader.hpp"
#include "MappedFile.hpp"

#include "util.hpp"

namespace GL {

char const* Shader::CompilationError::what() const noexcept {
	return "GL shader compilation error";
}
Shader::CompilationError::CompilationError(GLuint handle) {
	GLsizei log_length = 0;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
	std::vector<char> log_data;
	log_data.reserve(log_length);
	glGetShaderInfoLog(handle, log_length, &log_length, log_data.data());
}

Shader::Shader(char const* const filename, Type const type) {
	handle = glCreateShader(ECLASS_VAL(type));
	assert(handle != 0);
	{
		MappedFile file{ filename };
		auto const file_data = file.span();
		auto const file_ptr = file_data.data();
		auto const file_size_ = file_data.size();
		assert(file_size_ <= std::numeric_limits<GLint>::max());
		auto const file_size = (GLint)file_size_;
		glShaderSource(handle, 1, &file_ptr, &file_size);
	}
	glCompileShader(handle);
	check_for_compilation_error();
}
Shader::~Shader() {
	glDeleteShader(handle);
}
void Shader::check_for_compilation_error() {
	GLint compilation_status = GL_TRUE;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compilation_status);
	if (compilation_status != GL_TRUE) {
		throw CompilationError{ handle };
	}
}
}  // namespace GL
