#include "SB_InteractionWidget.h"

void USB_InteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InteractionText)
	{
		InteractionText->SetText(FText::FromString("Press E"));
		InteractionText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USB_InteractionWidget::ShowInteraction(bool bShow)
{
	if (!InteractionText) return;

	InteractionText->SetVisibility(
		bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden
	);
}	