#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SB_AntennaRepairWidget.generated.h"

class UButton;

UCLASS()
class SIGNAL_BETWEEN_US_API USB_AntennaRepairWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* RepairButton;

	UFUNCTION()
	void OnRepairClicked();
};