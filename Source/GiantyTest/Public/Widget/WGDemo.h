// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/Overlay.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WGDemo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GIANTYTEST_API UWGDemo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWGDemo(const FObjectInitializer& ObjectInitializer);

	void SetTextVisible(bool isVisOn);

	void SetOverlayVisible(bool isVisOn);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget Settings", DisplayName = "Status", meta = (BindWidget))
	UTextBlock* PlayerStatus;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget Settings", DisplayName = "Black Overlay", meta = (BindWidget))
	UOverlay* BlackOverlay;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget Settings", DisplayName = "Play Button", meta = (BindWidget))
	UButton* PlayBtn;

protected:

	UFUNCTION()
	void OnClickToPlay();

	void NativeConstruct() override;
};
