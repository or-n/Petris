#version 450 core

in vec4 pos;
in vec4 color;
in vec2 blockPos;
in vec2 blockSize;

out vec4 color_;

void main() {
	float x = min(abs(pos.x - blockPos.x - blockSize.x), abs(pos.x - blockPos.x + blockSize.x));
	float y = min(abs(pos.y - blockPos.y - blockSize.y), abs(pos.y - blockPos.y + blockSize.y));
	x /= blockSize.x;
	y /= blockSize.y;
	float tmpX = abs(pos.x - blockPos.x) * blockSize.y;
	float tmpY = abs(pos.y - blockPos.y) * blockSize.x;
	int up = 0, down = 1, left = 2, right = 3, nr = right;
	if(pos.y >= blockPos.y && tmpX <= tmpY)
		nr = up;
	else if(pos.y <= blockPos.y && tmpX <= tmpY)
		nr = down;
	else if(pos.x <= blockPos.x && tmpX >= tmpY)
		nr = left;
	color_ = color;
	if(nr == up)
		color_.rgb -= ((pos.y - blockPos.y) / blockSize.y) / 2 / 8;
	else if(nr == down)
		color_.rgb -= ((blockPos.y - pos.y) / blockSize.y) / 2;
	else
		color_.rgb -= .125 + (pos.y + blockSize.y - blockPos.y) / blockSize.y / 2 / 4;
	if(min(x, y) <= 5.0/12)
		color_.rgb *= max(.2, 2*min(x, y));
	else
		color_ = color;
} 