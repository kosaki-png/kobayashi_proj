#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Input* input)
{
	Object::Initialize(input);

	playerObj = new Fbx();
	playerObj->Initialize();
	playerObj->SetModel(modelMng->GetModel(1));

	position = { 0,0,0 };
	fhita = 0;
	phi = 0;
}

void Player::Update()
{
	// ˆÚ“®
	{
		playerObj->SetPosition(position);
	}
	// XV
	playerObj->Update();
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	playerObj->Draw(cmdList, false);
}