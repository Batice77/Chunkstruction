#pragma once

struct FMeshData;

#include "Direction.h"
#include "Block.generated.h"

USTRUCT(BlueprintType)
struct FBlock
{
	GENERATED_BODY()
private:
	UPROPERTY()
	uint8 type;
	UPROPERTY()
	uint8 data;

public:
	//Constructor
	FBlock(uint8 Type=0, uint8 Data=0)
	{
		type = Type;
		data = Data;
	}

	uint8 GetType() { return type; }

	bool IsSolid(EDirection direction);

	void AddBlockToMeshData(class UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData);
};

USTRUCT(BlueprintType)
struct FBlockField
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FBlock blocks[32];
};

USTRUCT(BlueprintType)
struct FBlockTwoField
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FBlockField blocks[32];
};