//=============================================================================
//
// �{�X�̒�` [boss.h]
// Author : kitade mayumi
//! @date	2020-08-28
//=============================================================================
#pragma once


// �}�N����`
#define BOSS_MOVE_SPEED	(1.2f)

#define BOSS_TEXTURE_SIZE_X	(100/2)		// �e�N�X�`���T�C�Y
#define BOSS_TEXTURE_BB_SIZE_X	(100/2.5)	// �e�N�X�`���T�C�Y

#define BOSS_TEXTURE_SIZE_Y	(100/2)		// ����

// SINGLE�^�A�j���[�V�����e�N�X�`��
#define BOSS_SINGLE_IDLE_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/idle_tiamat01.png")
#define BOSS_SINGLE_ATTACK_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/attack_tiamat01.png")
#define BOSS_SINGLE_RUN_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/run_tiamat01.png")
#define BOSS_SINGLE_DEATH_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/death_tiamat01.png")

// TWIN�^�A�j���[�V�����e�N�X�`��
#define BOSS_TWIN_IDLE_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/idle_tiamat01.png")
#define BOSS_TWIN_ATTACK_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/attack_tiamat01.png")
#define BOSS_TWIN_RUN_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/run_tiamat01.png")
#define BOSS_TWIN_DEATH_TEXTURE			_T("data/TEXTURE/EnemyChara/tiamat/death_tiamat01.png")

#define BOSS_TEXTURE_PATTERN_DIVIDE_X	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define BOSS_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define BOSS_ANIM_PATTERN_NUM			(BOSS_TEXTURE_PATTERN_DIVIDE_X*BOSS_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define BOSS_TIME_ANIMATION			(8)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BOSS_MAX						(3) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �{�X�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			vecUse;						// �v���C���[�̂�������ɑ΂��Ă̌���
	bool			damage;						// �_���[�W����
	bool			downUse;					// ������ݒ�
	bool			start;						// �v���C���[���X�^�[�g�ʒu�ɗ��������̔���
	bool			lenghtUse;
	bool			attackUse;					// �U������
	bool			attackUseBullet;			// �o���b�g���U���͈͊O�ɏo�Ă��邩�ǂ����̔���

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				hp;							// �̗�
	int				countShot;					// �e��ł܂ł̃J�E���g
	int				type;
	int				attackPtn;					// �U���p�^�[��
	float			colorCnt;					// ���l�̕ύX�J�E���g
	float			lenght;						// ����
	int				damageCnt;					// �_���[�W�J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	int				state;						// �{�X�̏�ԊǗ�
	int				direction;					// BOSS�̕���
	float			Radius;						// �{�X�̔��a
	float			BaseAngle;					// �{�X�̊p�x

} BOSS;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
BOSS *GetBoss(void);


