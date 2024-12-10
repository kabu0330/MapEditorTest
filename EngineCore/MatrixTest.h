#pragma once
#include "FirstMesh.h"

// 설명 :
class MatrixTest
{
public:
	// constrcuter destructer
	MatrixTest();
	~MatrixTest();

	// delete Function
	MatrixTest(const MatrixTest& _Other) = delete;
	MatrixTest(MatrixTest&& _Other) noexcept = delete;
	MatrixTest& operator=(const MatrixTest& _Other) = delete;
	MatrixTest& operator=(MatrixTest&& _Other) noexcept = delete;

	void BeginPlay();
	void Render(float _DeltaTime);
protected:

private:
	FirstMesh BoxMesh;

	FVector Scale = { 200, 200, 200 };
	FVector Roation = { 0, 0, 0 };

	FVector Position = { 0, 0, 0 };

	// 카메라도 어디에다가 가져다 놔야할가요?
	// 카메라맨이 플레이어를 찍는다는 개념으로 가게 된다.
	FVector CameraPosition = { -2, 0, -2 };

	FVector CameraRotation = { 0, -90, 0 };

};

