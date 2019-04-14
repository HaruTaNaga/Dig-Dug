#pragma once
#include "BaseState.h"


class IdleState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~IdleState() = default;
private:

};

class WalkingState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~WalkingState() = default;
private:

};


class ShootingState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~ShootingState() = default;
private:

};

class PumpingState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~PumpingState() = default;
private:

};

class ChrushingState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~ChrushingState() = default;
private:

};

class DyingState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~DyingState() = default;
private:

};

class RespawnState final : public BaseState
{
public:
	void Update(StateArgs & EvArg) {};
	~RespawnState() = default;
private:

};