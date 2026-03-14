#include "SB_AntennaPartActor.h"
#include "FP_FirstPersonCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ASB_AntennaPartActor::ASB_AntennaPartActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void ASB_AntennaPartActor::Interact()
{
	AFP_FirstPersonCharacter* Player =
		Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!Player)
		return;

	if (Player->bCarryingAntennaPart)
		return;

	Player->bCarryingAntennaPart = true;
	 
	Destroy();
}