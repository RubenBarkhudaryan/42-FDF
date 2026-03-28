# 42 FDF

## Overview
FDF renders a 3D wireframe representation of landscapes from height maps.

The program parses map files and displays them with interactive controls using MiniLibX.

Even though the output is a wireframe, this project introduces a complete mini graphics pipeline:
- parse model data
- transform vertices in virtual 3D space
- project to 2D screen coordinates
- draw lines with color logic
- react to user input in real time

## Features
- Height map parsing and validation
- 3D to 2D projection rendering
- Rotation and translation controls
- Zoom in/out
- Color handling and gradients
- Multiple projection views
- Error handling for invalid maps/files

## Core Concepts

### Height Map to Geometry
Input files describe terrain elevation by grid points. Each point becomes a vertex, and neighboring points are connected to form the wireframe mesh.

### Transformations
Before drawing, points are transformed using operations like:
- translation (move scene)
- scaling (zoom)
- rotation (change orientation)

These transformations are applied mathematically so the same model can be viewed from multiple angles.

### Projection
3D coordinates are mapped into 2D screen space. Different projection styles give different visual interpretations of the same data.

### Event-Driven Interaction
Keyboard hooks let the user manipulate the rendered scene without restarting the program.

## Build
- make

## Run
- ./fdf test_maps/42.fdf

## Controls
- Move: arrows or WASD
- Zoom: plus / minus
- Rotation axes: 1 2 3
- Projections: i, t, r, f
- Random color: c

## Input Format Notes
Each map line represents one row of points.
Each token represents height (and optionally color, depending on parser support).

Robust parsing is essential because malformed maps can break geometry assumptions.

## Project Structure
- includes: helper headers and utility includes
- mlx: MiniLibX integration
- test_maps: sample maps
- core C files: parser, validator, draw, transform, input handling

Rendering responsibilities are typically split into:
- parser/validator
- coordinate transformation
- line drawing and color interpolation
- event handling

## Key Learnings
- Graphics programming fundamentals
- Coordinate transformations and projections
- Event-driven input handling
- Defensive parsing and memory management

## Notes
This is a foundational graphics project at 42 and an important step toward larger MLX projects.
