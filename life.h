//=============================================================================
//
// ���C�t���� [life.h]
// Author : ���|��
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

enum CHANGE_LIFE
{
	ADD,
	MINUS,
	NONE,
	MAX_CHANGE_LIFE
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

//void ChangeLife(int value)
//����:�O�ȊO�̐����i1��-1�j
//����:�����ɍ��킹��life�̑���������iUI�̂݁j
void ChangeLife(int value);

#endif
