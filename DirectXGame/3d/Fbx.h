#pragma once

#include "FbxModel.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class Fbx
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体（座標変換行列用）
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;    // ビュープロジェクション行列
		XMMATRIX world; // ワールド行列
		XMFLOAT3 cameraPos; // カメラ座標（ワールド座標）
		float gomi1;
		XMFLOAT3 lightDir;
		bool isFog;
		XMFLOAT4 fogColor;
	};

public: // 静的メンバ関数
	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();
	// setter
	static void SetDevice(ID3D12Device* device) { Fbx::device = device; }
	static void SetCamera(Camera* camera) { Fbx::camera = camera; }

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// カメラ
	static Camera* camera;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(XMFLOAT3 lightDir = { 0,-1,0 });

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void SetModel(FbxModel* model) { this->model = model; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT3& GetPosition() { return position; }

	/// <summary>
	/// 回転の取得
	/// </summary>
	/// <returns>回転</returns>
	const XMFLOAT3& GetRotation() { return rotation; }

	/// <summary>
	/// 回転の取得
	/// </summary>
	/// <returns>回転</returns>
	const XMFLOAT3& GetScale() { return scale; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="position">回転</param>
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="position">回転</param>
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="position">回転</param>
	void SetFogColor(XMFLOAT4 color) { fogColor = color; }

	/// <summary>
	/// フォグをかけるか否か　defoult : on
	/// </summary>
	/// <param name="isFog"></param>
	void SetFog(bool isFog) { this->isFog = isFog; }

protected: // メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld = {};
	// モデル
	FbxModel* model = nullptr;
	// ライトの向き
	XMFLOAT3 lightDir = { 0,0,0 };
	// フォグ
	bool isFog = true;
	// フォグの色
	XMFLOAT4 fogColor = { 0,0,0,0 };
};

