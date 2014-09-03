#ifndef SENSORINPUT_H_UTH
#define SENSORINPUT_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Math/Vector3.hpp>

#include <android/sensor.h>

namespace uth
{

    class SensorInput : public InputBase
    {
    public:
        void Update();

        umath::vector3 getAccelerometerInput();
        umath::vector3 getGyroscopeInput();

        static void LostFocus();
        static void GainFocus();

        static ASensorManager* sensorManager;
        static ASensorEventQueue* sensorEventQueue;
        static const ASensor* accelerometer;
        static const ASensor* gyroscope;

    private:
        umath::vector3 m_accelerometer;
        umath::vector3 m_gyroscope;
    };
}

#endif