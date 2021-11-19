#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <Arduino.h>

class Buffer
{
protected:
    int in_index;
    int out_index;
    float* list;
    int size;
    int free_slots;

public:
    Buffer(int size);           //constructor para definir el tamaño del buffer
    bool add(float value);            //agregar un dato al buffer
    int remove();           //remover un dato del buffer
    int inIndex();          //posicion del index para agregar dato al buffer
    int outIndex();         //posicion del index para sacar dato del buffer
    int freeSlots();            //cantidad de espacios libres en el buffer
};

class BufferStat: public Buffer
{
public:
    BufferStat(int size):Buffer(size){}
    float avg();
    float min();
    float max();
    float moda();
    float median();

private:
    void intercambiar(float *a, float *b);
    float* burbuja();

};

#endif // __BUFFER_H__