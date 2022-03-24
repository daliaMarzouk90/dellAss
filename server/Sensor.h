#include "pthread.h"
#include "Producer.h"
class Sensor
{

public:
    Sensor(Producer *producer);
    ~Sensor();
private:
    void Run();
    void GetSensorReading();
    Producer *m_pProducer;
};

Sensor::Sensor(Producer *producer)
{
}

Sensor::~Sensor()
{
}
