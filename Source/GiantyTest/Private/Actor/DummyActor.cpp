// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DummyActor.h"

// Sets default values
ADummyActor::ADummyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	capsule->SetupAttachment(RootComponent);
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	boxComp->SetupAttachment(capsule);

	dummyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DummySkeletalMesh"));

	dummyMesh->SetupAttachment(capsule);
}

// Called when the game starts or when spawned
void ADummyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

