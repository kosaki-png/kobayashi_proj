#pragma once
#include<Windows.h>
#include<Xinput.h>

#pragma comment(lib,"xinput.lib")

// �R���g���[���[�̃{�^��
#define xinput_X 0
#define xinput_Y 1
#define xinput_A 2
#define xinput_B 3
#define xinput_R 4
#define xinput_L 5
#define xinput_R3 6
#define xinput_L3 7
#define xinput_LT 8
#define xinput_RT 9
#define xinput_LS 10
#define xinput_RS 11
#define xinput_START 12
#define xinput_BACK 13


// �R���g���[���[�̏\���L�[
#define xinput_UP 14
#define xinput_DOWN 15
#define xinput_LEFT 16
#define xinput_RIGHT 17

#define leftInput 0x00000001
#define rightInput 0x00000002
#define topInput 0x00000010
#define bottomInput 0x00000020

// �ڑ������A�R���g���[���[�̔ԍ�������
struct SetController
{
	bool controller1 = false;
	bool controller2 = false;
	bool controller3 = false;
	bool controller4 = false;
};

class Xinput
{

public:

	Xinput();
	~Xinput() {};

	// �X�V�p
	void Update();

	// �{�^���������ꂽ���ǂ���
	bool PushButtom(int controller, short buttom);
	bool TriggerButtom(int controller, short buttom);

	// �X�e�B�b�N�𓮂��������𔻒肷��
	int MoveStick(int controller,short stick);


	// �ڑ����̃R���g���[���[����Ԃ�
	int IsControllNUM() { return controllerNum; }

	// 

private:

	XINPUT_STATE state[4] = {};
	// �g���K�[�p
	XINPUT_STATE pastState[4] = {};


	int controllerNum = 4; // �ڑ�����Ă���R���g���[���[�̐�
	SetController pad ={};

};

