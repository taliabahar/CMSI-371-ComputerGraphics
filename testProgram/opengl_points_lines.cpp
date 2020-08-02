#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

class Vertex {
  GLfloat x, y;

 public:
  Vertex(GLfloat, GLfloat);
  GLfloat get_y() { return y; };
  GLfloat get_x() { return x; };
};

Vertex::Vertex(GLfloat X, GLfloat Y) {
  x = X;
  y = Y;
}

void setup() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void display() {
  // Vertex test;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Set our color to black (R, G, B)
  glColor3f(0.0f, 0.0f, 0.0f);
  // Draw 4 points with coordinates (x, y) counter-clockwise
  // (0.5, 0.5), (-0.5, 0.5), (-0.5f, -0.5f) (0.5f, -0.5f)
  // Note if we want clockwise then add: glFrontFace(GL_CW)
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glVertex2f(0.5f, 0.5f);
  glVertex2f(-0.5f, 0.5f);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glEnd();
  // Draw 2 lines from
  // (0.5, 0.5) to (-0.5, 0.5) and (-0.5f, -0.5f) to (0.5f, -0.5f)
  glBegin(GL_LINES);
  // First line
  glVertex2f(0.5f, 0.5f);
  glVertex2f(-0.5f, 0.5f);
  // Second line
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glEnd();
  glutSwapBuffers();
}
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Points and Lines");
  setup();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}