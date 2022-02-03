#include "FBX.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};

PSOutput main(VSOutput input)
{
	PSOutput output;
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	// Lambert反射
	float3 light = normalize(lightDir); // 真下からのライト
	//float3 light = normalize(float3(1, -1, 1));
	float diffuse = saturate(dot(light, input.normal));
	float brightness = diffuse + 0.3f;
	float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);

	// 陰影とテクスチャの色を合成
	// メインの描画
	float4 mainColor = lerp(shadecolor * texcolor, fogColor, input.fog);
	output.target0 = mainColor;

	float grayScale = mainColor.r * 0.299 + mainColor.g * 0.587 + mainColor.b * 0.114;
	float extract = step(0.9, grayScale);

	// サブの描画
	output.target1 = mainColor * grayScale;

	return output;
}

//float4 main(VSOutput input) : SV_TARGET
//{
//	float4 colortex0 = tex0.Sample(smp, input.uv);
//	float4 colortex1 = tex1.Sample(smp, input.uv);
//
//	float4 color = colortex0;
//	if (fmod(input.uv.y, 0.1f) < 0.05f) {
//		color = colortex1;
//	}
//
//	return float4(color.rgb, 1);
//}