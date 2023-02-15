#include "PrimeCheckerThread.h"
#include "IExecutionEvent.h"

PrimeCheckerThread::PrimeCheckerThread(int id)
{
	this->id = id;
}

void PrimeCheckerThread::Check(int currNumber, int numToCheck, int currDivisor, IExecutionEvent* execEvent, bool* isPrime)
{
	//Change values to be checked
	this->numToCheck = numToCheck;
	this->currNumber = currNumber;
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
		//std::cout << currNumber << std::endl;
		int max = currNumber + 10;
		//Prime checker logic
		//		current number		max number to check
		for (int i = currNumber; i <= max; i++){
			
			if (currDivisor != this->numToCheck) {
				//								change to max number
				if (currDivisor >= 2 && (this->numToCheck % i == 0)) {
					*isPrime = false;
					std::cout << numToCheck << "/" << i << " Check if Prime : False" << std::endl;
				}

				else {
					std::cout << numToCheck << "/" << i << " Check if Prime : True" << std::endl;
				}
			}			
		}
		
		isRunning = false;
		this->execEvent->onFinishedExecution();
	}
	
}
