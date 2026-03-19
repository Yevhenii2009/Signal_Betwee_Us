#include "SB_SignalConsoleWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

bool USB_SignalConsoleWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (Button_GeneratorStatus)
		Button_GeneratorStatus->OnClicked.AddDynamic(this, &USB_SignalConsoleWidget::OnGeneratorStatusClicked);
	if (Button_SignalLevel)
		Button_SignalLevel->OnClicked.AddDynamic(this, &USB_SignalConsoleWidget::OnSignalLevelClicked);

	if (Button_StartUpgrade)
		Button_StartUpgrade->OnClicked.AddDynamic(this, &USB_SignalConsoleWidget::OnStartUpgradeClicked);

	if (Button_Back)
		Button_Back->OnClicked.AddDynamic(this, &USB_SignalConsoleWidget::OnBackClicked);

	if (CloseButton)
		CloseButton->OnClicked.AddDynamic(this, &USB_SignalConsoleWidget::OnCloseClicked);

	CurrentPage = "MAIN";

	UpdateDisplayText();

	return true;
}

void USB_SignalConsoleWidget::SetGeneratorPercent(float NewPercent)
{
	GeneratorPercent = NewPercent;
	UpdateDisplayText();
}

void USB_SignalConsoleWidget::SetSignalStrength(float NewSignal)
{
	SignalStrength = NewSignal;
	UpdateDisplayText();
}

void USB_SignalConsoleWidget::OnGeneratorStatusClicked()
{
	CurrentPage = "GENERATOR";
	UpdateDisplayText();
}

void USB_SignalConsoleWidget::OnSignalLevelClicked()
{
	CurrentPage = "SIGNAL";
	UpdateDisplayText();
}

void USB_SignalConsoleWidget::OnStartUpgradeClicked()
{
	CurrentPage = "UPGRADE";
	UpdateDisplayText();
}

void USB_SignalConsoleWidget::OnBackClicked()
{
	CurrentPage = "MAIN";
	UpdateDisplayText();
}

void USB_SignalConsoleWidget::OnCloseClicked()
{
	OnConsoleClosed.Broadcast();
}

void USB_SignalConsoleWidget::UpdateDisplayText()
{
	if (!Text_Display) return;

	FString Text;

	if (CurrentPage == "GENERATOR")
	{
		Text = FString::Printf(TEXT("GENERATOR STATUS\n\nPower Level: %.0f%%"), GeneratorPercent);
	}
	else if (CurrentPage == "SIGNAL")
	{
		Text = FString::Printf(TEXT("SIGNAL ANALYSIS\n\nSignal Strength: %.0f%%"), SignalStrength);
	}
	else if (CurrentPage == "UPGRADE")
	{
		Text = "UPGRADE SYSTEM\n\nFeature not available.";
	}
	else
	{
		Text = "Signal Console\n\nSelect an option.";
	}

	Text_Display->SetText(FText::FromString(Text));
}