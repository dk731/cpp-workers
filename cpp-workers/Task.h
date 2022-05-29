#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <string>

class Task
{
public:
	Task(int taskLength);
	
	void doWork();

	float getProgress();

	std::vector<Task*> followingTasks;

	std::string myName;

private:
	int taskLength;
	int timeLeft;
};

