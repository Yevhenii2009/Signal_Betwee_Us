#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_AntennaActor.generated.h"

class UStaticMeshComponent;
class USB_AntennaRepairWidget;
UCLASS()
class SIGNAL_BETWEEN_US_API ASB_AntennaActor : public AActor
{
	GENERATED_BODY()

public:

	ASB_AntennaActor();

	void Interact();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RepairPart1;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RepairPart2;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RepairPart3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USB_AntennaRepairWidget> RepairWidgetClass;

private:

	int InstalledParts = 0;

	bool bAntennaComplete = false;

	void InstallPart();

	void OpenRepairUI();
};