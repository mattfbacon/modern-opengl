#pragma once

#include <stdexcept>

typedef unsigned int GLenum;

namespace GLEW {
struct Error : public std::exception {
	GLenum code;
	Error(GLenum code) : code(code) {}
	char const* what() const noexcept override;
};
}  // namespace GLEW
