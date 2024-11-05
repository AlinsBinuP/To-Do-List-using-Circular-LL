#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>


int main() {
    glfwInit();
    
    glfwMakeContextCurrent(window);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Todo-App", NULL, NULL);
    
        glfwTerminate();
        return -1;
    


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

        lf_begin();
        lf_end();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}