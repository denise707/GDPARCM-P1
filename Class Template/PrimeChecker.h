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
	void onFinishedExecution() override;
private:
	int numOfThreads;
	int currDivisor;
	int numToCheck;
	bool isPrime = false;
	bool isDone = false;
	std::deque<PrimeCheckerThread*> availableThreadList;
	std::deque<PrimeCheckerThread*> usedThreadList;
};

