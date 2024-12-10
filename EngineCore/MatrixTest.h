#pragma once
#include "FirstMesh.h"

// ���� :
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

	// ī�޶� ��𿡴ٰ� ������ �����Ұ���?
	// ī�޶���� �÷��̾ ��´ٴ� �������� ���� �ȴ�.
	FVector CameraPosition = { -2, 0, -2 };

	FVector CameraRotation = { 0, -90, 0 };

};

