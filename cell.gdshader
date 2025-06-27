shader_type canvas_item;

uniform vec4 fill_color : source_color;
uniform float border_width = 0.2;

void fragment() {
	vec2 uv = UV;
	float top = uv.y;
	float bottom = 1.0 - uv.y;
	float left = uv.x;
	float right = 1.0 - uv.x;
	float min_dist = min(min(top, bottom), min(left, right));
	vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
	if (min_dist < border_width && fill_color != black) {
		if (min_dist == top) {
			COLOR = mix(fill_color, white, 0.2);
		} else if (min_dist == bottom) {
			COLOR = mix(fill_color, black, 0.2);
		} else if (min_dist == left) {
			COLOR = mix(fill_color, white, 0.1);
		} else if (min_dist == right) {
			vec4 start = mix(fill_color, black, 0.1);
			vec4 end = mix(fill_color, black, 0.1);
			COLOR = mix(start, end, uv.y);
		}
	} else {
		COLOR = fill_color;
	}
}