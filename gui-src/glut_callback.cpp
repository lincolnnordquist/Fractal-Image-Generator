#include "glut_app.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display_cb(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  g_app_data->display();
  glutSwapBuffers();
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard_cb(unsigned char c, int x, int y) {
  (void)x;
  (void)y;
  bool post_redisplay = g_app_data->keyboard(c);
  if(post_redisplay) {
    glutPostRedisplay(); // tell glut to call display() as soon as possible.
  }
}

void special_cb(int c, int x, int y) {
  (void)x;
  (void)y;
  bool post_redisplay = g_app_data->special(c);
  if(post_redisplay) {
    glutPostRedisplay(); // tell glut to call display() as soon as possible.
  }
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape_cb(int w, int h) {
  // Reset our global variables to the new width and height.
  g_app_data->setSize(h, w);

  // all of the gl*() function calls below are part of the openGL
  // library, not our code.

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse_cb(int mouse_button, int state, int x, int y) {
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = g_app_data->getHeight() - y;
  bool post_redisplay = g_app_data->mouse(mouse_button, state, xdisplay, ydisplay);
  if(post_redisplay) {
    glutPostRedisplay();
  }
}
