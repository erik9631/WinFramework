#include "EventOnActivateInfo.h"

EventOnActivateInfo::EventOnActivateInfo(bool state)
{
    this->state = state;
}

bool EventOnActivateInfo::IsActive()
{
    return state;
}
