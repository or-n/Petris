#version 100

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec4 vertexColor;

uniform vec2 blep;

varying vec4 fragColorInput;

void main() {
    float x = ((vertexPosition.x + blep.x) / 1920.0) * 2.0 - 1.0;
    float y = -(((vertexPosition.y + blep.y) / 1080.0) * 2.0 - 1.0);
    gl_Position = vec4(x, y, 0.0, 1.0);
    // gl_Position = vec4(vertexPosition, 1.0);
    fragColorInput = vertexColor;
}
