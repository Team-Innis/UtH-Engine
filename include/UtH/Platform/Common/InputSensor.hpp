#ifndef SENSORINPUT_H_UTH
#define SENSORINPUT_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Math/Vector3.hpp>

namespace uth
{

    class SensorInput : public InputBase
    {
    public:
        void Update();

        umath::vector3 getAccelerometerInput();
        umath::vector3 getGyroscopeInput();

    private:
        umath::vector3 m_accelerometer;
        umath::vector3 m_gyroscope;
    };
}

#endif