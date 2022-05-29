#include "OpenBoxTask.h"

OpenBoxTask::OpenBoxTask(int shelfsAmount): Task(5000)
{
	this->myName = "Open Box";

	int lastIndex = shelfsAmount - 1;

	for (int i = 0; i < shelfsAmount; i++)
		this->followingTasks.push_back(new ShelfTask(i == lastIndex));
}
