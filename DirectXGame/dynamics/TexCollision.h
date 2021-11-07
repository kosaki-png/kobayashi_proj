#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <SafeDelete.h>
#include <vector>

/// <summary>
/// スプライト
/// </summary>
class TexCollision
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	/// <summary>
	/// 頂点データ構造体
	/// </summary>
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	/// <summary>
	/// 定数バッファ用データ構造体
	/// </summary>
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

	// 色情報取り出し
	struct ColorInfo
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};

public: // 静的メンバ関数
	TexCollision();
	~TexCollision();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texnumber">テクスチャ番号</param>
	/// <param name="filename">画像ファイル名</param>
	/// <returns>成否</returns>
	void LoadTexture(int texnumber, const wchar_t* filename);

	/// <summary>
	/// 指定座標のテクスチャ色情報取得
	/// </summary>
	/// <param name="texnum">テクスチャ番号</param>
	/// <param name="position">指定座標</param>
	/// <returns>色情報</returns>
	XMFLOAT4 GetPixelColor(int texNum, XMFLOAT2 position);

	/// <summary>
	/// 指定座標が赤かどうか
	/// </summary>
	/// <param name="texnum">テクスチャ番号</param>
	/// <param name="position">指定座標</param>
	/// <returns>成否</returns>
	bool GetRedFlag(int texNum, XMFLOAT2 position);

private:
	ColorInfo* pcolors[9];

	int texCnt;

	// テクスチャ色情報保存変数
	std::vector<std::vector<ColorInfo>> colors[9];

	XMFLOAT2 size;
};

