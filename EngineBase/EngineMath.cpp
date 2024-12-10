#include "PreCompile.h"
#include "EngineMath.h"

const double UEngineMath::DPI = 3.14159265358979323846264338327950288419716939937510;
const double UEngineMath::DPI2 = DPI * 2.0;

const float UEngineMath::PI = 3.14159265358979323846264f;
const float UEngineMath::PI2 = PI * 2.0f;

// ��׸��� �������� �ٲٴ� ���� �ȴ�.
const float UEngineMath::D2R = UEngineMath::PI / 180.0f;
const float UEngineMath::R2D = 180.0f / UEngineMath::PI;

const FVector FVector::ZERO = { 0, 0 };
const FVector FVector::LEFT = { -1, 0 };
const FVector FVector::RIGHT = { 1, 0 };
const FVector FVector::UP = { 0, -1 };
const FVector FVector::DOWN = { 0, 1 };

const FIntPoint FIntPoint::LEFT = { -1, 0 };
const FIntPoint FIntPoint::RIGHT = { 1, 0 };
const FIntPoint FIntPoint::UP = { 0, -1 };
const FIntPoint FIntPoint::DOWN = { 0, 1 };


const UColor UColor::WHITE = { 255, 255, 255, 0 };
const UColor UColor::BLACK = { 0, 0, 0, 0 };

FIntPoint FVector::ConvertToPoint() const
{
	return { iX(), iY() };
}


std::function<bool(const FTransform&, const FTransform&)> FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		// ������ ������ �ʱ�ȭ �ɶ� �ʱ�ȭ�ϴ� ���� �ڵ����� �����Ҽ� �ִ�.
		// ������ ������ ��������� �� �۾��� �ڵ����� ����ȴ�.
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;

		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CirCleToCirCle;

		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::CirCle)] = FTransform::RectToCirCle;

		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::Rect)] = FTransform::CirCleToRect;

	}
};

// ������ ����
CollisionFunctionInit Inst = CollisionFunctionInit();


bool FTransform::Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right)
{
	return FTransform::AllCollisionFunction[static_cast<int>(_LeftType)][static_cast<int>(_RightType)](_Left, _Right);
}

bool FTransform::PointToCirCle(const FTransform& _Left, const FTransform& _Right)
{
	FTransform LeftTrans = _Left;
	LeftTrans.Scale = FVector::ZERO;
	return CirCleToCirCle(LeftTrans, _Right);
}

// �� vs �簢��
bool FTransform::PointToRect(const FTransform& _Left, const FTransform& _Right)
{
	FTransform LeftTrans = _Left;
	LeftTrans.Scale = FVector::ZERO;
	return RectToRect(LeftTrans, _Right);
}

