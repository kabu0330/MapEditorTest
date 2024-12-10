#include "PreCompile.h"
#include "CrossTest.h"
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>

CrossTest::CrossTest()
{
}

CrossTest::~CrossTest()
{
}

void CrossTest::BeginPlay()
{


	{
		FirstMesh& Mesh = PlayerMesh;
		Mesh.Vertexs.resize(3);
		for (size_t i = 0; i < Mesh.Vertexs.size(); i++)
		{
			Mesh.Vertexs[i].resize(3);
		}

		// 앞면 만든거
		Mesh.Vertexs[0][0] = FVector(-0.5f, 0.5f, 0);
		Mesh.Vertexs[0][1] = FVector(0.5f, 0.5f, 0);
		Mesh.Vertexs[0][2] = FVector(-0.5f, -0.5f, 0);
		Mesh.Vertexs[1][0] = FVector(0.5f, 0.5f, 0);
		Mesh.Vertexs[1][1] = FVector(0.5f, -0.5f, 0);
		Mesh.Vertexs[1][2] = FVector(-0.5f, -0.5f, 0);
		Mesh.Vertexs[2][0] = FVector(0.5f, 0.5f, 0);
		Mesh.Vertexs[2][1] = FVector(-0.5f, 0.5f, 0);
		Mesh.Vertexs[2][2] = FVector(0.0f, 1.0f, 0);
	}

	{
		FirstMesh& Mesh = MonsterMesh;
		Mesh.Vertexs.resize(3);
		for (size_t i = 0; i < Mesh.Vertexs.size(); i++)
		{
			Mesh.Vertexs[i].resize(3);
		}

		// 앞면 만든거
		Mesh.Vertexs[0][0] = FVector(-0.5f, 0.5f, 0);
		Mesh.Vertexs[0][1] = FVector(0.5f, 0.5f, 0);
		Mesh.Vertexs[0][2] = FVector(-0.5f, -0.5f, 0);
		Mesh.Vertexs[1][0] = FVector(0.5f, 0.5f, 0);
		Mesh.Vertexs[1][1] = FVector(0.5f, -0.5f, 0);
		Mesh.Vertexs[1][2] = FVector(-0.5f, -0.5f, 0);
		Mesh.Vertexs[2][0] = FVector(0.5f, 0.5f, 0);
		Mesh.Vertexs[2][1] = FVector(-0.5f, 0.5f, 0);
		Mesh.Vertexs[2][2] = FVector(0.0f, 1.0f, 0);
	}

	{
		MonsterPos = { 400, 200 };
		//MonsterRot = { 45, 0, 0.0f };
		//MonsterScale = { 1000, 1000, 1.0f };
	}

}

void CrossTest::Render(float _Delta)
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	HDC BackDC = BackBufferImage->GetDC();

	if (UEngineInput::GetInst().IsPress('W'))
	{
		PlayerPos += FVector::UP * _Delta * PlayerSpeed;
	}

	if (UEngineInput::GetInst().IsPress('A'))
	{
		PlayerPos += FVector::LEFT * _Delta * PlayerSpeed;
	}

	if (UEngineInput::GetInst().IsPress('S'))
	{
		PlayerPos += FVector::DOWN * _Delta * PlayerSpeed;
	}

	if (UEngineInput::GetInst().IsPress('D'))
	{
		PlayerPos += FVector::RIGHT * _Delta * PlayerSpeed;
	}

	//{
	//	// 요것 하나.

	//	// 단위가 디그리 단위이다.
	//	// 특정한 예를 만들어서 그게 되게 만드는 방법을 만드는 식으로 가는게 편하다.
	//	//              0~180도 까지 밖에 안나오지 않는다.

	//	float Test = 0.0f;
	//	Test += 1.1f;
	//	Test += 0.2f;


	//	FVector MonsterDir = FVector::AngleToVectorDeg(MonsterRot.Z + 90);
	//	// 정확한 각도를 구할필요가 없죠.
	//	FVector CrossResult = FVector::Cross(MonsterDir, PlayerPos - MonsterPos);
	//	CrossResult.Normalize();
	//	// 회전하는 속력이 커지면
	//	MonsterRot.Z += CrossResult.Z * _Delta * 50.0f;

	//	// MonsterPos += (PlayerPos - MonsterPos).NormalizeReturn() * _Delta * 100.0f;

	//	MonsterDir = FVector::AngleToVectorDeg(MonsterRot.Z + 90);
	//	MonsterPos += MonsterDir * _Delta * 100.0f;

	//	// 외적 
	//	// 한번에 회전하는 공식
	//	//FVector CrossResult = FVector::Cross(FVector(0, 1, 0), PlayerPos - MonsterPos);
	//	//CrossResult.Normalize();
	//	//MonsterRot.Z = FVector::GetVectorAngleDeg(PlayerPos - MonsterPos,FVector(0, 1, 0)) * CrossResult.Z;

	//}


	// 플레이어 랜더링하기
	{
		FirstMesh Copy = PlayerMesh;

		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] *= PlayerScale;
			}
		}

		// 월드 변환을 해서 실제 게임세계에서 보이게 만드는 것이다.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex].RotationXDeg(PlayerRot.X);
				Copy.Vertexs[Tri][Vertex].RotationYDeg(PlayerRot.Y);
				Copy.Vertexs[Tri][Vertex].RotationZDeg(PlayerRot.Z);
			}
		}


		// 월드 변환을 해서 실제 게임세계에서 보이게 만드는 것이다.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] += PlayerPos;
			}
		}

		// 2개의 3각형
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			FVector Cross01 = Copy.Vertexs[Tri][0] - Copy.Vertexs[Tri][1];
			FVector Cross02 = Copy.Vertexs[Tri][1] - Copy.Vertexs[Tri][2];

			FVector CrossResult = FVector::Cross(Cross01, Cross02);

			if (CrossResult.Z > 0)
			{
				continue;
			}

			POINT WindowPoint[3];

			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				WindowPoint[Vertex] = Copy.Vertexs[Tri][Vertex].ConvertWindowPOINT();
			}

			Polygon(BackDC, WindowPoint, Copy.Vertexs[Tri].size());
		}
	}


	{
		FirstMesh Copy = MonsterMesh;

		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] *= MonsterScale;
			}
		}

		// 월드 변환을 해서 실제 게임세계에서 보이게 만드는 것이다.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex].RotationXDeg(MonsterRot.X);
				Copy.Vertexs[Tri][Vertex].RotationYDeg(MonsterRot.Y);
				Copy.Vertexs[Tri][Vertex].RotationZDeg(MonsterRot.Z);
			}
		}


		// 월드 변환을 해서 실제 게임세계에서 보이게 만드는 것이다.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] += MonsterPos;
			}
		}

		// 2개의 3각형
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			FVector Cross01 = Copy.Vertexs[Tri][0] - Copy.Vertexs[Tri][1];
			FVector Cross02 = Copy.Vertexs[Tri][1] - Copy.Vertexs[Tri][2];

			FVector CrossResult = FVector::Cross(Cross01, Cross02);

			if (CrossResult.Z > 0)
			{
				continue;
			}

			POINT WindowPoint[3];

			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				WindowPoint[Vertex] = Copy.Vertexs[Tri][Vertex].ConvertWindowPOINT();
			}

			Polygon(BackDC, WindowPoint, Copy.Vertexs[Tri].size());
		}
	}

}
