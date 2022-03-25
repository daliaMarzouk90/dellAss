#pragma once

#include "Producer.h"

class AMQProducer: public Producer
{
private:
    virtual void CreateConnection();
public:
    AMQProducer(/* args */);
    ~AMQProducer();
    virtual void Report(int value);
};


