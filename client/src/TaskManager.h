#include "AverageTask.h"
#include "AccumelationTask.h"
#include "thread"
#include <vector>
#include <memory>
#include <ctime>

class TaskManager
{
private:
    std::vector<std::unique_ptr<Task>>  m_pTasks;
    std::shared_ptr<Consumer>           m_pConsumer;
    std::thread                         m_thread;
    bool Loop();
public:
    TaskManager(std::shared_ptr<Consumer>);
    ~TaskManager();
    bool RunTasks();
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

bool TaskManager::RunTasks()
{
    m_thread = std::thread(&TaskManager::Loop, this);
    m_thread.join();
    
    return true;
}

bool TaskManager::Loop()
{
    clock_t begin = clock();

    clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    while (1)
    {
        float sensorValue = m_pConsumer->Consume();
        for(auto& task : m_pTasks){
            if(!task->RunTask(sensorValue)) return false;
        }

        end = clock();
        int diffSec = ((double)(end - begin)) / CLOCKS_PER_SEC ;
        
        if(diffSec % 5 == 0)
        {
            for(auto& task : m_pTasks){
                task->Print();
            }
        }

    }
    return true;
}