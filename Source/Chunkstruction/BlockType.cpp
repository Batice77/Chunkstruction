#include "Chunkstruction.h"
#include "MeshData.h"
#include "ChunkComponent.h"
#include "BlockType.h"

UBlockType::UBlockType()/*const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)*/
{
}

bool UBlockType::IsSolid(EDirection direction)
{
	return true;
}

void UBlockType::AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData)
{
}