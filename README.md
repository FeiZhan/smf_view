smf_view
========

#### A Mesh Viewer for SMF format

### Features

- Display a mesh in openGL;
- A display box in which a mesh can be shown flat shaded, smooth shaded, in wireframe, or shaded with mesh edges displayed, as shown below;
- Allow rotation, zooming, and translation;
- Allow input from and output to a mesh file in SMF;
- A “Quit” button to exit from the GUI;
- Input a triangle mesh given in SMF format and store the connectivity and geometric information in an appropriate data structure, and display the mesh in the display box of the GUI;

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

### Files

main.cpp						main entrance
MeshGui.h, MeshGui.cpp			OpenGL and GLUI setup
SmfModel.h, SmfModel.cpp		SMF file input and output, data structure for vertices, edges, and faces
Subdivision.h, Subdivision.cpp	attempt for the bonus problem

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
