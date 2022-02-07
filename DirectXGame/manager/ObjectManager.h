#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Fbx.h"
#include "FbxLoader.h"
#include "XinputControll.h"
#include "Input.h"
#include "DirectXCommon.h"

#include "Object.h"
#include "ModelManager.h"
#include "TexCollision.h"
#include <vector>

class ObjectManager
{
private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	ObjectManager();
	~ObjectManager();

	void AddObject(Object* object);
	void Initialize(Input* input, TexCollision* texCol);
	void Update(XMFLOAT3 playerPos = { 0,0,0 }, float length = 0);
	void Draw(ID3D12GraphicsCommandList* cmdList, XMFLOAT3 playerPos = { 0,0,0 }, float length = 0);
	void SpriteDraw();

private:
	std::vector<Object*> objects;

};

