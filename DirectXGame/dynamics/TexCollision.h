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
	// enumの定義
	enum ArgColor
	{
		Green,    // 0
		Blue,   // 1
		Red,  // 2
		Alpha, // 3
	};

	// 色情報取り出し
	struct ColorInfo
	{
		unsigned char colors[4];
	};

	// テクスチャ情報構造体
	struct TexInfo
	{
		std::vector<std::vector<ColorInfo>> pixelColors;	// 色情報
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

	/// <summary>
	/// 指定座標が指定色かどうか
	/// </summary>
	/// <param name="color">当たり判定を取る色</param>
	/// <param name="position">座標</param>
	/// <returns>成否</returns>
	bool GetHitFlag(ArgColor color, XMFLOAT3 position);

	/// <summary>
	/// 指定座標から上下左右１マスの色から無色への方向取得
	/// </summary>
	/// <param name="color">当たり判定を取る色</param>
	/// <param name="position">座標</param>
	/// <returns>戻るための移動方向</returns>
	//XMFLOAT3 Hit2Color(ArgColor color, XMFLOAT3 position);

	/// <summary>
	/// 指定座標から上下左右１マスの色から無色への方向取得
	/// </summary>
	/// <param name="color">当たり判定を取る色</param>
	/// <param name="position">座標</param>
	/// <returns>戻るための移動方向</returns>
	XMFLOAT3 Hit2Color(ArgColor color, XMFLOAT3 position, XMFLOAT3 move);

private:
	ColorInfo* pcolor;

	XMFLOAT2 size;

	std::vector<std::vector<TexInfo>> textures;

	int TEX_WIDTH;
	int TEX_HEIGHT;
};

