#pragma once
//Listener for calling specific functions after a thread has finished execution

class IExecutionEvent 
{
public:
	virtual void onFinishedExecution(int id) = 0;
};