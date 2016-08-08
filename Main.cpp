/* 
 * File:   Main.cpp
 * Author: Sam
 *
 * Created on 21 May 2016, 18:46
 */

#include <SME_window.h>
#include <SME_core.h>
#include <SME_event.h>
#include <SME_ui_events.h>
#include <SME_render.h>
#include <SME_pipeline.h>
#include <SME_config.h>
#include <SME_xml.h>
#include <SME_level.h>
#include <SME_entity.h>
#include <SME_audio.h>
#include <SME_source.h>
#include <SME_listener.h>
#include <assert.h>
#include <iostream>

#include "TestEntity.h"
#include "TestAttachment.h"

SME::Level::Level level;

SME::Level::Entity::Entity *e;

void update() {
    e->setRot(e->getRot() + glm::vec3(0, 2, 0));
    level.update();
}

class WindowListener : public SME::Event::EventListener {
    void onEvent(SME::Event::Event &event) {
        if (event.getType() == SME::Event::UI::UIEventKeys::WindowCloseEvent) {
            std::cout << "exit" << std::endl;
            SME::Core::stop();
        }
    }
};

bool paused = false;

class KeyboardListener : public SME::Event::EventListener {
    void onEvent(SME::Event::Event &event) {
        if (event.getType() == SME::Event::UI::UIEventKeys::KeyDownEvent) {
            SME::Event::UI::KeyEvent &ke = static_cast<SME::Event::UI::KeyEvent&>(event);
            std::cout << "keyc: " << ke.keycode << std::endl;
            std::cout << "scan: " << ke.scancode << std::endl;
        }
        if (paused) {
            SME::Audio::resumeAll();
        } else {
            SME::Audio::pauseAll();
        }
        paused = !paused;
    }
};

class MouseListener : public SME::Event::EventListener {
    void onEvent(SME::Event::Event &event) {
        SME::Event::UI::MouseEvent &me = static_cast<SME::Event::UI::MouseEvent&>(event);
        std::cout << me.x << ", " << me.y << std::endl;
    }
};

int main(int argc, char** argv) {
    SME::Core::init();

    WindowListener wl;
    SME::Event::registerListener(&wl,{
        SME::Event::UI::UIEventKeys::WindowCloseEvent,
        SME::Event::UI::UIEventKeys::WindowMaximiseEvent,
        SME::Event::UI::UIEventKeys::WindowMinimiseEvent,
        SME::Event::UI::UIEventKeys::WindowResizeEvent
    });
    
    KeyboardListener kl;
    SME::Event::registerListener(&kl,{
        SME::Event::UI::UIEventKeys::KeyDownEvent,
        SME::Event::UI::UIEventKeys::KeyUpEvent
    });
    
    MouseListener ml;
    SME::Event::registerListener(&ml,{
        SME::Event::UI::UIEventKeys::MouseDownEvent,
        SME::Event::UI::UIEventKeys::MouseUpEvent
    });

    SME::Config::loadFile("test.cfg");
    SME::Config::registerValue("a", "test");
    SME::Config::registerValue("b", 12);
    SME::Config::registerValue("c", 1.234);
    SME::Config::registerValue("d", 9223372036854775807);
    SME::Config::registerValue("e", -123);
    SME::Config::registerValue("f", true);

    std::cout << "f: " << SME::Config::getValue<bool>("f") << std::endl;

    SME::Config::saveFile("test.cfg");

    SME::XML::XMLBase xml = SME::XML::parseXML("model.dae");
    std::cout << "attrib contents = " << SME::XML::getFirstTag(xml, "COLLADA.library_effects.effect.profile_COMMON.technique.phong.emission.color")->contents << std::endl;

    level.setParameter<std::string>("test", "test str");
    level.setParameter("test1", 12);
    std::cout << "test: " << level.getParameter<std::string>("test") << ", test1: " << level.getParameter<int>("test1") << std::endl;
    
    SME_REGISTER_ENTITY(TestEntity);
    e = level.addEntity("TestEntity");
    glm::vec3 eRot (0, 0, 0);
    e->setRot(eRot);
    
    SME::Audio::init();
    SME::Audio::loadOGG("freq.ogg", "freq");
    SME::Audio::ListenerAttachment *l = new SME::Audio::ListenerAttachment(e);
    e->addAttachment(l);
    l->setActive();
    SME::Audio::Source s;
    s.playSound("freq");
    s.setPos(glm::vec3(0, 0, 3));
    
    glm::vec3 f = e->getForwardVector();
    glm::vec3 u = e->getUpwardVector();
    glm::vec3 le = glm::cross(f, u);
    
    std::cout << "p2.x=" << f.x << ";p2.y=" << f.y << ";p2.z=" << f.z << ";"
    << std::endl << "p3.x=" << u.x << ";p3.y=" << u.y << ";p3.z=" << u.z << ";"
    << std::endl << "p4.x=" << le.x << ";p4.y=" << le.y << ";p4.z=" << le.z << ";"
    << std::endl;
    
    SME::Window::create(1920 * 3 / 4, 1080 * 3 / 4, "Test", SME_WINDOW_RESIZABLE);
    SME::TestPipeline* pipeline = new SME::TestPipeline();
    SME::Render::addPipeline(pipeline);
    
#ifndef NORENDER
    if (!SME::Render::init("Test", VK_MAKE_VERSION(0, 0, 1))) {
        std::cerr << "Couldn't initialise rendering lib!" << std::endl;
        return -1;
    }
#endif
    
    SME::Core::addLoopUpdateHook(update);

    SME::Core::start();
    return 0;
}