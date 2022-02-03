#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// 色の取得(コメント)
	float4 colortex0 = tex0.Sample(smp, input.uv);
	float4 colortex1 = tex1.Sample(smp, input.uv);

	//return float4(colortex1.rgb, 1);
	float4 mainColor = { colortex0.r + colortex1.r,
						 colortex0.g + colortex1.g,
						 colortex0.b + colortex1.b, 1 }; 
	return mainColor;
}