// Copyright Epic Games, Inc. All Rights Reserved.

#include "Code_SampleGameMode.h"
#include "Code_SampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACode_SampleGameMode::ACode_SampleGameMode()
{
	// set default pawn class to our Blueprinted character
	//Class'/Script/Code_Sample.User_Character'
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Code_Sample.User_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
