#include "AverageTask.h"
#include "AccumelationTask.h"
#include <list>

class TaskManager
{
private:
    std::list<Task> m_Tasks;
public:
    TaskManager();
    ~TaskManager();
    bool RunTasks(int Value);
};

TaskManager::TaskManager(/* args */)
{
    m_Tasks.push_back(AccumelationTask());
    m_Tasks.push_back(AverageTask());
}

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