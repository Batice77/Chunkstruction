// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UChunkComponent;

#include "Block.h"

#include "GameFramework/Actor.h"
#include "Frame.generated.h"

UCLASS()
class CHUNKSTRUCTION_API AFrame : public AActor
{
	GENERATED_BODY()
	
private:
	TMap<FIntVector, UChunkComponent*> chunks;
public:	
	// Sets default values for this actor's properties
	AFrame();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void CreateChunk(FIntVector pos);
	void DestroyChunk(FIntVector pos);

	UChunkComponent* GetChunk(int x, int y, int z);

	FBlock GetBlock(int x, int y, int z);
	void SetBlock(int x, int y, int z, FBlock block);
};
