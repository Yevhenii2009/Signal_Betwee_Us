#include "TestPrintActor.h"
#include "Engine/Engine.h"

ATestPrintActor::ATestPrintActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestPrintActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("C++ WORKS: BeginPlay triggered"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			TEXT("C++ WORKS: On Screen Message")
		);
	}
}

void ATestPrintActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// пусто, можно добавить проверку или логику позже
}