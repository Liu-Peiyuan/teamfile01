//=============================================================================
//
// [substitute.h]
// Author : kitade mayumi
//! @date	2020-08-24
//! @brief	�g����A�C�e���̒�`
//=============================================================================
#pragma once
// �}�N����`
#define	NUM_SUBSTITUTE		(2)									// �|���S����

#define TEXTURE_GAME_SUBSTITUTE	_T("data/TEXTURE/egg.png")		// �摜
#define TEXTURE_SUBSTITUTE_SIZE_X		(48/2)					// �e�N�X�`���T�C�Y
#define TEXTURE_SUBSTITUTE_SIZE_Y		(48/2)					// ����

#define TEXTURE_SUBSTITUTE_PATTERN_X	(5)						// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_SUBSTITUTE_PATTERN_Y	(3)						// �A�j���p�^�[���̃e�N�X�`�����������iY)
//
//#define TIME_ANIMATION				(5)					// �A�j���[�V�����̐؂�ւ��J�E���g
//
//#define MOVE_ANIM_PATTERN			(4)
//
//#define MOVE_TYPE_TRAVERSE			(0)					// �o���b�g�e�L�X�`���[��Y��0��
//
//#define MOVE_SPEED					(5.0f)				// �ړ����x

#define SUBSTITUTE_JUMP_VAL				(6.0f)					// �o���b�g�̃W�����v���̍����␳�l
#define SUBSTITUTE_JUMP_SUM				(0.2f)					// �o���b�g�̃W�����v���̍����l�̕␳�l
#define SUBSTITUTE_DOWN_SUM				(0.18f)

#define SUBSTITUTE_HITANIM_VAL			(5.0f)					// �o���b�g�̃W�����v���̍����␳�l
#define SUBSTITUTE_HITANIM_SUM			(0.3f)					// �o���b�g�̃W�����v���̍����l�̕␳�l
//#define SUBSTITUTE_HITDOWN_SUM				(0.18f)


#define SUBSTITUTE_INTERVAL_MINIMUM		(48.0f)
#define SUBSTITUTE_INTERVAL_MAXIMUM		(64.0f)
#define SUBSTITUTE_INTERVAL_BETWEEN		(36.0f)

#define SUBSTITUTE_INITPOS_X			(PLAYER_INITPOS_X - SUBSTITUTE_INTERVAL_MINIMUM)
#define SUBSTITUTE_INITPOS_Y			(410.0f)				// �o���b�g��Y���̏����l

#define SUBSTITUTE_DISCHARGE_SPEED		(11.0f)					// �o���b�g�̔��ˑ��x

#define SUBSTITUTE_LIMIT_POS_X_MIN		(-100.0f)				// �o���b�g���ˎ��̍����E�l
#define SUBSTITUTE_LIMIT_POS_X_MAX		(SCREEN_WIDTH + TEXTURE_SUBSTITUTE_SIZE_X)	// �x���b�g���ˎ��̉E���E�l


#define SUBSTITUTE_POSX_MIN				(3.0f)					// �o���b�g���W�̍����E�l

#define DROP_WAVE_VAL				(5)						// �h���b�v���̒��_���W�̗h��͈�

typedef enum
{// �o���b�g�̃e�L�X�`���[X���̔ԍ�
	SUBSTITUTE_ANIM_WAIT,
	SUBSTITUTE_ANIM_WALK_A,
	SUBSTITUTE_ANIM_WALK_B,
	SUBSTITUTE_ANIM_WALK_C,
	SUBSTITUTE_ANIM_DMG,
}SUBSTITUTE_ANIM_NUM;

typedef enum
{// �o���b�g�̊e�A�N�V�����̃��x��
	SUBSTITUTE_ACT_MOVE,
	SUBSTITUTE_ACT_JUMP,
	SUBSTITUTE_ACT_DISCHARGE,
	SUBSTITUTE_ACT_HIT,
	SUBSTITUTE_ACT_WAIT,
	SUBSTITUTE_ACT_DROP
}SUBSTITUTE_ACTION;

typedef enum
{// �o���b�g�ԍ�
	SUBSTITUTE_PATTERN_DROP,
	SUBSTITUTE_PATTERN_USE,
	SUBSTITUTE_PATTERN_BORN
}SUBSTITUTE_ANIM_TYPE;

typedef enum
{// �o���b�g�ԍ�
	SUBSTITUTE_1ST,
	SUBSTITUTE_2ND,
	//SUBSTITUTE_3RD,
	SUBSTITUTE_MAX //= 10
}SUBSTITUTE_NUM;

typedef enum
{
	SUBSTITUTE_OPTIMAL_DISTANCE,
	SUBSTITUTE_TOO_NEAR,
	SUBSTITUTE_TOO_FAR,
	SUBSTITUTE_DISUSE
}SUBSTITUTE_DISTANCE;



//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool				use;					// true:�g�p		false:���g�p
	bool				useJump;				// true:�W�����v��	false:�W�����v���g�p
	bool				useDischarge;			// true:���˒�		flase:������
	bool				useHitAnim;				// true:���e��		false:���e�O

	int					patternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int					countAnim;				// �A�j���[�V�����J�E���g
	int					state;					// �o���b�g�̌������
	int					animType;				// �o���b�g�e�L�X�`���[�̂����̒l

	D3DXVECTOR3			pos;					// �|���S���̈ړ���
	D3DXVECTOR3			rot;					// �|���S���̉�]��

	float				turn;					// �o���b�g�̌���
	float				dirDischarge;			// ���˂̌��� +1.0f�ŉE�����A-1.0���ō�����

	float				yTemp;					// �W�����v���̂��l��Վ��ۑ�
	float				yPrev;					// �W�����v���̑O��̂��l��ۑ�

	float				radius;					// �o���b�g�̔��a
	float				baseAngle;				// �o���b�g�̊p�x

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D			vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

} SUBSTITUTE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSubstitute(int type);
void	UninitSubstitute(void);
void	UpdateSubstitute(void);
void	DrawSubstitute(void);
SUBSTITUTE	*GetSubstitute(int no);

void	SetMoveSubstitute(float val, float dir);
void	SetSubstituteDischarge(float direction);
void	SetHitSubstitute(int no);
void	UpdateJumpSubstitute(void);
void	SetJumpSubstitute(void);



