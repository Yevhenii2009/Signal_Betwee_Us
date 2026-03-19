#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SB_SignalConsoleActor.generated.h"

class UStaticMeshComponent;
class USB_SignalConsoleWidget;

UCLASS()
class SIGNAL_BETWEEN_US_API ASB_SignalConsoleActor : public AActor
{
	GENERATED_BODY()
public:
	ASB_SignalConsoleActor();

	virtual void Tick(float DeltaTime) override;

	/* Called by player interaction */
	void Interact();

	/* Opens console UI */
	void OpenConsoleUI();

	/* Closes console UI */
	UFUNCTION()
	void CloseConsoleUI();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	/* Widget class assigned in Blueprint */
	UPROPERTY(EditAnywhere)
	TSubclassOf<USB_SignalConsoleWidget> ConsoleWidgetClass;

private:

	/* Current active widget */
	USB_SignalConsoleWidget* ActiveWidget;

	/* Example signal value */
	float SignalStrength = 37.f;

	/* Generator power percent */
	float GeneratorPercent = 100.f;
};