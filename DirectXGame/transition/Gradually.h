#pragma once
#include "Transition.h"

class Gradually : public Transition
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="dir">�O���f�[�V�����̌��� �f�t�H���g��false(��)</param>
	Gradually(bool dir = false);
	~Gradually() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Start() override;

private:
	Sprite* gradually = nullptr;

	// �O���f�[�V�����̌���		false : �� / true : �c
	bool dir = false;

	XMFLOAT2 position = { 0,0 };
	float speed = 40.0f;
};

