// Copyright Epic Games, Inc. All Rights Reserved.

#include "Please_DefenceGameMode.h"
#include "Please_DefenceCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlease_DefenceGameMode::APlease_DefenceGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
