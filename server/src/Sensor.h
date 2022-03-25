#pragma once

#include "pthread.h"
#include "Producer.h"
#include <memory>
#include <thread>

class Sensor
{

public:
    Sensor(std::shared_ptr<Producer> producer);
    //Sensor() = delete;
    ~Sensor();
    void Run();
private:
    
    void     SensorLoop();
    float    ReadSensorVal();
    Producer    *m_pProducer;
    std::thread m_thread;
};

