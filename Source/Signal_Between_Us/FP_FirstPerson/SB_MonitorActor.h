#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_MonitorActor.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_MonitorActor : public AActor
{
	GENERATED_BODY()

public:
	ASB_MonitorActor();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActivateMonitor();

	UFUNCTION()
	void DeactivateMonitor();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* ScreenText;

	FTimerHandle UpdateTimerHandle;

	void UpdateMonitor();
};