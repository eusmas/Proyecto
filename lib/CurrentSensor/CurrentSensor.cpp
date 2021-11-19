#include <CurrentSensor.h>

CurrentSensor::CurrentSensor() 
{

}

CurrentSensor::~CurrentSensor() 
{

}

void CurrentSensor::setup(const uint8_t pin, int resolucion, float lectura_max)
{
    _pin=pin;
    pinMode(_pin,INPUT);
    _resolucion=resolucion;
    _lectura_max=lectura_max;
}

float CurrentSensor::read() 
{
    _digital_level= analogRead(_pin);
    _sensor_measure=_digital_level*(_lectura_max/(pow(2,_resolucion)-1));
       return _sensor_measure;

}

float CurrentSensor::getMeasure(measure type) 
{
    switch (type)
    {
    case DIGITAL_LEVEL:
        return _digital_level;
        break;
    case SENSOR_MEASURE:
        return _sensor_measure;
        break;   
    default:
        return _digital_level;  
        break;
    }
}

