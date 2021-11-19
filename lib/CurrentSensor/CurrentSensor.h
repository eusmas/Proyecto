#ifndef __CURRENTSENSOR_H__
#define __CURRENTSENSOR_H__

#include <Arduino.h>

enum measure{
    DIGITAL_LEVEL,
    SENSOR_MEASURE
};


class CurrentSensor
{
    public:
        CurrentSensor();
        ~CurrentSensor();
        void setup(const uint8_t pin, int resolucion, float lectura_max);
        float read();
        float getMeasure(measure type = DIGITAL_LEVEL);

    private:
        uint8_t _pin;
        float _resolucion;
        float _lectura_max;
        
    protected:
        uint16_t _digital_level;
        float _sensor_measure;

};


#endif