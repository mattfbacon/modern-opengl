#include <cassert>

#include "GL/Buffer.hpp"

#include "util.hpp"

namespace GL {

Buffer::Buffer(Type const type) : type(type) {
	glGenBuffers(1, &handle);
	assert(handle != 0);
}
Buffer::~Buffer() {
	glDeleteBuffers(1, &handle);
}
void Buffer::set_data(std::span<std::byte const> const data, DataUsage const usage) {
	glNamedBufferData(handle, data.size(), data.data(), ECLASS_VAL(usage));
}
void Buffer::bind() {
	glBindBuffer(ECLASS_VAL(type), handle);
}

}  // namespace GL
