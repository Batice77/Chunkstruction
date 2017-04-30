// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunkstruction.h"
#include "ChunkComponent.h"
#include "MeshData.h"
#include "Block.h"
#include "Frame.h"

// Sets default values for this component's properties
UChunkComponent::UChunkComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//bWantsBeginPlay = true; //Does it fix BeginPlay Problem ?
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Panel.M_Tech_Panel'"));

	if (Material.Object != NULL)
	{
		SetMaterial(0, (UMaterial*)Material.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Material2(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Wall.M_Basic_Wall'"));

	if (Material2.Object != NULL)
	{
		SetMaterial(1, (UMaterial*)Material2.Object);
	}

}

// Called when the game starts
void UChunkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UChunkComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (bUpdate)
	{
		bUpdate = false;
		UpdateChunk();
	}
}

FBlock UChunkComponent::GetBlock(int x, int y, int z)
{
	if(x >= 0 && x < UChunkComponent::nbBlockPerAxis && y >= 0 && y < UChunkComponent::nbBlockPerAxis && z >= 0 && z < UChunkComponent::nbBlockPerAxis)
		return blocks[x].blocks[y].blocks[z];
	AFrame* frame = Cast<AFrame>(GetOwner());
	if (frame) 
	{
		FVector pos = RelativeLocation / UChunkComponent::blockSize;
		return frame->GetBlock(pos.X+x, pos.Y+y, pos.Z+z);
	}
	return FBlock();
}

void UChunkComponent::SetBlock(int x, int y, int z, FBlock block)
{
	blocks[x].blocks[y].blocks[z] = block;
	bUpdate = true;
}

void UChunkComponent::UpdateChunk()
{
	//	MultiThreading
	AsyncTask(ENamedThreads::AnyThread, [this] {
		UChunkComponent* Chunk = this;
		TArray<FMeshData> mDs = TArray<FMeshData>();
		mDs.SetNum(2);

		for (int x = 0; x < UChunkComponent::nbBlockPerAxis; x++)
		{
			for (int y = 0; y < UChunkComponent::nbBlockPerAxis; y++)
			{
				for (int z = 0; z < UChunkComponent::nbBlockPerAxis; z++)
				{
					int material = 0;//Chunk->GetBlock(x, y, z).GetMaterial();
					Chunk->GetBlock(x, y, z).AddBlockToMeshData(Chunk, x, y, z, mDs[material]);
				}
			}
		}


		AsyncTask(ENamedThreads::GameThread, [mDs, Chunk] {
			Chunk->ClearAllMeshSections();
			for (int i = 0; i < 2; i++)
			{
				Chunk->CreateMeshSection(i, mDs[i].vertices, mDs[i].triangles, mDs[i].normals, mDs[i].uvs, mDs[i].vertexColors, mDs[i].tangents, true, EUpdateFrequency::Infrequent);
			}

		});
	});

}

bool UChunkComponent::IsEmpty()
{
	for (int x = 0; x < UChunkComponent::nbBlockPerAxis; x++)
	{
		for (int y = 0; y < UChunkComponent::nbBlockPerAxis; y++)
		{
			for (int z = 0; z < UChunkComponent::nbBlockPerAxis; z++)
			{
				if (GetBlock(x, y, z).GetType() != 0)
					return false;
			}
		}
	}
	return true;
}
