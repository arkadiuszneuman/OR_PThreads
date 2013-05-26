#pragma once

#include <string>
#include "Config.h"

using namespace std;

class Message
{
private:
	int msg;
	bool read[CONSUMER_COUNT];

public:
	Message(int msg);
	~Message(void);

	int getMsg() { return msg; }

	void setRead(int threadId);
	bool allRead();	
};

