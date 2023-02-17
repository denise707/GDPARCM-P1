#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include "PrimeCheckerThread.h"
#include <deque>

class PrimeChecker : public AGameObject, public IExecutionEvent
{
public:
	PrimeChecker(int numOfThreads, int numToCheck);
	~PrimeChecker();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void onFinishedExecution(int id) override;
private:
	int numOfThreads;
	int currDivisor;
	int numToCheck;
	int currNumber;
	int index = 0;
	int finishedThreads = 0;
	bool isPrime = true;
	bool isDone = false;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
};

