// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>


int main(int argc, char *argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    auto mWindow = glfwCreateWindow(
        // 2560,
        // 1500,
        mWidth,
        mHeight,
        "OpenGL",
        // glfwGetPrimaryMonitor(),
        nullptr,
        nullptr
    );

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    // GLuint vertexBuffer;
    // glGenBuffers(1, &vertexBuffer);
    // printf("%u\n", vertexBuffer);

    double vertices[] = {
        0.0f, 0.5f,   //
        0.5f, -0.5f,  //
        -0.5f, -0.5f, //
    };


    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




    const char *vertexSource = R"glsl(
        #version 460
        in vec2 position;

        void main() {
            gl_Position = vec4(position, 0.0, 1.0);
        }
    )glsl";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint vertexStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
    if (vertexStatus == GL_TRUE) {
        printf("vertex shader compiled sucessfully!\n");
    } else {
        printf("vertex shader compiled failed!\n");
    }




    const char *fragmentSource = R"glsl(
        #version 460

        out vec4 outColor;

        void main() {
            outColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )glsl";

    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLint fragmentStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
    if (fragmentStatus == GL_TRUE) {
        printf("fragment shader compiled sucessfully!\n");
    } else {
        printf("fragment shader compiled failed!\n");
    }





    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.45f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}
