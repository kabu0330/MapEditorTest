#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// 설명 :
class Tile : public ISerializObject
{
public:
	USpriteRenderer* SpriteRenderer;
	bool IsMove = true;
	int TileType = -1;

	FVector Scale;
	FVector Pivot;
	int SpriteIndex;


	// ISerializObject을(를) 통해 상속됨
	void Serialize(UEngineSerializer& _Ser) override
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;
	}

};

class ATileMap : public AActor, public ISerializObject
{
public:
	// constrcuter destructer
	ATileMap();
	~ATileMap();

	// delete Function
	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	void Create(std::string_view _Sprite, FIntPoint _Count, FVector _TileSize);

	// 여기에서    이 인덱스에다가    이스프라이트 

	void SetTileLocation(FVector _Location, int _SpriteIndex);

	void SetTileIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileIndex(FIntPoint _Index, FVector _Pivot, FVector _SpriteScale, int _SpriteIndex);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector _Location);

	FVector IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector _Location);

	bool IsIndexOver(FIntPoint _Index);

	// 데이터를 직렬화(압축)
	void Serialize(UEngineSerializer& _Ser);

	// 데이터를 복구(할때)
	void DeSerialize(UEngineSerializer& _Ser);

protected:

private:
	FIntPoint TileCount;
	std::string SpriteName;
	FVector TileSize;
	std::vector<std::vector<Tile>> AllTiles;
};
