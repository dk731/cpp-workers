#include "ShelfTask.h"

ShelfTask::ShelfTask(bool isLast): Task(15000)
{
	this->myName = "Assemble Shelf";

	if (isLast)
		this->followingTasks.push_back(new AssembleShelfs());
}
