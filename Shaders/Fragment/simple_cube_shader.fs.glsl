#version 410

uniform vec3 camPos;
in vec3 pos;
out vec3 color;

void main() {
    float cnum = distance(camPos.xy, pos.xy);
    cnum *= cnum;
    cnum /= 2;
    color = vec3(cnum, cnum, cnum);
}
