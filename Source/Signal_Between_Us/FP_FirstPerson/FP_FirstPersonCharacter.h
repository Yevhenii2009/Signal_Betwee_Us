#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FP_FirstPersonCharacter.generated.h"

class ASB_CableActor;
class ASB_GeneratorActor;
class ASB_SignalConsoleActor;
class ASB_AntennaActor;
class ASB_AntennaPartActor;
class USB_InteractionWidget;

UCLASS()
class SIGNAL_BETWEEN_US_API AFP_FirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFP_FirstPersonCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Interact();
	void CheckForInteractable();

private:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere)
	float InteractionDistance = 600.f;

	/* 🔹 Виджет */
	UPROPERTY()
	TSubclassOf<USB_InteractionWidget> InteractionWidgetClass;

	UPROPERTY()
	USB_InteractionWidget* InteractionWidget;

	ASB_CableActor* CurrentCable;
	ASB_GeneratorActor* CurrentGenerator;
	ASB_SignalConsoleActor* CurrentConsole;
	ASB_AntennaActor* CurrentAntenna;
	ASB_AntennaPartActor* CurrentAntennaPart;

public:

	UPROPERTY(BlueprintReadWrite)
	bool bCarryingAntennaPart = false;

	UPROPERTY(BlueprintReadWrite)
	int CarriedPartIndex = 0;
};