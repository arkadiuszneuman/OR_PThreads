#include "stdafx.h"
#include "Message.h"


Message::Message(int msg)
{
	this->msg = msg;
}


Message::~Message(void){}

bool Message::allRead()
{
	for (int i = 0; i < CONSUMER_COUNT; ++i)
	{
		if (!read[i])
			return false;
	}

	return true;
}

void Message::setRead(int threadID)
{
	read[threadID] = true;
}
