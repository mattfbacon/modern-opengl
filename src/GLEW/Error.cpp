#include "GLEW/Error.hpp"

namespace GLEW {

char const* Error::what() const noexcept {
	return "GLEW error";
}

}  // namespace GLEW
