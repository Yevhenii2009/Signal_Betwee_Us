#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SB_GameState.h"
#include "SB_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowerRestoredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowerLostDelegate);

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASB_GameMode();

	UPROPERTY(BlueprintAssignable)
	FOnPowerRestoredDelegate OnPowerRestored;

	UPROPERTY(BlueprintAssignable)
	FOnPowerLostDelegate OnPowerLost;

	void SetCableCollected();
	bool IsCableCollected() const;

	void RestorePower();
	void TurnOffPower();

	bool IsPowerOn() const;
	float GetRemainingPowerPercent() const;

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	FTimerHandle GeneratorTimerHandle;
};