#include "FP_FirstPersonCharacter.h"
#include "SB_CableActor.h"
#include "SB_GeneratorActor.h"
#include "SB_SignalConsoleActor.h"
#include "SB_AntennaActor.h"
#include "SB_AntennaPartActor.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

AFP_FirstPersonCharacter::AFP_FirstPersonCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
    FirstPersonCamera->bUsePawnControlRotation = true;

    GetCharacterMovement()->MaxWalkSpeed = 400.f;
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    CurrentCable = nullptr;
    CurrentGenerator = nullptr;
    CurrentConsole = nullptr;
    CurrentAntenna = nullptr;
    CurrentAntennaPart = nullptr;
}

void AFP_FirstPersonCharacter::BeginPlay()
{
    Super::BeginPlay();

    PrimaryActorTick.SetTickFunctionEnable(true);
    SetActorTickEnabled(true);
}

void AFP_FirstPersonCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckForInteractable();
}

void AFP_FirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AFP_FirstPersonCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFP_FirstPersonCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFP_FirstPersonCharacter::Interact);
    PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AFP_FirstPersonCharacter::Interact);
}

void AFP_FirstPersonCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void AFP_FirstPersonCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void AFP_FirstPersonCharacter::Interact()
{
    if (CurrentCable)
    {
        CurrentCable->Interact();
        return;
    }

    if (CurrentGenerator)
    {
        CurrentGenerator->StartMiniGame();
        return;
    }

    if (CurrentConsole)
    {
        CurrentConsole->Interact();
        return;
    }

    if (CurrentAntennaPart)
    {
        CurrentAntennaPart->Interact();
        return;
    }

    if (CurrentAntenna)
    {
        CurrentAntenna->Interact();
        return;
    }
}

void AFP_FirstPersonCharacter::CheckForInteractable()
{
    if (!FirstPersonCamera) return;

    FVector Start = FirstPersonCamera->GetComponentLocation();
    FVector End = Start + FirstPersonCamera->GetForwardVector() * InteractionDistance;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    CurrentCable = nullptr;
    CurrentGenerator = nullptr;
    CurrentConsole = nullptr;
    CurrentAntenna = nullptr;
    CurrentAntennaPart = nullptr;

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        Start,
        End,
        ECC_Visibility,
        Params
    );

    if (bHit && Hit.GetActor())
    {
        AActor* HitActor = Hit.GetActor();

        if (ASB_CableActor* Cable = Cast<ASB_CableActor>(HitActor))
        {
            CurrentCable = Cable;
            return;
        }
        if (ASB_GeneratorActor* Generator = Cast<ASB_GeneratorActor>(HitActor))
        {
            CurrentGenerator = Generator;
            return;
        }
        if (ASB_SignalConsoleActor* Console = Cast<ASB_SignalConsoleActor>(HitActor))
        {
            CurrentConsole = Console;
            return;
        }
        if (ASB_AntennaPartActor* Part = Cast<ASB_AntennaPartActor>(HitActor))
        {
            CurrentAntennaPart = Part;
            return;
        }
        if (ASB_AntennaActor* Antenna = Cast<ASB_AntennaActor>(HitActor))
        {
            CurrentAntenna = Antenna;
            return;
        }
    }
}