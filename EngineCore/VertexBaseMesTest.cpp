#include "PreCompile.h"
#include "VertexBaseMesTest.h"
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineAPICore.h>

VertexBaseMesTest::VertexBaseMesTest()
{
}

VertexBaseMesTest::~VertexBaseMesTest()
{
}

void VertexBaseMesTest::BeginPlay()
{

	BoxMesh.Vertexs.resize(12);

	for (size_t i = 0; i < BoxMesh.Vertexs.size(); i++)
	{
		BoxMesh.Vertexs[i].resize(3);
	}


	Scale = { 200, 200, 200 };

	// 아래가 정석
	// BoxMesh.Vertexs[0][0] = FVector(-0.5, );

	// 앞면 만든거
	BoxMesh.Vertexs[0][0] = FVector(-0.5f, 0.5f, -0.5f);
	BoxMesh.Vertexs[0][1] = FVector(0.5f, 0.5f, -0.5f);
	BoxMesh.Vertexs[0][2] = FVector(-0.5f, -0.5f, -0.5f);
	BoxMesh.Vertexs[1][0] = FVector(0.5f, 0.5f, -0.5f);
	BoxMesh.Vertexs[1][1] = FVector(0.5f, -0.5f, -0.5f);
	BoxMesh.Vertexs[1][2] = FVector(-0.5f, -0.5f, -0.5f);


	// 뒷면
	BoxMesh.Vertexs[2][0] = BoxMesh.Vertexs[0][0].RotationXDegReturn(180);
	BoxMesh.Vertexs[2][1] = BoxMesh.Vertexs[0][1].RotationXDegReturn(180);
	BoxMesh.Vertexs[2][2] = BoxMesh.Vertexs[0][2].RotationXDegReturn(180);
	BoxMesh.Vertexs[3][0] = BoxMesh.Vertexs[1][0].RotationXDegReturn(180);
	BoxMesh.Vertexs[3][1] = BoxMesh.Vertexs[1][1].RotationXDegReturn(180);
	BoxMesh.Vertexs[3][2] = BoxMesh.Vertexs[1][2].RotationXDegReturn(180);

	// 왼쪽면
	BoxMesh.Vertexs[4][0] = BoxMesh.Vertexs[0][0].RotationYDegReturn(90);
	BoxMesh.Vertexs[4][1] = BoxMesh.Vertexs[0][1].RotationYDegReturn(90);
	BoxMesh.Vertexs[4][2] = BoxMesh.Vertexs[0][2].RotationYDegReturn(90);
	BoxMesh.Vertexs[5][0] = BoxMesh.Vertexs[1][0].RotationYDegReturn(90);
	BoxMesh.Vertexs[5][1] = BoxMesh.Vertexs[1][1].RotationYDegReturn(90);
	BoxMesh.Vertexs[5][2] = BoxMesh.Vertexs[1][2].RotationYDegReturn(90);

	// 오른쪽
	BoxMesh.Vertexs[6][0] = BoxMesh.Vertexs[0][0].RotationYDegReturn(-90);
	BoxMesh.Vertexs[6][1] = BoxMesh.Vertexs[0][1].RotationYDegReturn(-90);
	BoxMesh.Vertexs[6][2] = BoxMesh.Vertexs[0][2].RotationYDegReturn(-90);
	BoxMesh.Vertexs[7][0] = BoxMesh.Vertexs[1][0].RotationYDegReturn(-90);
	BoxMesh.Vertexs[7][1] = BoxMesh.Vertexs[1][1].RotationYDegReturn(-90);
	BoxMesh.Vertexs[7][2] = BoxMesh.Vertexs[1][2].RotationYDegReturn(-90);

	// 윗면
	BoxMesh.Vertexs[8][0] = BoxMesh.Vertexs[0][0].RotationXDegReturn(-90);
	BoxMesh.Vertexs[8][1] = BoxMesh.Vertexs[0][1].RotationXDegReturn(-90);
	BoxMesh.Vertexs[8][2] = BoxMesh.Vertexs[0][2].RotationXDegReturn(-90);
	BoxMesh.Vertexs[9][0] = BoxMesh.Vertexs[1][0].RotationXDegReturn(-90);
	BoxMesh.Vertexs[9][1] = BoxMesh.Vertexs[1][1].RotationXDegReturn(-90);
	BoxMesh.Vertexs[9][2] = BoxMesh.Vertexs[1][2].RotationXDegReturn(-90);

	// 윗면
	BoxMesh.Vertexs[10][0] = BoxMesh.Vertexs[0][0].RotationXDegReturn(90);
	BoxMesh.Vertexs[10][1] = BoxMesh.Vertexs[0][1].RotationXDegReturn(90);
	BoxMesh.Vertexs[10][2] = BoxMesh.Vertexs[0][2].RotationXDegReturn(90);
	BoxMesh.Vertexs[11][0] = BoxMesh.Vertexs[1][0].RotationXDegReturn(90);
	BoxMesh.Vertexs[11][1] = BoxMesh.Vertexs[1][1].RotationXDegReturn(90);
	BoxMesh.Vertexs[11][2] = BoxMesh.Vertexs[1][2].RotationXDegReturn(90);
}
void VertexBaseMesTest::Render(float _Delta)
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	HDC BackDC = BackBufferImage->GetDC();


	// 기존의 매쉬의 카피를 만든다.
	// 로컬 스페이스라고 부르는 자신만의 공간에 존재했다.
	FirstMesh Copy = BoxMesh;

	// Scale.X -= _Delta * 10.0f;

	for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
	{
		for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
		{
			Copy.Vertexs[Tri][Vertex] *= Scale;
		}
	}
	// 월드 변환은 순서가 있습니다.
	// 크자이공부
	// 크기 자전 이동 공전 부모

	// 크기

	Roation.X += _Delta * 360;
	Roation.Y = 30;
	Roation.Z += _Delta * 360;

	// 월드 변환을 해서 실제 게임세계에서 보이게 만드는 것이다.
	for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
	{
		for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
		{
			Copy.Vertexs[Tri][Vertex].RotationXDeg(Roation.X);
			Copy.Vertexs[Tri][Vertex].RotationYDeg(Roation.Y);
			Copy.Vertexs[Tri][Vertex].RotationZDeg(Roation.Z);
		}
	}


	// 월드 변환을 해서 실제 게임세계에서 보이게 만드는 것이다.
	for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
	{
		for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
		{
			Copy.Vertexs[Tri][Vertex] += Position;
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

		// 어떻게 할거냐?
		//if (true)
		//{
		//	continue;
		//}

		POINT WindowPoint[3];

		for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
		{
			WindowPoint[Vertex] = Copy.Vertexs[Tri][Vertex].ConvertWindowPOINT();
		}

		Polygon(BackDC, WindowPoint, Copy.Vertexs[Tri].size());
	}

}