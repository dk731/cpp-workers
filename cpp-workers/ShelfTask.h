#pragma once
#include "Task.h"
#include "AssembleShelfs.h"

class ShelfTask :
    public Task
{
public:
    ShelfTask(bool isLast);
};

