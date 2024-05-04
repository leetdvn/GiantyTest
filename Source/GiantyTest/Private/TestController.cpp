// Fill out your copyright notice in the Description page of Project Settings.


#include "TestController.h"
#include "Blueprint/UserWidget.h"
#include <Widget/WGDemo.h>

ATestController::ATestController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void ATestController::ShowActionInfo(bool isShow)
{
	if (!CurrentWG) return;

	UWGDemo* wgdemo = Cast<UWGDemo>(CurrentWG);
	if (wgdemo) wgdemo->SetTextVisible(isShow);

}

void ATestController::SetStatusText(FString inText)
{
	UWGDemo* wgdemo = Cast<UWGDemo>(CurrentWG);

	if (!wgdemo) return;

	wgdemo->PlayerStatus->SetText(FText::FromString(inText));
}

void ATestController::BeginPlay()
{
	Super::BeginPlay();

	
	CurrentWG = CreateWidget(GetWorld(), PlayStatus);
	if (CurrentWG) {
		CurrentWG->AddToViewport();
	}
}
