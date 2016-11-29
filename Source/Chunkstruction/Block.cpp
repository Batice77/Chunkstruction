#include "Chunkstruction.h"
#include "Block.h"
#include "ChunkComponent.h"
#include "MeshData.h"
#include "BlockTypes.h"

bool FBlock::IsSolid(EDirection direction) {
	return UBlockTypes::GetBlockType(type)->IsSolid(direction);
}

void FBlock::AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData) {
	UBlockTypes::GetBlockType(type)->AddBlockToMeshData(Chunk, x, y, z, meshData);
}