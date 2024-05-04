// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WGDemo.h"
#include "Character/GiantyTestCharacter.h"


UWGDemo::UWGDemo(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UWGDemo::SetTextVisible(bool isVisOn)
{
	if (!PlayerStatus) return;

	ESlateVisibility vis = isVisOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	PlayerStatus->SetVisibility(vis);
}

void UWGDemo::SetOverlayVisible(bool isVisOn)
{
	if (!BlackOverlay) return;

	ESlateVisibility vis = isVisOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	BlackOverlay->SetVisibility(vis);
}

void UWGDemo::OnClickToPlay()
{
	SetOverlayVisible(false);
	APlayerController* Controler =  GetWorld()->GetFirstPlayerController();
	if (!Controler) return;
	
	Controler->bShowMouseCursor = false;

	ACharacter* iChar = Controler->GetCharacter();
	if (iChar) {
		AGiantyTestCharacter* gChar = Cast<AGiantyTestCharacter>(iChar);
		if (gChar) gChar->lockscreen = false;
	}
}

void UWGDemo::NativeConstruct()
{
	Super::NativeConstruct();

	SetTextVisible(false);

	PlayBtn->OnClicked.AddDynamic(this, &UWGDemo::OnClickToPlay);
}
