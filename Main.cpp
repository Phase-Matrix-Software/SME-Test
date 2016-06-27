/* 
 * File:   Main.cpp
 * Author: Sam
 *
 * Created on 21 May 2016, 18:46
 */

#include <SME_window.h>
#include <SME_core.h>
#include <SME_events.h>
#include <SME_render.h>
#include <SME_pipeline.h>
#include <SME_config.h>
#include <SME_xml.h>
#include <assert.h>
#include <iostream>

void update() {
    SME::Events::Event event;
    while (SME::Events::getEvent(event)) {
        switch (event.type) {
            case SME::Events::SME_WINDOW:
                if (event.windowEvent.event == SME::Events::SME_WINDOW_CLOSE) {
                    std::cout << "exit" << std::endl;
                    SME::Core::stop();
                } else if (event.windowEvent.event == SME::Events::SME_WINDOW_RESIZE) {
                    std::cout << "new dimensions: " << +event.windowEvent.width << ", " << +event.windowEvent.height << std::endl;
                } else if (event.windowEvent.event == SME::Events::SME_WINDOW_MAXIMISE) {
                    std::cout << "maximise" << std::endl;
                } else if (event.windowEvent.event == SME::Events::SME_WINDOW_MINIMISE) {
                    std::cout << "minimise" << std::endl;
                }
                break;
            case SME::Events::SME_KEYBOARD:
                if (event.keyboardEvent.event == SME::Events::SME_KEYBOARD_KEYDOWN) {
                    std::cout << "d repeated: " << event.keyboardEvent.repeated << std::endl;
                } else if (event.keyboardEvent.event == SME::Events::SME_KEYBOARD_KEYUP) {
                    std::cout << "u repeated: " << event.keyboardEvent.repeated << std::endl;
                }
            case SME::Events::SME_MOUSE:
                if (event.mouseEvent.event == SME::Events::SME_MOUSE_MOVE) {
//                    std::cout << "mouse move: " << event.mouseEvent.x << ", " << event.mouseEvent.y << std::endl;
//                    std::cout << "mouse rel: " << event.mouseEvent.xdelta << ", " << event.mouseEvent.ydelta << std::endl;
                } else if (event.mouseEvent.event == SME::Events::SME_MOUSE_MOUSEDOWN) {
                    std::cout << "mouse down: " << event.mouseEvent.button << std::endl;
                } else if (event.mouseEvent.event == SME::Events::SME_MOUSE_MOUSEUP) {
                    std::cout << "mouse up: " << event.mouseEvent.button << std::endl;
                } else if (event.mouseEvent.event == SME::Events::SME_MOUSE_WHEEL) {
                    std::cout << "scroll: " << +event.mouseEvent.scroll << std::endl;
                }
        }
    }
}

int main(int argc, char** argv) {
    SME::Config::loadFile("test.cfg");
    SME::Config::registerValue("a", "test");
    SME::Config::registerValue("b", 12);
    SME::Config::registerValue("c", 1.234);
    SME::Config::registerValue("d", 9223372036854775807);
    SME::Config::registerValue("e", -123);
    SME::Config::registerValue("f", true);
    
    std::cout << "f: " << SME::Config::getValue<bool>("f") << std::endl;
    
    SME::Config::saveFile("test.cfg");
    
    SME::XML::Tag tag = SME::XML::parseXML("model.dae");
    
    std::cout << "attrib contents = " << SME::XML::getFirstTag(tag, "COLLADA.library_effects.effect.profile_COMMON.technique.phong.emission.color").contents << std::endl;
    
    SME::Core::init();
    SME::Window::create(1920 * 3 / 4, 1080 * 3 / 4, "Test", SME_WINDOW_RESIZABLE);
    SME::TestPipeline* pipeline = new SME::TestPipeline();
    SME::Render::addPipeline(pipeline);
    if(!SME::Render::init("Test", VK_MAKE_VERSION(0, 0, 1))){
        std::cerr << "Couldn't initialise rendering lib!" << std::endl;
        return -1;
    }
    SME::Core::addLoopUpdateHook(update);
    SME::Core::start();
    return 0;
}