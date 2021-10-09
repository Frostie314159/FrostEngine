#ifndef OPENGL_UTIL_HPP_
#define OPENGL_UTIL_HPP_
#if  defined _WIN32 || defined __CYGWIN__
	#include <windef.h>
#endif

#include "GL/glew.h"
#include "Version.hpp"

class OpenGLUtil
{
public:
	static Version getOpenGLVersion();
	template<typename T>
	static GLenum getTypenameAsOpenGLType(T t_data) {
		if (typeid(T) == typeid(GLfloat)) {
			return GL_FLOAT;
		}
		else if (typeid(T) == typeid(GLdouble)) {
			return GL_DOUBLE;
		}
		else if (typeid(T) == typeid(GLint)) {
			return GL_INT;
		}
		else if (typeid(T) == typeid(GLboolean)) {
			return GL_BOOL;
		}
		else if (typeid(T) == typeid(GLshort)) {
			return GL_SHORT;
		}
		else if (typeid(T) == typeid(GLushort)) {
			return GL_UNSIGNED_SHORT;
		}
		else if (typeid(T) == typeid(GLuint)) {
			return GL_UNSIGNED_INT;
		}
		else if (typeid(T) == typeid(GLubyte)) {
			return GL_UNSIGNED_BYTE;
		}
		else {
			return 0;
		}
	}
};

#endif