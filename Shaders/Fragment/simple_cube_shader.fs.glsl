#version 410

uniform vec3 camPos;
in vec3 pos;
out vec3 color;

void main() {
    color = vec3(distance(camPos, pos) / 4.0, 0.0, 0.0);
}
