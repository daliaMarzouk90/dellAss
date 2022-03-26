#include <iostream>
#include "AMQProducer.h"
#include "Sensor.h"

#include <memory>

class Server
{
private:
    std::shared_ptr<Producer> m_pProducer;
    std::shared_ptr<Sensor>   m_pSensor;    
public:
    Server(/* args */);
    ~Server();

    void Run();
};

Server::Server(/* args */)
{
    m_pProducer = std::make_shared<AMQProducer>();
    m_pSensor = std::make_shared<Sensor>(m_pProducer);
}

Server::~Server()
{
}

void Server::Run()
{
    m_pSensor->Run();
}

int main()
{
    std::cout << "starting server ..." << std::endl;

    Server _server;
    _server.Run();
}