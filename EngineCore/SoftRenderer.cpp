#include "PreCompile.h"
#include "SoftRenderer.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineInput.h>

USoftRenderer::USoftRenderer()
{
}

USoftRenderer::~USoftRenderer()
{
}

void USoftRenderer::BeginPlay()
{
	URenderer::BeginPlay();

	VTest.BeginPlay();
	CTest.BeginPlay();
	MatrixTest.BeginPlay();
	// BoxMesh.Vertexs.resize(12);

	// 라디안을 => 디그리(360분법)
	// 라디안각도의 개념
	// 6.28
}

void USoftRenderer::Render(float _Delta)
{

	URenderer::Render(_Delta);

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	HDC BackDC = BackBufferImage->GetDC();

	FTransform MainTrans = { {40, 40}, {300, 300} };


	// 11명
	FTransform SubTrans = { {40, 40}, {0, 0} };

	// 회전하는 벡터 1

	for (size_t i = 0; i < 4; i++)
	{
		if (true == UEngineInput::GetInst().IsDown('1' + i))
		{
			Select = i + 1;
			break;
		}
	}

	switch (Select)
	{
	case 0:
	{
		MatrixTest.Render(_Delta);
		break;
	}

	case 5:
	{
		CTest.Render(_Delta);
		VTest.Render(_Delta);
		break;
	}
	case 1:
#pragma region RotVector
	{
		SubTrans.Location += MainTrans.Location;
		Angle += _Delta;
		FVector DirVector = FVector::AngleToVectorRad(Angle);
		SubTrans.Location += DirVector * 100.0f;
		FVector LT = SubTrans.CenterLeftTop();
		FVector RB = SubTrans.CenterRightBottom();
		Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
	}
#pragma endregion
	break;
	case 2:
#pragma region Sin

	{
		SinG.clear();

		FVector StartPos = { 300, 300 };

		for (size_t i = 0; i < 360; i++)
		{
			float SinValue = cosf(static_cast<float>(i) * UEngineMath::D2R);
			FTransform ValueTrans = { { 30, 30 }, StartPos + FVector{ static_cast<float>(i * 2.0f),  SinValue * 100.0f } };
			SinG.push_back(ValueTrans);
		}


		// Ranged for

		// SinG.begin();
		// SinG.end();

		// 레인지드 for
		// 절대로 삭제할때 쓰지마라.

		for (FTransform& Trans : SinG)
		{
			FVector LT = Trans.CenterLeftTop();
			FVector RB = Trans.CenterRightBottom();

			Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
		}

	}
#pragma endregion
	break;
	case 3:
#pragma region Rotfigure
	{
		// 점을 회전시키는걸 보여줬다.
		const int PointCount = 10;

		FVector Point[PointCount];
		FVector Pos = { 200, 200 };

		Angle += _Delta * 100;

		float StartAngle = 90.0f;
		float interAngle = static_cast<float>(360) / static_cast<float>(PointCount);
		float Len = 100.0f;


		for (size_t i = 0; i < PointCount; i++)
		{
			if ((i % 2) == 0)
			{
				Len = 100.0f;
			}
			else {
				Len = 40.0f;
			}

			Point[i] = FVector::AngleToVectorDeg(StartAngle + interAngle * i + Angle) * Len;


		}

		POINT WindowPoint[PointCount];

		for (size_t i = 0; i < PointCount; i++)
		{
			Point[i] += Pos;
			WindowPoint[i] = Point[i].ConvertWindowPOINT();
		}

		Polygon(BackDC, WindowPoint, PointCount);
	}
#pragma endregion
	break;
	case 4:
#pragma region RotVector
	{
		{
			static FVector SubRotPivot = FVector(200, 50);
			SubRotPivot.RotationZDeg(_Delta * 360.0f);

			{
				FVector LT = MainTrans.CenterLeftTop();
				FVector RB = MainTrans.CenterRightBottom();
				Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
			}

			{
				SubTrans.Location += SubRotPivot;
				FVector LT = SubTrans.CenterLeftTop();
				FVector RB = SubTrans.CenterRightBottom();
				Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
			}
		}
	}
#pragma endregion
	default:
		break;
	}
	// 사인 그래프



	// 그냥 그대로 사각형을 그려보겠습니다.

}