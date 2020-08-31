//=============================================================================
//
// �g����A�C�e���̏��� [subtitute.h]
// Author : kitade mayumi
//
//=============================================================================

//=============================================================================
//
// [substitute.cpp]
// Author : kitade mayumi
//! @date	2020-08-24
//! @brief	�g����A�C�e���̎���
//=============================================================================

#pragma once

// �e�N�X�`���T�C�Y
#define	SUBSTITUTE_TEXTURE_SIZE_X						(32.0f)		// SUBSTITUTE�̃T�C�Y(X����)
#define	SUBSTITUTE_TEXTURE_SIZE_Y						(32.0f)		// SUBSTITUTE�̃T�C�Y(Y����)

#define	SUBSTITUTE_TEXTURE_BB_SIZE_TOP_X				(SUBSTITUTE_TEXTURE_SIZE_X / 2.5f)		// SUBSTITUTE�̃T�C�Y(X����)
#define	SUBSTITUTE_TEXTURE_BB_SIZE_X					(SUBSTITUTE_TEXTURE_SIZE_X / 2.0f)		// SUBSTITUTE�̃T�C�Y(X����)
#define	SUBSTITUTE_TEXTURE_BB_SIZE_Y					(SUBSTITUTE_TEXTURE_SIZE_Y / 2.0f)		// SUBSTITUTE�̃T�C�Y(Y����)

#define SUBSTITUTE_HP	(4)

// Jump�W��-----------------------------------
#define SUBSTITUTE_JUMP_HIGH							(25)				// �W�����v�̍���
#define SUBSTITUTE_ACCELE								(16.0f)				// �����x

// Move���x-----------------------------------
//#define SUBSTITUTE_MOVE_SPEED							(8.0f)				// �ړ���
#define	SUBSTITUTE_ROTATE								(D3DX_PI * 0.02f)	// ��]��

// Idle�A�j���[�V����----------------------
#define	TEXTURE_SUBSTITUTE_IDLE					"data/TEXTURE/substitute/substitute_idle.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_X		(4)										// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_Y		(1)										// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define SUBSTITUTE_IDLE_ANIM_PATTERN_NUM				(SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_X*SUBSTITUTE_IDLE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define SUBSTITUTE_IDLE_TIME_ANIMATION					(20)									// �A�j���[�V�����̐؂�ւ��J�E���g

// Running�A�j���[�V����----------------------
#define	TEXTURE_SUBSTITUTE_RUN					"data/TEXTURE/substitute/substitute_run.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define SUBSTITUTE_RUN_TEXTURE_PATTERN_DIVIDE_X			(6)										// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SUBSTITUTE_RUN_TEXTURE_PATTERN_DIVIDE_Y			(1)										// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define SUBSTITUTE_RUN_ANIM_PATTERN_NUM					(SUBSTITUTE_RUN_TEXTURE_PATTERN_DIVIDE_X*SUBSTITUTE_RUN_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define SUBSTITUTE_RUN_TIME_ANIMATION					(8)										// �A�j���[�V�����̐؂�ւ��J�E���g

// Jump�A�j���[�V����-----------------------------------
#define	TEXTURE_SUBSTITUTE_JUMP					"data/TEXTURE/substitute/substitute_jump.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define SUBSTITUTE_JUMP_TEXTURE_PATTERN_DIVIDE_X		(2)										// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define SUBSTITUTE_JUMP_TEXTURE_PATTERN_DIVIDE_Y		(1)										// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define SUBSTITUTE_JUMP_ANIM_PATTERN_NUM				(SUBSTITUTE_JUMP_TEXTURE_PATTERN_DIVIDE_X*SUBSTITUTE_JUMP_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define SUBSTITUTE_JUMP_TIME_ANIMATION					(8)										// �A�j���[�V�����̐؂�ւ��J�E���g

typedef struct							// SUBSTITUTE�A�j���[�V�����p�����\����
{
	int		PatDivX;					// �A�j���p�^�[���̃e�N�X�`�����������iX)
	int		PatDivY;					// �A�j���p�^�[���̃e�N�X�`�����������iY)
	int		AnimPatNum;					// �A�j���[�V�����p�^�[����
	int		TimeAnim;					// �A�j���[�V�����̐؂�ւ��J�E���g
	int		PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int		CountAnim;					// �A�j���[�V�����J�E���g
}SUBSTITUTE_ANIMCNT;

typedef struct
{
	int		PatDivX;					// �A�j���p�^�[���̃e�N�X�`�����������iX)
	int		PatDivY;					// �A�j���p�^�[���̃e�N�X�`�����������iY)
	int		AnimPatNum;					// �A�j���[�V�����p�^�[����
	int		TimeAnim;					// �A�j���[�V�����̐؂�ւ��J�E���g
}SUBSTITUTE_ANIM_DATE;


typedef struct					// SUBSTITUTE�\����
{
	D3DXVECTOR3			pos;				// �ʒu
	D3DXVECTOR3			scrollPos;			// �J�����p�̈ʒu
	D3DXVECTOR3			rot;				// �|���S���̌���(��])
	D3DXVECTOR3			scl;				// �|���S���̑傫��(�X�P�[��)
	D3DXVECTOR3			ofsPos;				// �I�t�Z�b�g���W

	float				moveSpeed;			// �ړ���
	float				radius;				// ���a
	float				baseAngle;			// �p�x
	float				lenght;				// ����

	bool				moveble;			// �ړ��\
	bool				use;				// �g�p��Ԃ��ǂ���
	bool				releaseUse;			// ����Ă��邩�ǂ���
	bool				sticking;			// ��x�����������ǂ���
	bool				attackUse;			// �U�����Ă��邩�ǂ���

	int					moveCount;			// �ړ��J�E���g
	int					countReleaseTime;	// �v���C���[���痣��Ă��鎞��
	int					jumpForce;			// �W�����v��
	float				dropSpeed;			// �������x�i�d�́j
	D3DXVECTOR2			textureSize;		// �e�N�X�`���T�C�Y

	int					direction;			// SUBSTITUTE�̕���
	int					state;				// SUBSTITUTE�̏��

	SUBSTITUTE_ANIMCNT	animeCnt;			// SUBSTITUTE�A�j���[�V�����p�����\����
	LPDIRECT3DTEXTURE9	Texture;			// �e�N�X�`�����

	VERTEX_2D		vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

}SUBSTITUTE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSubstitute(void);
void UninitSubstitute(void);
void UpdateSubstitute(void);
void DrawSubstitute(void);
SUBSTITUTE *GetSubstitute(void);
void SetPosSubstitute(void);
