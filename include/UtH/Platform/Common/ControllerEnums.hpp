#ifndef CONTROLLERENUMS_H_UTH
#define CONTROLLERENUMS_H_UTH

namespace uth
{
    namespace Controller
    {
        enum Button
        {
            ButtonA,
            ButtonB,
            ButtonX,
            ButtonY,
            L1,
            R1,
            LB = L1,
            RB = R1,
            Select,
            Start,
            ThumbLeft,
            ThumbRight,
            DpadUp,
            DpadRight,
            DpadDown,
            DpadLeft,
            BUTTON_COUNT
        };

        enum Axis
        {
            DpadX,
            DpadY,
            LeftTrigger,
            RightTrigger,
            LeftThumbX,
            LeftThumbY,
            RightThumbX,
            RightThumbY,
            AXIS_COUNT
        };
    }
}

#endif