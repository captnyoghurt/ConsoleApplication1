#pragma once

#include "B_Event.h"
#include "Fighter.h"
#include <memory>

class B_EventAttack : public B_Event
{
public:
	B_EventAttack();
	~B_EventAttack();

public:

	// Do the event
	virtual int execute(Battle *bat);
private:

};

