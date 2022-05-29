#include "Worker.h"

std::mutex Worker::statusDisplayLock;
HANDLE Worker::stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

Worker::Worker(TasksManager& taskManager, int lineIndex): myTaskManager(taskManager), lineIndex(lineIndex), isRunning(true)
{
	this->myThread = std::thread([this] { this->workerRoutine(); });
	this->statusThread = std::thread([this] { this->statusDisplay(); });
}

void Worker::workerRoutine()
{
	while (true)
	{

		Task* tmpTask = this->myTaskManager.getTask();

		this->taskUpdateLock.lock();
		this->currentTask = tmpTask;
		this->taskUpdateLock.unlock();
		

		// If taks is empty, stop worker
		if (this->currentTask == NULL)
		{
			this->isRunning = false;
			this->statusThread.join();
			return;
		}

		this->currentTask->doWork();

		this->taskUpdateLock.lock();
		this->myTaskManager.endTask(this->currentTask);
		this->currentTask = NULL;
		this->taskUpdateLock.unlock();
	}
}

void Worker::statusDisplay()
{
	while (this->isRunning)
	{
		// Lock, to prevent reading from deleted task
		this->taskUpdateLock.lock();

		// Lock between workers, to prevent artifacts during text rendering
		this->statusDisplayLock.lock();

		SetConsoleCursorPosition(this->stdHandle, { 0, (short)(this->lineIndex + 3) });
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		std::printf("\33[2K\r"); // Clear line

		if (this->currentTask == NULL)
			std::printf("Worker[%d]		job[]				Waiting for job...", this->lineIndex);
		else
			std::printf("Worker[%d]		job[%s]				progress:	%.2f %%", this->lineIndex, this->currentTask->myName.c_str(), (1.0f - this->currentTask->getProgress()) * 100.0f);

		this->statusDisplayLock.unlock();
		this->taskUpdateLock.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}


