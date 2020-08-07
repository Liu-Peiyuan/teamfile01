//=============================================================================
//
// �G���� [enemy.h]
// Author : kitade mayumi
//
//=============================================================================
#pragma once


// �}�N����`
#define ENEMY_MOVE_SPEED	(1.2f)

#define ENEMY_TEXTURE_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define ENEMY_TEXTURE_SIZE_Y	(50/2)		// ����

// SNIPER�^�A�j���[�V�����e�N�X�`��
#define ENEMY_SNIPER_IDLE_TEXTURE			_T("data/TEXTURE/EnemyChara/ventos/idle_ventos01.png")
#define ENEMY_SNIPER_ATTACK_TEXTURE			_T("data/TEXTURE/EnemyChara/ventos/attack_ventos01.png")
#define ENEMY_SNIPER_DEATH_TEXTURE			_T("data/TEXTURE/EnemyChara/ventos/death_ventos01.png")

// TRACKER�^�A�j���[�V�����e�N�X�`��
#define ENEMY_TRACKER_IDLE_TEXTURE			_T("data/TEXTURE/EnemyChara/slime/idle_slime01.png")
#define ENEMY_TRACKER_ATTACK_TEXTURE			_T("data/TEXTURE/EnemyChara/slime/attack_slime01.png")
#define ENEMY_TRACKER_DEATH_TEXTURE			_T("data/TEXTURE/EnemyChara/slime/death_slime01.png")

// GUARDIAN�^�A�j���[�V�����e�N�X�`��
#define ENEMY_GUARDIAN_IDLE_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/idle_tiamat01.png")
#define ENEMY_GUARDIAN_ATTACK_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/attack_tiamat01.png")
#define ENEMY_GUARDIAN_DEATH_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/death_tiamat01.png")

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ENEMY_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY_MAX						(15) // �G�̍ő吔

enum ENEMYTYPE
{
	SNIPER,
	TRACKER,
	GUARDIAN,
	ENEMYTYPEMAX
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				hp;							// �̗�
	bool			damage;						// �_���[�W����
	int				countShot;					// �e��ł܂ł̃J�E���g
	int				type;

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	int				state;						// �G�l�~�[�̏�ԊǗ�
	int				direction;					// ENEMY�̕���
	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x
	float			dropSpeed;					// �������x�i�d�́j

} ENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);


