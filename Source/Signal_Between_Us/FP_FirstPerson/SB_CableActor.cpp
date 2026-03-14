#include "SB_CableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SB_GameMode.h"

ASB_CableActor::ASB_CableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionProfileName("BlockAll");
}

void ASB_CableActor::Interact()
{
	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));

	if (GM)
	{
		GM->SetCableCollected();
	}

	Destroy();
}