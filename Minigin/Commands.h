#pragma once
#include "MiniginPCH.h"
#include "GameObject.h"
namespace  dae {
	class Command
	{
		virtual ~Command() = default;
		virtual void Execute(const GameObject& go) = 0 ; 

	};

	class MoveLeftCommand : public Command
	{
		 ~MoveLeftCommand() = default;
		 void Execute(const GameObject& go) override {

		 }
	};
	class MoveRightCommand : public Command
	{
		~MoveRightCommand() = default;
		void Execute(const GameObject& go) override {

		}
	};
	class MoveUpCommand : public Command
	{
		~MoveUpCommand() = default;
		void Execute(const GameObject& go)  override {

		}
	};
	class MoveDownCommand : public Command
	{
		~MoveDownCommand() = default;
		void Execute(const GameObject& go) override {

		}
	};
}
