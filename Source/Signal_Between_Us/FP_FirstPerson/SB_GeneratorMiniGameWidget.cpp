#include "SB_GeneratorMiniGameWidget.h"
#include "SB_GeneratorActor.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

void USB_GeneratorMiniGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!BackgroundImage) return;

	FVector2D BGSize = BackgroundImage->GetCachedGeometry().GetLocalSize();

	if (CursorImage)
	{
		if (UCanvasPanelSlot* CursorSlot = Cast<UCanvasPanelSlot>(CursorImage->Slot))
		{
			CursorSlot->SetAnchors(FAnchors(0.f, 0.f));
			CursorSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CursorPosition = BGSize.X / 2.f;
			CursorSlot->SetPosition(FVector2D(CursorPosition, BGSize.Y / 2.f));
		}
	}

	if (SuccessZone)
	{
		if (UCanvasPanelSlot* SuccessSlot = Cast<UCanvasPanelSlot>(SuccessZone->Slot))
		{
			SuccessSlot->SetAnchors(FAnchors(0.f, 0.f));
			SuccessSlot->SetAlignment(FVector2D(0.f, 0.5f));
		}
	}

	if (PerfectZone)
	{
		if (UCanvasPanelSlot* PerfectSlot = Cast<UCanvasPanelSlot>(PerfectZone->Slot))
		{
			PerfectSlot->SetAnchors(FAnchors(0.f, 0.f));
			PerfectSlot->SetAlignment(FVector2D(0.f, 0.5f));
		}
	}

	if (ScoreText)
	{
		if (UCanvasPanelSlot* ScoreSlot = Cast<UCanvasPanelSlot>(ScoreText->Slot))
		{
			ScoreSlot->SetAnchors(FAnchors(0.5f, 0.f));
			ScoreSlot->SetAlignment(FVector2D(0.5f, 0.f));
			ScoreSlot->SetPosition(FVector2D(BGSize.X / 2.f, 10.f));
		}
	}

	if (ResultText)
	{
		if (UCanvasPanelSlot* ResultSlot = Cast<UCanvasPanelSlot>(ResultText->Slot))
		{
			ResultSlot->SetAnchors(FAnchors(0.5f, 0.f));
			ResultSlot->SetAlignment(FVector2D(0.5f, 0.f));
			ResultSlot->SetPosition(FVector2D(BGSize.X / 2.f, 50.f));
		}
	}

	if (SkillButton)
	{
		if (UCanvasPanelSlot* ButtonSlot = Cast<UCanvasPanelSlot>(SkillButton->Slot))
		{
			ButtonSlot->SetAnchors(FAnchors(0.5f, 1.f));
			ButtonSlot->SetAlignment(FVector2D(0.5f, 1.f));
			ButtonSlot->SetPosition(FVector2D(BGSize.X / 2.f, BGSize.Y - 50.f));
		}

		SkillButton->SetClickMethod(EButtonClickMethod::MouseDown);
		SkillButton->SetTouchMethod(EButtonTouchMethod::Down);
		SkillButton->OnClicked.AddDynamic(this, &USB_GeneratorMiniGameWidget::OnSkillPressed);
	}

	UpdateScoreText();
	GenerateZones();
}

void USB_GeneratorMiniGameWidget::SetGenerator(ASB_GeneratorActor* InGenerator)
{
	Generator = InGenerator;
}

void USB_GeneratorMiniGameWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (!BackgroundImage) return;

	FVector2D BGSize = BackgroundImage->GetCachedGeometry().GetLocalSize();

	if (bMoveRight)
		CursorPosition += CursorSpeed * DeltaTime;
	else
		CursorPosition -= CursorSpeed * DeltaTime;

	if (CursorPosition >= BGSize.X)
	{
		CursorPosition = BGSize.X;
		bMoveRight = false;
	}

	if (CursorPosition <= 0)
	{
		CursorPosition = 0;
		bMoveRight = true;
	}

	if (CursorImage)
	{
		if (UCanvasPanelSlot* CursorSlot = Cast<UCanvasPanelSlot>(CursorImage->Slot))
		{
			CursorSlot->SetPosition(FVector2D(CursorPosition, BGSize.Y / 2.f));
		}
	}
}

void USB_GeneratorMiniGameWidget::OnSkillPressed()
{
	if (!BackgroundImage) return;

	float CursorX = CursorPosition;

	if (CursorX >= PerfectStart && CursorX <= PerfectEnd)
	{
		Score += 2;

		// PERFECT makes faster 
		CursorSpeed = FMath::Min(CursorSpeed + SpeedIncrease * 2, MaxCursorSpeed);

		if (ResultText)
			ResultText->SetText(FText::FromString("PERFECT"));
	}
	else if (CursorX >= SuccessStart && CursorX <= SuccessEnd)
	{
		Score += 1;

		// Defolt speed
		CursorSpeed = FMath::Min(CursorSpeed + SpeedIncrease, MaxCursorSpeed);

		if (ResultText)
			ResultText->SetText(FText::FromString("GOOD"));
	}
	else
	{
		Score = 0;

		// Reset speed 
		CursorSpeed = BaseCursorSpeed;

		if (ResultText)
			ResultText->SetText(FText::FromString("FAIL"));
	}

	UpdateScoreText();

	if (Score >= RequiredScore)
	{
		FinishMiniGame(true);
		return;
	}

	GenerateZones();
}

void USB_GeneratorMiniGameWidget::GenerateZones()
{
	if (!BackgroundImage) return;

	FVector2D BGSize = BackgroundImage->GetCachedGeometry().GetLocalSize();

	float SuccessWidth = FMath::Min(200.f, BGSize.X);
	float PerfectWidth = FMath::Min(60.f, BGSize.X);

	SuccessStart = FMath::RandRange(0.f, BGSize.X - SuccessWidth);
	SuccessEnd = SuccessStart + SuccessWidth;

	PerfectStart = FMath::RandRange(SuccessStart, SuccessEnd - PerfectWidth);
	PerfectEnd = PerfectStart + PerfectWidth;

	if (SuccessZone)
	{
		if (UCanvasPanelSlot* SuccessSlot = Cast<UCanvasPanelSlot>(SuccessZone->Slot))
		{
			SuccessSlot->SetPosition(FVector2D(SuccessStart, BGSize.Y / 2.f));
			SuccessSlot->SetSize(FVector2D(SuccessWidth, 40.f));
		}
	}

	if (PerfectZone)
	{
		if (UCanvasPanelSlot* PerfectSlot = Cast<UCanvasPanelSlot>(PerfectZone->Slot))
		{
			PerfectSlot->SetPosition(FVector2D(PerfectStart, BGSize.Y / 2.f));
			PerfectSlot->SetSize(FVector2D(PerfectWidth, 40.f));
		}
	}
}

void USB_GeneratorMiniGameWidget::UpdateScoreText()
{
	if (ScoreText)
	{
		FString Text = FString::Printf(TEXT("Progress: %d / %d"), Score, RequiredScore);
		ScoreText->SetText(FText::FromString(Text));
	}
}

void USB_GeneratorMiniGameWidget::FinishMiniGame(bool bSuccess)
{
	if (Generator)
	{
		Generator->OnMiniGameCompleted(bSuccess);
	}
}