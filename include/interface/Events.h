#ifndef interface_Events_h
#define interface_Events_h

#include <queue>
#include <string>

namespace interface
{

class Widget;

class Event
{
public:
	Event():source(NULL){}
	Widget* source;
	std::string type;
};

class Event_queue
{
public:
	bool Empty();
	void Add_event(Event event);
	Event Get_next_event();
private:
	typedef std::queue<Event> Queue;
	Queue queue;
};

void Add_event_queue(Event_queue* event_queue);
void Remove_event_queue(Event_queue* event_queue);
void Emit_event(Event event);

void Push_event_queues();
void Pop_event_queues();

}

#endif
