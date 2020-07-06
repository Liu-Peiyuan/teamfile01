//=============================================================================
//
// player.h
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <d3dx9.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_PLAYER_POLYGON		(2)					// �|���S����
#define	NUM_PLAYER_VERTEX		(4)					// ���̒��_��

// Idle�A�j���[�V����------------------------
#define	TEXTURE_PLAYER_IDLE							"data/TEXTURE/Charactor/stand.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_X			(4)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_IDLE_ANIM_PATTERN_NUM					(PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_X*PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_IDLE_TIME_ANIMATION					(20)		// �A�j���[�V�����̐؂�ւ��J�E���g

// Running�A�j���[�V����----------------------
#define	TEXTURE_PLAYER_RUN							"data/TEXTURE/Charactor/WALK.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_X			(6)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_RUN_ANIM_PATTERN_NUM					(PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_X*PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_RUN_TIME_ANIMATION					(8)			// �A�j���[�V�����̐؂�ւ��J�E���g

// Jump�A�j���[�V����-----------------------------------
#define	TEXTURE_PLAYER_JUMP							"data/TEXTURE/Charactor/$erzaDark_3.png"				// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_X			(6)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_JUMP_ANIM_PATTERN_NUM					(PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_X*PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_JUMP_TIME_ANIMATION					(8)			// �A�j���[�V�����̐؂�ւ��J�E���g

// Fall�A�j���[�V����-----------------------------------
#define	TEXTURE_PLAYER_FALLING						"data/TEXTURE/Charactor/$erzaSword_3.png"					// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_FALLING_TEXTURE_PATTERN_DIVIDE_X		(4)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_FALLING_TEXTURE_PATTERN_DIVIDE_Y		(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_FALLING_ANIM_PATTERN_NUM				(PLAYER_FALLING_TEXTURE_PATTERN_DIVIDE_X*PLAYER_FALLING_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_FALLING_TIME_ANIMATION				(8)			// �A�j���[�V�����̐؂�ւ��J�E���g

// Attack�A�j���[�V����-----------------------------------
// Attack1
#define	TEXTURE_PLAYER_ATK1							"data/TEXTURE/Charactor/attack1.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_ATK1_TEXTURE_PATTERN_DIVIDE_X			(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_ATK1_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ATK1_ANIM_PATTERN_NUM					(PLAYER_ATK1_TEXTURE_PATTERN_DIVIDE_X*PLAYER_ATK1_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_ATK1_TIME_ANIMATION					(4)			// �A�j���[�V�����̐؂�ւ��J�E���g
// Attack2
#define	TEXTURE_PLAYER_ATK2							"data/TEXTURE/Charactor/attack2.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_ATK2_TEXTURE_PATTERN_DIVIDE_X			(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_ATK2_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ATK2_ANIM_PATTERN_NUM					(PLAYER_ATK2_TEXTURE_PATTERN_DIVIDE_X*PLAYER_ATK2_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_ATK2_TIME_ANIMATION					(4)			// �A�j���[�V�����̐؂�ւ��J�E���g
// Attack3
#define	TEXTURE_PLAYER_ATK3							"data/TEXTURE/Charactor/attack3.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_ATK3_TEXTURE_PATTERN_DIVIDE_X			(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_ATK3_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ATK3_ANIM_PATTERN_NUM					(PLAYER_ATK3_TEXTURE_PATTERN_DIVIDE_X*PLAYER_ATK3_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_ATK3_TIME_ANIMATION					(4)			// �A�j���[�V�����̐؂�ւ��J�E���g
// Attack4
#define	TEXTURE_PLAYER_ATK4							"data/TEXTURE/Charactor/attack4.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_ATK4_TEXTURE_PATTERN_DIVIDE_X			(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_ATK4_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ATK4_ANIM_PATTERN_NUM					(PLAYER_ATK4_TEXTURE_PATTERN_DIVIDE_X*PLAYER_ATK4_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_ATK4_TIME_ANIMATION					(4)			// �A�j���[�V�����̐؂�ւ��J�E���g
// Attack5
#define	TEXTURE_PLAYER_ATK5							"data/TEXTURE/Charactor/attack5.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PLAYER_ATK5_TEXTURE_PATTERN_DIVIDE_X			(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_ATK5_TEXTURE_PATTERN_DIVIDE_Y			(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ATK5_ANIM_PATTERN_NUM					(PLAYER_ATK5_TEXTURE_PATTERN_DIVIDE_X*PLAYER_ATK5_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_ATK5_TIME_ANIMATION					(4)			// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_TEXTURE_SIZE_X		(50/2) // �e�N�X�`���T�C�Y  
#define PLAYER_TEXTURE_SIZE_Y		(100/2) // ����  


