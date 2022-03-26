#pragma once

#include "Task.h"

class AccumelationTask : public Task
{
private:
    int     m_callingCount = 0;
    float   m_AccTemp = 0;
public:
    AccumelationTask();
    ~AccumelationTask();
    bool RunTask(int Value);
};

AccumelationTask::AccumelationTask()
{
}

AccumelationTask::~AccumelationTask( )
{
}

bool AccumelationTask::RunTask(float Value)
{
    m_callingCount += 1;
    m_AccTemp += Value;

    return true;
}
