// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/GiantyTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"
#include <TestController.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGiantyTestCharacter

AGiantyTestCharacter::AGiantyTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AGiantyTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AGiantyTestCharacter::OnHit);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGiantyTestCharacter::OnOverLapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AGiantyTestCharacter::OnOverLapEnd);

	APlayerController* pControl = GetWorld()->GetFirstPlayerController();
	iController = Cast<ATestController>(pControl);
}

void AGiantyTestCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	FVector currentLoc = GetActorLocation();
	FVector newLoc = (150 * GetActorForwardVector()) + currentLoc;

	FHitResult* hitresult = new FHitResult();
	if (!OnAction) {
		OnAction = true;

		//TargetActor = OtherActor;
		
		//OtherActor->SetActorLocation(newLoc, false, hitresult, ETeleportType::ResetPhysics);

		FTimerHandle tHandle;
		GetWorld()->GetTimerManager().SetTimer(tHandle, [this]() {
			OnAction = false;
			},
			1.5f,
			false,
			0.5f
		);

	}


}

void AGiantyTestCharacter::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//FString targetName = OtherActor->GetName();
	//FString Info = FString("OverLap : ") + targetName;
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, Info, true);
	if (iController) {
		iController->SetStatusText(TEXT("Press F Key for Attack Enemy"));
		iController->ShowActionInfo(true);
	}

	TargetActor = OtherActor;
	CanAction = true;
}

void AGiantyTestCharacter::OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Out.."), true);
	CanAction = false;
	if (iController) iController->ShowActionInfo(false);

}

void AGiantyTestCharacter::LineTrace()
{

	if (!CanAction) return;

	FHitResult hitLine;

	TArray<AActor*> IgroreActor = TArray<AActor*>();

	CameraBoom->K2_GetComponentToWorld().GetLocation();

	FVector StartVec = GetActorLocation();

	//Trace List Vector 30 Degree
	TArray<FVector> lineTrace = { FVector( 0,-300,0) , FVector::ZeroVector , FVector(0,300,0) };

	bool canAct = false;

	for (int i = 0; i < 3; ++i) {

		FVector EndVec = GetActorForwardVector() * 1000;

		bool isHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			StartVec,
			(StartVec - lineTrace[i]) +  EndVec ,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			true,
			IgroreActor, EDrawDebugTrace::None,
			hitLine, true, FLinearColor::Red,
			FLinearColor::Green,
			10.f
		);

		if (isHit) {
			TArray<FHitResult> Hits;
			FString hitInfo = FString("Hit : ") + EndVec.ToString();

			if (hitLine.Component->ComponentHasTag("Enemy")) {
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, hitInfo, true);
				canAct = true; 
				break;
			}
		}

	}

	if (canAct) {

		canMove = false;
		UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();

		UAnimMontage* montage = AnimIns->PlaySlotAnimationAsDynamicMontage(AnimAction, TEXT("DefaultSlot"), .25f, .25f, 1.5f, 1, -1.f, 0);

		FTimerHandle tHandle;
		GetWorld()->GetTimerManager().SetTimer(tHandle, [this]() {
			canMove = true;
			},
			1.5f,
			false,
			montage->GetPlayLength() - 2.f
		);

	}
	else
	{
		if (iController) {
			iController->SetStatusText("Look At forward direction no enemy target");
			iController->ShowActionInfo(true);
		}
	}

}

void AGiantyTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGiantyTestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGiantyTestCharacter::Look);

		// Attack Action
		EnhancedInputComponent->BindAction(iAction, ETriggerEvent::Started, this, &AGiantyTestCharacter::Attack);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGiantyTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		if (!canMove) return;
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGiantyTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGiantyTestCharacter::Attack(const FInputActionValue& Value)
{
	bool isAttack = Value.Get<bool>();

	if (Controller != nullptr)
	{

		if (TargetActor == nullptr) return;

		LineTrace();

	}
}
