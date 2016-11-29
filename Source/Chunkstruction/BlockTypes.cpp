// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunkstruction.h"
#include "BlockTypes.h"
#include "MeshData.h"
#include "ChunkComponent.h"

UBlockType* UBlockTypes::types[3];
void SetupTypes()
{
	UNoneType* noneType = NewObject<UNoneType>();
	noneType->AddToRoot();
	UBlockTypes::types[0] = noneType;

	UCubeTechPanelType* cubeTechPanelType = NewObject<UCubeTechPanelType>();
	cubeTechPanelType->AddToRoot();
	UBlockTypes::types[1] = cubeTechPanelType;

	UDemiCubeTechPanelType* demiCubeTechPanelType = NewObject<UDemiCubeTechPanelType>();
	demiCubeTechPanelType->AddToRoot();
	UBlockTypes::types[2] = demiCubeTechPanelType;

}
static int dummy = (SetupTypes(), 0);

UBlockTypes::UBlockTypes()
{
}

UBlockType* UBlockTypes::GetBlockType(int type)
{
	return types[type];
}

//	NoneType

bool UNoneType::IsSolid(EDirection direction)
{
	return false;
}

void UNoneType::AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData)
{
}

//	CubeTechPanelType

bool UCubeTechPanelType::IsSolid(EDirection direction)
{
	return true;
}

void UCubeTechPanelType::AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData)
{
	static const int blockSize = UChunkComponent::blockSize;
	//Up
	if (!Chunk->GetBlock(x, y, z + 1).IsSolid(EDirection::Down))
	{
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z + 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, 0, 1));
		meshData.normals.Add(FVector(0, 0, 1));
		meshData.normals.Add(FVector(0, 0, 1));
		meshData.normals.Add(FVector(0, 0, 1));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));

		meshData.AddQuadTriangles();
	}

	//Down
	if (!Chunk->GetBlock(x, y, z - 1).IsSolid(EDirection::Up))
	{
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, 0, -1));
		meshData.normals.Add(FVector(0, 0, -1));
		meshData.normals.Add(FVector(0, 0, -1));
		meshData.normals.Add(FVector(0, 0, -1));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));

		meshData.AddQuadTriangles();
	}

	//Forward
	if (!Chunk->GetBlock(x + 1, y, z).IsSolid(EDirection::Backward))
	{
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(1, 0, 0));
		meshData.normals.Add(FVector(1, 0, 0));
		meshData.normals.Add(FVector(1, 0, 0));
		meshData.normals.Add(FVector(1, 0, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));

		meshData.AddQuadTriangles();
	}

	//Back
	if (!Chunk->GetBlock(x - 1, y, z).IsSolid(EDirection::Forward))
	{
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(-1, 0, 0));
		meshData.normals.Add(FVector(-1, 0, 0));
		meshData.normals.Add(FVector(-1, 0, 0));
		meshData.normals.Add(FVector(-1, 0, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));

		meshData.AddQuadTriangles();
	}

	//Left
	if (!Chunk->GetBlock(x, y - 1, z).IsSolid(EDirection::Right))
	{
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, -1, 0));
		meshData.normals.Add(FVector(0, -1, 0));
		meshData.normals.Add(FVector(0, -1, 0));
		meshData.normals.Add(FVector(0, -1, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));

		meshData.AddQuadTriangles();
	}

	//Right
	if (!Chunk->GetBlock(x, y + 1, z).IsSolid(EDirection::Left))
	{
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z + 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, 1, 0));
		meshData.normals.Add(FVector(0, 1, 0));
		meshData.normals.Add(FVector(0, 1, 0));
		meshData.normals.Add(FVector(0, 1, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));

		meshData.AddQuadTriangles();
	}
}

//	DemiCubeTechPanelType

bool UDemiCubeTechPanelType::IsSolid(EDirection direction)
{
	if (direction == EDirection::Down) return true;
	return false;
}

void UDemiCubeTechPanelType::AddBlockToMeshData(UChunkComponent *Chunk, int x, int y, int z, FMeshData &meshData)
{
	static const int blockSize = UChunkComponent::blockSize;
	//Up
	/*if (!Chunk->GetBlock(x, y, z + 1).IsSolid(EDirection::Down))
	{*/
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z) * blockSize);

		meshData.normals.Add(FVector(0, 0, 1));
		meshData.normals.Add(FVector(0, 0, 1));
		meshData.normals.Add(FVector(0, 0, 1));
		meshData.normals.Add(FVector(0, 0, 1));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));

		meshData.AddQuadTriangles();
	//}

	//Down
	if (!Chunk->GetBlock(x, y, z - 1).IsSolid(EDirection::Up))
	{
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, 0, -1));
		meshData.normals.Add(FVector(0, 0, -1));
		meshData.normals.Add(FVector(0, 0, -1));
		meshData.normals.Add(FVector(0, 0, -1));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));

		meshData.AddQuadTriangles();
	}

	//Forward
	if (!Chunk->GetBlock(x + 1, y, z).IsSolid(EDirection::Backward))
	{
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(1, 0, 0));
		meshData.normals.Add(FVector(1, 0, 0));
		meshData.normals.Add(FVector(1, 0, 0));
		meshData.normals.Add(FVector(1, 0, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, 1, 0));

		meshData.AddQuadTriangles();
	}

	//Back
	if (!Chunk->GetBlock(x - 1, y, z).IsSolid(EDirection::Forward))
	{
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(-1, 0, 0));
		meshData.normals.Add(FVector(-1, 0, 0));
		meshData.normals.Add(FVector(-1, 0, 0));
		meshData.normals.Add(FVector(-1, 0, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(0, -1, 0));

		meshData.AddQuadTriangles();
	}

	//Left
	if (!Chunk->GetBlock(x, y - 1, z).IsSolid(EDirection::Right))
	{
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y - 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y - 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, -1, 0));
		meshData.normals.Add(FVector(0, -1, 0));
		meshData.normals.Add(FVector(0, -1, 0));
		meshData.normals.Add(FVector(0, -1, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(1, 0, 0));

		meshData.AddQuadTriangles();
	}

	//Right
	if (!Chunk->GetBlock(x, y + 1, z).IsSolid(EDirection::Left))
	{
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z - 0.5f) * blockSize);
		meshData.vertices.Add(FVector(x - 0.5f, y + 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z) * blockSize);
		meshData.vertices.Add(FVector(x + 0.5f, y + 0.5f, z - 0.5f) * blockSize);

		meshData.normals.Add(FVector(0, 1, 0));
		meshData.normals.Add(FVector(0, 1, 0));
		meshData.normals.Add(FVector(0, 1, 0));
		meshData.normals.Add(FVector(0, 1, 0));

		meshData.uvs.Add(FVector2D(0, 0));
		meshData.uvs.Add(FVector2D(0, 1));
		meshData.uvs.Add(FVector2D(1, 1));
		meshData.uvs.Add(FVector2D(1, 0));

		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);
		meshData.vertexColors.Add(FColor::White);

		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
		meshData.tangents.Add(FRuntimeMeshTangent(-1, 0, 0));

		meshData.AddQuadTriangles();
	}
}