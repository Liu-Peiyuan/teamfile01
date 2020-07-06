//=============================================================================
//
// �^�C�}�[���� [timer.h]
// Author : ���|��
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

// �\���̒�`

// time�̑����Ɏg���\����
struct TIME
{
	D3DXCOLOR	color;		// �F�A���₷�͐A���炷�͐�

	int			time;		// �ω�����l
	bool		use;		// �g�p�����ǂ���
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

void EnableTimer(bool bEnable);
void ResetTimer(int nTime = 999);

void ChangeTimer(int value);

#endif
