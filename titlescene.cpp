//! @file	titlescene.cpp
//! @author	�܂�
//! @date	2020-07-13
//! @brief	�^�C�g���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "bg.h"

// �}�N����`

//�O���[�o���ϐ�

// ����������
void InitTitleScene(void)
{
	InitBg();
}

// �I������
void UninitScene(void)
{
	UninitBg();
}

// �X�V����
void UpdateScene(void)
{
	UpdateBg();
}

// �`�揈��
void DrawScene(void)
{
	DrawBg();
}
