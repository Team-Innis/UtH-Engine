#pragma once
#ifndef INPUTCONTROLLER_H_UTH
#define INPUTCONTROLLER_H_UTH

#include <vector>
#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Platform/Common/ControllerEnums.hpp>
#include <pmath/Vector2.hpp>

namespace uth
{
    
    class ControllerInput : public InputBase
    {
    public:
        ControllerInput();
        ~ControllerInput();
        
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
        float GetAxis(const Controller::Axis axis, const float deadzone = 0.001f) const;
    };
}

#endif