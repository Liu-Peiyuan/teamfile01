//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
enum 
{
	SOUND_LABEL_BGM_TITLE,			// �^�C�g���̉�	
	SOUND_LABEL_BGM_TUTRIAL,		// �`���[�g���A���̉�	
	SOUND_LABEL_BGM_GAMESTAGE,		// �Q�[�����̉�
	SOUND_LABEL_BGM_BOSS_STAGE,		// �{�X��̉�
	SOUND_LABEL_BGM_RESULT,			// ���U���g�̉�
	SOUND_LABEL_SE_SHOT01,	 		// �e���ˉ�
	SOUND_LABEL_SE_ITEM,	 		// �A�C�e����
	SOUND_LABEL_SE_JUMP,		 	// �W�����v��
	SOUND_LABEL_SE_STARTBUTTON,	 	// �X�^�[�g�{�^����
	SOUND_LABEL_SE_WARP,			// ���[�v��
	SOUND_LABEL_SE_SHOT02,			// �e���ˉ�
	SOUND_LABEL_SE_HIT,				// �q�b�g��
	SOUND_LABEL_MAX,				// �T�E���h���x���̐�
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

#endif
