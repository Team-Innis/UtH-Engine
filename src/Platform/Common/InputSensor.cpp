#include <UtH/Platform/Common/InputSensor.hpp>

using namespace uth;


void SensorInput::Update()
{
}

umath::vector3 SensorInput::getAccelerometerInput()
{
    return umath::vector3(0, 0, 0);
}


umath::vector3 SensorInput::getGyroscopeInput()
{
    return umath::vector3(0, 0, 0);
}
