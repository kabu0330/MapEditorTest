#pragma once
#include "FirstMesh.h"


// ���� :
class CrossTest
{
public:
	// constrcuter destructer
	CrossTest();
	~CrossTest();

	// delete Function
	CrossTest(const CrossTest& _Other) = delete;
	CrossTest(CrossTest&& _Other) noexcept = delete;
	CrossTest& operator=(const CrossTest& _Other) = delete;
	CrossTest& operator=(CrossTest&& _Other) noexcept = delete;

	void BeginPlay();
	void Render(float _DeltaTime);

protected:

private:
	// 0�� �Ž� �÷��̾�
	FirstMesh PlayerMesh;
	float PlayerSpeed = 200.0f;
	FVector PlayerPos = { 100, 100, 0 };
	FVector PlayerRot = { 0, 0, 0 };
	// scale�� �����Ҷ� �߿����� ��� �����̶� 0�̵Ǹ� 
	FVector PlayerScale = {100, 100, 1};

	// 1�� �Ž� ����
	FirstMesh MonsterMesh;

	FVector MonsterPos = { 100, 100, 0 };
	FVector MonsterRot = { 0, 0, 0 };
	// scale�� �����Ҷ� �߿����� ��� �����̶� 0�̵Ǹ� 
	FVector MonsterScale = { 80, 80, 1 };

};

