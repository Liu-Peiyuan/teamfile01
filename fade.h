//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#pragma once

#include "scene.h"

//*************************************
// �t�F�[�h�̏��
//*************************************
enum FADE
{
	FADE_NONE = 0,		// �����Ȃ����
	FADE_IN,			// �t�F�[�h�C������
	FADE_MUSIC_STOP,
	FADE_OUT,			// �t�F�[�h�A�E�g����
	FADE_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade);
void SetFade(FADE fade, SCENE next, int sno );
FADE GetFade(void);

