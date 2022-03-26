#include "AMQProducer.h"
#include "iostream"

AMQProducer::AMQProducer(/* args */)
{
    m_pProducer = std::make_unique<SimpleProducer>("tcp://localhost:61616", "ForstTemp");
}

AMQProducer::~AMQProducer()
{
}

void AMQProducer::Report(float value)
{
    m_pProducer->send(value);
}