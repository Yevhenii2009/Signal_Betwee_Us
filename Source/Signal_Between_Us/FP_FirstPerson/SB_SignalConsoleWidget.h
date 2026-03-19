#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "SB_SignalConsoleWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConsoleClosed);

UCLASS()
class SIGNAL_BETWEEN_US_API USB_SignalConsoleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetGeneratorPercent(float NewPercent);

	UFUNCTION(BlueprintCallable)
	void SetSignalStrength(float NewSignal);

	/* Actor subscribes to this */
	UPROPERTY(BlueprintAssignable)
	FOnConsoleClosed OnConsoleClosed;

protected:

	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_GeneratorStatus;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SignalLevel;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartUpgrade;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Back;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Display;

private:

	float GeneratorPercent = 0.f;
	float SignalStrength = 0.f;

	UFUNCTION()
	void OnGeneratorStatusClicked();

	UFUNCTION()
	void OnSignalLevelClicked();

	UFUNCTION()
	void OnStartUpgradeClicked();

	UFUNCTION()
	void OnBackClicked();

	UFUNCTION()
	void OnCloseClicked();

	void UpdateDisplayText();

	FString CurrentPage;
};