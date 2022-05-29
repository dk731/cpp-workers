#pragma once
#include "Task.h"
#include "ShelfTask.h"

class OpenBoxTask :
    public Task
{
public:
    OpenBoxTask(int shelfsAmount);
};

