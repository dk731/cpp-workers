#include <iostream>
#include <chrono>

#include "Worker.h"
#include "TasksManager.h"
#include "OpenBoxTask.h"

int main()
{
	int shelfsAmount, workersAmount;
	std::cout << "Please enter shelfs amount: ";
	std::cin >> shelfsAmount;

	std::cout << "Please enter workers amount: ";
	std::cin >> workersAmount;

	std::queue<Worker*> workersQueue;
	std::queue<Task*> startingTasks;

	startingTasks.push(new OpenBoxTask(shelfsAmount));

	TasksManager tasksManager(startingTasks);

	for (int i = 0; i < workersAmount; i++)
	{
		workersQueue.push(new Worker(tasksManager, i));
	}

	auto begin = std::chrono::steady_clock::now();

	tasksManager.startExecuting();
	

	while (!workersQueue.empty())
	{
		workersQueue.front()->myThread.join();
		delete workersQueue.front();

		workersQueue.pop();
	}

	auto end = std::chrono::steady_clock::now();
	float tasksDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0f;

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "All tasks are finished in: " << tasksDuration << " seconds" << std::endl;


	return 0;
}


//0x0093f918