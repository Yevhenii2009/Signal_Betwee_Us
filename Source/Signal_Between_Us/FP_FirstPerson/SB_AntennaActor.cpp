#include "SB_AntennaActor.h"
#include "SB_AntennaRepairWidget.h"
#include "FP_FirstPersonCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

ASB_AntennaActor::ASB_AntennaActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	RepairPart1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RepairPart1"));
	RepairPart1->SetupAttachment(BaseMesh);

	RepairPart2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RepairPart2"));
	RepairPart2->SetupAttachment(BaseMesh);

	RepairPart3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RepairPart3"));
	RepairPart3->SetupAttachment(BaseMesh);
}

void ASB_AntennaActor::BeginPlay()
{
	Super::BeginPlay();

	if (RepairPart1) RepairPart1->SetVisibility(false);
	if (RepairPart2) RepairPart2->SetVisibility(false);
	if (RepairPart3) RepairPart3->SetVisibility(false);
}

void ASB_AntennaActor::Interact()
{
	AFP_FirstPersonCharacter* Player =
		Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!Player)
		return;

	if (Player->bCarryingAntennaPart && InstalledParts < 3)
	{
		InstallPart();
		Player->bCarryingAntennaPart = false;
		return;
	}

	if (bAntennaComplete)
	{
		OpenRepairUI();
	}
}

void ASB_AntennaActor::InstallPart()
{
	InstalledParts++;

	if (InstalledParts == 1)
		RepairPart1->SetVisibility(true);

	if (InstalledParts == 2)
		RepairPart2->SetVisibility(true);

	if (InstalledParts == 3)
	{
		RepairPart3->SetVisibility(true);
		bAntennaComplete = true;
	}
}

void ASB_AntennaActor::OpenRepairUI()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC || !RepairWidgetClass)
		return;

	USB_AntennaRepairWidget* Widget =
		CreateWidget<USB_AntennaRepairWidget>(PC, RepairWidgetClass);

	if (!Widget)
		return;

	Widget->AddToViewport();

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}