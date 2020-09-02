//! @file	spear.h
//! @author	kitade mayumi
//! @date	2020-08-20
//! @brief  �j�̒�`

#ifndef _SPEAR_H_
#define _SPEAR_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_SPEAR				(2)			// �|���S����


#define TEXTURE_SPEAR_SIZE_X	(16.0f)		// �e�N�X�`���T�C�Y
#define TEXTURE_SPEAR_SIZE_Y	(16.0f)		// ����


#define TEXTURE_PATTERN_DIVIDE_X_SPEAR	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_SPEAR	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_SPEAR			(TEXTURE_PATTERN_DIVIDE_X_SPEAR*TEXTURE_PATTERN_DIVIDE_Y_SPEAR)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_SPEAR			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define SPEAR_MAX						(10) // �j�̍ő吔
#define SPEAR_DAMAGE_SCORE				(50) // �j�̃X�R�A���Z�l

#define SPEAR_SPEED			(6.0f)		// �j�̈ړ��X�s�[�h

/**************************************************************************//**
	@struct		SPEAR
	@brief		�j�̍\����
	@par		[�j�̒�`]
*//***************************************************************************/
typedef struct	
{
	bool			use;						// true:�g�p  false:���g�p
	bool			downUse;					// ���ɉ�������
	bool			popUse;

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		vec;						// �x�N�g��

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				type;						// �^�C�v�i��ށj
	int				direction;					// ����
	int				MoveCnt;					// �ړ��J�E���g
	int				PopCnt;						// ��؃J�E���g

	float			speed;						// �ړ����x

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} SPEAR;

/**************************************************************************//**
	@brief		InitSpear
	@brief		�j�̏���������
	@param[in]	type		�e�N�X�`���^�C�v
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitSpear(int type);

/**************************************************************************//**
	@brief		UninitSpear
	@brief		�j�̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitSpear(void);

/**************************************************************************//**
	@brief		UpdateSpear
	@brief		�j�̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateSpear(void);

/**************************************************************************//**
	@brief		DrawSpear
	@brief		�j�̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawSpear(void);

/**************************************************************************//**
	@brief		GetSpear
	@brief		�j�̃A�h���X�擾
	@param[in]	no		�j�̔ԍ�
	@return		&g_killer[no] �u���b�N�ԍ��̃A�h���X
*//***************************************************************************/
SPEAR *GetSpear(int no);


#endif
