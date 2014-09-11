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
            Start,
            Select,
            DpadUp,
            DpadDown,
            DpadLeft,
            DpadRight,
            ThumbLeft,
            ThumbRight,
            L1,
            R1,
            LB = L1,
            RB = R1,
            BUTTON_COUNT
        };

        enum Axis
        {
            HatY,
            HatX,
            LeftTrigger,
            RightTrigger,
            LeftThumbY,
            LeftThumbX,
            RightThumbY,
            RightThumbX,
            AXIS_COUNT
        };
    }
}

#endif