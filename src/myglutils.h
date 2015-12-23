#pragma once

#if defined(__WIN32__) && !defined(GLEW_STATIC)
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

int setupGLFW();
int setupGLEW();
void setupCoreGL();

#define TRI_RECT_SIZE (108 * sizeof(float))
#define TRI_RECT_VERTS 36

GLchar* shaderError(GLuint shader);
GLchar* programError(GLuint program);
GLuint getProgram(const char* vs, const char* fs);
GLuint getProgramFromFiles(const char* vsFileName, const char* fsFileName);
GLuint loadBMP(const char* fileName);
int loadWavefront1(const char* fileName, float** vertexBuffer, int* length);
float* getTriangulatedRect(float width, float height, float depth);

#ifdef __cplusplus
}
#endif
