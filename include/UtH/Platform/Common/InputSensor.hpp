#ifndef SENSORINPUT_H_UTH
#define SENSORINPUT_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <pmath/Vector3.hpp>

namespace uth
{

    class SensorInput : public InputBase
    {
    public:
        void Update();

        pmath::Vec3 getAccelerometerInput();
        pmath::Vec3 getGyroscopeInput();

    private:
        pmath::Vec3 m_accelerometer;
        pmath::Vec3 m_gyroscope;
    };
}

#endif