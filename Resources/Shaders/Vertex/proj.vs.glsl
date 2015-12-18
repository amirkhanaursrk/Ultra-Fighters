#version 330

uniform vec3 pos;
uniform mat4 MVP;

in vec3 vert;

void main() {
    gl_Position = MVP * vec4(vert + pos, 1.0);
}
