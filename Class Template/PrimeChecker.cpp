#include "PrimeChecker.h"

const int SUBTRACTOR = 100;
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
		// this->numToCheck (max)
		// subtracted by 10 per increment
		// 0-10
		// 11-20
		// 21-30 and so on
		this->currNumber = this->currDivisor - SUBTRACTOR;
		if (this->currNumber < 0) {
			this->currNumber = 2;
		}
		currThread->Check(this->currNumber, this->numToCheck, this->currDivisor, this, &isPrime);
		usedThreadList.push_front(currThread);
		availableThreadList.pop_back();
		currThread->start();
		this->currDivisor -= SUBTRACTOR;
		if (this->currDivisor < 0) {
			currDivisor -= 1;
			if (currDivisor < 1) {
				currDivisor = 0;
			}
		}
		//std::cout << this->currDivisor << std::endl;
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
