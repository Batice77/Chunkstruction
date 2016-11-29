// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UChunkComponent;

#include "BlockType.h"
#include "BlockTypes.generated.h"

UCLASS()
class CHUNKSTRUCTION_API UBlockTypes : public UObject
{
	GENERATED_BODY()

public:
	static UBlockType* types[];
public:
	UBlockTypes();
	static UBlockType* GetBlockType(int type);
};

UCLASS()
class CHUNKSTRUCTION_API UNoneType : public UBlockType
{
	GENERATED_BODY()

public:
	virtual bool IsSolid(EDirection direction) override;
	virtual void AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData) override;
};

UCLASS()
class CHUNKSTRUCTION_API UCubeTechPanelType : public UBlockType
{
	GENERATED_BODY()

public:
	virtual bool IsSolid(EDirection direction) override;
	virtual void AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData) override;
};

UCLASS()
class CHUNKSTRUCTION_API UDemiCubeTechPanelType : public UBlockType
{
	GENERATED_BODY()

public:
	virtual bool IsSolid(EDirection direction) override;
	virtual void AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData) override;
};