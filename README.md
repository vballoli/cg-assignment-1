# Computer Graphics Assignment 1

This repository contains code to IS F311 Computer Graphics assignment 1
using OpenGL and GLUT libraries in C.

## Requirements

OpenGL: GL/glut.h
Math: math.h

Linux: ` sudo apt-get install freeglut3-dev doxygen`.

Mac: `Import GL through XCode binaries`.

## Run
### Run project

~: `bash run.sh`

### Run individual files

~: `gcc file.c -lGL -lGLU -lglut`

(if includes math.h)

~: `gcc file.c -lm -lGL -lGLU -lglut`

### Open documentation

Linux-only: `bash doc.sh`

## Files

1. algorithms.c - Implements Midpoint Line algorithm and Midpoint Circle algorithm.
2. fractals.c - Implements fractal using a recursive funtion and above algorithms.
3. html/index.html - Base documentation generated using Doxygen.
4. Doxyfile - Config file for generating documentation from comments of methods. Required for Doxygen

## Documentation

Auto-generated using Doxygen.

Build documentation: Run ~: `doxygen Doxyfile`

HTML Documentation Location: `html/index.html`

LaTex Documentation Location:  `latex/`

## Contribution Guidelines

1. Write docstrings in the Javadoc format as set in the Doxyfile config.
2. Store images in result folder.
