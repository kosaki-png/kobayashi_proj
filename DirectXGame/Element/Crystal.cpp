#include "Crystal.h"

Crystal::Crystal()
{
}

Crystal::~Crystal()
{
	safe_delete(crystalObj);
	safe_delete(circleObj);
	safe_delete(debri);
}

void Crystal::Initialize(Input* input, TexCollision* texCol)
{
	Object::Initialize(input, texCol);

	// �{��
	crystalObj = new Fbx();
	crystalObj->Initialize();
	crystalObj->SetModel(ModelManager::GetInstance()->GetModel(3));

	// ���͂̉~
	circleObj = new Fbx();
	circleObj->Initialize();
	circleObj->SetModel(ModelManager::GetInstance()->GetModel(4));

	// ����
	debri = new Fbx();
	debri->Initialize({0, 1.0f, 0});
	debri->SetModel(ModelManager::GetInstance()->GetModel(6));

	// �z�u
	Placement(TexCollision::ArgColor::Red);
}

void Crystal::Update()
{
	// ����ł��Ȃ��Ƃ�
	if (!isDead)
	{
		// �㉺������
		rot += 0.02f;

		// �{��
		rotation.y--;
		crystalObj->SetRotation(rotation);
		crystalObj->SetPosition({ position.x, position.y + sinf(rot) / 2, position.z });
		crystalObj->Update();

		// ���͂̉~
		circleRot++;
		circleObj->SetPosition({ position.x, position.y + sinf(rot) / 2, position.z });
		circleObj->SetRotation({ 0,circleRot,0 });
		circleObj->Update();
	}

	// �l����̉��o
	if (isEffect)
	{
		// �g�U
		if (debriScale <= 1.0f && effectCnt <= 90)
		{
			debriScale += (1.01f - debriScale) / 8;
		}
		// ���@�̈ʒu�֋z�����܂��
		if (effectCnt >= 90)
		{
			debriPos.x += (playerPos.x - debriPos.x) / 8;
			debriPos.z += (playerPos.z - debriPos.z) / 8;

			if (debriScale >= 0)
			{
				debriScale -= 0.03f;
			}
		}

		// ���o�I���
		float tmpDis = abs(playerPos.x - debriPos.x) + abs(playerPos.z - debriPos.z);	// ���ЂƎ��@�̋���
		// ��莞�Ԍo�ߌ�A�߂�������A�傫�������ȉ��̂Ƃ�
		if (effectCnt >= 90 && tmpDis < 1.0f && debriScale <= 0.2f)
		{
			isEffect = false;
		}

		// ��]������
		debriRot.y += 5;

		// �X�P�[���ݒ�
		debri->SetPosition(debriPos);
		debri->SetRotation(debriRot);
		debri->SetScale({ debriScale, debriScale, debriScale });

		debri->Update();

		effectCnt++;
	}
}

void Crystal::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isEffect)
	{
		debri->Draw(cmdList);
	}
	if (!isDead && !isEffect)
	{
		crystalObj->Draw(cmdList);
		circleObj->Draw(cmdList);
	}
}

void Crystal::SpriteDraw()
{
}

void Crystal::SetIsDead(bool isDead)
{
	Object::SetIsDead(isDead);

	isEffect = true;
	effectCnt = 0;
	debriScale = 0;

	// ������̈ʒu���ꎞ�I�Ɍ���
	debriPos.x = position.x;
	debriPos.y = 1.0f;
	debriPos.z = position.z;
}
