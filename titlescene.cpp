//! @file	titlescene.cpp
//! @author	�܂�
//! @date	2020-07-13
//! @brief	�^�C�g���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "bg.h"
#include "savefile.h"

// �}�N����`

//�O���[�o���ϐ�

// ����������
void InitTitleScene(void)
{
	InitBg();
	SaveData();
}

// �I������
void UninitTitleScene(void)
{
	UninitBg();
}

// �X�V����
void UpdateTitleScene(void)
{
	UpdateBg();
}

// �`�揈��
void DrawTitleScene(void)
{
	DrawBg();
}
