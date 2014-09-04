#include <UtH/Platform/Common/InputSensor.hpp>

using namespace uth;


void SensorInput::Update()
{
}

pmath::Vec3 SensorInput::getAccelerometerInput()
{
    return pmath::Vec3(0, 0, 0);
}


pmath::Vec3 SensorInput::getGyroscopeInput()
{
    return pmath::Vec3(0, 0, 0);
}
