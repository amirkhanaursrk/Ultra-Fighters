#version 330

uniform mat4 MVP;

in vec3 vert;

void main() {
    gl_Position = MVP * vec4(vert, 1.0);
}
