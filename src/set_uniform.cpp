#include "set_uniform.hpp"
#include "logger.h"

GLint getUniformID(GLuint program, const char* name) {
    GLint id = glGetUniformLocation(program, name);
    if (id == -1) {
        log_msg(LOG_WARNING, "Cannot get id for name %s in program %u\n", name, program);
    }

    return id;
}

bool setUniform(GLuint program, const char* name, GLfloat v0) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform1f(id, v0);
    return true;
}

bool setUniform(GLuint program, const char* name, GLfloat v0, GLfloat v1) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform2f(id, v0, v1);
    return true;
}

bool setUniform(GLuint program, const char* name, GLfloat v0, GLfloat v1, GLfloat v2) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform3f(id, v0, v1, v2);
    return true;
}

bool setUniform(GLuint program, const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform4f(id, v0, v1, v2, v3);
    return true;
}

bool setUniform(GLuint program, const char* name, GLint v0) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform1i(id, v0);
    return true;
}

bool setUniform(GLuint program, const char* name, GLint v0, GLint v1) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform2i(id, v0, v1);
    return true;
}

bool setUniform(GLuint program, const char* name, GLint v0, GLint v1, GLint v2) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform3i(id, v0, v1, v2);
    return true;
}

bool setUniform(GLuint program, const char* name, GLint v0, GLint v1, GLint v2, GLint v3) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform4i(id, v0, v1, v2, v3);
    return true;
}

// ####### @temp

bool setUniform(GLuint program, const char* name, GLuint v0) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform1ui(id, v0);
    return true;
}

bool setUniform(GLuint program, const char* name, GLuint v0, GLuint v1) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform2ui(id, v0, v1);
    return true;
}

bool setUniform(GLuint program, const char* name, GLuint v0, GLuint v1, GLuint v2) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform3ui(id, v0, v1, v2);
    return true;
}

bool setUniform(GLuint program, const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    glUniform4ui(id, v0, v1, v2, v3);
    return true;
}

// this function is special because it also does matrices
bool setUniform(GLuint program, const char* name, UniformType type, GLsizei count, const GLfloat* value) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    switch (type) {
    case SINGLE:
        glUniform1fv(id, count, value);
        break;
    case DOUBLE:
        glUniform2fv(id, count, value);
        break;
    case TRIPLE:
        glUniform3fv(id, count, value);
        break;
    case QUAD:
        glUniform4fv(id, count, value);
        break;
    case MAT2:
        glUniformMatrix2fv(id, count, GL_FALSE, value);
        break;
    case MAT3:
        glUniformMatrix3fv(id, count, GL_FALSE, value);
        break;
    case MAT4:
        glUniformMatrix4fv(id, count, GL_FALSE, value);
        break;
    case MAT2x3:
        glUniformMatrix2x3fv(id, count, GL_FALSE, value);
        break;
    case MAT3x2:
        glUniformMatrix3x2fv(id, count, GL_FALSE, value);
        break;
    case MAT2x4:
        glUniformMatrix2x4fv(id, count, GL_FALSE, value);
        break;
    case MAT4x2:
        glUniformMatrix4x2fv(id, count, GL_FALSE, value);
        break;
    case MAT3x4:
        glUniformMatrix3x4fv(id, count, GL_FALSE, value);
        break;
    case MAT4x3:
        glUniformMatrix4x3fv(id, count, GL_FALSE, value);
        break;
    }

    return true;
}

bool setUniform(GLuint program, const char* name, UniformType type, GLsizei count, const GLint* value) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    switch (type) {
    case SINGLE:
        glUniform1iv(id, count, value);
        break;
    case DOUBLE:
        glUniform2iv(id, count, value);
        break;
    case TRIPLE:
        glUniform3iv(id, count, value);
        break;
    case QUAD:
        glUniform4iv(id, count, value);
        break;
    default:
        log_msg(LOG_WARNING, "setUniform(GLuint, const char*, UniformType, GLsizei, const GLint*) does not support matrices!\n");
        return false;
    }

    return true;
}

bool setUniform(GLuint program, const char* name, UniformType type, GLsizei count, const GLuint* value) {
    GLint id = getUniformID(program, name);

    if (id == -1) return false;

    switch (type) {
    case SINGLE:
        glUniform1uiv(id, count, value);
        break;
    case DOUBLE:
        glUniform2uiv(id, count, value);
        break;
    case TRIPLE:
        glUniform3uiv(id, count, value);
        break;
    case QUAD:
        glUniform4uiv(id, count, value);
        break;
    default:
        log_msg(LOG_WARNING, "setUniform(GLuint, const char*, UniformType, GLsizei, const GLuint*) does not support matrices!\n");
        return false;
    }

    return true;
}