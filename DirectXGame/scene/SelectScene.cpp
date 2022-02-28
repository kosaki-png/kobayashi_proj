#include "SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	safe_delete(camera);
	for (auto x : map)
	{
		safe_delete(x);
	}
	delete back;
	for (auto x : gush)
	{
		safe_delete(x);
	}
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new FixedCamera(WinApp::window_width, WinApp::window_height);
		
		// �f�o�C�X���Z�b�g
		Fbx::SetDevice(dxCommon->GetDevice());
		// �J�������Z�b�g
		Fbx::SetCamera(camera);
		// �O���t�B�b�N�X�p�C�v���C������
		Fbx::CreateGraphicsPipeline();
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			// ���[�h���Ă��Ȃ��Ȃ炷��
			if (!SpriteLoader::GetSelectFlag())
			{
				SpriteLoader::LoadSelectSprite();
			}
		}

		// �X�v���C�g����
		{
			flame.reset(Sprite::Create(SELECT_FLAME, { 0,0 }));
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// FBX�I�u�W�F�N�g�����ݒ�
	{
		// �Z���N�g�p�}�b�v
		for (int i = 0; i < 4; i++)
		{
			map[i] = new Fbx();
			map[i]->Initialize();
			map[i]->SetModel(ModelManager::GetInstance()->GetModel(i + stageData->GetDeSelectData().firstNum + 2));
			map[i]->SetFogColor({ 0.01f, 0.01f, 0.01f, 1.0f });
		}

		// �w�i
		back = new Fbx();
		back->Initialize({0,1,0});
		back->SetModel(ModelManager::GetInstance()->GetModel(stageData->GetDeSelectData().firstNum));
		back->SetFog(false);
		back->SetPosition({ 0,0,300 });
		back->SetScale({ 5,5,6 });
		back->SetRotation({ 0,0,180 });
	}

	// �J����������
	{
		// �J���������_���Z�b�g
		camera->SetTarget({ 0, -50, 0 });
		camera->SetEye({ 0,250,500 });
	}

	// �e�N���X�̏�����
	{
		for (int i = 0; i < gush.size(); i++)
		{
			gush[i] = new Gush();
			gush[i]->Setheight(230);
			gush[i]->SetPlayerPos({ 0,250,450 });
			gush[i]->Initialize();
		}
	}

	isGodray = false;
	trans = 1;
}

void SelectScene::Update()
{
	// �}�E�X�|�C���g
	{
		static POINT p;
		GetCursorPos(&p);
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	// �Z���N�g�}�b�v��]�w��
	{
		// �~�܂��Ă���Ƃ�
		if (!isMove)
		{
			// ��]�X�^�[�g
			if (input->TriggerKey(DIK_LEFT) || input->TriggerKey(DIK_A))
			{
				map[nowMap]->SetScale({ 1, 1, 1 });
				nowMap--;
				vel = 1;
				isMove = true;
				// ��]�I���_����
				reRot = rad + 90 * vel;
				selRad = 0.0f;
			}
			if (input->TriggerKey(DIK_RIGHT) || input->TriggerKey(DIK_D))
			{
				map[nowMap]->SetScale({ 1, 1, 1 });
				nowMap++;
				vel = -1;
				isMove = true;
				// ��]�I���_����
				reRot = rad + 90 * vel;
				selRad = 0.0f;
			}
		}
		// ��]��
		else
		{
			// ��]
			rad += 2.0f * vel;

			// ���Ŏ~�܂�
			if ((vel == 1 && reRot < rad) || (vel == -1 && rad < reRot))
			{
				vel = 0;
				rad = reRot;
				isMove = false;
			}
		}

		// �������[�v
		if (nowMap == 4)
		{
			nowMap = 0;
		}
		if (nowMap == -1)
		{
			nowMap = 3;
		}
	}

	// �I�𒆂̃}�b�v�̋���
	if (!isMove)
	{
		// ��{�Â�
		for (auto x : map)
		{
			x->SetFog(true);
		}

		// ���邭����
		map[nowMap]->SetFog(false);

		// ������Ƒ傫������
		map[nowMap]->SetScale({ 1.5f, 1.5f, 1.5f });

		// ��]������
		map[nowMap]->SetRotation({ map[nowMap]->GetRotation().x, 
								   map[nowMap]->GetRotation().y + 0.5f, 
								   map[nowMap]->GetRotation().z });

		// �㉺������
		selRad += 0.03f;
		XMFLOAT3 tmpPos = map[nowMap]->GetPosition();
		map[nowMap]->SetPosition({ tmpPos.x, sinf(selRad) * 25.0f, tmpPos.z });

	}

	// �V�[���ڍs
	if (input->TriggerKey(DIK_SPACE))
	{
		// �I�������}�b�v�ŃQ�[���V�[����
		nextScene = new LoadScene(nowMap);
	}
	if (input->TriggerKey(DIK_ESCAPE))
	{
		// �^�C�g���V�[����
		nextScene = new TitleScene();
	}

	// 3D�I�u�W�F�N�g�X�V
	{
		for (int i = 0; i < 4; i++)
		{
			// ���݂̑S�̃��W�A��
			float radian = (rad + 90.0f * (float)i + 180.0f) * 3.14f / 180.0f;

			map[i]->Update();
			map[i]->SetPosition({ (float)sinf(radian) * 200, 0, -(float)cosf(radian) * 200 });
		}

		back->Update();
	}

	// �e�N���X�̍X�V
	{
		camera->Update();
		for (auto x : gush)
		{
			x->Update();
		}
	}

}

void SelectScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		// �w�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
		// �[�x�o�b�t�@�N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�`��
	{
		back->Draw(cmdList);

		for (auto x : map)
		{
			x->Draw(cmdList);
		}

		for (auto x : gush)
		{
			x->Draw(cmdList);
		}
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}

void SelectScene::FrontDraw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �X�v���C�g�`��
	Sprite::PreDraw(cmdList);
	{
		flame->Draw();
	}
	Sprite::PostDraw();
}

void SelectScene::Finalize()
{
}
