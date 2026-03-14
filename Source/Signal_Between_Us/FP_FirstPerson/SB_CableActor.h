#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_CableActor.generated.h"

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_CableActor : public AActor
{
	GENERATED_BODY()

public:
	ASB_CableActor();
	void Interact();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
};