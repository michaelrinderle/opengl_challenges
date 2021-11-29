/*
      __ _/| _/. _  ._/__ /
    _\/_// /_///_// / /_|/
               _/
    sof digital 2021
    written by michael rinderle <michael@sofdigital.net>
    mit license
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "include/stdafx.h"
#include "include/app.h"

bool app::invert_color = false;

float app::vertex[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

app::app()
{
    if (!glfwInit()) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(app::error_callback);

    window = glfwCreateWindow(screen_width, screen_height, app_name, NULL, NULL);
    if (window == NULL) {
        std::cout << "[*] failed to create glfw window, exiting.";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, app::framebuffer_size_callback);
    glfwSetKeyCallback(window, app::key_callback);
    glfwSetMouseButtonCallback(window, app::mouse_button_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[*] failed to initalize glad, exiting.";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, screen_width, screen_height);

    glfwSwapInterval(1);
}

void
app::setup()
{
    // generate 1 buffer
    glGenBuffers(1, &vertex_buffer);
    // bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // pass vertices to opengl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        this->render();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void
app::render()
{
    glClearColor(0.1, 0.5, 0.75, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);


    // 1 att buffer

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glColor4f(0, 0, 1, 0);

    if (invert_color)
        glColor4f(1, 0.2, 1, 0);
    else
        glColor4f(.35, .5, 0.5, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);

    glfwPollEvents();
}

void
app::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error : %s\n", description);
}

void
app::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    /*else if (key == 32) {
        app::state.isSorting = true;
    }
    else if (key == 82) {
        app::state.isRestarting = true;
    }*/
}

void
app::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void app::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == 1) {
        app::invert_color = !app::invert_color;
    }
}
