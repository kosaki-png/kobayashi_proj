#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "GameScene.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
#include "PostEffect.h"
#include "FlameRate.h"

#include "SceneManager.h"

#include "Fade.h"
#include "ModelManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	FlameRate* flamerate = nullptr;

	SceneManager* sceneMng = nullptr;
	//BaseScene* scene = nullptr;

	//PostEffect* postEffect = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();

	//フレームレート固定の初期化
	flamerate = new FlameRate();
		
	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

	// シーン管理初期化
	sceneMng = SceneManager::GetInstance();

#pragma region 汎用機能初期化

	// 入力の初期化
	input = Input::GetInstance();
	if (!input->Initialize(win->GetInstance(), win->GetHwnd())) {
		assert(0);
		return 1;
	}
	// オーディオの初期化
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	// ライト静的初期化
	LightGroup::StaticInitialize(dxCommon->GetDevice());
	// パーティクルマネージャ初期化
	ParticleManager::GetInstance()->Initialize(dxCommon->GetDevice());
	// OBJ関連静的初期化
	//Object3d::StaticInitialize(dxCommon->GetDevice());
	// FBX関連静的初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

#pragma endregion

	// ポストエフェクト用テクスチャの読み込み
	//Sprite::LoadTexture(100, L"Resources/background.png");
	// ポストエフェクトの初期化
	//postEffect = new PostEffect();
	//postEffect->Initialize();

	// 最初のシーンの初期化
	sceneMng->Start(dxCommon, input, audio);

	// カーソルON/OFF
	//ShowCursor(FALSE);
	
	// メインループ
	while (true)
	{
		//フレームレート固定の更新処理
		flamerate->Update();
		// メッセージ処理
		if (win->ProcessMessage()) {	break; }

		// 入力関連の毎フレーム処理
		input->Update();

		// シーン切り替え
		sceneMng->Update();

		// レンダーテクスチャへの描画
		/*postEffect->PreDrawScene(dxCommon->GetCommandList());
		scene->Draw();
		postEffect->PostDrawScene(dxCommon->GetCommandList());*/
		
		// 描画開始
		dxCommon->PreDraw();
		// ポストエフェクトの描画
		//postEffect->Draw(dxCommon->GetCommandList());
		sceneMng->Draw();
		// 描画終了
		dxCommon->PostDraw();
		//フレームレート待機処理
		flamerate->Wait();
	}

	sceneMng->Finalize();
	// 各種解放
	FbxLoader::GetInstance()->Finalize();
	ModelManager::GetInstance()->Destroy();
	SceneManager::GetInstance()->Destroy();
	safe_delete(audio);
	safe_delete(dxCommon);
	safe_delete(flamerate);
	//delete postEffect;

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}