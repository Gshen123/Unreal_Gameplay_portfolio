// Copyright Epic Games, Inc. All Rights Reserved.

#include "SPGameModeBase.h"
#include "Gameplay_Portfolio/Character/SPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASPGameModeBase::ASPGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> BP_SPCharacter(TEXT("/Game/Characters/BP_SPCharacter.BP_SPCharacter_C"));
	if (BP_SPCharacter.Class != NULL)
	{
		DefaultPawnClass = BP_SPCharacter.Class;
	}
}
