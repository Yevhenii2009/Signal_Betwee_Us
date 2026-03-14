#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_GeneratorMiniGameWidget.generated.h"

class UImage;
class UButton;
class UTextBlock;
class ASB_GeneratorActor;

UCLASS()
class SIGNAL_BETWEEN_US_API USB_GeneratorMiniGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	void SetGenerator(ASB_GeneratorActor* InGenerator);
	void CheckInput();

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CursorImage;

	UPROPERTY(meta = (BindWidget))
	UImage* SuccessZone;

	UPROPERTY(meta = (BindWidget))
	UImage* PerfectZone;

	UPROPERTY(meta = (BindWidget))
	UButton* SkillButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResultText;

private:
	void GenerateZones();
	void UpdateScoreText();
	void FinishMiniGame(bool bSuccess);

	UFUNCTION()
	void OnSkillPressed();

	float CursorPosition = 0.f;
	float CursorSpeed = 500.f;
	bool bMoveRight = true;
	float BaseCursorSpeed = 500.f;


	float SpeedIncrease = 200.f;
	float MaxCursorSpeed = 1500.f;
	float SuccessStart;
	float SuccessEnd;

	float PerfectStart;
	float PerfectEnd;

	int Score = 0;
	int RequiredScore = 5;

	ASB_GeneratorActor* Generator;
};