#pragma once
#ifndef INPUTCONTROLLER_H_UTH
#define INPUTCONTROLLER_H_UTH

#include <vector>
#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Platform/Common/ControllerEnums.hpp>
#include <pmath/Vector2.hpp>

#include <android/input.h>

namespace uth
{

    class ControllerInput : public InputBase
    {
    public:
        ControllerInput();
        ~ControllerInput();

        void Update();

        bool IsButtonDown(Controller::Button button);
        bool IsButtonUp(Controller::Button button);
        bool IsButtonPressed(Controller::Button button);
        bool IsButtonReleased(Controller::Button button);

        static void HandleInput(AInputEvent* inputEvent);

    private:
        static void handleKeys(AInputEvent* inputEvent);
        static void handleAxes(AInputEvent* inputEvent);

        std::vector<bool> m_buttons;
        std::vector<bool> m_PrevButtons;
        std::vector<pmath::Vec2> m_axes;
    };
}

#endif