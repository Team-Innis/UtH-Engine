#ifndef SENSORINPUT_H_UTH
#define SENSORINPUT_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <pmath/Vector3.hpp>

#include <android/sensor.h>

namespace uth
{

    class SensorInput : public InputBase
    {
    public:
        pmath::Vec3 getAccelerometerInput();
        pmath::Vec3 getGyroscopeInput();

        static int getSensorEvents(int fd, int events, void* data);

        static void LostFocus();
        static void GainFocus();

        static ASensorManager* sensorManager;
        static ASensorEventQueue* sensorEventQueue;
        static const ASensor* accelerometer;
        static const ASensor* gyroscope;

    private:
        static pmath::Vec3 m_accelerometer;
        static pmath::Vec3 m_gyroscope;

        static bool m_enabled;
    };
}

#endif