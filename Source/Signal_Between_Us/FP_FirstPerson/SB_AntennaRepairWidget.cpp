#include "SB_AntennaRepairWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void USB_AntennaRepairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RepairButton)
	{
		RepairButton->OnClicked.AddDynamic(this, &USB_AntennaRepairWidget::OnRepairClicked);
	}
}

void USB_AntennaRepairWidget::OnRepairClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	RemoveFromParent();
}