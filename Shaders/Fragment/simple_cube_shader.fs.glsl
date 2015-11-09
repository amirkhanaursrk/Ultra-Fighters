#version 410

uniform vec3 camPos;
in vec3 pos;
out vec3 color;

void main() {
    float colornum = distance(camPos, pos) / 2.0;
    color = vec3(colornum, colornum, colornum);
}
