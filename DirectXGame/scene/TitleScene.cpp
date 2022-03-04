#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace DirectX;
using namespace SpriteData;

// 非同期ロード用
ModelManager* modelMngTitle = ModelManager::GetInstance();
bool isLoadedTitle = false;
std::mutex isLoadedMutexTitle;

// 非同期ロード用
void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexTitle);
	isLoadedTitle = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexTitle);
	return isLoadedTitle;
}

// 非同期ロード関数
void AsyncLoad()
{
	// セレクトに使うデータ取得
	StageDataStorage::LoadData selectData = StageDataStorage::GetInstance()->GetDeSelectData();

	// 情報から必要なモデルをロード
	for (int i = 0; i < selectData.modelName.size(); i++)
	{
		modelMngTitle->Load(selectData.firstNum + i, selectData.modelName[i]);
	}

	modelMngTitle->Load(100, "01_77");	// 23
	modelMngTitle->Load(101, "02_41");	// 43
	modelMngTitle->Load(102, "03_40");	// 63
	modelMngTitle->Load(103, "04_85");	// 83

	SetLockFlag(true);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	safe_delete(camera);
	safe_delete(tmpSprite);
	safe_delete(fadeSprite);
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);
	
		// デバイスをセット
		Fbx::SetDevice(dxCommon->GetDevice());
		// カメラをセット
		Fbx::SetCamera(camera);
		// グラフィックスパイプライン生成
		Fbx::CreateGraphicsPipeline();

		// 非同期ロード用
		auto count = std::thread::hardware_concurrency();
		if (count < 3)
		{
			assert(1);
		}
	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			// スプライトをロードしていないならする
			if (!SpriteLoader::GetTitleFlag())
			{
				SpriteLoader::LoadTitleSprite();
			}
		}

		// スプライト生成
		{
			tmpSprite = Sprite::Create(TITLE, { 0,0 });
			fadeSprite = Sprite::Create(FADE, { 0,0 });
		}

		// スプライト初期設定
		{
			fadeSprite->SetPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
			fadeSprite->SetAnchorPoint({ 0.5f, 0.5f });
		}
	}

	// 非同期ロード開始
	if (!isLoadedTitle)
	{
		th = new std::thread(AsyncLoad);
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, -1, 0 });

	// 各クラス初期化
	{
	}

	isGodray = true;
	trans = 0;
}

void TitleScene::Update()
{	
	// ロード終了後
	if (GetLockFlag())
	{
		// SPACEで次のシーン
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new SelectScene();
		}	
	}

	// タイトル演出
	{
		if (fadeSize.x <= 2000)
		{
			fadeSize.x += 30.0f;
			fadeSize.y += 30.0f;
		}
		else
		{
			fadeAlpha -= 0.005f;
		}
	}

	// マウスポイント
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(FindWindowA(nullptr, "seeker"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	camera->Update();

	// 3Dオブジェクト更新
	{
	}

	// スプライト更新
	{
		fadeSprite->SetSize(fadeSize);
		fadeSprite->SetAlpha(fadeAlpha);
	}

}

void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			if (fadeSize.x >= 2000)
			{
				tmpSprite->Draw();
			}
		}
		Sprite::PostDraw();

		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3Dオブジェクト描画
	{

	}

	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			fadeSprite->Draw();
		}
		Sprite::PostDraw();
	}
}

void TitleScene::FrontDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// スプライト描画
	Sprite::PreDraw(cmdList);
	{

	}
	Sprite::PostDraw();
}

void TitleScene::Finalize()
{
	if (!isLoadedTitle)
	{
		th->join();
	}
}
