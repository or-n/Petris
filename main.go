package main

import (
	"fmt"
	. "github.com/gen2brain/raylib-go/raylib"
)

var (
	music  Music
	shader Shader
	offset int32
	update = func() {
		UpdateMusicStream(music)
		GameUpdate()
		BeginDrawing()
		ClearBackground(Blank)
		GameDraw()
		BeginShaderMode(shader)
		EndShaderMode()
		EndDrawing()
	}
)

func main() {
	AddFileSystem(ASSETS)
	InitWindow(1920, 1080, "")
	InitAudioDevice()
	music = LoadMusicStream("asset/TetrisThemeDubstep.ogg")
	PlayMusicStream(music)
	defer CloseWindow()
	// ToggleBorderlessWindowed()
	SetTargetFPS(600)
	ShapeInit()
	GameInit()
	shader = LoadShader("asset/block.vert", "asset/block.frag")
	offset = GetShaderLocation(shader, "blep")
	fmt.Println("offset: ", offset)
	// SetShaderValue(shader, 0, []float32{200.0, 200.0}, ShaderUniformVec2)
	SetMainLoop(update)
	for !WindowShouldClose() {
		update()
	}
}
