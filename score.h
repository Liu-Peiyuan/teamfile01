//=============================================================================
//
// �X�R�A���� [score.h]
// Author : ���|��
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

struct LANKING_SCORE
{
	int num;
};


typedef struct					// �Z�[�u�f�[�^�̍\����
{
	// �X�R�A�f�[�^��ۑ�
	LANKING_SCORE r_score;	// �����L���O�X�R�A
	int		  score;	// �v���C��̃X�R�A
} SAVEDATA;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

LANKING_SCORE *GetResult_Score(void);
void ChangeScore(int value);
int GetScore(void);
#endif
