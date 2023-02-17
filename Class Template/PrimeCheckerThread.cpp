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
}

PrimeCheckerThread::~PrimeCheckerThread()
{
}

void PrimeCheckerThread::run()
{
	IETThread::sleep(500);

	for (int i = currNumber; i <= currDivisor; i++) {
		if (i != this->numToCheck) {
			if (i >= 2 && (this->numToCheck % i == 0)) {
				*isPrime = false;
			}
		}

		//std::cout << "Thread: " << currDivisor << " Divisor: " << i << std::endl;
		if (i == 2147483647) break;
	}
	
	this->execEvent->onFinishedExecution(this->id);
	delete this;
}
