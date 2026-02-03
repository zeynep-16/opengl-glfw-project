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
------------------------------

#include <GL/glut.h>
 
int en = 200, boy = 200;
float derece = 0;
float xolcu = 1, yolcu = 1, zolcu = 1;
void yanuzat(void)
{
glLoadIdentity();
xolcu += 0.1;
}
 
void boyuzat(void)
{
glLoadIdentity();
yolcu += 0.1;
}
 
void cevirsag(void)
{
glLoadIdentity();
derece += 0.5;
}
 
void cevirsol(void)
{
glLoadIdentity();
derece -= 0.5;
}
 
 
void keyFunc(unsigned char key, int x, int y)
{
switch (key)
{
case'a':yanuzat(); break;
case's':boyuzat(); break;
case'z':cevirsol(); break;
case'x':cevirsag(); break;
 
}
glutPostRedisplay();
}
 
void ucbcokgen(void)
{
glColor3f(0.5, 0.1, 0.1);
glRotatef(derece, 0.0, 1.0, 0.0);
glScalef(xolcu, yolcu, zolcu);
 
glutWireCube(1.0);
 
}
void ciz(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 1.0, 1.0);
glLoadIdentity();
gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
ucbcokgen();
glutSwapBuffers();
}
 
void reshape(int en, int boy)
{
glViewport(0, 0, en, boy);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(90, (float)en / (float)boy, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(en, boy);
glutInitWindowPosition(0, 0);
glutCreateWindow("3bcokgen2");
glClearColor(1.0, 1.0, 1.0, 1.0);
glShadeModel(GL_FLAT);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glutReshapeFunc(reshape);
glutDisplayFunc(ciz);
glutKeyboardFunc(keyFunc);
glutMainLoop();
return 0;
}