// �e�N�X�`���T�C�Y-----------------------------------
#define	PLAYER_SIZE_STAND_X							(50.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_STAND_Y							(80.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
#define	PLAYER_SIZE_RUNNING_X						(85.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_RUNNING_Y						(70.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
#define	PLAYER_SIZE_ATK1_X							(115.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_ATK1_Y							(115.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
#define	PLAYER_SIZE_ATK2_X							(115.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_ATK2_Y							(115.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
#define	PLAYER_SIZE_ATK3_X							(165.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_ATK3_Y							(115.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
#define	PLAYER_SIZE_ATK4_X							(125.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_ATK4_Y							(115.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)
#define	PLAYER_SIZE_ATK5_X							(145.0f/2.0f)		// PLAYER�̃T�C�Y(X����)
#define	PLAYER_SIZE_ATK5_Y							(115.0f/2.0f)		// PLAYER�̃T�C�Y(Y����)

// Jump�W��-----------------------------------
#define PLAYER_JUMP_HIGH								(25)		// �W�����v�̍���
#define PLAYER_ACCELE								(0.8f)			// �����x

// Move���x-----------------------------------
#define PLAYER_MOVE_SPEED							(8.0f)				// �ړ���
#define	PLAYER_ROTATE								(D3DX_PI * 0.02f)	// ��]��

// �ő�U���x�����x-----------------------
#define MAX_ATK_DELAY_RESPONSE_TIME						(100)

typedef struct					// PLAYER�A�j���[�V�����p�����\����
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

typedef struct 					// PLAYER�̏��
{
	bool idle;							// ���삵�Ă��Ȃ�
	bool running;						// �����Ă���
	bool jumping;						// �W�����v���Ă���
	bool falling;						// �����Ă���	
	bool Grounded;						// �n�ʏ�ɗ����Ă���
	bool Attack;						// �U��
}PLAYER_STATE;

typedef struct					// PLAYER�\����
{
	D3DXVECTOR3			pos;				// �|���S���̈ʒu
	D3DXVECTOR3			oldpos;				// �|���S���̈ʒu
	D3DXVECTOR3			rot;				// �|���S���̌���(��])
	D3DXVECTOR3			scl;				// �|���S���̑傫��(�X�P�[��)
	float				moveSpeed;			// �ړ���

	bool				moveble;			// �ړ��\
	bool				keyPressing;
	bool				selected;
	float				jumpForce;			// �W�����v��
	int					AtkPat;				// �U���^�C�v
	int					NextAtkPat;
	bool				AtkDeReSwi;			// (Delay response switch)
	int					AtkDeRespTime;		// (Delay response time)
	D3DXVECTOR2			textureSize;		// �e�N�X�`���T�C�Y

	int					direction;			// PLAYER�̕���
	PLAYER_STATE		state;				// PLAYER�̏��

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

enum PLAYER_ATK_ANIME
{
	Atk_Pat1,
	Atk_Pat2,
	Atk_Pat3,
	Atk_Pat4,
	Atk_Pat5,
	Atk_Max,
};

enum PLAYER_STATE_ANIME
{
	IDLE,
	RUN,
	JUMP,
	FALLING,
	ATTACK1,
	STATE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
