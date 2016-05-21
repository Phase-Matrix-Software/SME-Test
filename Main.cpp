/* 
 * File:   Main.cpp
 * Author: Sam
 *
 * Created on 21 May 2016, 18:46
 */

#include <SME_window.h>
#include <SME_core.h>
#include <iostream>

int main(int argc, char** argv) {
    SME::Window::create(1920*3/4, 1080*3/4, "Test", SME_WINDOW_RESIZABLE);
    SME::Core::start();
    return 0;
}