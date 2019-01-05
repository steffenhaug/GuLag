#include <iostream>
#include <string>


#include <algorithm>

#include "window.h"
#include "event.h"


void handle_resize_event(Gulag::Event::WinResize e) {
    std::cout
        << "Window changed size: "
        << e.width << ", " << e.height
        << std::endl;
}

int main() {

    Gulag::Window window("OpenGL Test", 256, 256);

    Gulag::Subscriber<Gulag::Event::WinResize> sub(handle_resize_event);

    sub.subscribe_to(window.resize_dispatcher());

    while (!window.should_close()) {
        window.tick();
    }

}
