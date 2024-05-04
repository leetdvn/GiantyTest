// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/GiantyAnimNotifyState.h"
#include <Kismet/KismetMathLibrary.h>

void UGiantyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor*owner = MeshComp->GetOwner();
	
	character = Cast<AGiantyTestCharacter>(owner);

	if (character) {
		if (GEngine) {

			if (character->TargetActor) {

				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Action Start"), true);
				Dummy = Cast<ADummyCharacter>(character->TargetActor);
				if (!Dummy) return;

				
				FVector currentLoc = character->GetActorLocation();
				FVector newLoc = (115 * character->GetActorForwardVector()) + currentLoc;

				FHitResult* hitresult = new FHitResult();

				character->TargetActor->SetActorLocation(newLoc, false, hitresult, ETeleportType::ResetPhysics);
				FRotator currRot = character->GetActorRotation();
				FRotator newRot = FRotator(0,currRot.Yaw -90,currRot.Roll);
				character->TargetActor->SetActorRotation(newRot,ETeleportType::ResetPhysics);
				Dummy->PlayAction();
			}
		}
	}
}