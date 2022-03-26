#include "Consumer.h"
#include "SimpleConsumer.h"
#include <memory>
class AMQConsumer:public Consumer
{
private:
    std::unique_ptr<SimpleConsumer> m_pSimpleConsumer;

public:
    AMQConsumer(/* args */);
    ~AMQConsumer();
    float Consume();
};

AMQConsumer::AMQConsumer(/* args */)
{
    m_pSimpleConsumer = std::make_unique<SimpleConsumer>("failover:(tcp://localhost:61616)", "ForstTemp");
}

AMQConsumer::~AMQConsumer()
{
}

float AMQConsumer::Consume()
{
    return m_pSimpleConsumer->consume();
}