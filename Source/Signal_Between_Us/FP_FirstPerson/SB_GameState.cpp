#include "SB_GameState.h"

void ASB_GameState::SetCableCollected()
{
	bCableCollected = true;
}

bool ASB_GameState::IsCableCollected() const
{
	return bCableCollected;
}

void ASB_GameState::SetPowerOn(bool bOn)
{
	bPowerOn = bOn;
}
bool ASB_GameState::IsPowerOn() const
{
	return bPowerOn;
}

void ASB_GameState::SetRemainingPowerTime(float Time)
{
	RemainingPowerTime = Time;
}

float ASB_GameState::GetRemainingPowerTime() const
{
	return RemainingPowerTime;
}

void ASB_GameState::SetGeneratorDuration(float Duration)
{
	GeneratorDuration = Duration;
}

float ASB_GameState::GetGeneratorDuration() const
{
	return GeneratorDuration;
}