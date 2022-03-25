#pragma once

#include "Task.h"

class AverageTask : public Task
{
private:
    int     m_callingCount = 0;
    float   m_AccTemp = 0;
    float   m_Average;
public:
    AverageTask();
    ~AverageTask();
    bool RunTask(int Value);
};

AverageTask::AverageTask()
{
}

AverageTask::~AverageTask( )
{
}

bool AverageTask::RunTask(int Value)
{
    m_callingCount += 1;
    m_AccTemp += Value;
    m_Average = m_AccTemp / m_callingCount;

    return true;
}
