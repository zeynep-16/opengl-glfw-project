int en = 200, boy = 200;
float derece = 0;
float xolcu = 1, yolcu = 1, zolcu = 1;
void yanuzat(void){
    glLoadIdentity();
    xolcu += 0.1;
}
void boyuzat(void){
    glLoadIdentity();
    yolcu += 0.1;
}



void cevirsag(void){
    glLoadIdentity();
    derece -= 0.5;
}
void gotursag(void){
    glLoadIdentity();
    xgotur += 0.1;
}
void gotursol(void){
    glLoadIdentity();
    xgotur -= 0.1;
}
void goturyuk(void){
    glLoadIdentity();
    ygotur += 0.1;
}
void goturas(void){
    glLoadIdentity();
    ygotur -= 0.1;
}

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



glutSpecialFunc(specFonk);
glutKeybordFunc(keyFonc);



glutMainLoop();
return 0;
}