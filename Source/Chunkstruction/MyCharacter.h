// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class CHUNKSTRUCTION_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	uint8 blockType = 1;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

	/** RemoveBlock */
	void OnRemoveBlock();

	/** PlaceBlock */
	void OnPlaceBlock();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TraceAim(FHitResult &hitResult);

	void SelectNextBlock();
	
};
