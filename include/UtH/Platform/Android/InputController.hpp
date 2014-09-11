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


        void Initiate();
        void Update();

        bool IsButtonDown(Controller::Button button);
        bool IsButtonUp(Controller::Button button);
        bool IsButtonPressed(Controller::Button button);
        bool IsButtonReleased(Controller::Button button);

        float GetAxis(Controller::Axis axis);

        void HandleInput(AInputEvent* inputEvent);

    private:
        class Axis
        {
        public:
            Axis();
            int mappedAxis;
            float value;
            void update(AInputEvent* inputEvent);
        };

        void handleKeys(AInputEvent* inputEvent);
        void handleAxes(AInputEvent* inputEvent);

        std::vector<int> m_buttons;
        std::vector<int> m_prevButtons;
        std::vector<Axis> m_axes;
    };
}

#endif