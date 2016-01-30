/*

Functions to help set uniform variable in OpenGL 4 Shaders

*/

#pragma once

#include "myglutils.h"

typedef enum UniformTypes {
    SINGLE,
    DOUBLE,
    TRIPLE,
    QUAD,
    MAT2,
    MAT3,
    MAT4,
    MAT2x3,
    MAT3x2,
    MAT2x4,
    MAT4x2,
    MAT3x4,
    MAT4x3,
} UniformType;

GLint getUniformID(GLuint program, const char* name);

bool setUniform(GLuint program, const char* name, GLfloat v0);
bool setUniform(GLuint program, const char* name, GLfloat v0, GLfloat v1);
bool setUniform(GLuint program, const char* name, GLfloat v0, GLfloat v1, GLfloat v2);
bool setUniform(GLuint program, const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

bool setUniform(GLuint program, const char* name, GLint v0);
bool setUniform(GLuint program, const char* name, GLint v0, GLint v1);
bool setUniform(GLuint program, const char* name, GLint v0, GLint v1, GLint v2);
bool setUniform(GLuint program, const char* name, GLint v0, GLint v1, GLint v2, GLint v3);

bool setUniform(GLuint program, const char* name, GLuint v0);
bool setUniform(GLuint program, const char* name, GLuint v0, GLuint v1);
bool setUniform(GLuint program, const char* name, GLuint v0, GLuint v1, GLuint v2);
bool setUniform(GLuint program, const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

bool setUniform(GLuint program, const char* name, UniformType type, GLsizei count, const GLfloat* value);
bool setUniform(GLuint program, const char* name, UniformType type, GLsizei count, const GLint* value);
bool setUniform(GLuint program, const char* name, UniformType type, GLsizei count, const GLuint* value);