#pragma once
#include "FirstMesh.h"

// Ό³Έν :
class VertexBaseMesTest
{
public:
	// constrcuter destructer
	VertexBaseMesTest();
	~VertexBaseMesTest();

	// delete Function
	VertexBaseMesTest(const VertexBaseMesTest& _Other) = delete;
	VertexBaseMesTest(VertexBaseMesTest&& _Other) noexcept = delete;
	VertexBaseMesTest& operator=(const VertexBaseMesTest& _Other) = delete;
	VertexBaseMesTest& operator=(VertexBaseMesTest&& _Other) noexcept = delete;

	void BeginPlay();
	void Render(float _DeltaTime);
protected:

private:
	FirstMesh BoxMesh;
	FVector Scale = { 1, 1, 1 };
	FVector Roation = { 0, 0, 0 };
	FVector Position = { 300, 300 };
};

