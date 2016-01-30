#version 330

in vec2 screenPos;

void main() {
    gl_Position = vec4(screenPos, -1.0, 1.0);
}
