// Copyright Epic Games, Inc. All Rights Reserved.

#include "GiantyTestGameMode.h"
#include "Character/GiantyTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGiantyTestGameMode::AGiantyTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
