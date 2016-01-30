#version 330

uniform mat4 MVP;
uniform float r;

in vec3 vert;

void main() {
    gl_Position = MVP * vec4(vert * r, 1.0);
}
