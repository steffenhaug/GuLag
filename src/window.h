/* The Window class encapsulates all interactions
 * with your window, like managing resources,
 * handling events/callbacks and so on.
 * */
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "common.h"
#include "event.h"

namespace Gulag {

    namespace Event {
        struct WinResize {
            u32 width, height;
        };
    }

    /* We keep all info about a window in one struct [0] */
    struct WindowProperties {
        std::string title;
        u32         width, height;
        /* Event Handling */
        Dispatcher<Event::WinResize> resize_dispatcher;
    };

    class Window {
        public:
            Window(std::string title, u32 width, u32 height);
            ~Window();

            bool should_close();
            void tick();
            Dispatcher<Event::WinResize>& resize_dispatcher();

        private:
            GLFWwindow* glfw_window;
            WindowProperties properties;

    };

    namespace Callback {
        void window_resize(GLFWwindow* window, int w, int h);
        void key_press(GLFWwindow* window, int key, int sc, int action, int mods);
    }

}



/* [0] This is so that we can keep a pointer to it
 * in the internal GLFW window (read the docs regarding
 * glfw{Set, Get}WindowUserPointer() for more). This is
 * important because we need it when handling callbacks.
 */
