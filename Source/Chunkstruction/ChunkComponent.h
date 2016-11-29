// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Block.h"

#include "RuntimeMeshComponent.h"
#include "ChunkComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHUNKSTRUCTION_API UChunkComponent : public URuntimeMeshComponent
{
	GENERATED_BODY()

public:
	static const int nbBlockPerAxis = 32;
	static const int blockSize = 50;
	bool bUpdate = false;

private:
	UPROPERTY()
	FBlockTwoField blocks[nbBlockPerAxis];

public:	
	// Sets default values for this component's properties
	UChunkComponent(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	FBlock GetBlock(int x, int y, int z);
	void SetBlock(int x, int y, int z, FBlock block);
	
	void UpdateChunk();
	bool IsEmpty();
};