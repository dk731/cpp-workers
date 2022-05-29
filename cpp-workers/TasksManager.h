#pragma once
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "Task.h"

class TasksManager
{
public:
	TasksManager(std::queue<Task*> &startingTasks);

	void startExecuting();

	Task* getTask();
	void endTask(Task* finishedTask);

private:
	std::mutex getTaskLock;

	std::mutex waitTaskLock;
	std::atomic<int> runningTasks;
	std::condition_variable taskFinishCV;


	std::queue<Task*> activeTasks;

	Task* getLatestTask();


};

