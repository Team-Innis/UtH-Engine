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

        bool IsButtonDown(const Controller::Button button) const;
        bool IsButtonUp(const Controller::Button button) const;
        bool IsButtonPressed(const Controller::Button button) const;
        bool IsButtonReleased(const Controller::Button button) const;

        // Depeding on the platform and the controller 
        // the maximum value might be less than one.
        // Deadzone removes values from the bottom end
        // so you get a zero value when not touching the controller.
        // Deadzone is inclusive
        float GetAxis(Controller::Axis axis, const float deadzone = 0.001f) const;

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