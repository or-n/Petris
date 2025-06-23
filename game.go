package main

import (
	. "github.com/gen2brain/raylib-go/raylib"
	"strconv"
)

var (
	screen Vector2
	width  = 10
	height = 22
	grid   = make([][]Color, height)
	cx, cy int
	shape  Shape
	clock  = float32(0)
	score  int
)

func GameInit() {
	screen = NewVector2(float32(GetScreenWidth()), float32(GetScreenHeight()))
	for y := range height {
		grid[y] = make([]Color, width)
		for x := range width {
			grid[y][x].A = 255
		}
	}
	newShape()
}

func GameClear() {
	score = 0
	for y := range height {
		grid[y] = make([]Color, width)
		for x := range width {
			grid[y][x] = Black
		}
	}
	newShape()
}

func clearLines() {
	var current = height - 1
	for i := range height {
		y := height - 1 - i
		var all = true
		for x := range width {
			if grid[y][x] == Black {
				all = false
			}
		}
		if !all {
			for x := range width {
				grid[current][x] = grid[y][x]
			}
			current -= 1
			continue
		}
		for x := range width {
			grid[y][x] = Black
		}
		score += 1
	}
}

func newShape() {
	switch GetRandomValue(0, 6) {
	case 0:
		shape = I.Clone()
	case 1:
		shape = J.Clone()
	case 2:
		shape = L.Clone()
	case 3:
		shape = O.Clone()
	case 4:
		shape = S.Clone()
	case 5:
		shape = T.Clone()
	case 6:
		shape = Z.Clone()
	}
	cx, cy = width/2, 0
	if collides(cx, cy) {
		GameClear()
	} else {
		print(shape.Color)
	}
}

func GameDraw() {
	v := screen.Y / 108
	s := NewVector2(4*v, 4*v)
	gs := NewVector2(float32(width)*s.X, float32(height)*s.Y)
	min := Vector2Scale(Vector2Subtract(screen, gs), 0.5)
	pad := NewVector2(v, v)
	minPad := Vector2Subtract(min, pad)
	gsPad := Vector2Add(gs, Vector2Scale(pad, 2))
	DrawRectangleV(minPad, gsPad, White)
	for y := range height {
		for x := range width {
			p := NewVector2(float32(x)*s.X, float32(y)*s.Y)
			DrawRectangleV(Vector2Add(p, min), s, grid[y][x])
		}
	}
	DrawText(strconv.Itoa(score), int32(screen.X/4), int32(screen.Y/2), 40, Green)
}

func GameUpdate() {
	var resetShape bool
	print(Black)
	{
		var delay float32
		if IsKeyDown(KeyS) {
			delay = 0.05
		} else {
			delay = 0.2
		}
		clock += GetFrameTime()
		if clock >= delay {
			clock = 0
			if collides(cx, cy+1) {
				resetShape = true
			} else {
				cy += 1
			}
		}
	}
	if IsKeyPressed(KeyW) {
		shape.RotateRight()
		if collides(cx, cy) {
			shape.RotateRight()
			shape.RotateRight()
			shape.RotateRight()
		}
	}
	{
		if IsKeyPressed(KeyA) && !collides(cx-1, cy) {
			cx -= 1
		}
		if IsKeyPressed(KeyD) && !collides(cx+1, cy) {
			cx += 1
		}
	}
	print(shape.Color)
	if resetShape {
		clearLines()
		newShape()
	}
}

func print(c Color) {
	for _, p := range shape.Points {
		y := cy + int(p.Y)/2
		x := cx + int(p.X)/2
		grid[y][x] = c
	}
}

func collides(cx, cy int) bool {
	for _, p := range shape.Points {
		y := cy + int(p.Y)/2
		x := cx + int(p.X)/2
		if !inside(x, y) || grid[y][x] != Black {
			return true
		}
	}
	return false
}

func inside(x, y int) bool {
	return x >= 0 && x < width && y >= 0 && y < height
}
