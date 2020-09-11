//! @file	titlescene.cpp
//! @author	kitade mayumi
//! @date	2020-07-13
//! @brief	�^�C�g���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "bg.h"
#include "savefile.h"
#include "sound.h"

// �}�N����`

//�O���[�o���ϐ�

// ����������
void InitTitleScene(void)
{
	InitBg(TITLE_BG);
	SaveData();
	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

// �I������
void UninitTitleScene(void)
{
	UninitBg();
	// BGM��~
	StopSound(SOUND_LABEL_BGM_TITLE);

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
