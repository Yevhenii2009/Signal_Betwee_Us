#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_AntennaPartActor.generated.h"

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_AntennaPartActor : public AActor
{
	GENERATED_BODY()

public:
	ASB_AntennaPartActor();

	void Interact();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PartIndex = 1;
};