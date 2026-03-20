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

	// ❗ Проверка правильного порядка установки
	if (Player->bCarryingAntennaPart &&
		Player->CarriedPartIndex == InstalledParts + 1)
	{
		InstallPart(Player->CarriedPartIndex);

		Player->bCarryingAntennaPart = false;
		return;
	}

	if (bAntennaComplete)
	{
		OpenRepairUI();
	}
}

void ASB_AntennaActor::InstallPart(int PartIndex)
{
	InstalledParts++;

	if (PartIndex == 1 && RepairPart1)
		RepairPart1->SetVisibility(true);

	if (PartIndex == 2 && RepairPart2)
		RepairPart2->SetVisibility(true);

	if (PartIndex == 3 && RepairPart3)
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