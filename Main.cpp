/* 
 * File:   Main.cpp
 * Author: Sam
 *
 * Created on 21 May 2016, 18:46
 */

#include <SME_window.h>
#include <SME_core.h>
#include <SME_events.h>
#include <iostream>

void update() {
    SME::Events::Event event;
    while (SME::Events::getEvent(event)) {
        switch (event.type) {
            case SME::Events::SME_WINDOW:
                if (event.windowEvent.event == SME::Events::SME_WINDOW_CLOSE) {
                    std::cout << "exit" << std::endl;
                    SME::Core::stop();
                }
                break;
            case SME::Events::SME_KEYBOARD:
                if (event.keyboardEvent.event == SME::Events::SME_KEYBOARD_KEYDOWN) {
                    std::cout << +event.keyboardEvent.scancode << std::endl;
                }
        }
    }
}

int main(int argc, char** argv) {
    SME::Core::init();
    SME::Window::create(1920 * 3 / 4, 1080 * 3 / 4, "Test", 0);
    SME::Core::addLoopUpdateHook(update);
    SME::Core::start();
    return 0;
}