#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

// 
float rayStrength(VSOutput input, float2 raySource, float2 rayRefDirection, float2 coord, float seedA, float seedB, float speed)
{
	// 解像度
	float2 iResolution = float2(1280, 720);
	float2 fragCoord = input.uv * iResolution;

	float2 sourceToCoord = coord - raySource;
	float cosAngle = dot(normalize(sourceToCoord), rayRefDirection);

	return clamp(
		(0.45 + 0.15 * sin(cosAngle * seedA + iTime * speed)) +
		(0.3 + 0.2 * cos(-cosAngle * seedB + iTime * speed)),
		0.0, 1.0) *
		clamp((iResolution.x - length(sourceToCoord)) / iResolution.x, 0.5, 1.0);
}

float3 Godray(VSOutput input)
{
	// 解像度
	float2 iResolution = float2(1280, 720);
	float2 fragCoord = input.uv * iResolution;

	float2 uv = input.uv;
	float2 coord = float2(fragCoord.x, iResolution.y - fragCoord.y);

	// 太陽光線のパラメータ
	// ライト１
	float2 rayPos1 = float2(iResolution.x * 0.7, iResolution.y * 1.4);
	float2 rayRefDir1 = normalize(float2(1.0, -0.116));
	float raySeedA1 = 36.2214;
	float raySeedB1 = 21.11349;
	float raySpeed1 = 1.5;

	// ライト２
	float2 rayPos2 = float2(iResolution.x * 0.8, iResolution.y * 1.6);
	float2 rayRefDir2 = normalize(float2(1.0, 0.241));
	const float raySeedA2 = 22.39910;
	const float raySeedB2 = 18.0234;
	const float raySpeed2 = 1.1;

	// フラグメントの太陽光線の色
	float3 rays1 =
		float3(1.0, 1.0, 1.0) *
		rayStrength(input, rayPos1, rayRefDir1, coord, raySeedA1, raySeedB1, raySpeed1);

	float3 rays2 =
		float3(1.0, 1.0, 1.0) *
		rayStrength(input, rayPos2, rayRefDir2, coord, raySeedA2, raySeedB2, raySpeed2);

	float3 fragColor = rays1.x * 0.5 + rays2.x * 0.4;

	// 光を下に行くにつれて減衰
	float brightness = (coord.y / iResolution.y);
	fragColor.x *= 0.1 + (brightness * 0.8);
	fragColor.y *= 0.3 + (brightness * 0.6);
	fragColor.z *= 0.5 + (brightness * 0.5);

	return fragColor;
}

float4 main(VSOutput input) : SV_TARGET
{
	// 色の取得(コメント)
	float4 colortex0 = tex0.Sample(smp, input.uv);
	float4 colortex1 = tex1.Sample(smp, input.uv);

	//return Godray(input);

	return float4(colortex0.rgb + Godray(input) * isGodray, 1);
	/*float4 mainColor = { colortex0.r + colortex1.r,
						 colortex0.g + colortex1.g,
						 colortex0.b + colortex1.b, 1 }; 
	return mainColor;*/
}
