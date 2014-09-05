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

        void HandleInput(AInputEvent* inputEvent);

    private:
        void handleKeys(AInputEvent* inputEvent);
        void handleAxes(AInputEvent* inputEvent);

        std::vector<int> m_buttons;
        std::vector<int> m_prevButtons;
        std::vector<pmath::Vec2> m_axes;
    };
}

#endif