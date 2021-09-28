#pragma once

#include <stdexcept>

namespace GLFW {
struct Error : public std::exception {
	int code;
	char const* msg;
	explicit Error();
	char const* what() const noexcept override;
};
}  // namespace GLFW
