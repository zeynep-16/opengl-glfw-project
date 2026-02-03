#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

// --- Minimal GL fonksiyonları ---
typedef float GLclampf;
extern "C" {
    void glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
    void glClear(unsigned int mask);
    void glBegin(unsigned int mode);
    void glEnd();
    void glVertex2f(float x, float y);
    void glLineWidth(float width);
}
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_LINES 0x0001
// --------------------------------

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW başlatılamadı!\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cizgilerle Koordinat Ekseni", NULL, NULL);
    if (!window)
    {
        std::cerr << "Pencere oluşturulamadı!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        // Arka plan kırmızı
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(4.0f); // Çizgi kalınlığı

        glBegin(GL_LINES);

        // --- DİKEY EKSEN (Y ekseni) ---
        for (float y = -1.0f; y <= 1.0f; y += 0.05f)
        {
            glVertex2f(0.0f, y);
            glVertex2f(0.0f, y + 0.05f);
        }

        // --- YATAY EKSEN (X ekseni) ---
        for (float x = -1.0f; x <= 1.0f; x += 0.05f)
        {
            glVertex2f(x, 0.0f);
            glVertex2f(x + 0.05f, 0.0f);
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

