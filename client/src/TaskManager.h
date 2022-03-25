#include "AverageTask.h"
#include "AccumelationTask.h"
#include <vector>
#include <memory>

class TaskManager
{
private:
    std::vector<std::unique_ptr<Task>> m_pTasks;
public:
    TaskManager();
    ~TaskManager();
    bool RunTasks(int Value);
};

TaskManager::TaskManager(/* args */)
{
    m_pTasks.push_back(std::make_unique<AccumelationTask>());
    m_pTasks.push_back(std::make_unique<AverageTask>());

TaskManager::~TaskManager()
{
    m_Tasks.clear();
}

bool TaskManager::RunTasks(int Value)
{
    for(auto task: m_Tasks){
        if(!task.RunTask())
            return false;
    }

    return true;
}