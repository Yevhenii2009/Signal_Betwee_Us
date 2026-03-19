#include "SB_LightActor.h"
#include "Components/PointLightComponent.h"
#include "SB_GameMode.h"
#include "Kismet/GameplayStatics.h"

ASB_LightActor::ASB_LightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	RootComponent = LightComponent;

	LightComponent->SetMobility(EComponentMobility::Movable);
	LightComponent->SetVisibility(false);
	LightComponent->SetIntensity(FMath::FRandRange(2000.f, 5000.f));
	LightComponent->SetLightColor(FLinearColor::White);
}

void ASB_LightActor::BeginPlay()
{
	Super::BeginPlay();

	ASB_GameMode* GM = Cast<ASB_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->OnPowerRestored.AddDynamic(this, &ASB_LightActor::ActivateLight);
		GM->OnPowerLost.AddDynamic(this, &ASB_LightActor::DeactivateLight);

		if (GM->IsPowerOn())
		{
			ActivateLight();
		}
	}
}

void ASB_LightActor::ActivateLight()
{
	GetWorld()->GetTimerManager().SetTimer(
		FlickerTimerHandle,
		this,
		&ASB_LightActor::FlickerLight,
		0.1f,
		true
	);

	GetWorld()->GetTimerManager().SetTimer(
		StopFlickerHandle,
		this,
		&ASB_LightActor::StopFlicker,
		3.0f,
		false
	);
}

void ASB_LightActor::DeactivateLight()
{
	GetWorld()->GetTimerManager().ClearTimer(FlickerTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(StopFlickerHandle);

	if (LightComponent)
	{
		LightComponent->SetVisibility(false);
	}
}

void ASB_LightActor::FlickerLight()
{
	if (LightComponent)
	{
		LightComponent->SetVisibility(!LightComponent->IsVisible());
	}
}

void ASB_LightActor::StopFlicker()
{
	GetWorld()->GetTimerManager().ClearTimer(FlickerTimerHandle);

	if (LightComponent)
	{
		LightComponent->SetVisibility(true);
	}
}