#include "SB_GameMode.h"
#include "SB_GameState.h"
#include "FP_FirstPersonCharacter.h"
#include "TimerManager.h"

ASB_GameMode::ASB_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// ВОТ ГЛАВНОЕ ИСПРАВЛЕНИЕ
	DefaultPawnClass = AFP_FirstPersonCharacter::StaticClass();

	GameStateClass = ASB_GameState::StaticClass();
}
void ASB_GameMode::SetCableCollected()
{
	ASB_GameState* GS = GetGameState<ASB_GameState>();
	if (GS)
	{
		GS->SetCableCollected();
	}
}

bool ASB_GameMode::IsCableCollected() const
{
	ASB_GameState* GS = GetGameState<ASB_GameState>();
	return GS && GS->IsCableCollected();
}

void ASB_GameMode::RestorePower()
{
	ASB_GameState* GS = GetGameState<ASB_GameState>();
	if (!GS || GS->IsPowerOn())
		return;

	GS->SetPowerOn(true);
	GS->SetRemainingPowerTime(GS->GetGeneratorDuration());

	OnPowerRestored.Broadcast();

	GetWorldTimerManager().SetTimer(
		GeneratorTimerHandle,
		this,
		&ASB_GameMode::TurnOffPower,
		GS->GetGeneratorDuration(),
		false
	);
}

void ASB_GameMode::TurnOffPower()
{
	ASB_GameState* GS = GetGameState<ASB_GameState>();
	if (!GS || !GS->IsPowerOn())
		return;

	GS->SetPowerOn(false);
	GS->SetRemainingPowerTime(0.f);

	OnPowerLost.Broadcast();

	GetWorldTimerManager().ClearTimer(GeneratorTimerHandle);
}

bool ASB_GameMode::IsPowerOn() const
{
	ASB_GameState* GS = GetGameState<ASB_GameState>();
	return GS && GS->IsPowerOn();
}

float ASB_GameMode::GetRemainingPowerPercent() const
{
	ASB_GameState* GS = GetGameState<ASB_GameState>();
	if (!GS || !GS->IsPowerOn())
		return 0.f;

	float Remaining = GS->GetRemainingPowerTime();
	float Duration = GS->GetGeneratorDuration();

	if (Duration <= 0.f)
		return 0.f;

	return (Remaining / Duration) * 100.f;
}

void ASB_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ASB_GameState* GS = GetGameState<ASB_GameState>();
	if (!GS || !GS->IsPowerOn())
		return;

	float NewRemaining = GS->GetRemainingPowerTime() - DeltaSeconds;

	if (NewRemaining < 0.f)
		NewRemaining = 0.f;

	GS->SetRemainingPowerTime(NewRemaining);
}