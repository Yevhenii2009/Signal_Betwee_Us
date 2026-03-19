#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SB_GameState.generated.h"

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	void SetCableCollected();
	bool IsCableCollected() const;

	void SetPowerOn(bool bOn);
	bool IsPowerOn() const;
	void SetRemainingPowerTime(float Time);
	float GetRemainingPowerTime() const;

	void SetGeneratorDuration(float Duration);
	float GetGeneratorDuration() const;

private:
	bool bCableCollected = false;
	bool bPowerOn = false;

	float RemainingPowerTime = 0.f;
	float GeneratorDuration = 15.f;
};