// GLFW'nin OpenGL başlıklarını otomatik olarak eklemesini engeller.
// OpenGL fonksiyonlarını manuel olarak tanımlayacağımız için kullanılır.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

/* ---------------- OpenGL minimal bildirimler ---------------- */
typedef float GLclampf;
typedef unsigned int GLenum;
typedef unsigned int GLbitfield;

extern "C"
{
    void glClearColor(GLclampf, GLclampf, GLclampf, GLclampf);
    void glClear(GLbitfield);

    void glBegin(GLenum);
    void glEnd();
    void glVertex2f(float, float);
    void glVertex3f(float, float, float);
    void glColor3f(float, float, float);
    void glNormal3f(float, float, float);

    void glRotatef(float, float, float, float);
    void glTranslatef(float, float, float);
    void glPushMatrix(void);
    void glPopMatrix(void);
    void glLoadIdentity(void);

    void glEnable(unsigned int);
    void glDisable(unsigned int);
    void glLightfv(unsigned int, unsigned int, const float *);
    void glMaterialfv(unsigned int, unsigned int, const float *);
    void glColorMaterial(unsigned int, unsigned int);

    void glMatrixMode(unsigned int);
    void glFrustum(double, double, double, double, double, double);
    void glOrtho(double, double, double, double, double, double);

    void glColorMask(unsigned char, unsigned char, unsigned char, unsigned char);
    void glDepthMask(unsigned char);

    void gluLookAt(double, double, double,
                   double, double, double,
                   double, double, double);

    void *gluNewQuadric(void);
    void gluCylinder(void *, double, double, double, int, int);
    void gluSphere(void *, double, int, int);
}

/* ---------------- Sabitler ---------------- */
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100

#define GL_TRIANGLES 0x0004
#define GL_QUADS 0x0007
#define GL_TRIANGLE_FAN 0x0006

#define GL_LIGHTING 0x0B50
#define GL_LIGHT0 0x4000
#define GL_LIGHT1 0x4001

#define GL_POSITION 0x1203
#define GL_AMBIENT 0x1200
#define GL_DIFFUSE 0x1201
#define GL_SPECULAR 0x1202

#define GL_COLOR_MATERIAL 0x0B57
#define GL_FRONT_AND_BACK 0x0408
#define GL_AMBIENT_AND_DIFFUSE 0x1602

#define GL_EMISSION 0x1600
#define GL_SHININESS 0x1601

#define GL_DEPTH_TEST 0x0B71

#define GL_PROJECTION 0x1701
#define GL_MODELVIEW 0x1700

#define GL_FALSE 0
#define GL_TRUE 1

/* ---------------- Sahne sabitleri ---------------- */
const float TEKNE_X_LIMIT = 0.70f;

/* ---------------- Animasyon ve Konum Değişkenleri---------------- */
float tekneX = 0.0f;
float tekneY = -0.5f;

float dalga = 0.0f;
float bayrak = 0.0f;

int dalgaYon = 1;
int bayrakYon = 1;


float camX = 0.0f;
float camY = 0.4f;
float camZ = 4.5f;

/* ---------------- Animasyonlar ---------------- */
void dalgaAnimasyonu()
{
    dalga += dalgaYon ? 0.05f : -0.05f;
    if (dalga > 5)
        dalgaYon = 0;
    if (dalga < -5)
        dalgaYon = 1;
}

void bayrakAnimasyonu()
{
    bayrak += bayrakYon ? 3.5f : -3.5f;
    if (bayrak > 25)
        bayrakYon = 0;
    if (bayrak < -25)
        bayrakYon = 1;
}

/* ---------------- 2B Arka Plan ---------------- */
void gokyuzuCiz()
{
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.2f, 0.5f);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glColor3f(0.9f, 0.5f, 0.3f);
    glVertex2f(1, 0);
    glVertex2f(-1, 0);
    glEnd();
}

void denizCiz()
{
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.6f, 0.9f);
    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glColor3f(0.0f, 0.2f, 0.5f);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
}

