#pragma once

class Producer
{
private:
    virtual void CreateConnection() = 0;
public:
    virtual void Report(int value) = 0;
};
