#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_GeneratorActor.generated.h"

class USB_GeneratorMiniGameWidget;
class ASB_GameMode;

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_GeneratorActor : public AActor
{
	GENERATED_BODY()

public:
	ASB_GeneratorActor();

	void StartMiniGame();
	void OnMiniGameCompleted(bool bSuccess);

	bool CanUseGenerator() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Generator")
	TSubclassOf<USB_GeneratorMiniGameWidget> MiniGameWidgetClass;

private:

	UPROPERTY()
	USB_GeneratorMiniGameWidget* ActiveWidget;

	bool bMiniGameCompleted = false;

	UFUNCTION()
	void ResetGenerator();
};