/* ---------------- Işık Kurulumu ---------------- */
void sahneIsiklariniKur()
{
    const float sunPos[] = {0.0f, 0.60f, -2.50f, 1.0f}; // w=1 -> noktasal ışık (güneş)

    // Gün doğumu tonu
    const float light0_amb[] = {0.10f, 0.06f, 0.03f, 1.0f};
    const float light0_diff[] = {1.00f, 0.70f, 0.35f, 1.0f};
    const float light0_spec[] = {0.80f, 0.60f, 0.40f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);

    // Gökyüzü dolgu ışığı (yukarıdan zayıf)
    const float light1_pos[] = {0.0f, 1.0f, 0.0f, 0.0f}; // w=0 -> yönsel ışık
    const float light1_amb[] = {0.03f, 0.03f, 0.04f, 1.0f};
    const float light1_diff[] = {0.18f, 0.22f, 0.28f, 1.0f};
    const float light1_spec[] = {0.00f, 0.00f, 0.00f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);

    // Parlaklık kontrolü (malzeme shininess)
    const float shiny[] = {40.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}

/* ---------------- 3B Güneş (tam küre) ---------------- */
void gunes3BCiz()
{
    void *q = gluNewQuadric();
    glPushMatrix();

    glTranslatef(0.0f, 0.60f, -2.50f);

    // Güneşin “kendi ışığını yayması” için emission
    const float sun_emission[] = {0.90f, 0.45f, 0.15f, 1.0f};
    const float sun_diffuse[] = {1.00f, 0.70f, 0.35f, 1.0f};
    const float sun_specular[] = {0.60f, 0.40f, 0.20f, 1.0f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emission);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_specular);

    // Tam küre
    gluSphere(q, 0.35, 64, 64);

    const float no_emission[] = {0, 0, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_emission);

    glPopMatrix();
}

/* ---------------- Bayrak ---------------- */
void bayrakCiz()
{
    glPushMatrix();
    glTranslatef(0, 0, 0.02f);
    glRotatef(bayrak, 0, 1, 0);
    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.1f, 0);
    glVertex3f(0.18f, 0.05f, 0);
    glEnd();

    glPopMatrix();
}

/* ---------------- Direk ---------------- */
void direkCiz()
{
    void *q = gluNewQuadric();
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.85f, 0.85f, 0.85f);
    gluCylinder(q, 0.015, 0.015, 0.30, 24, 1);
    glPopMatrix();
}

/* ---------------- Tekne ---------------- */
void tekneCiz()
{
    const float z1 = -0.05f, z2 = 0.05f;

    glPushMatrix();
    glTranslatef(tekneX, tekneY + std::sin(dalga * 0.05f) * 0.05f, 0);

    glColor3f(0.4f, 0.25f, 0.1f);

    glBegin(GL_QUADS); // Ön
    glNormal3f(0, 0, 1);
    glVertex3f(-0.4f, 0.05f, z2);
    glVertex3f(0.4f, 0.05f, z2);
    glVertex3f(0.3f, -0.05f, z2);
    glVertex3f(-0.3f, -0.05f, z2);
    glEnd();

    glBegin(GL_QUADS); // Arka
    glNormal3f(0, 0, -1);
    glVertex3f(-0.4f, 0.05f, z1);
    glVertex3f(-0.3f, -0.05f, z1);
    glVertex3f(0.3f, -0.05f, z1);
    glVertex3f(0.4f, 0.05f, z1);
    glEnd();

    glBegin(GL_QUADS); // Sol
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.4f, 0.05f, z1);
    glVertex3f(-0.4f, 0.05f, z2);
    glVertex3f(-0.3f, -0.05f, z2);
    glVertex3f(-0.3f, -0.05f, z1);
    glEnd();

    glBegin(GL_QUADS); // Sağ
    glNormal3f(1, 0, 0);
    glVertex3f(0.4f, 0.05f, z2);
    glVertex3f(0.4f, 0.05f, z1);
    glVertex3f(0.3f, -0.05f, z1);
    glVertex3f(0.3f, -0.05f, z2);
    glEnd();

    glBegin(GL_QUADS); // Alt
    glNormal3f(0, -1, 0);
    glVertex3f(-0.3f, -0.05f, z1);
    glVertex3f(-0.3f, -0.05f, z2);
    glVertex3f(0.3f, -0.05f, z2);
    glVertex3f(0.3f, -0.05f, z1);
    glEnd();

    // Direk ve bayrak
    glTranslatef(0, 0.05f, 0);
    direkCiz();

    glTranslatef(0.01f, 0.25f, 0);
    bayrakCiz();

    glPopMatrix();
}

