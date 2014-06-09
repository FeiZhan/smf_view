smf_view
========

#### A Mesh Viewer for SMF format

### Features

- Display a mesh in openGL;
- A display box in which a mesh can be shown flat shaded, smooth shaded, in wireframe, or shaded with mesh edges displayed, as shown below;
- Allow rotation, zooming, and translation;
- Allow input from and output to a mesh file in SMF;
- A “Quit” button to exit from the GUI;
- Input a triangle mesh given in SMF format and store the connectivity and geometric information in an appropriate data structure, and isplay the mesh in the display box of your GUI;

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
