# CS 330 Module Three (3-2 Assignment) — 3D Scene Replication (Basic Shapes)

## Overview
This project is part of SNHU’s CS 330 (Computational Graphics and Visualization).  
In Module Three’s 3-2 Assignment, the objective is to build a simple **3D scene** by placing and transforming basic 3D meshes (ex: boxes, cylinders, cones, spheres, pyramids) to match one of the provided 2D reference scenes.

The starter project renders two planes (background + floor). I expanded the scene by adding and transforming additional 3D shapes using translation, rotation, and scaling.

## What This Program Does
- Renders a basic 3D environment with:
  - A floor plane
  - A background plane
- Adds multiple 3D primitives into the scene
- Uses transformations to match the chosen 2D layout:
  - Scale (size)
  - Rotate (orientation)
  - Translate (position)
- Applies colors to improve visual clarity

## Key Concepts Demonstrated
- 3D transformations and matrix ordering
- Scene composition using multiple objects
- Rendering basic OpenGL meshes (plane, box, cylinder, cone, sphere, pyramid)
- Iterative tuning of scale/rotation/translation to match a reference

## Files Updated
- `SceneManager.cpp`
  - `SceneManager::RenderScene()` — added shapes and transformations to replicate the selected 2D scene.

## How to Build and Run
1. Open the `.sln` file in **Visual Studio 2022**
2. Use the project’s required configuration (commonly **Debug** / **x86**)
3. Build and run:
   - **Build:** `Ctrl + Shift + B`
   - **Run:** `F5`

## Notes
- The colors do not need to exactly match the reference image, but the **scale, position, and orientation** of the shapes should closely resemble the selected 2D scene.
- This project is based on the provided CS330Content preconfigured Visual Studio solution.

## Author
Kevin Simmons  
CS 330 — SNHU
