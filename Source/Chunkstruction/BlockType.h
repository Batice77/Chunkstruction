#pragma once

struct FBlock;
struct FMeshData;
class UChunkComponent;

#include "Direction.h"
#include "BlockType.generated.h"

UCLASS()
class CHUNKSTRUCTION_API UBlockType : public UObject
{
	GENERATED_BODY()

public:
	UBlockType();
	virtual bool IsSolid(EDirection direction);
	virtual void AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData);
};