package main

import (
	"fmt"
	. "github.com/go-gl/mathgl/mgl64"
	. "github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
	"image/color"
	"log"
	"strings"
)

type Model struct {
	pos Vec2
}

func (g *Model) Update() error {
	if IsKeyPressed(KeyQ) {
		return Termination
	}
	var dir Vec2
	if IsKeyPressed(KeyD) {
		dir[0] += 1
	}
	if IsKeyPressed(KeyA) {
		dir[0] -= 1
	}
	if IsKeyPressed(KeyW) {
		dir[1] -= 1
	}
	if IsKeyPressed(KeyS) {
		dir[1] += 1
	}
	if dir.LenSqr() > 0 {
		g.pos = g.pos.Add(dir.Mul(10))
	}
	return nil
}

func (g *Model) Draw(screen *Image) {
	{
		rect := NewImage(100, 100)
		rect.Fill(color.RGBA{255, 0, 0, 255})
		op := &DrawImageOptions{}
		op.GeoM.Translate(g.pos[0], g.pos[1])
		op.ColorScale.ScaleAlpha(0.5)
		screen.DrawImage(rect, op)
	}
	w, h := Monitor().Size()
	lines := []string{
		"Use WASD keys to move the square.",
		fmt.Sprintf("Monitor size: %d x %d", w, h),
		fmt.Sprintf("FPS: %.2f", CurrentFPS()),
	}
	ebitenutil.DebugPrint(screen, strings.Join(lines, "\n"))
}

func (g *Model) Layout(outsideWidth, outsideHeight int) (int, int) {
	return outsideWidth, outsideHeight
}

func main() {
	w, h := Monitor().Size()
	game := &Model{pos: Vec2{100, 100}}
	SetWindowSize(w, h)
	SetWindowTitle("")
	SetFullscreen(true)
	if err := RunGame(game); err != nil {
		log.Fatal(err)
	}
}
