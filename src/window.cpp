#include <iostream>

#include "window.h"

namespace Gulag {

    Window::Window(std::string title, u32 w, u32 h) {
        properties.title  = title;
        properties.width  = w;
        properties.height = h;

        /* Configure the GL Context */

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(
                GLFW_OPENGL_PROFILE,
                GLFW_OPENGL_CORE_PROFILE
        );

        /* Create the internal window */

        glfw_window = glfwCreateWindow(
                properties.width,
                properties.height,
                properties.title.c_str(),
                NULL, NULL
        );

        if (NULL == glfw_window) {
            std::cout << "oopsie" << std::endl;
        }

        glfwMakeContextCurrent(glfw_window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "oopsie" << std::endl;
            /* todo: handle this properly */
        }

        glViewport(0, 0, properties.width, properties.height);

        /* Set up window with callbacks */
        glfwSetWindowUserPointer(glfw_window, &properties);

        glfwSetFramebufferSizeCallback(glfw_window, Callback::window_resize);
        glfwSetKeyCallback(glfw_window, Callback::key_press);

    }

    Window::~Window() {
        /* Terminate the GL Context when window dies */
        glfwTerminate();
    }

    bool Window::should_close() {
        glfwWindowShouldClose(glfw_window);
    }

    void Window::tick() {
        glfwPollEvents();
        glfwSwapBuffers(glfw_window);
    }

    Dispatcher<Event::WinResize>& Window::resize_dispatcher() {
        return properties.resize_dispatcher;
    }

    namespace Callback {

        void window_resize(GLFWwindow* window, int width, int height) {
            WindowProperties* properties =
                (WindowProperties*) glfwGetWindowUserPointer(window);

            properties->width  = width;
            properties->height = height;

            glViewport(0, 0, width, height);

            properties->resize_dispatcher.dispatch(Event::WinResize {
                (u32) width, (u32) height
            });
        }

        void key_press(GLFWwindow* window, int key, int sc, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }
        }

    }
}
