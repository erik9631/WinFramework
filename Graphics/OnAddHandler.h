#pragma once
#include "AddSubject.h"
#include "OnAddSubscriber.h"
#include "EventOnAddInfo.h"
#include <vector>

template <class type>
class OnAddHandler : AddSubject<type>
{
private:
	std::vector<std::reference_wrapper<OnAddSubscriber<type>>> subscribers;
public:
	virtual void NotifyOnAddInfo(EventOnAddInfo<type> e) override
	{
		for (OnAddSubscriber<type>& subscriber : subscribers)
			subscriber.OnAdd(e);
	}

	virtual void AddOnAddSubscriber(OnAddSubscriber<type>& subscriber) override
	{
		subscribers.push_back(subscriber);
	}

	virtual void RemoveOnAddSubscriber(OnAddSubscriber<type>& subscriber) override
	{
		for (typename std::vector<std::reference_wrapper<OnAddSubscriber<type>>>::iterator it = subscribers.begin(); it != subscribers.end(); it++)
			if (&it->get() == &subscriber)
			{
				subscribers.erase(it);
				return;
			}

	}
};