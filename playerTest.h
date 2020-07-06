#pragma once
#include "main.h"

// �e�N�X�`���T�C�Y
#define	PLAYER_TEXTURE_SIZE_X						(64.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_TEXTURE_SIZE_Y						(64.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
// Jump�W��-----------------------------------
#define PLAYER_JUMP_HIGH							(25)				// �W�����v�̍���
#define PLAYER_ACCELE								(16.0f)				// �����x

// Move���x-----------------------------------
#define PLAYER_MOVE_SPEED							(8.0f)				// �ړ���
#define	PLAYER_ROTATE								(D3DX_PI * 0.02f)	// ��]��

// �ő�U���x�����x-----------------------
#define MAX_ATK_DELAY_RESPONSE_TIME					(100)

#define	TEXTURE_PLAYER_IDLE							"data/TEXTURE/CharaTest/idle.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_X		(8)										// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_Y		(1)										// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_IDLE_ANIM_PATTERN_NUM				(PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_X*PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_IDLE_TIME_ANIMATION					(20)									// �A�j���[�V�����̐؂�ւ��J�E���g

// Running�A�j���[�V����----------------------
#define	TEXTURE_PLAYER_RUN							"data/TEXTURE/CharaTest/run.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_X			(9)										// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_Y			(1)										// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_RUN_ANIM_PATTERN_NUM					(PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_X*PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_RUN_TIME_ANIMATION					(8)										// �A�j���[�V�����̐؂�ւ��J�E���g

// Jump�A�j���[�V����-----------------------------------
#define	TEXTURE_PLAYER_JUMP							"data/TEXTURE/CharaTest/jump.png"// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_X		(9)										// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_Y		(1)										// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_JUMP_ANIM_PATTERN_NUM				(PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_X*PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_JUMP_TIME_ANIMATION					(8)										// �A�j���[�V�����̐؂�ւ��J�E���g

typedef struct							// PLAYER�A�j���[�V�����p�����\����
{
	int		PatDivX;					// �A�j���p�^�[���̃e�N�X�`�����������iX)
	int		PatDivY;					// �A�j���p�^�[���̃e�N�X�`�����������iY)
	int		AnimPatNum;					// �A�j���[�V�����p�^�[����
	int		TimeAnim;					// �A�j���[�V�����̐؂�ւ��J�E���g
	int		PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int		CountAnim;					// �A�j���[�V�����J�E���g
}PLAYER_ANIMCNT;

typedef struct
{
	int		PatDivX;					// �A�j���p�^�[���̃e�N�X�`�����������iX)
	int		PatDivY;					// �A�j���p�^�[���̃e�N�X�`�����������iY)
	int		AnimPatNum;					// �A�j���[�V�����p�^�[����
	int		TimeAnim;					// �A�j���[�V�����̐؂�ւ��J�E���g
}PLAYER_ANIM_DATE;


typedef struct					// PLAYER�\����
{
	D3DXVECTOR3			pos;				// �ʒu
	D3DXVECTOR3			mapPos;				// �}�b�v�p�̈ʒu
	D3DXVECTOR3			scrollPos;			// �J�����p�̈ʒu
	D3DXVECTOR3			rot;				// �|���S���̌���(��])
	D3DXVECTOR3			scl;				// �|���S���̑傫��(�X�P�[��)
	D3DXVECTOR3			ofsPos;				// �I�t�Z�b�g���W

	float				moveSpeed;			// �ړ���
	float				radius;				// ���a
	float				baseAngle;			// �p�x

	bool				moveble;			// �ړ��\
	bool				keyPressing;
	bool				invincible;			// ���G���
	bool				use;				// �g�p��Ԃ��ǂ���

	int					countShot;			// ���܂ł̃J�E���g
	int					countInvincible;	// ���G��Ԃ̃J�E���g
	int					hp;					// �̗�
	int					jumpForce;			// �W�����v��
	float				dropSpeed;			// �������x�i�d�́j
	int					AtkPat;				// �U���^�C�v

	int					NextAtkPat;
	bool				AtkDeReSwi;			// (Delay response switch)
	int					AtkDeRespTime;		// (Delay response time)
	D3DXVECTOR2			textureSize;		// �e�N�X�`���T�C�Y


	int					direction;			// PLAYER�̕���
	int					state;				// PLAYER�̏��

	PLAYER_ANIMCNT		animeCnt;			// PLAYER�A�j���[�V�����p�����\����
	LPDIRECT3DTEXTURE9	Texture;			// �e�N�X�`�����

	VERTEX_2D		vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
}PLAYER;


enum PLAYER_DIRECTION			// PLAYER�̕���
{
	Right,				// �E����
	Left,				// ������
	Down,				// ������
};

enum PLAYER_STATE_ANIME
{
	IDLE,
	RUN,
	JUMP,
	STATE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);