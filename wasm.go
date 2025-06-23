package main

import (
	"embed"
	"syscall/js"
)

func isTabFocused() bool {
	document := js.Global().Get("document")
	if !document.Truthy() {
		return false
	}
	hasFocus := document.Call("hasFocus")
	return hasFocus.Bool()
}

func viewportSize() (width, height int) {
	window := js.Global().Get("window")
	width = window.Get("innerWidth").Int()
	height = window.Get("innerHeight").Int()
	return
}

var (
	//go:embed asset
	ASSETS embed.FS
)
