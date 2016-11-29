#pragma once
struct FRuntimeMeshTangent;
#include "MeshData.generated.h"

USTRUCT(BlueprintType)
struct FMeshData
{
	GENERATED_BODY()

	TArray<FVector> vertices = TArray<FVector>();
	TArray<int32> triangles = TArray<int32>();
	TArray<FVector> normals = TArray<FVector>();
	TArray<FVector2D> uvs = TArray<FVector2D>();
	TArray<FColor> vertexColors = TArray<FColor>();
	TArray<FRuntimeMeshTangent> tangents = TArray<FRuntimeMeshTangent>();


	void AddQuadTriangles() {
		triangles.Add(vertices.Num() - 4);
		triangles.Add(vertices.Num() - 2);
		triangles.Add(vertices.Num() - 3);

		triangles.Add(vertices.Num() - 4);
		triangles.Add(vertices.Num() - 1);
		triangles.Add(vertices.Num() - 2);
	}

};