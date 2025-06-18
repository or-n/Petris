package main

import (
	. "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	InitAudioDevice()
	music := LoadMusicStream("asset/TetrisThemeDubstep.ogg")
	PlayMusicStream(music)
	InitWindow(1920, 1080, "")
	defer CloseWindow()
	ToggleBorderlessWindowed()
	SetTargetFPS(600)
	ShapeInit()
	GameInit()
	for !WindowShouldClose() {
		UpdateMusicStream(music)
		GameUpdate()
		BeginDrawing()
		ClearBackground(Blank)
		GameDraw()
		EndDrawing()
	}
}
