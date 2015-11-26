#version 410

uniform vec3 camPos;
in vec3 pos;
out vec3 color;

void main() {
    float colornum = distance(camPos, pos) / 12.0;
    color = vec3(colornum, colornum, colornum);
}
