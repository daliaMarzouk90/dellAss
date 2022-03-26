#pragma once

#include "Producer.h"
#include "SimpleProducer.h"
#include <memory>

class AMQProducer: public Producer
{
private:
    std::unique_ptr<SimpleProducer> m_pProducer;
public:
    AMQProducer();
    ~AMQProducer();
    virtual void Report(float value);
};


