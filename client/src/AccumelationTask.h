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
    bool RunTask(float Value);
    void Print();
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

void AccumelationTask::Print(){
        static int count = 0;
        std::cout << count << ": Accumelated sensor value is: " << m_AccTemp / m_callingCount << std::endl;
        count += 1;
    }