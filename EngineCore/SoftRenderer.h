#pragma once
#include <EngineBase/EngineMath.h>
#include "Renderer.h"
#include <list>
#include <vector>
#include "VertexBaseMesTest.h"
#include "CrossTest.h"
#include "MatrixTest.h"

// Ό³Έν :
class USoftRenderer : public URenderer
{
public:
	// constrcuter destructer
	USoftRenderer();
	~USoftRenderer();

	// delete Function
	USoftRenderer(const USoftRenderer& _Other) = delete;
	USoftRenderer(USoftRenderer&& _Other) noexcept = delete;
	USoftRenderer& operator=(const USoftRenderer& _Other) = delete;
	USoftRenderer& operator=(USoftRenderer&& _Other) noexcept = delete;

protected:
	void BeginPlay();
	virtual void Render(float _Delta);

private:
	float Angle = 0.0f;
	float Speed = 0.0f;
	std::list<FTransform> SinG;
	std::list<FTransform> CosG;
	int Select;

	VertexBaseMesTest VTest;
	CrossTest CTest;
	MatrixTest MatrixTest;
};

