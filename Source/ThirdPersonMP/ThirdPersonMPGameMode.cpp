// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMPGameMode.h"
#include "ThirdPersonMPCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "HttpService.h"

AThirdPersonMPGameMode::AThirdPersonMPGameMode():HttpService(nullptr)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AThirdPersonMPGameMode::StartPlay()
{
	Super::StartPlay();
	HttpService = GetWorld()->SpawnActor<AHttpService>();
}