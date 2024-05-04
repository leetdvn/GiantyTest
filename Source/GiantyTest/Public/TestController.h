// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GIANTYTEST_API ATestController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATestController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* CurrentWG;

	UFUNCTION()
	void ShowActionInfo(bool isShow);

	UFUNCTION()
	void SetStatusText(FString inText);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayStatus;

	void BeginPlay() override;
};
