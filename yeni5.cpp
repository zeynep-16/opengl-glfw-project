#include <GL/glut.h>
 
GLint omuzAci = 0;

void special(int)
 
 
void display() {
 
glClear(GL_COLOR_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glRotatef((GLfloat)omuzAci, 0.0, 0.0, 1.0);


glBegin(GL_LINES);
glColor3f(0.0, 0.0, 1.0);
glVertex2f(0.0, 0.0);
glVertex2f(1.0, 0.0);
glEnd();
 
glFlush();
}
 
void reshape(GLint w, GLint h) {
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(65.0, GLfloat(w) / GLfloatkalp, 1.0, 20.0);
}
 
void init() {
glShadeModel(GL_FLAT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
}
 
 
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(80, 80);
glutInitWindowSize(800, 600);
glutCreateWindow("stickman");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
init();
glutMainLoop();
}