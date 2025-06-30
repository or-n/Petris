extends Node2D

const width = 10
const height = 22
const cell_scale = 40
const empty_color = Color.BLACK

var I = load_shape("shape/I.txt")
var J = load_shape("shape/J.txt")
var L = load_shape("shape/L.txt")
var O = load_shape("shape/O.txt")
var S = load_shape("shape/S.txt")
var T = load_shape("shape/T.txt")
var Z = load_shape("shape/Z.txt")

var timer
var score
var tetro
var tetro_pos
var grid : Array
var fullscreen = false

var sprites : Array
var block_shader := preload("res://cell.gdshader")
var block_texture := ImageTexture.create_from_image(Image.create(cell_scale, cell_scale, false, Image.FORMAT_RGBA8))

func create_block(x, y, color: Color):
	var sprite = Sprite2D.new()
	sprite.texture = block_texture
	var mat = ShaderMaterial.new()
	mat.shader = block_shader
	mat.set_shader_parameter("fill_color", color)
	sprite.material = mat
	sprite.position = Vector2(x, y) * cell_scale
	add_child(sprite)

func clear_game():
	score = 0
	timer = 0
	grid = []
	for y in range(height):
		var row = []
		for x in range(width):
			row.append(empty_color)
		grid.append(row)
	new_shape()

func create_sprites():
	sprites = []
	var screen_size = get_viewport_rect().size
	var s = cell_scale * screen_size[1] / 1080
	var offset = (screen_size - Vector2(width, height) * s) / 2
	for y in range(height):
		var row := []
		for x in range(width):
			var sprite := Sprite2D.new()
			sprite.texture = block_texture
			sprite.position = offset + Vector2(x + 0.5, y + 0.5) * cell_scale
			sprite.z_index = -1000
			var mat := ShaderMaterial.new()
			mat.shader = block_shader
			mat.set_shader_parameter("fill_color", grid[y][x])
			sprite.material = mat
			add_child(sprite)
			row.append(sprite)
		sprites.append(row)

func _ready():
	clear_game()
	create_sprites()
	var music = AudioStreamPlayer.new()
	add_child(music)
	music.stream = load("res://TetrisThemeDubstep.ogg")
	music.stream.loop = true
	music.play()

func random_color() -> Color:
	return Color(randf(), randf(), randf())
	
func _input(event):
	if event.is_action_pressed("fullscreen"):
		JavaScriptBridge.eval("document.getElementById('canvas').requestFullscreen();")
		if fullscreen:
			DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_WINDOWED)
		else:
			DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_MAXIMIZED)
		fullscreen = not fullscreen

func _unhandled_input(event):
	if event is InputEventScreenTouch or event is InputEventMouseButton:
		if event.pressed:
			_handle_press(event.position)
		else:
			_handle_release()

func _handle_press(pos: Vector2):
	var center = get_viewport().get_visible_rect().size / 2
	var direction = (pos - center).normalized()
	if abs(direction.x) > abs(direction.y):
		if direction.x < 0:
			Input.action_press("left")
		else:
			Input.action_press("right")
	else:
		if direction.y > 0:
			Input.action_press("speed_up")
		else:
			Input.action_press("rotate")

func _handle_release():
	Input.action_release("left")
	Input.action_release("right")
	Input.action_release("speed_up")
	Input.action_release("rotate")

func _process(delta):
	$Label.text = "Score: %d" % score
	if Input.is_action_just_pressed("quit"):
		get_tree().quit()
	print_shape(empty_color)
	if Input.is_action_just_pressed("rotate"):
		rotate_shape()
		if collides():
			rotate_shape()
			rotate_shape()
			rotate_shape()
	if Input.is_action_just_pressed("left"):
		tetro_pos[0] -= 1
		if collides():
			tetro_pos[0] += 1
	if Input.is_action_just_pressed("right"):
		tetro_pos[0] += 1
		if collides():
			tetro_pos[0] -= 1
	var reset_shape = false
	var delay = 0.05 if Input.is_action_pressed("speed_up") else 0.2
	timer += delta
	if timer > delay:
		timer = 0
		tetro_pos[1] += 1
		if collides():
			tetro_pos[1] -= 1
			reset_shape = true
	print_shape(tetro.color)
	if reset_shape:
		clear_lines()
		new_shape()
	queue_redraw()
	
func new_shape():
	tetro = [I, J, L, O, S, T, Z].pick_random().duplicate(true)
	tetro_pos = Vector2(width/2., 0)
	for i in range(0, randi_range(0, 3)):
		rotate_shape()
	if collides():
		clear_game()

func rotate_shape():
	for i in range(tetro.blocks.size()):
		var block = tetro.blocks[i]
		var new = tetro.center
		new[0] += -(block[1] - tetro.center[1])
		new[1] += block[0] - tetro.center[0]
		tetro.blocks[i] = new

func load_shape(file_path: String) -> Dictionary:
	var shape = {
		"blocks": [],
		"color": Color.WHITE,
		"center": Vector2.ZERO
	}
	var file = FileAccess.open(file_path, FileAccess.READ)
	if file == null:
		push_error("Failed to open tetromino file: " + file_path)
		return shape
	var line_count = int(file.get_line())
	for i in range(line_count):
		var parts = file.get_line().split(" ")
		var pos = Vector2(parts[0].to_int(), parts[1].to_int())
		shape["blocks"].append(pos)
	var rgb = file.get_line().split(" ")
	shape["color"] = Color8(rgb[0].to_int(), rgb[1].to_int(), rgb[2].to_int())
	var spawn = file.get_line().split(" ")
	shape["center"] = Vector2(spawn[0].to_int(), spawn[1].to_int())
	return shape
	
func print_shape(color):
	for block in tetro.blocks:
		var p = tetro_pos + block / 2
		grid[p[1]][p[0]] = color
		
func collides():
	for block in tetro.blocks:
		var p = tetro_pos + block / 2
		if not is_inside(p) or grid[p[1]][p[0]] != empty_color:
			return true
	return false

func is_inside(p):
	var x = p[0] >= 0 and p[0] < width
	var y = p[1] >= 0 and p[1] < height
	return x and y

func clear_lines():
	var current = height - 1
	for i in range(height):
		var y = height - 1 - i
		var all = true
		for x in range(width):
			if grid[y][x] == empty_color:
				all = false
				break
		if !all:
			for x in range(width):
				grid[current][x] = grid[y][x]
			current -= 1
			continue
		for x in range(width):
			grid[y][x] = empty_color
		score += 1

func _draw():
	var screen_size = get_viewport_rect().size
	var s = cell_scale * screen_size[1] / 1080
	var offset = (screen_size - Vector2(width, height) * s) / 2
	var rect = Rect2(offset, Vector2(width, height) * s)
	draw_rect(rect, Color.WHITE, false)
	for y in range(height):
		for x in range(width):
			var color = grid[y][x]
			#var rect_pos = offset + Vector2(x, y) * s
			#var rect = Rect2(rect_pos, Vector2(s, s))
			#draw_rect(rect, color)
			#draw_rect(rect, Color.BLACK, false)
			var sprite = sprites[y][x]
			sprite.position = offset + Vector2(x + 0.5, y + 0.5) * s
			sprite.scale = Vector2(1, 1) * screen_size[1] / 1080
			var mat = sprite.material as ShaderMaterial
			mat.set_shader_parameter("fill_color", color)
