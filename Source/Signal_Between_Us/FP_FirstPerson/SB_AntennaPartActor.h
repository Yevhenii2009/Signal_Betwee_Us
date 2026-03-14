#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_AntennaPartActor.generated.h"

/*
Simple pickup object for antenna repair.
Player can carry only one part at a time.
*/

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_AntennaPartActor : public AActor
{
	GENERATED_BODY()

public:
	ASB_AntennaPartActor();

	/* Called when player interacts */
	void Interact();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

};