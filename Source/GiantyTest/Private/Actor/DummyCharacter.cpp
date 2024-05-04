// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DummyCharacter.h"
#include "Character/GiantyTestCharacter.h"

// Sets default values
ADummyCharacter::ADummyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	boxComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADummyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	startRotator = GetActorRotation();
}

// Called every frame
void ADummyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADummyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADummyCharacter::PlayAction()
{
	if (ActionMontage) {
		PlayAnimMontage(ActionMontage, 1.5f);
		

		FTimerHandle tHandle;
		GetWorld()->GetTimerManager().SetTimer(tHandle, [this]() {
			GetMesh()->SetSimulatePhysics(false);			},
			1.5f,
			false,
			ActionMontage->GetPlayLength() - 2.f
		);

	}
}



