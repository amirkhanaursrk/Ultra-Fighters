#version 330

uniform vec3 camPos;
in vec3 pos;
out vec3 color;

void main() {
    float colornum = 1.5 * 0.5 / sqrt(distance(camPos, pos));
    color = vec3(colornum, colornum, colornum);
}
