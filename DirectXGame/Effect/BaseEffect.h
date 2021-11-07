#pragma once

#include "SafeDelete.h"
#include "Sprite.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>

class BaseEffect
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// エフェクト開始
	
	/// <summary>
	/// エフェクトイン
	/// </summary>
	/// <param name="goOut"> Inの後にOutを起動するか </param>
	void InStart(bool goOut);

	/// <summary>
	/// エフェクトアウト
	/// </summary>
	void OutStart();

	// In中かどうか
	bool GetInFlag() { return in; }
	// Out中かどうか
	bool GetOutFlag() { return out; }

protected:
	bool in = false;	// Inが効果しているか
	bool out = false;	// Outが効果しているか
	bool goOut = false; // Inの後にOutを起動するか

	int effectTimeIn = 0;	// 効果時間
	int effectTimeOut = 0;	// 効果時間
	int count = 0;			// スタートしてからの時間
};