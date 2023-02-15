#include "PrimeCheckerThread.h"
#include "IExecutionEvent.h"

PrimeCheckerThread::PrimeCheckerThread(int id)
{
	this->id = id;
}

void PrimeCheckerThread::Check(int numToCheck, int currDivisor, IExecutionEvent* execEvent, bool* isPrime)
{
	//Change values to be checked
	this->numToCheck = numToCheck;
	this->currDivisor = currDivisor;
	this->execEvent = execEvent;
	this->isPrime = isPrime;
	this->isRunning = true;
}

PrimeCheckerThread::~PrimeCheckerThread()
{
}

void PrimeCheckerThread::run()
{
	if (isRunning) {
		//Add sleep time
		IETThread::sleep(200);

		//Prime checker logic
		if (currDivisor >= 2 && (this->numToCheck % this->currDivisor == 0)) {
			*isPrime = false;
			std::cout <<  numToCheck << "/" << currDivisor << " Check if Prime : False" << std::endl;
		}

		else {
			std::cout << numToCheck << "/" << currDivisor << " Check if Prime : True"  << std::endl;
		}
		isRunning = false;
		this->execEvent->onFinishedExecution();
	}
	
}
