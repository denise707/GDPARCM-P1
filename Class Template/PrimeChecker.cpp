#include "PrimeChecker.h"

PrimeChecker::PrimeChecker(int numOfThreads, int numToCheck): AGameObject("PrimeChecker")
{
	this->numOfThreads = numOfThreads;
	this->numToCheck = numToCheck;
}

PrimeChecker::~PrimeChecker()
{
}

void PrimeChecker::initialize()
{
	//Create threads
	for (int i = 0; i < this->numOfThreads; i++) {
		PrimeCheckerThread* thread = new PrimeCheckerThread(i);
		this->availableThreadList.push_back(thread);
	}
	this->currDivisor = numToCheck;
}

void PrimeChecker::processInput(sf::Event event)
{
}

void PrimeChecker::update(sf::Time deltaTime)
{
	//Remove thread at the last index of the available threads then push in front of used threads
	if (this->availableThreadList.size() > 0 && currDivisor > 0 && !isDone) {	

		PrimeCheckerThread* currThread = availableThreadList[availableThreadList.size() - 1];
		currThread->Check(this->numToCheck, this->currDivisor, this, &isPrime);
		usedThreadList.push_front(currThread);
		availableThreadList.pop_back();
		currThread->start();
		this->currDivisor -= 1;
		
	}
	
	//Display result
	if (this->usedThreadList.size() <= 0 && !isDone) {
		if (this->isPrime)
			std::cout << numToCheck << " is a prime number." << std::endl;
		else {
			std::cout << numToCheck << " is not a prime number." << std::endl;
		}
		this->isDone = true;
	}
}

void PrimeChecker::onFinishedExecution()
{
	//Return used thread (last index) to available threads (front)
	if (this->usedThreadList.size() > 0) {
		PrimeCheckerThread* currThread = usedThreadList[usedThreadList.size() - 1];
		usedThreadList.pop_back();
		availableThreadList.push_front(currThread);
	}
}
