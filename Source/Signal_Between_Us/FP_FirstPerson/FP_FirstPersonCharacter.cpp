#include "FP_FirstPersonCharacter.h"
#include "SB_CableActor.h"
#include "SB_GeneratorActor.h"
#include "SB_SignalConsoleActor.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

/*
Constructor

Initializes player camera, movement settings
and interaction variables.
*/
AFP_FirstPersonCharacter::AFP_FirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Automatically possess this character as Player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set capsule collision size
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Create first person camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Configure movement parameters
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Initialize interactable references
	CurrentCable = nullptr;
	CurrentGenerator = nullptr;
	CurrentConsole = nullptr;
}

/*
Tick

Runs every frame.
Used here to constantly check for interactable objects.
*/
void AFP_FirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForInteractable();
}

/*
SetupPlayerInputComponent

Binds player input (movement, camera, jump, interaction).
*/
void AFP_FirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Movement input
	PlayerInputComponent->BindAxis("MoveForward", this, &AFP_FirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFP_FirstPersonCharacter::MoveRight);

	// Camera rotation
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Jump input
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Interaction input
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFP_FirstPersonCharacter::Interact);
}

/*
MoveForward

Moves the character forward/backward.
*/
void AFP_FirstPersonCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

/*
MoveRight

Moves the character left/right.
*/
void AFP_FirstPersonCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

/*
Interact

Handles interaction with nearby objects:
- Cable
- Generator
- Signal Console
*/
void AFP_FirstPersonCharacter::Interact()
{
	// Cable interaction
	if (CurrentCable)
	{
		CurrentCable->Interact();
		return;
	}

	// Generator interaction
	if (CurrentGenerator)
	{
		CurrentGenerator->StartMiniGame();
		return;
	}

	// Signal console interaction
	if (CurrentConsole)
	{
		CurrentConsole->Interact();
		return;
	}
}

/*
CheckForInteractable

Uses LineTrace from the camera to detect
interactable objects in front of the player.
*/
void AFP_FirstPersonCharacter::CheckForInteractable()
{
	// Start position (camera)
	FVector Start = FirstPersonCamera->GetComponentLocation();

	// End position (forward direction)
	FVector End = Start + FirstPersonCamera->GetForwardVector() * InteractionDistance;

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// Reset interactable references
	CurrentCable = nullptr;
	CurrentGenerator = nullptr;
	CurrentConsole = nullptr;

	// Perform LineTrace
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	if (bHit)
	{
		// Check Cable
		if (ASB_CableActor* Cable = Cast<ASB_CableActor>(Hit.GetActor()))
		{
			CurrentCable = Cable;
			return;
		}

		// Check Generator
		if (ASB_GeneratorActor* Generator = Cast<ASB_GeneratorActor>(Hit.GetActor()))
		{
			CurrentGenerator = Generator;
			return;
		}

		// Check Signal Console
		if (ASB_SignalConsoleActor* Console = Cast<ASB_SignalConsoleActor>(Hit.GetActor()))
		{
			CurrentConsole = Console;
			return;
		}
	}
}