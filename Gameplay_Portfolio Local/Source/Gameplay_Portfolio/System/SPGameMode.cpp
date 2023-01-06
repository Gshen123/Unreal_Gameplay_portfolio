// Copyright Epic Games, Inc. All Rights Reserved.

#include "SPGameMode.h"
#include "Gameplay_Portfolio/Character/SPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASPGameMode::ASPGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
