#include "ZE_Core.h"
#include "ZE_EventDispatcher.h"

using namespace std;

// FIXME：这个函数不能在多线程中调用，因为GlobalState没法在构造函数中初始化，现在在此类型的某个对象初始化时间比GlobalState早
void EventDispatcher::addEventListener(EventMode event_mode, Uint32 type, function<void(SDL_Event)> func)
{
	GlobalState->ZE_eventHandler->addEventFunction(dispatch_index, event_mode, type, func);
}

void EventDispatcher::removeEventListeners(SDL_EventType type) const
{
	GlobalState->ZE_eventHandler->removeAllEventOfDispatchAndType(dispatch_index, type);
}

void EventDispatcher::removeEventListeners(EventMode type) const
{
	GlobalState->ZE_eventHandler->removeAllEventOfDispatchAndModeType(dispatch_index, type);
}

void EventDispatcher::removeAllEvents() const
{
	GlobalState->ZE_eventHandler->removeAllEventOfDispatch(this->dispatch_index);
}

// 所有的EventDispatcher都应该在GlobalState->ZE_eventHandler初始化后初始化
EventDispatcher::EventDispatcher()
	:dispatch_index(GlobalState->ZE_eventHandler->dispatchIndexDistributor())
{}

EventDispatcher::~EventDispatcher()
{
	removeAllEvents();
}
