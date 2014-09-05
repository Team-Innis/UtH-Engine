#pragma once
#ifndef INPUTCONTROLLER_H_UTH
#define INPUTCONTROLLER_H_UTH

#include <vector>
#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Platform/Common/ControllerEnums.hpp>

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

    private:

        std::vector<bool> m_keys;
        std::vector<bool> m_Lkeys;
    };
}

#endif