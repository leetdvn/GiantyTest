// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <DummyCharacter.h>
#include "../GiantyTestCharacter.h"
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GiantyAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class GIANTYTEST_API UGiantyAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration) override;

protected:

	AGiantyTestCharacter* character = nullptr;

	ADummyCharacter* Dummy = nullptr;
};
