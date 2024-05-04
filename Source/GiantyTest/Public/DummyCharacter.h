// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Components/BoxComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DummyCharacter.generated.h"

UCLASS()
class GIANTYTEST_API ADummyCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ADummyCharacter();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LeeSettings)
	UBoxComponent* boxComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FRotator startRotator;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LeeSettings)
	UAnimMontage* ActionMontage;
	
	UFUNCTION()
	void PlayAction();

	UFUNCTION()
	void ResetRotation();
};
