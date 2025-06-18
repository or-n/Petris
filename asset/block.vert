#version 300 es
  
layout (location = 0) in vec3 _pos;

out vec4 color;
out vec2 blockPos;
out vec2 blockSize;

out vec4 pos;

uniform vec4 _color;
uniform vec2 _blockPos;
uniform vec2 _blockSize;

void main() {
	color = _color;
	blockPos = _blockPos;
	blockSize = _blockSize;
	
	gl_Position = vec4(_pos.x * _blockSize.x, _pos.y * _blockSize.y, _pos.z, 1.0);
	gl_Position.xy += _blockPos;
	pos = gl_Position;
}