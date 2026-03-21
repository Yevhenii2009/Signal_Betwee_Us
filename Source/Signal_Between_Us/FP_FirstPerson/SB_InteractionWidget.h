#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SB_InteractionWidget.generated.h"

UCLASS()
class SIGNAL_BETWEEN_US_API USB_InteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	/* Показать / скрыть текст */
	UFUNCTION(BlueprintCallable)
	void ShowInteraction(bool bShow);

protected:

	/* Текст "Press E" (привязываешь в BP) */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionText;
};