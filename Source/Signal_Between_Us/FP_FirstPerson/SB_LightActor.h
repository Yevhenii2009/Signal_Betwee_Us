#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_LightActor.generated.h"

class UPointLightComponent;

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_LightActor : public AActor
{
	GENERATED_BODY()

public:
	ASB_LightActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* LightComponent;

	FTimerHandle FlickerTimerHandle;
	FTimerHandle StopFlickerHandle;

	UFUNCTION()
	void ActivateLight();

	UFUNCTION()
	void DeactivateLight();

	UFUNCTION()
	void FlickerLight();

	UFUNCTION()
	void StopFlicker();
};