#include <UtH/Platform/Android/InputSensor.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

ASensorManager* SensorInput::sensorManager = nullptr;
ASensorEventQueue* SensorInput::sensorEventQueue = nullptr;
const ASensor* SensorInput::accelerometer = nullptr;
const ASensor* SensorInput::gyroscope = nullptr;

umath::vector3 SensorInput::m_accelerometer = umath::vector3();
umath::vector3 SensorInput::m_gyroscope = umath::vector3();

bool SensorInput::m_enabled = false;

int SensorInput::getSensorEvents(int fd, int events, void* data)
{
    if (accelerometer != NULL || gyroscope != NULL)
    {
        ASensorEvent e;
        // Go trough all the events
        while (ASensorEventQueue_getEvents(sensorEventQueue, &e, 1) > 0)
        {
            switch (e.type)
            {
            case ASENSOR_TYPE_ACCELEROMETER:
                m_accelerometer = umath::vector3(e.acceleration.x, e.acceleration.y,
                    e.acceleration.z);
                break;
            case ASENSOR_TYPE_GYROSCOPE:
                m_gyroscope = umath::vector3(e.vector.x, e.vector.y, e.vector.z);
                break;
            default:
                break;
            }
        }
    }

    WriteLog("acc: %f, %f, %f", m_accelerometer.x, m_accelerometer.y, m_accelerometer.z);
    WriteLog("gyr: %f, %f, %f", m_gyroscope.x, m_gyroscope.y, m_gyroscope.z);

    return 1;
}

umath::vector3 SensorInput::getAccelerometerInput()
{
    return m_accelerometer;
}


umath::vector3 SensorInput::getGyroscopeInput()
{
    return m_gyroscope;
}

void SensorInput::LostFocus()
{
    if (m_enabled)
    {
        if (accelerometer != NULL)
            ASensorEventQueue_disableSensor(sensorEventQueue, accelerometer);

        if (gyroscope != NULL)
            ASensorEventQueue_disableSensor(sensorEventQueue, gyroscope);

        m_enabled = false;
    }
}

void SensorInput::GainFocus()
{
    if (!m_enabled)
    {
        if (accelerometer != NULL)
        {
            ASensorEventQueue_enableSensor(sensorEventQueue, accelerometer);
            ASensorEventQueue_setEventRate(sensorEventQueue, accelerometer, (1000 / 60) * 1000);
        }

        if (gyroscope != NULL)
        {
            ASensorEventQueue_enableSensor(sensorEventQueue, gyroscope);
            ASensorEventQueue_setEventRate(sensorEventQueue, gyroscope, (1000 / 60) * 1000);
        }
        m_enabled = true;
    }
}
