#pragma once

class EventBus {
public:
	EventBus();
	~EventBus();

	template<typename TEvent> void SubscribeToEvent();
	template<typename TEvent> void EmitEvent();
};