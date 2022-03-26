#include "Consumer.h"
#include "SimpleConsumer.h"
#include <memory>
class AMQConsumer:Consumer
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
}

AMQConsumer::~AMQConsumer()
{
}

float AMQConsumer::Consume()
{
    return m_pSimpleConsumer->consume();
}