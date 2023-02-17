#include "PrimeChecker.h"

int SUBTRACTOR = (2147483647/1) + 0;
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
	begin = std::chrono::steady_clock::now();

	//Create threads
	this->currDivisor = numToCheck;
	if ((currDivisor - SUBTRACTOR) > 0) {
		currNumber = currDivisor - SUBTRACTOR;
	}

	else {
		currNumber = 2;
	}
	
	while (index < numOfThreads && !isDone) {
		std::cout << "Index: " << index << " Min: " << currNumber << " Max: " << currDivisor << std::endl;
		PrimeCheckerThread* currThread = new PrimeCheckerThread(index);
		currThread->Check(this->currNumber, this->numToCheck, this->currDivisor, this, &isPrime);
		currThread->start();

		if (currNumber <= 2) {
			currNumber = 0;
		}
		else if ((this->currDivisor - SUBTRACTOR) < 0) {
			currDivisor -= 1;
			this->currNumber = 2;
		}
		else { 
			this->currDivisor -= (SUBTRACTOR + 1);
			if ((currDivisor - SUBTRACTOR) < 0) {
				currNumber = 2;
			}
			else {
				currNumber = currDivisor - SUBTRACTOR;
			}
		}
		index++;
	}
}

void PrimeChecker::processInput(sf::Event event)
{
}

void PrimeChecker::update(sf::Time deltaTime)
{
	//Display result
	if (finishedThreads >= numOfThreads && !isDone) {
		if (this->isPrime)
			std::cout << numToCheck << " is a prime number." << std::endl;
		else {
			std::cout << numToCheck << " is not a prime number." << std::endl;
		}
		end = std::chrono::steady_clock::now();
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
		this->isDone = true;
	}
}

void PrimeChecker::onFinishedExecution(int id)
{
	finishedThreads++;
}
