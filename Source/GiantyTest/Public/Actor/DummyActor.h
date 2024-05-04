// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include "GameFramework/Actor.h"
#include "DummyActor.generated.h"

UCLASS(BlueprintType)
class GIANTYTEST_API ADummyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LeeSettings)
	UAnimMontage* iMontageAct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LeeSettings)
	USkeletalMeshComponent* dummyMesh;


protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LeeSettings)
	UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LeeSettings)
	UCapsuleComponent* capsule;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
