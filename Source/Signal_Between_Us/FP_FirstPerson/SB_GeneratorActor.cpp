#include "SB_GeneratorActor.h"
#include "SB_GeneratorMiniGameWidget.h"
#include "SB_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASB_GeneratorActor::ASB_GeneratorActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASB_GeneratorActor::BeginPlay()
{
	Super::BeginPlay();

	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->OnPowerLost.AddDynamic(this, &ASB_GeneratorActor::ResetGenerator);
	}
}

bool ASB_GeneratorActor::CanUseGenerator() const
{
	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GM)
		return false;

	return GM->IsCableCollected() && !bMiniGameCompleted;
}

void ASB_GeneratorActor::StartMiniGame()
{
	if (!MiniGameWidgetClass)
		return;

	if (!CanUseGenerator())
		return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC)
		return;

	ActiveWidget = CreateWidget<USB_GeneratorMiniGameWidget>(PC, MiniGameWidgetClass);

	if (!ActiveWidget)
		return;

	ActiveWidget->AddToViewport();
	ActiveWidget->SetGenerator(this);

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void ASB_GeneratorActor::OnMiniGameCompleted(bool bSuccess)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	if (ActiveWidget)
	{
		ActiveWidget->RemoveFromParent();
		ActiveWidget = nullptr;
	}

	if (!bSuccess)
		return;
	bMiniGameCompleted = true;

	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GM)
	{
		GM->RestorePower();
	}
}

void ASB_GeneratorActor::ResetGenerator()
{
	bMiniGameCompleted = false;
}