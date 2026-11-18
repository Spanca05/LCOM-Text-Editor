# Text Editor for Minix

A text editor running on Minix 3, built on top of device drivers written from scratch in C. Developed for the Computer Laboratory (LCOM) course at FEUP (University of Porto), 2024/2025.

## Features
- **Graphics (VBE):** graphics mode setup, video memory mapping and **double buffering** for flicker-free rendering
- **Text rendering:** bitmap fonts (16×32) to draw characters and strings directly to the framebuffer, with a header and a footer showing the cursor position
- **Text buffer:** character insertion and deletion with cursor movement
- **Interrupt-driven input:** keyboard (i8042) and timer (i8254) handled through interrupts
- **Error handling:** every driver returns a typed `Result` with specific error codes

## Structure
`src/drivers` (timer, keyboard, KBC, mouse, graphics) · `src/graphics` (fonts, text and buffer rendering) · `src/model` (text buffer, lines, cursor) · `src/utils`

## Build and run
Inside the LCOM Minix virtual machine:
```bash
make
lcom_run proj
```

## Authors
Vasco Vieira · Cláudio Meireles · Leonardo Carvalho · Frederica Pereira
