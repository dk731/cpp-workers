#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <ctime>

#include "TasksManager.h"

class Worker
{
public:
	Worker(TasksManager& taskManager, int lineIndex);
	std::thread myThread;

private:
	TasksManager &myTaskManager;
	std::atomic<bool> isRunning;
	Task* currentTask;

	int lineIndex;
	std::thread statusThread;

	std::mutex taskUpdateLock;

	static std::mutex statusDisplayLock;
	static HANDLE stdHandle;

	void workerRoutine();
	void statusDisplay();
};

