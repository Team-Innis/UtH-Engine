#include <UtH/Platform/Android/InputSensor.hpp>

using namespace uth;

ASensorManager* SensorInput::sensorManager = nullptr;
ASensorEventQueue* SensorInput::sensorEventQueue = nullptr;
const ASensor* SensorInput::accelerometer = nullptr;
const ASensor* SensorInput::gyroscope = nullptr;

void SensorInput::Update()
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
    if (accelerometer != NULL)
        ASensorEventQueue_disableSensor(sensorEventQueue, accelerometer);

    if (gyroscope != NULL)
        ASensorEventQueue_disableSensor(sensorEventQueue, gyroscope);
}

void SensorInput::GainFocus()
{
    if (accelerometer != NULL)
    {
        ASensorEventQueue_enableSensor(sensorEventQueue, accelerometer);
        ASensorEventQueue_setEventRate(sensorEventQueue, accelerometer, (1000/60)*1000);
    }

    if (gyroscope != NULL)
    {
        ASensorEventQueue_enableSensor(sensorEventQueue, gyroscope);
        ASensorEventQueue_setEventRate(sensorEventQueue, gyroscope, (1000 / 60) * 1000);
    }
}
