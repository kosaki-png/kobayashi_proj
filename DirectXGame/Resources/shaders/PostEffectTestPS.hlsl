#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// 色の取得(コメント)
	float4 colortex0 = tex0.Sample(smp, input.uv);
	float4 colortex1 = tex1.Sample(smp, input.uv);
	// 色反転
	//colortex0 = float4(1 - colortex0.r, 1 - colortex0.g, 1 - colortex0.b, 1);

	// ぼかし
	//float pixelX = 1.0 / 1280.0;
	//float pixelY = 1.0 / 720.0;
	//int filter = 20;	// ぼかす範囲
	//float4 total = { 0,0,0,0 };

	// 範囲分を平均化
	/*for (int y = 0; y < filter; y++)
	{
		for (int x = 0; x < filter; x++)
		{
			total += tex1.Sample(smp, input.uv + float2((float)x * pixelX, (float)y * pixelY));
		}
	}
	total = total / (float)filter / (float)filter;*/

	// ２０分割で交互に(コメント)
	/*float4 color = total;
	if (fmod(input.uv.y,0.2f) < 0.1f) {
		color = float4(colortex0.rgb, 1);
	}*/

	//return float4(color.rgb, 1);
	float4 mainColor = { colortex0.r + colortex1.r,
						 colortex0.g + colortex1.g,
						 colortex0.b + colortex1.b, 1 };
	return mainColor;
	//return float4(colortex1.rgb, 1);
}