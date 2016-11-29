// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunkstruction.h"
#include "Frame.h"
#include "ChunkComponent.h"

// Sets default values
AFrame::AFrame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* ChunkHandler = CreateDefaultSubobject<UBoxComponent>(FName("ChunkHandler"));
	SetRootComponent(ChunkHandler);
	ChunkHandler->SetBoxExtent(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void AFrame::BeginPlay()
{
	Super::BeginPlay();

	CreateChunk(FIntVector(0,0,0));
	GetChunk(0, 0, 0)->SetBlock(0, 0, 0, FBlock(1));

	/*for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			for (int z = 0; z < 64; z++)
			{
				SetBlock(x, y, z, FBlock(1));
			}
		}
	}*/
}

// Called every frame
void AFrame::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFrame::CreateChunk(FIntVector pos)
{
	UChunkComponent* chunk = NewObject<UChunkComponent>(this);
	if (chunk)
	{
		chunk->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		chunk->RegisterComponent();
		chunk->SetRelativeLocation(FVector(pos.X*UChunkComponent::nbBlockPerAxis*UChunkComponent::blockSize, pos.Y*UChunkComponent::nbBlockPerAxis*UChunkComponent::blockSize, pos.Z*UChunkComponent::nbBlockPerAxis*UChunkComponent::blockSize));
		chunks.Add(pos, chunk);
		//chunk->BeginPlay();
	}
}

void AFrame::DestroyChunk(FIntVector pos)
{
	if (chunks.Contains(pos))
	{
		chunks[pos]->DestroyComponent();
		chunks.Remove(pos);
	}
}

UChunkComponent * AFrame::GetChunk(int x, int y, int z)
{
	FIntVector pos;

	int log = (int)FMath::Sqrt(UChunkComponent::nbBlockPerAxis); // 5 for 32*32*32 chunk
	pos.X = x >> log;
	pos.Y = y >> log;
	pos.Z = z >> log;

	if (chunks.Contains(pos))
		return chunks[pos];
	return nullptr;
}

FBlock AFrame::GetBlock(int x, int y, int z)
{
	UChunkComponent* containerChunk = GetChunk(x, y, z);
	if (containerChunk != nullptr)
	{
		//block relative to their chunk
		x &= (UChunkComponent::nbBlockPerAxis - 1);
		y &= (UChunkComponent::nbBlockPerAxis - 1);
		z &= (UChunkComponent::nbBlockPerAxis - 1);
		return containerChunk->GetBlock(x, y, z);
	}
	return FBlock();
}

void AFrame::SetBlock(int x, int y, int z, FBlock block)
{
	UChunkComponent* containerChunk = GetChunk(x, y, z);
	if (containerChunk != nullptr)
	{
		FIntVector pos;
		pos.X = x & (UChunkComponent::nbBlockPerAxis - 1);
		pos.Y = y & (UChunkComponent::nbBlockPerAxis - 1);
		pos.Z = z & (UChunkComponent::nbBlockPerAxis - 1);
		containerChunk->SetBlock(pos.X, pos.Y, pos.Z, block);

		UChunkComponent* chunk = nullptr;
		for (int i = -1; i <= 1; i += 2)
		{
			chunk = GetChunk(x + i, y, z);
			if (chunk && chunk != containerChunk)
				chunk->bUpdate = true;

			chunk = GetChunk(x, y + i, z);
			if (chunk && chunk != containerChunk)
				chunk->bUpdate = true;

			chunk = GetChunk(x, y, z + i);
			if (chunk && chunk != containerChunk)
				chunk->bUpdate = true;
		}

		if (containerChunk->IsEmpty()) {
			int log = (int)FMath::Sqrt(UChunkComponent::nbBlockPerAxis);
			pos.X = x >> log;
			pos.Y = y >> log;
			pos.Z = z >> log;
			DestroyChunk(pos);

			if (chunks.Num() == 0)
				Destroy();
		}
	}
	else
	{
		FIntVector pos;

		int log = (int)FMath::Sqrt(UChunkComponent::nbBlockPerAxis);
		pos.X = x >> log;
		pos.Y = y >> log;
		pos.Z = z >> log;

		CreateChunk(pos);
		SetBlock(x, y, z, block);
	}
}