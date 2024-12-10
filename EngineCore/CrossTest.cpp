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

		// �ո� �����
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

		// �ո� �����
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
	//	// ��� �ϳ�.

	//	// ������ ��׸� �����̴�.
	//	// Ư���� ���� ���� �װ� �ǰ� ����� ����� ����� ������ ���°� ���ϴ�.
	//	//              0~180�� ���� �ۿ� �ȳ����� �ʴ´�.

	//	float Test = 0.0f;
	//	Test += 1.1f;
	//	Test += 0.2f;


	//	FVector MonsterDir = FVector::AngleToVectorDeg(MonsterRot.Z + 90);
	//	// ��Ȯ�� ������ �����ʿ䰡 ����.
	//	FVector CrossResult = FVector::Cross(MonsterDir, PlayerPos - MonsterPos);
	//	CrossResult.Normalize();
	//	// ȸ���ϴ� �ӷ��� Ŀ����
	//	MonsterRot.Z += CrossResult.Z * _Delta * 50.0f;

	//	// MonsterPos += (PlayerPos - MonsterPos).NormalizeReturn() * _Delta * 100.0f;

	//	MonsterDir = FVector::AngleToVectorDeg(MonsterRot.Z + 90);
	//	MonsterPos += MonsterDir * _Delta * 100.0f;

	//	// ���� 
	//	// �ѹ��� ȸ���ϴ� ����
	//	//FVector CrossResult = FVector::Cross(FVector(0, 1, 0), PlayerPos - MonsterPos);
	//	//CrossResult.Normalize();
	//	//MonsterRot.Z = FVector::GetVectorAngleDeg(PlayerPos - MonsterPos,FVector(0, 1, 0)) * CrossResult.Z;

	//}


	// �÷��̾� �������ϱ�
	{
		FirstMesh Copy = PlayerMesh;

		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] *= PlayerScale;
			}
		}

		// ���� ��ȯ�� �ؼ� ���� ���Ӽ��迡�� ���̰� ����� ���̴�.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex].RotationXDeg(PlayerRot.X);
				Copy.Vertexs[Tri][Vertex].RotationYDeg(PlayerRot.Y);
				Copy.Vertexs[Tri][Vertex].RotationZDeg(PlayerRot.Z);
			}
		}


		// ���� ��ȯ�� �ؼ� ���� ���Ӽ��迡�� ���̰� ����� ���̴�.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] += PlayerPos;
			}
		}

		// 2���� 3����
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

		// ���� ��ȯ�� �ؼ� ���� ���Ӽ��迡�� ���̰� ����� ���̴�.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex].RotationXDeg(MonsterRot.X);
				Copy.Vertexs[Tri][Vertex].RotationYDeg(MonsterRot.Y);
				Copy.Vertexs[Tri][Vertex].RotationZDeg(MonsterRot.Z);
			}
		}


		// ���� ��ȯ�� �ؼ� ���� ���Ӽ��迡�� ���̰� ����� ���̴�.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] += MonsterPos;
			}
		}

		// 2���� 3����
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
