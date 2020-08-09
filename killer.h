//! @file	killer.h
//! @author	kitade mayumi
//! @date	2020-08-07
//! @brief �L���[�̒�`

#ifndef _KILLER_H_
#define _KILLER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KILLER				(2)			// �|���S����


#define TEXTURE_KILLER_SIZE_X	(50)		// �e�N�X�`���T�C�Y
#define TEXTURE_KILLER_SIZE_Y	(50)		// ����


#define TEXTURE_PATTERN_DIVIDE_X_KILLER	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_KILLER	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_KILLER			(TEXTURE_PATTERN_DIVIDE_X_KILLER*TEXTURE_PATTERN_DIVIDE_Y_KILLER)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_KILLER			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define KILLER_MAX						(6) // �L���[�̍ő吔

#define KILLER_SPEED			(6.0f)		// �L���[�̈ړ��X�s�[�h

/**************************************************************************//**
	@struct		KILLER
	@brief		�L���[�̍\����
	@par		[�L���[�̒�`]
*//***************************************************************************/
typedef struct	
{
	bool			use;						// true:�g�p  false:���g�p
	bool			vecUse;						// �x�N�g���^�C�v�̎g�p���
	bool			dead;						// ���񂾂��ǂ���

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		vec;						// �x�N�g��

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				type;						// �^�C�v�i��ށj
	int				popCnt;						// ���X�{�[���J�E���g
	int				direction;					// ����

	float			speed;						// �ړ����x

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} KILLER;

/**************************************************************************//**
	@brief		InitKiller
	@brief		�L���[�̏���������
	@param[in]	type		�e�N�X�`���^�C�v
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitKiller(int type);

/**************************************************************************//**
	@brief		UninitKiller
	@brief		�L���[�̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitKiller(void);

/**************************************************************************//**
	@brief		UpdateKiller
	@brief		�L���[�̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateKiller(void);

/**************************************************************************//**
	@brief		DrawKiller
	@brief		�L���[�̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawKiller(void);

/**************************************************************************//**
	@brief		SetKiller
	@brief		�L���[�̔��ːݒ�
	@param[in]	pos		�L���[�̍��W
	@param[in]	type	�L���[�̌���
	@return		ptr		�L���[�̐擪�A�h���X
*//***************************************************************************/
void SetKiller(D3DXVECTOR3 pos, int type);

/**************************************************************************//**
	@brief		GetKiller
	@brief		�L���[�̃A�h���X�擾
	@param[in]	no		�L���[�̔ԍ�
	@return		&g_killer[no] �u���b�N�ԍ��̃A�h���X
*//***************************************************************************/
KILLER *GetKiller(int no);


#endif
