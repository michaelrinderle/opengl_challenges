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

bool app::isSorting;

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
    this->isSorting = false;

    initialize_array();

    while (!glfwWindowShouldClose(window)) {

        if (this->isSorting) {
            this->sort_array();
        }
        this->render();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void
app::render()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    float l = (float)length;
    float widthAdder = 1 / l;

    for (int i = 0; i < length; ++i)
    {
        glBegin(GL_POLYGON);

        float arrayIndexHeightRation = 2 * (arr[i] + 1) / l;
        float widthIndexAdder = 2 * i / l;

        float leftX = -1 + widthIndexAdder;
        float rightX = leftX + widthAdder;
        float bottomY = -1;
        float topY = bottomY + arrayIndexHeightRation;

        // bottom left
        glColor4f(0, 0, 1, .75);
        glVertex2f(leftX, bottomY);

        // bottom right
        glColor4f(0, 0, 1, .75);
        glVertex2f(rightX, bottomY);

        // top right
        glColor4f(0, 0, 1, 0);
        glVertex2f(rightX, topY);

        // top left
        glColor4f(0, 0, 1, 0);
        glVertex2f(leftX, topY);

        glEnd();
    }

    glfwSwapBuffers(window);

    glfwPollEvents();
}


void
app::initialize_array()
{
    arr = (int*)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }

    for (int i = length - 1; i > 0; --i) {
        std::swap(arr[i], arr[rand() % (i + 1)]);
    }
}

void
app::sort_array()
{
    for (int i = 0; i < length; i++) {
        if (arr[i] > arr[i + 1]) {
            std::swap(arr[i], arr[i + 1]);
        }
    }
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
    else if (key == 32) {
        app::isSorting = true;
    }
}

void
app::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}