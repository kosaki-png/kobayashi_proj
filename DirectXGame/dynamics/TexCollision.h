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
	// 色情報取り出し
	struct ColorInfo
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};

	// テクスチャ情報構造体
	struct TexInfo
	{
		std::vector<std::vector<ColorInfo>> colors;	// 色情報
	};

public: // 静的メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texWidth">基本テクスチャの横幅</param>
	/// <param name="texHeight">基本テクスチャの縦幅</param>
	/// /// <param name="texWidth">配置テクスチャの最大横</param>
	/// <param name="texHeight">配置テクスチャの最大縦</param>
	TexCollision(int texWidth, int texHeight, int maxMapX, int maxMapY);

	~TexCollision();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="mapX">座標番号横</param>
	/// <param name="mapY">座標番号縦</param>
	/// <param name="filename">画像ファイル名</param>
	/// <returns>成否</returns>
	void LoadTexture(int mapX, int mapY, const wchar_t* filename);

	/// <summary>
	/// 指定座標のテクスチャ色情報取得
	/// </summary>
	/// <param name="texnum">テクスチャ番号</param>
	/// <param name="position">指定座標</param>
	/// <returns>色情報</returns>
	XMFLOAT4 GetPixelColor(XMFLOAT3 position);

	/// <summary>
	/// 指定座標が赤かどうか
	/// </summary>
	/// <param name="texnum">テクスチャ番号</param>
	/// <param name="position">指定座標</param>
	/// <returns>成否</returns>
	bool GetRedFlag(XMFLOAT3 position);

private:
	ColorInfo* pcolor;

	int texCnt;

	// テクスチャ色情報保存変数
	//std::vector<std::vector<ColorInfo>> colors[9];

	XMFLOAT2 size;

	std::vector<std::vector<TexInfo>> textures;

	int TEX_WIDTH;
	int TEX_HEIGHT;
};

