cbuffer cbuff0 : register(b0)
{
	matrix viewproj;	// ビュープロジェクション行列
	matrix world;		// ワールド行列
	float3 cameraPos;	// カメラ座標（ワールド座標）
	float gomi;
	float3 lightDir;		// ライトの向き
	bool isFog;			// フォグをかけるか
};

//cbuffer cbuff1 : register(b0)
//{
//	matrix viewproj; // ビュープロジェクション行列
//	matrix world; // ワールド行列
//	float3 cameraPos; // カメラ座標（ワールド座標）
//};

//バーテックスバッファーの入力
struct VSInput
{
	float4 pos	: POSITION;//位置   
	float3 normal : NORMAL;//頂点法線
	float2 uv	: TEXCOORD;//テクスチャー座標
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float3 normal :NORMAL; // 法線
	float2 uv  :TEXCOORD; // uv値
	float3 lightDir : TEXCOORD1;	// ライトの向き
	float fog : TEXCOORD2;	// フォグ
};
