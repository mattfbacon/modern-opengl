#pragma once

namespace GL {

class Program;

template <typename T, typename U = T>
class Attribute {
	friend class Program;
protected:
	static constexpr GLint INVALID_HANDLE = -1;
	GLint handle = INVALID_HANDLE;
	explicit Attribute(GLint handle) : handle(handle) {}
public:
	Attribute(Attribute const&) = default;
	Attribute(Attribute&&) = default;
public:
	// void set(U val) {
	// 	assert(false);
	// }
	bool present() {
		return handle != INVALID_HANDLE;
	}
};

/* example
template <>
class Attribute<unsigned int> {
public:
  void set(unsigned int val);
};
*/

template <typename T, size_t E>
class VertexAttribute {
public:
	friend class Program;
protected:
	static constexpr GLint INVALID_HANDLE = -1;
	GLint handle = INVALID_HANDLE;
	explicit VertexAttribute(GLint handle) : handle(handle) {}
public:
	VertexAttribute(VertexAttribute const&) = default;
	VertexAttribute(VertexAttribute&&) = default;
public:
	/* void set(size_t buf_pos, size_t buf_item_size) { */
	/* 	assert(false); */
	/* } */
	bool present() {
		return handle != INVALID_HANDLE;
	}
};

template <size_t E>
class VertexAttribute<float, E> {
public:
	friend class Program;
protected:
	static constexpr GLint INVALID_HANDLE = -1;
	GLint handle = INVALID_HANDLE;
	explicit VertexAttribute(GLint handle) : handle(handle) {}
public:
	VertexAttribute(VertexAttribute const&) = default;
	VertexAttribute(VertexAttribute&&) = default;
public:
	bool present() {
		return handle != INVALID_HANDLE;
	}
	void set(size_t buf_pos, size_t buf_item_size) {
		glEnableVertexAttribArray(handle);
		glVertexAttribPointer(handle, (GLint)E, GL_FLOAT, GL_FALSE, buf_item_size, (void*)buf_pos);
	}
};

}  // namespace GL
