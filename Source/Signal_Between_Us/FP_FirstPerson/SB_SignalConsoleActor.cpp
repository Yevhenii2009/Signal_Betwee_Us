#include "SB_SignalConsoleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SB_GameMode.h"
#include "GameFramework/PlayerController.h"
#include "SB_SignalConsoleWidget.h"

ASB_SignalConsoleActor::ASB_SignalConsoleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionProfileName("BlockAll");

	ActiveWidget = nullptr;
}

void ASB_SignalConsoleActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASB_SignalConsoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ActiveWidget) return;

	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GM) return;

	// If generator turned off -> close console
	if (!GM->IsPowerOn())
	{
		CloseConsoleUI();
		return;
	}

	// Update generator percent in real time
	float CurrentPower = GM->GetRemainingPowerPercent();
	ActiveWidget->SetGeneratorPercent(CurrentPower);
}

void ASB_SignalConsoleActor::Interact()
{
	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GM) return;

	// Console works only if power is on
	if (!GM->IsPowerOn())
	{
		UE_LOG(LogTemp, Warning, TEXT("Console has no power"));
		return;
	}

	// Prevent opening multiple times
	if (ActiveWidget)
	{
		return;
	}

	OpenConsoleUI();
}

void ASB_SignalConsoleActor::OpenConsoleUI()
{
	if (!ConsoleWidgetClass) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	ActiveWidget = CreateWidget<USB_SignalConsoleWidget>(PC, ConsoleWidgetClass);
	if (!ActiveWidget) return;

	// subscribe to close event
	ActiveWidget->OnConsoleClosed.AddDynamic(this, &ASB_SignalConsoleActor::CloseConsoleUI);

	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));

	if (GM)
	{
		float CurrentPower = GM->GetRemainingPowerPercent();
		ActiveWidget->SetGeneratorPercent(CurrentPower);
	}

	ActiveWidget->SetSignalStrength(SignalStrength);

	ActiveWidget->AddToViewport();

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void ASB_SignalConsoleActor::CloseConsoleUI()
{
	if (!ActiveWidget) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	ActiveWidget->RemoveFromParent();
	ActiveWidget = nullptr;
}