#version 100

precision mediump float;

varying vec4 fragColorInput;

void main() {
    gl_FragColor = fragColorInput;
}
