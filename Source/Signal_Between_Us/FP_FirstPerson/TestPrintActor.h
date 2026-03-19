#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPrintActor.generated.h"

UCLASS()
class SIGNAL_BETWEEN_US_API ATestPrintActor : public AActor
{
	GENERATED_BODY()

public:
	// Конструктор
	ATestPrintActor();

protected:
	// Вызывается при старте игры
	virtual void BeginPlay() override;

public:
	// Вызывается каждый тик
	virtual void Tick(float DeltaTime) override;
};