package main

import (
	"fmt"
	. "github.com/gen2brain/raylib-go/raylib"
	// "os"
	"slices"
	"strconv"
	"strings"
)

type Shape struct {
	Points []Vector2
	Color  Color
	Origin Vector2
}

var (
	I, J, L, O, S, T, Z Shape
)

func ShapeInit() {
	I.LoadShapeHandleError("asset/I")
	J.LoadShapeHandleError("asset/J")
	L.LoadShapeHandleError("asset/L")
	O.LoadShapeHandleError("asset/O")
	S.LoadShapeHandleError("asset/S")
	T.LoadShapeHandleError("asset/T")
	Z.LoadShapeHandleError("asset/Z")
}

func (s Shape) Clone() Shape {
	new := s
	new.Points = slices.Clone(s.Points)
	return new
}

func (s *Shape) LoadShapeHandleError(path string) {
	err := s.LoadShape(path)
	if err != nil {
		fmt.Println(path, err)
	} else {
		fmt.Println(path, *s)
	}
}

func (s *Shape) LoadShape(path string) error {
	// data, err := os.ReadFile(path)
	data, err := ASSETS.ReadFile(path)
	if err != nil {
		return err
	}
	lines := strings.Split(strings.TrimSpace(string(data)), "\n")
	n, _ := strconv.Atoi(lines[0])
	for i := range n {
		parts := strings.Fields(lines[1+i])
		x, _ := strconv.Atoi(parts[0])
		y, _ := strconv.Atoi(parts[1])
		s.Points = append(s.Points, NewVector2(float32(x), float32(y)))
	}
	rgb := strings.Fields(lines[1+n])
	r, _ := strconv.Atoi(rgb[0])
	g, _ := strconv.Atoi(rgb[1])
	b, _ := strconv.Atoi(rgb[2])
	s.Color = NewColor(uint8(r), uint8(g), uint8(b), 255)
	originParts := strings.Fields(lines[2+n])
	ox, _ := strconv.Atoi(originParts[0])
	oy, _ := strconv.Atoi(originParts[1])
	s.Origin = NewVector2(float32(ox), float32(oy))
	return nil
}

func (s *Shape) RotateRight() {
	for i, p := range s.Points {
		new := s.Origin
		new.X += -(p.Y - s.Origin.Y)
		new.Y += p.X - s.Origin.X
		s.Points[i] = new
	}
}
