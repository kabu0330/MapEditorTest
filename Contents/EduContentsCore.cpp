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

// ������ ����ǰ� �� 1�� ����ȴ�.
void EduContentsCore::BeginPlay()
{


	// �̹����ε�
	//{
	//	UEngineDirectory Dir;
	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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


	// �̹����ε�
	{
	/*	UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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

		// �׽�Ʈ �ε�
	}



	// �Ϲ� �ؽ�ó�� �� �ε��Ǹ�
	// �ڸ��� �۾��� �Ʒ��� ���ִ°� ����.

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
		// Ÿ�ϼ� �ε�
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, {1280, 720});

	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");


	UEngineAPICore::GetCore()->OpenLevel("Tile");

}

void EduContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}