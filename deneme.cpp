#include <math.h>
#include <gl/glut.h>
 
GLfloat angle = 0.0;
GLfloat red = 0.0, blue = 0.0, green = 0.0;
 
void BoyutDegis(int w, int h) {
 
if (h == 0)
h = 1;
 
GLfloat ratio = 1.0 * w / h;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
 
glViewport(0, 0, w, h);
gluPerspective(45, ratio, 1, 10);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}
 
void displayFunc(void) {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
 
glPushMatrix();
 
glRotatef(angle, 0.0, 1.0, 0.0);
glColor3f(red, green, blue);
glBegin(GL_TRIANGLES);
glColor3f(red, green, blue);
glVertex3f(-0.5, -0.5, 0.0);
glColor3f(1.0, 0.0, 0.0);
glVertex3f(0.5, 0.0, 0.0);
glColor3f(0.0, 1.0, 0.0);
glVertex3f(0.0, 0.5, 0.0);
glEnd();
glPopMatrix();
angle = angle + 0.05;
glutSwapBuffers();
}
 
void main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100, 100);
glutInitWindowSize(320, 320);
glutCreateWindow("Dönen Üçgen");
glutDisplayFunc(displayFunc);
glutIdleFunc(displayFunc);
glutReshapeFunc(BoyutDegis);
glEnable(GL_DEPTH_TEST);
glutMainLoop();
}