#pragma once

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <GL/glui.h>

class MeshGui
{
public:
	int run(void);
private:
	int initGlui(void);
};

extern int main_window;
void myGlutDisplay(void);
void myGlutReshape(int x, int y);
void myGlutKeyboard(unsigned char Key, int x, int y);
void myGlutMouse(int button, int button_state, int x, int y);
void myGlutMotion(int x, int y);
void myGlutMenu(int value);
void myGlutIdle(void);
