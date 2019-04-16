#pragma once
#include "BaseEvent.h"
#include "MiniginPCH.h"
#include "ComponentsH.h"
#include <memory>
/*
namespace dae {
	//Up
	

	class InputEventKeyPressedUp final : public Event
	{
	public: 
		~InputEventKeyPressedUp() = default;
		void Execute(EventArgs & EvArg) override
		{
			dynamic_cast<EventArgKeyDown &>(EvArg).MComp.SetVelocity( 0,-g_runspeed);
		};
	};

	//Right
	class InputEventKeyPressedRight final : public Event
	{
	public:
		~InputEventKeyPressedRight() = default;
		void Execute(EventArgs & EvArg) override
		{
			dynamic_cast<EventArgKeyDown &>(EvArg).MComp.SetVelocity(g_runspeed, 0);
		};
	};
	//Down

	class InputEventKeyPressedDown final : public Event
	{
	public:
		~InputEventKeyPressedDown() = default;
		void Execute(EventArgs & EvArg) override
		{
			dynamic_cast<EventArgKeyDown &>(EvArg).MComp.SetVelocity(0, g_runspeed);
		};
	};
	//Left
	
	class InputEventKeyPressedLeft  final  : public Event 
	{
	public:
		~InputEventKeyPressedLeft() = default;
		void Execute(EventArgs & EvArg) override
		{
			dynamic_cast<EventArgKeyDown &>(EvArg).MComp.SetVelocity(-g_runspeed, 0);
		};
	};
	class InputEventKeyUp  final : public Event
	{
	public:
		~InputEventKeyUp() = default;
		void Execute(EventArgs & EvArg) override
		{
			dynamic_cast<EventArgKeyDown &>(EvArg).MComp.SetVelocity(0, 0);
		};
	};
	class InputEventEmpty  final : public Event
	{
	public:
		~InputEventEmpty() = default;
		void Execute(EventArgs & ) override
		{
			
		};
	};
	struct PlayerInputKeyEvents {

		InputEventKeyPressedRight  KeyDownRight;
		InputEventKeyPressedLeft KeyDownLeft;
		InputEventKeyPressedDown  KeyDownDown;
		InputEventKeyPressedUp KeyDownUp;
		InputEventKeyUp KeyUp; 
		InputEventEmpty EmptyEvent;  
	};
}*/
