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

#include "ModelManager.h"
#include "TexCollision.h"

class Object
{
protected:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Object();
	~Object();

	virtual void Initialize(Input* input, TexCollision* texCol);
	virtual void Update() = 0;
	virtual void Draw(ID3D12GraphicsCommandList* cmdList) = 0;
	virtual void SpriteDraw() = 0;

	void SetPosition(XMFLOAT3 position) { this->position = position; }
	XMFLOAT3 GetPosition() { return position; }

	void SetRotation(XMFLOAT3 position) { this->rotation = rotation; }
	XMFLOAT3 GetRotation() { return rotation; }

	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	XMFLOAT3 GetScale() { return scale; }

	// éÄÇÒÇæÇ©
	void SetIsDead(bool isDead) { this->isDead = isDead; }
	bool GetIsDead() { return isDead; }

	/// <summary>
	/// îzíu
	/// </summary>
	void Placement(TexCollision::ArgColor color);

protected:
	Input* input = nullptr;
	TexCollision* texCol = nullptr;
	ModelManager* modelMng = ModelManager::GetInstance();

	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 rotation = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };

	bool isDead = false;
	int a = 0;
};

