#pragma once
#include <iostream>
#include "IETThread.h"

class IExecutionEvent;
class PrimeCheckerThread : public IETThread
{
private:
	typedef std::string String;
public:
	PrimeCheckerThread(int id);
	void Check(int numToCheck, int currDivisor, IExecutionEvent* execEvent, bool* isPrime);
	~PrimeCheckerThread();

public:
	int id;

private:
	void run() override;
	
	bool isRunning = false;
	int numToCheck;
	int currDivisor;
	bool* isPrime; 
	IExecutionEvent* execEvent;
};

