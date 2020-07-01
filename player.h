//=============================================================================
//
// �|���S������ [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


// �}�N����`
#define PLAYER_TEXTURE			_T("data/TEXTURE/runningman003.png")	// �T���v���p�摜  
#define PLAYER_TEXTURE_SIZE_X		(50/2) // �e�N�X�`���T�C�Y  
#define PLAYER_TEXTURE_SIZE_Y		(100/2) // ����  

#define PLAYER_TEXTURE_BB_SIZE_X	(40/2) // �e�N�X�`���T�C�Y  
#define PLAYER_TEXTURE_BB_SIZE_Y	(80/2) // ����  


#define PLAYER_TEXTURE_PATTERN_DIVIDE_X		(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y		(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define PLAYER_ANIM_PATTERN_NUM				(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����  
#define PLAYER_TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g  

typedef struct
{
	D3DXVECTOR3 oldPos;			// �|���S���̈ړ���
	D3DXVECTOR3 pos;			// �|���S���̈ړ���
	D3DXVECTOR3 rot;			// �|���S���̉�]��
	int			countAnim;		// �A�j���[�V�����J�E���g 
	int			patternAnim;	// �A�j���[�V�����p�^�[���i���o�[

	VERTEX_2D		vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

}PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif
