// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WGDemo.h"


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

void UWGDemo::NativeConstruct()
{
	Super::NativeConstruct();

	SetTextVisible(false);

}
