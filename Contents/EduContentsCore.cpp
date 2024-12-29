#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "PlayGameMode.h"
#include "TileMapGameMode.h"


EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

// 엔진이 실행되고 단 1번 실행된다.
void EduContentsCore::BeginPlay()
{


	// 이미지로드
	//{
	//	UEngineDirectory Dir;
	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//		return;
	//	}
	//	Dir.Append("Image");
	//	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
	//	for (size_t i = 0; i < ImageFiles.size(); i++)
	//	{
	//		std::string FilePath = ImageFiles[i].GetPathToString();
	//		UImageManager::GetInst().Load(FilePath);
	//	}
	//}


	// 이미지로드
	{
	/*	UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		UEngineFile File = Dir.GetFile("Player_Right_Test.png");

		UEngineFile MetaFile = Dir.GetFile("Player_Right_Test.png.meta");
		MetaFile.FileOpen("rb");

		UEngineSerializer Ser;
		MetaFile.Read(Ser);

		size_t Size = Ser.GetDataSize();

		std::string Data = reinterpret_cast<const char*>(Ser.GetDataPtr());

		int a = 0;*/

		// 테스트 로드
	}



	// 일반 텍스처가 다 로딩되면
	// 자르는 작업을 아래서 해주는게 좋다.

	//UImageManager::GetInst().CuttingSprite("Player_Right.png", {128, 128});
	//UImageManager::GetInst().CuttingSprite("Text.bmp", { 16, 32 });

	//UEngineSprite* Sprite = UImageManager::GetInst().FindSprite("Player_Right.png");
	//UEngineWinImage* Image = UImageManager::GetInst().FindImage("Player_Right.png");
	//Sprite->ClearSpriteData();
	//Sprite->PushData(Image, { {0,0}, {350, 350} });

	//{

	//	UEngineDirectory BombDir;
	//	BombDir.MoveParentToDirectory("Resources//Image");
	//	BombDir.Append("bomb");

	//	UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());

	//}

	{
		// 타일셋 로드
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	// 이거 꼭 호출해줘야 합니다.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, {1280, 720});

	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");


	UEngineAPICore::GetCore()->OpenLevel("Tile");

}

void EduContentsCore::Tick()
{
	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
}