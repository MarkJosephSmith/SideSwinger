// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SideSwingerGameMode.h"
#include "SideSwingerCharacter.h"

ASideSwingerGameMode::ASideSwingerGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASideSwingerCharacter::StaticClass();	
}
