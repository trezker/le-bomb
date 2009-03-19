#include "interface/Events.h"
#include <list>
#include <algorithm>

namespace interface
{

typedef std::list<Event_queue*> Event_queues;
Event_queues event_queues;

void Add_event_queue(Event_queue* event_queue)
{
	event_queues.push_back(event_queue);
}

void Remove_event_queue(Event_queue* event_queue)
{
	Event_queues::iterator i = std::find(event_queues.begin(), event_queues.end(), event_queue);
	if(i != event_queues.end())
	{
		event_queues.erase(i);
	}
}

void Emit_event(Event event)
{
	for(Event_queues::iterator i = event_queues.begin(); i != event_queues.end(); ++i)
	{
		(*i)->Add_event(event);
	}
}

void Event_queue::Add_event(Event event)
{
	queue.push(event);
}

Event Event_queue::Get_next_event()
{
	if(queue.empty())
		return Event();
	Event event = queue.front();
	queue.pop();
	return event;
}

}
