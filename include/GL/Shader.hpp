#pragma once

#include <GL/glew.h>
#include <stdexcept>
#include <vector>

namespace GL {

class Program;

class Shader {
public:
	enum class Type : GLenum {
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER,
	};
public:
	struct CompilationError : public std::exception {
		std::vector<char> log_data;
		char const* what() const noexcept override;
	protected:
		CompilationError(GLuint handle);
		friend class Shader;
	};
public:
	Shader(char const* const filename, Type const type);
	Shader(Shader const&) = delete;
	Shader(Shader&&) = default;
	~Shader();
protected:
	void check_for_compilation_error();
protected:
	GLuint handle;
	friend class Program;
};

}  // namespace GL
