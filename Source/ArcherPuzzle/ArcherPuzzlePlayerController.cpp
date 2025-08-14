// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcherPuzzlePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ArcherPuzzleCameraManager.h"

AArcherPuzzlePlayerController::AArcherPuzzlePlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AArcherPuzzleCameraManager::StaticClass();
}

void AArcherPuzzlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
