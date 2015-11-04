#version 410

in vec2 pos;
out vec4 color;

void main() {
    color = noise4(pos.x * pos.y);
    color.z = 1.0;
}