bool FTransform::CirCleToCirCle(const FTransform& _Left, const FTransform& _Right)
{
	FVector Len = _Left.Location - _Right.Location;

	// Ʈ�������� ������ ������ �������� x�� ����ũ�⸦ ���������� ���ڽ��ϴ�.
	// �ο��� �������� ���� ������ ���̺��� ũ�ٸ� 
	if (Len.Length() < _Left.Scale.hX() + _Right.Scale.hX())
	{
		return true;
	}

	return false;
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{

	if (_Left.CenterLeft() > _Right.CenterRight())
	{
		return false;
	}

	if (_Left.CenterRight() < _Right.CenterLeft())
	{
		return false;
	}

	if (_Left.CenterTop() > _Right.CenterBottom())
	{
		return false;
	}

	if (_Left.CenterBottom() < _Right.CenterTop())
	{
		return false;
	}
	// ���� ����� �ȴ�.
	return true;
}

bool FTransform::RectToCirCle(const FTransform& _Left, const FTransform& _Right)
{
	return CirCleToRect(_Right, _Left);
}


bool FTransform::CirCleToRect(const FTransform& _Left, const FTransform& _Right)
{
	// �¿�� ������ Ȯ���� Ʈ������
	FTransform WTransform = _Right;
	WTransform.Scale.X += _Left.Scale.X;

	// ���Ʒ��� ������ ��ŭ Ȯ���� Ʈ������
	FTransform HTransform = _Right;
	HTransform.Scale.Y += _Left.Scale.X;

	if (true == PointToRect(_Left, WTransform) || true == PointToRect(_Left, HTransform))
	{
		return true;
	}

	// ��� ������ ���ؼ� static���� ����� ����� �ִµ�.
	// static FVector ArrPoint[4];
	// �����忡���� ������.
	FVector ArrPoint[4];

	ArrPoint[0] = _Right.CenterLeftTop();
	ArrPoint[1] = _Right.CenterLeftBottom();
	ArrPoint[2] = _Right.CenterRightTop();
	ArrPoint[3] = _Right.CenterRightBottom();

	FTransform PointCirCle;
	PointCirCle.Scale = _Left.Scale;
	for (size_t i = 0; i < 4; i++)
	{
		PointCirCle.Location = ArrPoint[i];
		if (true == PointToCirCle(_Left, PointCirCle))
		{
			return true;
		}
	}

	return false;
}

FVector FVector::Transform(const FVector& _Vector, const class FMatrix& _Matrix)
{
	return _Vector * _Matrix;
}

FVector FVector::TransformCoord(const FVector& _Vector, const class FMatrix& _Matrix)
{
	FVector Copy = _Vector;
	Copy.W = 1.0f;
	return Copy * _Matrix;
}

FVector FVector::TransformNormal(const FVector& _Vector, const class FMatrix& _Matrix)
{
	FVector Copy = _Vector;
	Copy.W = 0.0f;
	return Copy * _Matrix;
}

FVector FVector::operator*(const class FMatrix& _Matrix) const
{
	FVector Result;
	// ������ �ϼ��ϰ� ���ؼ� ��� Ȯ���غ�����.

	// x y z w�� �� �������� �Ѵ�.
	Result.X = Arr2D[0][0] * _Matrix.Arr2D[0][0] + Arr2D[0][1] * _Matrix.Arr2D[1][0] + Arr2D[0][2] * _Matrix.Arr2D[2][0] + Arr2D[0][3] * _Matrix.Arr2D[3][0];
	Result.Y = Arr2D[0][0] * _Matrix.Arr2D[0][1] + Arr2D[0][1] * _Matrix.Arr2D[1][1] + Arr2D[0][2] * _Matrix.Arr2D[2][1] + Arr2D[0][3] * _Matrix.Arr2D[3][1];
	Result.Z = Arr2D[0][0] * _Matrix.Arr2D[0][2] + Arr2D[0][1] * _Matrix.Arr2D[1][2] + Arr2D[0][2] * _Matrix.Arr2D[2][2] + Arr2D[0][3] * _Matrix.Arr2D[3][2];
	Result.W = Arr2D[0][0] * _Matrix.Arr2D[0][3] + Arr2D[0][1] * _Matrix.Arr2D[1][3] + Arr2D[0][2] * _Matrix.Arr2D[2][3] + Arr2D[0][3] * _Matrix.Arr2D[3][3];


	//std::cout << "X : " << Arr2D[0][0] << "*" << _Matrix.Arr2D[0][0] << "+" << Arr2D[0][1] << "*" << _Matrix.Arr2D[1][0] << "+" << Arr2D[0][2] << "*" << _Matrix.Arr2D[2][0] << "+" << Arr2D[0][3] << "*" << _Matrix.Arr2D[3][0] << std::endl;
	//std::cout << "Y : " << Arr2D[0][0] << "*" << _Matrix.Arr2D[0][1] << "+" << Arr2D[0][1] << "*" << _Matrix.Arr2D[1][1] << "+" << Arr2D[0][2] << "*" << _Matrix.Arr2D[2][1] << "+" << Arr2D[0][3] << "*" << _Matrix.Arr2D[3][1] << std::endl;
	//std::cout << "Z : " << Arr2D[0][0] << "*" << _Matrix.Arr2D[0][2] << "+" << Arr2D[0][1] << "*" << _Matrix.Arr2D[1][2] << "+" << Arr2D[0][2] << "*" << _Matrix.Arr2D[2][2] << "+" << Arr2D[0][3] << "*" << _Matrix.Arr2D[3][2] << std::endl;
	//std::cout << "W : " << Arr2D[0][0] << "*" << _Matrix.Arr2D[0][3] << "+" << Arr2D[0][1] << "*" << _Matrix.Arr2D[1][3] << "+" << Arr2D[0][2] << "*" << _Matrix.Arr2D[2][3] << "+" << Arr2D[0][3] << "*" << _Matrix.Arr2D[3][3] << std::endl;

	//std::cout << Result.ToString() << std::endl;


	return Result;
}

FVector& FVector::operator*=(const FMatrix& _Matrix)
{
	FVector Copy = *this;

	this->X = Copy.X * _Matrix.Arr2D[0][0] + Copy.Y * _Matrix.Arr2D[1][0] + Copy.Z * _Matrix.Arr2D[2][0] + Copy.W * _Matrix.Arr2D[3][0];
	this->Y = Copy.X * _Matrix.Arr2D[0][1] + Copy.Y * _Matrix.Arr2D[1][1] + Copy.Z * _Matrix.Arr2D[2][1] + Copy.W * _Matrix.Arr2D[3][1];
	this->Z = Copy.X * _Matrix.Arr2D[0][2] + Copy.Y * _Matrix.Arr2D[1][2] + Copy.Z * _Matrix.Arr2D[2][2] + Copy.W * _Matrix.Arr2D[3][2];
	this->W = Copy.X * _Matrix.Arr2D[0][3] + Copy.Y * _Matrix.Arr2D[1][3] + Copy.Z * _Matrix.Arr2D[2][3] + Copy.W * _Matrix.Arr2D[3][3];


	return *this;
}

FMatrix FMatrix::operator*(const FMatrix& _Matrix)
{
	FMatrix Result;

	Result.Arr2D[0][0] = Arr2D[0][0] * _Matrix.Arr2D[0][0] + Arr2D[0][1] * _Matrix.Arr2D[1][0] + Arr2D[0][2] * _Matrix.Arr2D[2][0] + Arr2D[0][3] * _Matrix.Arr2D[3][0];
	Result.Arr2D[0][1] = Arr2D[0][0] * _Matrix.Arr2D[0][1] + Arr2D[0][1] * _Matrix.Arr2D[1][1] + Arr2D[0][2] * _Matrix.Arr2D[2][1] + Arr2D[0][3] * _Matrix.Arr2D[3][1];
	Result.Arr2D[0][2] = Arr2D[0][0] * _Matrix.Arr2D[0][2] + Arr2D[0][1] * _Matrix.Arr2D[1][2] + Arr2D[0][2] * _Matrix.Arr2D[2][2] + Arr2D[0][3] * _Matrix.Arr2D[3][2];
	Result.Arr2D[0][3] = Arr2D[0][0] * _Matrix.Arr2D[0][3] + Arr2D[0][1] * _Matrix.Arr2D[1][3] + Arr2D[0][2] * _Matrix.Arr2D[2][3] + Arr2D[0][3] * _Matrix.Arr2D[3][3];

	Result.Arr2D[1][0] = Arr2D[1][0] * _Matrix.Arr2D[0][0] + Arr2D[1][1] * _Matrix.Arr2D[1][0] + Arr2D[1][2] * _Matrix.Arr2D[2][0] + Arr2D[1][3] * _Matrix.Arr2D[3][0];
	Result.Arr2D[1][1] = Arr2D[1][0] * _Matrix.Arr2D[0][1] + Arr2D[1][1] * _Matrix.Arr2D[1][1] + Arr2D[1][2] * _Matrix.Arr2D[2][1] + Arr2D[1][3] * _Matrix.Arr2D[3][1];
	Result.Arr2D[1][2] = Arr2D[1][0] * _Matrix.Arr2D[0][2] + Arr2D[1][1] * _Matrix.Arr2D[1][2] + Arr2D[1][2] * _Matrix.Arr2D[2][2] + Arr2D[1][3] * _Matrix.Arr2D[3][2];
	Result.Arr2D[1][3] = Arr2D[1][0] * _Matrix.Arr2D[0][3] + Arr2D[1][1] * _Matrix.Arr2D[1][3] + Arr2D[1][2] * _Matrix.Arr2D[2][3] + Arr2D[1][3] * _Matrix.Arr2D[3][3];

	Result.Arr2D[2][0] = Arr2D[2][0] * _Matrix.Arr2D[0][0] + Arr2D[2][1] * _Matrix.Arr2D[1][0] + Arr2D[2][2] * _Matrix.Arr2D[2][0] + Arr2D[2][3] * _Matrix.Arr2D[3][0];
	Result.Arr2D[2][1] = Arr2D[2][0] * _Matrix.Arr2D[0][1] + Arr2D[2][1] * _Matrix.Arr2D[1][1] + Arr2D[2][2] * _Matrix.Arr2D[2][1] + Arr2D[2][3] * _Matrix.Arr2D[3][1];
	Result.Arr2D[2][2] = Arr2D[2][0] * _Matrix.Arr2D[0][2] + Arr2D[2][1] * _Matrix.Arr2D[1][2] + Arr2D[2][2] * _Matrix.Arr2D[2][2] + Arr2D[2][3] * _Matrix.Arr2D[3][2];
	Result.Arr2D[2][3] = Arr2D[2][0] * _Matrix.Arr2D[0][3] + Arr2D[2][1] * _Matrix.Arr2D[1][3] + Arr2D[2][2] * _Matrix.Arr2D[2][3] + Arr2D[2][3] * _Matrix.Arr2D[3][3];

	Result.Arr2D[3][0] = Arr2D[3][0] * _Matrix.Arr2D[0][0] + Arr2D[3][1] * _Matrix.Arr2D[1][0] + Arr2D[3][2] * _Matrix.Arr2D[2][0] + Arr2D[3][3] * _Matrix.Arr2D[3][0];
	Result.Arr2D[3][1] = Arr2D[3][0] * _Matrix.Arr2D[0][1] + Arr2D[3][1] * _Matrix.Arr2D[1][1] + Arr2D[3][2] * _Matrix.Arr2D[2][1] + Arr2D[3][3] * _Matrix.Arr2D[3][1];
	Result.Arr2D[3][2] = Arr2D[3][0] * _Matrix.Arr2D[0][2] + Arr2D[3][1] * _Matrix.Arr2D[1][2] + Arr2D[3][2] * _Matrix.Arr2D[2][2] + Arr2D[3][3] * _Matrix.Arr2D[3][2];
	Result.Arr2D[3][3] = Arr2D[3][0] * _Matrix.Arr2D[0][3] + Arr2D[3][1] * _Matrix.Arr2D[1][3] + Arr2D[3][2] * _Matrix.Arr2D[2][3] + Arr2D[3][3] * _Matrix.Arr2D[3][3];

	return Result;

}