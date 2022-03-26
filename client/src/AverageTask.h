#pragma once

#include "Task.h"

class AverageTask : public Task
{
private:
    int     m_callingCount = 0;
    float   m_AccTemp = 0;
    float   m_Average = 0;
public:
    AverageTask();
    ~AverageTask();
    bool RunTask(float Value);
    void Print();
};

AverageTask::AverageTask()
{
}

AverageTask::~AverageTask( )
{
}

bool AverageTask::RunTask(float Value)
{
    m_callingCount += 1;
    m_AccTemp += Value;
    m_Average = m_AccTemp / m_callingCount;

    return true;
}

void AverageTask::Print(){
        static int count = 0;
        std::cout << count << ": Average sensor value is: " << m_AccTemp / m_callingCount << std::endl;
        count += 1;
    }