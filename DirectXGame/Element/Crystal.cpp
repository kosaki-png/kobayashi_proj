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

	// 本体
	crystalObj = new Fbx();
	crystalObj->Initialize();
	crystalObj->SetModel(ModelManager::GetInstance()->GetModel(3));

	// 周囲の円
	circleObj = new Fbx();
	circleObj->Initialize();
	circleObj->SetModel(ModelManager::GetInstance()->GetModel(4));

	// 欠片
	debri = new Fbx();
	debri->Initialize({0, 1.0f, 0});
	debri->SetModel(ModelManager::GetInstance()->GetModel(6));

	// 配置
	Placement(TexCollision::ArgColor::Red);
}

void Crystal::Update()
{
	// 死んでいないとき
	if (!isDead)
	{
		// 上下させる
		rot += 0.02f;

		// 本体
		rotation.y--;
		crystalObj->SetRotation(rotation);
		crystalObj->SetPosition({ position.x, position.y + sinf(rot) / 2, position.z });
		crystalObj->Update();

		// 周囲の円
		circleRot++;
		circleObj->SetPosition({ position.x, position.y + sinf(rot) / 2, position.z });
		circleObj->SetRotation({ 0,circleRot,0 });
		circleObj->Update();
	}

	// 獲得後の演出
	if (isEffect)
	{
		// 拡散
		if (debriScale <= 1.0f && effectCnt <= 90)
		{
			debriScale += (1.01f - debriScale) / 8;
		}
		// 自機の位置へ吸い込まれる
		if (effectCnt >= 90)
		{
			debriPos.x += (playerPos.x - debriPos.x) / 8;
			debriPos.z += (playerPos.z - debriPos.z) / 8;

			if (debriScale >= 0)
			{
				debriScale -= 0.03f;
			}
		}

		// 演出終わり
		float tmpDis = abs(playerPos.x - debriPos.x) + abs(playerPos.z - debriPos.z);	// 欠片と自機の距離
		// 一定時間経過後、近かったら、大きさが一定以下のとき
		if (effectCnt >= 90 && tmpDis < 1.0f && debriScale <= 0.2f)
		{
			isEffect = false;
		}

		// 回転させる
		debriRot.y += 5;

		// スケール設定
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

	// かけらの位置を一時的に決定
	debriPos.x = position.x;
	debriPos.y = 1.0f;
	debriPos.z = position.z;
}
