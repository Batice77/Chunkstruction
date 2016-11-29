// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunkstruction.h"
#include "ChunkstructionGameMode.h"
#include "MyCharacter.h"

AChunkstructionGameMode::AChunkstructionGameMode()
{
	DefaultPawnClass = AMyCharacter::StaticClass();

	static ConstructorHelpers::FObjectFinder<UBlueprint> Character(TEXT("Blueprint'/Game/TheCharacter.TheCharacter'"));
	if (Character.Object) {
		DefaultPawnClass = (UClass*)Character.Object->GeneratedClass;
	}
}