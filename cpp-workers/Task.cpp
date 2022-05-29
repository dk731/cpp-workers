#include "Task.h"

Task::Task(int taskLength): taskLength(taskLength), myName("EmptyJob"), timeLeft(0)
{
}

void Task::doWork()
{
	this->timeLeft = this->taskLength;
	while (this->timeLeft > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->timeLeft -= 100;
	}
}

float Task::getProgress()
{
	return this->timeLeft / (float)this->taskLength;
}
