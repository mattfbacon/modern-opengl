#pragma once

#include <GL/glew.h>
#include <span>

namespace GL {

class Buffer {
public:
	enum class Type : GLenum {
		array_buffer = GL_ARRAY_BUFFER,
	};
	enum class DataUsage : GLenum {
		static_draw = GL_STATIC_DRAW,
	};
public:
	Buffer(Type const type);
	Buffer(Buffer const&) = delete;
	Buffer(Buffer&&) = default;
	~Buffer();
	void set_data(std::span<std::byte const> const data, DataUsage const usage);
	template <typename T>
	void set_data(std::span<T const> const data, DataUsage const usage) {
		set_data(std::span{ (std::byte const*)data.data(), data.size_bytes() }, usage);
	}
	template <typename T, size_t E>
	void set_data(std::array<T const, E> const data, DataUsage const usage) {
		set_data(std::span<T const>{ data.data(), data.size() }, usage);
	}
	void bind();
protected:
	Type const type;
	GLuint handle;
};

}  // namespace GL
