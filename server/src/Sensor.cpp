#include "Sensor.h"
#include "pthread.h"
#include <chrono>

#include <stdlib.h>
#include<time.h>
#include "iostream"

Sensor::Sensor(std::shared_ptr<Producer> producer)
{
    srand(time(0));
    m_pProducer = producer.get();
}

Sensor::~Sensor()
{
    //pthread_exit(NULL); 
}

void Sensor::Run()
{
    m_thread = std::thread(&Sensor::SensorLoop, this);
    m_thread.join();
}
 
void Sensor::SensorLoop()
{
    float sensorVal;

    while(true){
        sensorVal = ReadSensorVal();
        m_pProducer->Report(sensorVal);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

float Sensor::ReadSensorVal()
{
    float fraction =  0.01 * (rand() % 100) ; //between 0.0 and 0.99
    float digit = rand() % 80 - 30; //between -30 and 49

    return digit + fraction;
}

