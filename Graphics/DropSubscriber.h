#pragma once
#include "EventOnDragInfo.h"

class DropSubscriber
{
public:
	virtual void OnDragOver(EventOnDragInfo e) = 0;
	virtual void OnDrop(EventOnDragInfo e) = 0;
};

