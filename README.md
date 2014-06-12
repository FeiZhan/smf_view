smf_view
========

#### A Mesh Viewer for SMF format

github: https://github.com/FeiZhan/smf_view

### Features

- All features required are implemented;
- Display a mesh in openGL;
- A display box in which a mesh can be shown flat shaded, smooth shaded, in wireframe, or shaded with mesh edges displayed;
- Allow rotation, zooming, and translation;
- Allow input from and output to a mesh file in SMF;
- A “Quit” button to exit from the GUI;
- Input a triangle mesh given in SMF format and store the connectivity and geometric information in an appropriate data structure, and display the mesh in the display box of the GUI.

### Usage

Execute:
```
$ ./smf_view
```
Complie:
```
$ cmake .
$ make
```

### Notice

- In order to compile, don't forget "cmake .";
- To open or save to a file, please specify a filename without path and extension in the textbox. Don't use a file name which is too long. To test opening a file, you could try "cube", "eight", "sphere", "horse" (without quote or .smf).

### Claim

I have read and understood the policy concerning collaboration on assignments.

I have had discussions with the following fellow students
- Rao Fu;
- Ziyang Zhao.

I have consulted the following outside sources
- GLUI example 5;
- Mepp https://github.com/MEPP-team/MEPP

### Files

- main.cpp							main entrance
- MeshGui.h, MeshGui.cpp			OpenGL and GLUI setup
- SmfModel.h, SmfModel.cpp			SMF file input and output, data structure for vertices, edges, and faces
- Subdivision.h, Subdivision.cpp	attempt for the bonus problem

### Dependencies

- OpenGL
- GLUT
- GLUI
- make
- cmake

### License

smf_view is released with a BSD license. For full terms and conditions, see the [LICENSE](LICENSE) file.

### Authors

Fei Zhan (Simon Fraser University)
