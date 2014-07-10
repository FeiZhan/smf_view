mcaq
========

#### A Mesh Viewer for SMF format

github: https://github.com/FeiZhan/smf_view

### Features

- All features required are implemented;
- Implemented a mesh decimation algorithm driven by the quadric-based errors, where the outer optimization is implemented using the multiple choice scheme;
- Selected the edge collapse amongst k randomly chosen candidate edges which gives the least quadric error;
- Found the best vertex location which minimizes the quadric error;
- Each vertex stores a sum of quadrics of the supporting planes of its incident triangles;
- Added a text field for selecting the value k, a text field to specify the percentage of edges to collapse, and a button labeled “Decimate” which when pressed will decimation;
- Allow to output the current mesh obtained by writing it into an SMF file;

### Usage

Execute:
```
$ ./mcaq
```
Complie:
```
$ cmake .
$ make
```

### Notice

- Instead of specifying the number of edges to collapse, I designed to specify the percentage of edges to collapse, which is compatible with meshes with different number of edges;
- In order to compile, don't forget "cmake .";
- To open or save to a file, please specify a filename without path and extension in the textbox. Don't use a file name which is too long. To test opening a file, you could try "cube", "eight", "sphere", "horse" (without quote or .smf).

### Claim

I have read and understood the policy concerning collaboration on assignments.

I have had discussions with the following fellow students
- Rao Fu;
- Ziyang Zhao;
- Shuai Wu.

I have consulted the following outside sources
- Surface Simpliﬁcation Using Quadric Error Metrics
- Fast Mesh Decimation by Multiple-Choice Techniques;
- Inverse matrix of 2-by-2 matrix, 3-by-3 matrix, 4-by-4 matrix (http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html)
- Calculates the plane equation given three points (http://keisan.casio.com/has10/SpecExec.cgi?id=system/2006/1223596129)

### Files

- main.cpp							main entrance
- MeshGui.h, MeshGui.cpp			OpenGL and GLUI setup
- SmfModel.h, SmfModel.cpp			SMF file input and output, data structure for vertices, edges, and faces
- Subdivision.h, Subdivision.cpp	attempt for the bonus problem
- Decimator.h, Decimator.cpp		decimation algorithm

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
