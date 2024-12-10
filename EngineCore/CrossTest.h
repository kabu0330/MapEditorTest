#pragma once
#include "FirstMesh.h"


// 설명 :
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
	// 0번 매쉬 플레이어
	FirstMesh PlayerMesh;
	float PlayerSpeed = 200.0f;
	FVector PlayerPos = { 100, 100, 0 };
	FVector PlayerRot = { 0, 0, 0 };
	// scale을 설정할때 중요한점 어느 한축이라도 0이되면 
	FVector PlayerScale = {100, 100, 1};

	// 1번 매쉬 몬스터
	FirstMesh MonsterMesh;

	FVector MonsterPos = { 100, 100, 0 };
	FVector MonsterRot = { 0, 0, 0 };
	// scale을 설정할때 중요한점 어느 한축이라도 0이되면 
	FVector MonsterScale = { 80, 80, 1 };

};

