#include "TasksManager.h"

TasksManager::TasksManager(std::queue<Task*>& startingTasks): activeTasks(startingTasks), runningTasks(0), getTaskLock()
{
	this->getTaskLock.lock();
}

void TasksManager::startExecuting()
{
	this->getTaskLock.unlock();
}

Task* TasksManager::getLatestTask()
{
	this->getTaskLock.lock();
	if (this->activeTasks.empty())
	{
		this->getTaskLock.unlock();
		return NULL;
	}

	Task* tmpTask = this->activeTasks.front();
	this->activeTasks.pop();

	this->runningTasks++;

	this->getTaskLock.unlock();

	return tmpTask;
}

Task* TasksManager::getTask()
{
	while (true)
	{
		this->getTaskLock.lock();
		if (!this->activeTasks.empty())
		{
			Task* tmpTask = this->activeTasks.front();
			this->activeTasks.pop();

			this->runningTasks++;

			this->getTaskLock.unlock();

			return tmpTask;
		}


		this->getTaskLock.unlock();

		if (this->runningTasks == 0)
			return NULL;

		const int curRunTasks = this->runningTasks;
		{
			auto ul = std::unique_lock<std::mutex>(this->waitTaskLock);
			this->taskFinishCV.wait(ul, [this, curRunTasks]() {return this->runningTasks != curRunTasks; });
		}
	}

}

void TasksManager::endTask(Task* endedTask)
{
	if (endedTask == NULL)
		return;

	this->getTaskLock.lock();

	for (auto t = endedTask->followingTasks.begin(); t != endedTask->followingTasks.end(); t++)
		this->activeTasks.push(*t);
	
	{
		auto ul = std::unique_lock<std::mutex>(this->waitTaskLock);
		this->runningTasks--;
	}
	this->taskFinishCV.notify_all();

	this->getTaskLock.unlock();

	delete endedTask;
}
