#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FP_FirstPersonCharacter.generated.h"

class ASB_CableActor;
class ASB_GeneratorActor;
class ASB_SignalConsoleActor;

UCLASS()
class SIGNAL_BETWEEN_US_API AFP_FirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFP_FirstPersonCharacter();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	/* Player interaction input */
	void Interact();

	/* LineTrace check for interactable objects */
	void CheckForInteractable();

private:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere)
	float InteractionDistance = 600.f;

	ASB_CableActor* CurrentCable;
	ASB_GeneratorActor* CurrentGenerator;

	/* Signal console reference */
	ASB_SignalConsoleActor* CurrentConsole;
};