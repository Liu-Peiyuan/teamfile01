//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

// �\���̒�`

// score�̑����Ɏg���\����
struct SCORE
{
	D3DXCOLOR	color;		// �F�A���₷�͐A���炷�͐�

	int			score;		// �ω�����l
	bool		use;		// �g�p�����ǂ���
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void ChangeScore(int value);

#endif
