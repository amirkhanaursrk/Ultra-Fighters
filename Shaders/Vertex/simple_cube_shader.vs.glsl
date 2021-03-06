#version 410

uniform mat4 MVP;
in vec3 in_pos;
out vec3 pos;

void main() {
    gl_Position = MVP * vec4(in_pos, 1.0);
    pos = in_pos;
}