/* ---------------- 3B Bulut ---------------- */
void bulutCiz(float x, float y, float z)
{
    void *q = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.95f, 0.95f, 0.95f);

    gluSphere(q, 0.12, 20, 20);
    glTranslatef(0.12f, 0.02f, 0);
    gluSphere(q, 0.10, 20, 20);
    glTranslatef(-0.24f, 0.01f, 0);
    gluSphere(q, 0.09, 20, 20);

    glPopMatrix();
}

/* ---------------- Klavye ---------------- */
void klavyeKontrol(GLFWwindow *w)
{
    if (glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS)
        tekneX += 0.01f;
    if (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)
        tekneX -= 0.01f;
    if (glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS)
        tekneY += 0.01f;
    if (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS)
        tekneY -= 0.01f;

    if (tekneX > TEKNE_X_LIMIT)
        tekneX = TEKNE_X_LIMIT;
    if (tekneX < -TEKNE_X_LIMIT)
        tekneX = -TEKNE_X_LIMIT;

    if (tekneY > -0.15f)
        tekneY = -0.15f;
    if (tekneY < -0.95f)
        tekneY = -0.95f;
}

void kameraKontrol(GLFWwindow *w)
{
    float hiz = 0.05f;

    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
        camZ -= hiz; // ileri
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
        camZ += hiz; // geri

    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
        camX -= hiz; // sola
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
        camX += hiz; // sağa

    if (glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS)
        camY += hiz; // yukarı
    if (glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS)
        camY -= hiz; // aşağı

    // Kamera sınırları 
    if (camZ < 1.5f)
        camZ = 1.5f; 
    if (camZ > 30.0f)
        camZ = 30.0f; 

    if (camX < -2.5f)
        camX = -2.5f;
    if (camX > 2.5f)
        camX = 2.5f;

    if (camY < -0.2f)
        camY = -0.2f;
    if (camY > 2.0f)
        camY = 2.0f;
}

/* ---------------- Main ---------------- */
int main()
{
    glfwInit(); // GLFW yi başlatıyoruz
    GLFWwindow *w = glfwCreateWindow(800, 600, "3B Tekne Sahnesi", NULL, NULL);
    glfwMakeContextCurrent(w); // OpenGL çizimlerini bu pencereye yapacağımızı söylüyoruz

    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST); // Hangi nesne önde–arkada doğru görünsün diye derinliği açıyoruz.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL); // ışıklandırma açıkken nesnenin malzeme rengi olarak kullanılmasını sağlar

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    while (!glfwWindowShouldClose(w)) // pencere kapanana kadar sürekli çizim yap
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2B arka plan
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        glMatrixMode(GL_PROJECTION); // Projeksiyon matrisi seçilir ve sıfırlanır.
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -1, 1); // 2B ortografik (perspektifsiz) görüntü ayarlanır.

        glMatrixMode(GL_MODELVIEW); // Model–görünüm matrisi sıfırlanır.
        glLoadIdentity();

        gokyuzuCiz();
        glLoadIdentity();
        denizCiz();

        // 3B sahne
        glEnable(GL_DEPTH_TEST); // 3B nesneler için derinlik testi ve ışıklandırma açılır
        glEnable(GL_LIGHTING);

        glMatrixMode(GL_PROJECTION); // 3B projeksiyon için matris sıfırlanır
        glLoadIdentity();
        glFrustum(-1, 1, -1, 1, 0.5, 50);
        // Perspektifli 3B görüntü (derinlikli sahne) ayarlanır

        glMatrixMode(GL_MODELVIEW); // Kamera ve nesneler için matris sıfırlanır.
        glLoadIdentity();
        gluLookAt(
            camX, camY, camZ,  
            0.0f, -0.2f, 0.0f, // sahnenin merkezi (tekne hizası)
            0.0f, 1.0f, 0.0f);

        sahneIsiklariniKur();

        gunes3BCiz();

        bulutCiz(-0.8f, 0.6f, -1.6f);
        bulutCiz(0.7f, 0.55f, -1.8f);

        dalgaAnimasyonu();
        bayrakAnimasyonu();
        kameraKontrol(w);
        klavyeKontrol(w);
        tekneCiz();

        glfwSwapBuffers(w); // çizilen sahne ekrana basılıyor
        glfwPollEvents();
    }

    glfwTerminate(); // GLFW düzgün şekilde kapatılır.
    return 0;
}
