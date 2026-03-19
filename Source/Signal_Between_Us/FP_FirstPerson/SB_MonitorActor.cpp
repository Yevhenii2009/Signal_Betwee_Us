#include "SB_MonitorActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "SB_GameMode.h"
#include "Kismet/GameplayStatics.h"

ASB_MonitorActor::ASB_MonitorActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	ScreenText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScreenText"));
	ScreenText->SetupAttachment(RootComponent);
	ScreenText->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	ScreenText->SetHorizontalAlignment(EHTA_Center);
	ScreenText->SetWorldSize(50.f);
	ScreenText->SetTextRenderColor(FColor::Green);
	ScreenText->SetText(FText::FromString("NO POWER"));
}

void ASB_MonitorActor::BeginPlay()
{
	Super::BeginPlay();

	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->OnPowerRestored.AddDynamic(this, &ASB_MonitorActor::ActivateMonitor);
		GM->OnPowerLost.AddDynamic(this, &ASB_MonitorActor::DeactivateMonitor);

		if (GM->IsPowerOn())
		{
			ActivateMonitor();
		}
	}
}

void ASB_MonitorActor::ActivateMonitor()
{
	GetWorld()->GetTimerManager().SetTimer(
		UpdateTimerHandle,
		this,
		&ASB_MonitorActor::UpdateMonitor,
		1.0f,
		true
	);
}

void ASB_MonitorActor::DeactivateMonitor()
{
	GetWorld()->GetTimerManager().ClearTimer(UpdateTimerHandle);
	ScreenText->SetText(FText::FromString("NO POWER"));
}

void ASB_MonitorActor::UpdateMonitor()
{
	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GM) return;

	// Get generator power percent
	float GeneratorPercent = GM->GetRemainingPowerPercent();

	// Display only generator power
	FString Text = FString::Printf(
		TEXT("GENERATOR POWER: %.0f%%"),
		GeneratorPercent
	);

	ScreenText->SetText(FText::FromString(Text));
}
