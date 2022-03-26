#include "AverageTask.h"
#include "AccumelationTask.h"
#include <vector>
#include <memory>

class TaskManager
{
private:
    std::vector<std::unique_ptr<Task>>  m_pTasks;
    std::shared_ptr<Consumer>           m_pConsumer;
public:
    TaskManager(std::shared_ptr<Consumer>);
    ~TaskManager();
    bool RunTasks(int Value);
};

TaskManager::TaskManager(std::shared_ptr<Consumer> Consumer)
{
    m_pTasks.push_back(std::make_unique<AccumelationTask>());
    m_pTasks.push_back(std::make_unique<AverageTask>());

    m_pConsumer = Consumer;
}

TaskManager::~TaskManager()
{
    m_pTasks.clear();
}

bool TaskManager::RunTasks(int Value)
{
    float sensorValue = 0;
    for(auto& task : m_pTasks){
        if(!task->RunTask(sensorValue))
            return false;
    }

    return true;
}