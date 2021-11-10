#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "Fbx.h"
#include "FbxLoader.h"
#include "Text.h"
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
	void Initialize(Input* input);
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
	//TexCollision* texCol = nullptr;

	Fbx* objKogakuin = nullptr;

	std::vector<Object*> objects;
	int objCnt = 0;
};

