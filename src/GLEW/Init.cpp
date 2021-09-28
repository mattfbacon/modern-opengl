#include <GL/glew.h>

#include "GLEW/Error.hpp"
#include "GLEW/Init.hpp"

namespace GLEW {

Init::Init() {
	glewExperimental = true;
	if (GLenum const err = glewInit(); err != GLEW_OK) {
		throw GLEW::Error{ err };
	}
}
Init::~Init() {
	//
}

}  // namespace GLEW
