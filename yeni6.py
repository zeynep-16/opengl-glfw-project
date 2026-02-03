----------------------hatalı

#include <GL/glut.h>
 
 
GLint omuzAci = 0, dirsekAci = 0 ;
 
void special(int key, int, int) {
switch (key) {
case GLUT_KEY_LEFT: (dirsekAci += 5) %= 360; break;
case GLUT_KEY_RIGHT: (dirsekAci -= 5) %= 360; break;
case GLUT_KEY_UP: (omuzAci += 5) %= 360; break;
case GLUT_KEY_DOWN: (omuzAci -= 5) %= 360; break;
default: return;
}
glutPostRedisplay();
}
 
 
void display() {
 
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
 
glPushMatrix();
glTranslatef(0.0, 0.5, 0.0);
glutSolidSphere(0.5, 20, 20);
glBegin(GL_LINES);
glVertex2f(0.0, 0.0);
glVertex2f(0.0, -3.0);
glVertex2f(0.0, -3.0);
glVertex2f(-1.0, -5.0);
glVertex2f(0.0, -3.0);
glVertex2f(1.0, -5.0);
glEnd();
glPopMatrix();
glPushMatrix();
glRotatef((GLfloat)omuzAci, 0.0, 0.0, 1.0);
glBegin(GL_LINES);
glColor3f(1.0, 1.0, 1.0);
glVertex2f(0.0, 0.0);
glVertex2f(1.0, 0.0);
glEnd();
glTranslatef(1.0, 0.0, 0.0);
glRotatef((GLfloat)dirsekAci, 0.0, 0.0, 1.0);
glTranslatef(-1.0, 0.0, 0.0);
glLineWidth(3);
glBegin(GL_LINES);
glColor3f(0, 1, 0);
glVertex2f(1.0, 0.0);
glVertex2f(2.0, 0.0);
glEnd();
glPopMatrix();
glPushMatrix();
glRotatef(-(GLfloat)omuzAci, 0.0, 0.0, 1.0);
glBegin(GL_LINES);
glColor3f(0.0, 0.0, 1.0);
glLineWidth(5.0);
glVertex2f(0.0, 0.0);
glVertex2f(-1.0, 0.0);
glEnd();
glTranslatef(-1.0, 0.0, 0.0);
glRotatef(-(GLfloat)dirsekAci, 0.0, 0.0, 1.0);
glTranslatef(1.0, 0.0, 0.0);
glLineWidth(5.0);
glBegin(GL_LINES);
glColor3f(0.0, 1.0, 0.0);
glVertex2f(-1.0, 0.0);
glVertex2f(-2.0, 0.0);
glEnd();
glPopMatrix();
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
glutSpecialFunc(special);
init();
glutMainLoop();
}