#include <iostream>
#include "AMQConsumer.h"
#include "TaskManager.h"
#include <memory>

class Client
{
private:
    std::shared_ptr<Consumer> m_pConsumer;
    std::shared_ptr<TaskManager>   m_pTaskManager;    
public:
    Client(/* args */);
    ~Client();

    void Run();
};

Client::Client(/* args */)
{
    m_pConsumer = std::make_shared<AMQConsumer>();
    m_pTaskManager = std::make_shared<TaskManager>(m_pConsumer);
}

Client::~Client()
{
}

void Client::Run()
{
    m_pTaskManager->RunTasks();
}

int main()
{
    std::cout << "starting client ..." << std::endl;

    Client _client;
    _client.Run();
}