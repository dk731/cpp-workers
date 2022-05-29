#include "AssembleShelfs.h"

AssembleShelfs::AssembleShelfs(): Task(30000)
{
	this->myName = "Assemble All Shelfs";

	this->followingTasks.push_back(new FinishShelf());
}
