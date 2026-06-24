# Tucil2_13524090_13524093
# 3D to Voxel Converter

![Logo](cover.png)

# Program Description

Have you ever looked at an object and imagined what it would look like if it were built inside Minecraft? This program does exactly that automatically!

The program converts a standard 3D model (with smooth surfaces made of triangles) into a structure composed of 3D blocks. This transformation process is known as **Voxelization**.

This program implements voxelization for 3D models in OBJ format using a divide-and-conquer approach based on an octree.

* **Voxel (Volumetric Pixel):** If a 2D image on your phone screen is made up of colored dots called *pixels*, then a 3D shape can be represented by cubes called *voxels*. Simply put, a voxel is equivalent to a building block in Minecraft.

* **Octree & Divide and Conquer (A Smart Way to Build):** To determine where blocks should be placed, the program does not blindly inspect the entire space. Instead, it uses a clever data structure called an **Octree** (an 8-way tree):

  1. The program creates one **large bounding box** that encloses the entire 3D object.
  2. The bounding box is then **subdivided into 8 smaller boxes**.
  3. Any box that is completely empty is immediately discarded.
  4. If a box intersects part of the 3D object, it is subdivided again into 8 smaller boxes. This process continues until the boxes reach the desired Minecraft block size.

In general, the program workflow is:

1. Read the triangle mesh from an OBJ file (vertices and faces).
2. Compute the model's bounding box.
3. Recursively build the octree up to a specified maximum depth.
4. Determine which octree nodes represent valid voxels.
5. Export the voxelized result as a new OBJ file.

# Requirements

This program requires:

1. Linux, macOS, or Windows operating system.
2. A C++ compiler with C++17 support (e.g., g++).
3. GNU Make (recommended).

Verify the required tools:

```bash
g++ --version
make --version
```

# Compilation

The program uses a Makefile. From the project root directory, run:

```bash
make
```

This command will:

1. Create the `bin` folder if it does not already exist.
2. Compile all source files in the `src` directory.
3. Generate the executable:

```bash
bin/voxelizer.exe
```

To clean build artifacts:

```bash
make clean
```

# Running the Program

Command format:

```bash
bin/voxelizer.exe <input.obj> <maxDepth>
```

Parameter description:

1. `input.obj`: Path to the input OBJ file.
2. `maxDepth`: Maximum octree depth (integer from 1 to 20).

Examples:

```bash
bin/voxelizer.exe test/cow.obj 15
bin/voxelizer.exe test/pumpkin.obj 9
bin/voxelizer.exe test/teapot.obj 8
```

# Running the GUI Viewer

The project also includes a simple viewer for interactively visualizing OBJ files.

Additional requirements:

1. SFML library (graphics, window, system).
2. `pkg-config` for SFML detection during build.

Example installation on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install -y libsfml-dev pkg-config
```

Build the viewer:

```bash
make viewer
```

If SFML is detected, the viewer executable will be generated at:

```bash
bin/viewer.exe
```

Run the viewer:

```bash
bin/viewer.exe <obj-file>
```

Examples:

```bash
bin/viewer.exe test/cube.obj
bin/viewer.exe test/cube-voxelized-4.obj
```

Viewer controls:

1. Click and drag the mouse to rotate the object.
2. Use the mouse wheel to zoom in or out.
3. Close the window to exit.

Notes:

1. `make` will attempt to build both `bin/voxelizer.exe` and `bin/viewer.exe`.
2. If SFML is not installed, the viewer build step is automatically skipped.
3. The viewer accepts direct file paths and will also search in the `test/` folder if the provided path cannot be found.

# Supported Input Format

Input files must be in OBJ format with the following assumptions:

1. Faces are triangles (each `f` line contains exactly 3 indices).
2. Face indices are positive and valid with respect to the number of vertices.
3. Prefixes other than `v` and `f` may be ignored by the parser.

# Output

The program generates:

1. A voxelized OBJ file with the naming pattern:

```text
<input-file-name>-voxelized-<depth>.obj
```

2. Terminal statistics, including:

   * Number of voxels
   * Number of output vertices and faces
   * Octree node statistics
   * Processing time

# Directory Structure

```text
Tucil2_13524090_13524093/
├── src/              # main source code
├── bin/              # compiled executables
├── test/             # OBJ test files and outputs
├── doc/              # project report
├── makefile          # build and clean instructions
└── README.md
```

# Technology Stack

1. Language: C++17
2. Compiler: g++
3. Build Tool: GNU Make
4. Approach: Octree-based voxelization (divide and conquer)

# Authors

1. Nashiruddin Akram — 13524090
2. Reinsen Silitonga — 13524093


---

Tugas Kecil 2 - IF2211 Strategi Algoritma  
Semester Genap Tahun 2025/2026
