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

	/* Player interaction input */
	void Interact();

	/* LineTrace check for interactable objects */
	void CheckForInteractable();

public:
	/* 🔹 Игрок может нести только ОДНУ деталь */
	UPROPERTY(BlueprintReadWrite)
	bool bCarryingAntennaPart = false;

	/* 🔹 Номер переносимой детали (0 = ничего, 1-3 = части антенны) */
	UPROPERTY(BlueprintReadWrite)
	int CarriedPartIndex = 0;

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere)
	float InteractionDistance = 600.f;

	ASB_CableActor* CurrentCable;
	ASB_GeneratorActor* CurrentGenerator;

	/* Signal console reference */
	ASB_SignalConsoleActor* CurrentConsole;

	/* Antenna */
	ASB_AntennaActor* CurrentAntenna;

	/* Antenna repair part */
	ASB_AntennaPartActor* CurrentAntennaPart;
};