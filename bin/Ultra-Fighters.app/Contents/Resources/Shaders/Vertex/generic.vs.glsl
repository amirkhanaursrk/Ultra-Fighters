#version 330

uniform mat4 MVP = mat4(1.0);

in vec3 vert;

void main() {
    gl_Position = MVP * vec4(vert, 1.0);
}
