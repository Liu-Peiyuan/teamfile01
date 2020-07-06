//! @file	block.h
//! @author	�܂�
//! @date	2020-06-18
//! @brief	�e�̒�`

#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_BULLET				(2)			// �|���S����

#define TEXTURE_GAME_BULLET		_T("data/TEXTURE/lightning_ball.png")	// �摜
#define TEXTURE_BULLET_SIZE_X	(50)		// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y	(50)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BULLET			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLET_MAX						(3) // �e�̍ő吔

#define BULLET_SPEED			(6.0f)		// �e�̈ړ��X�s�[�h


/**************************************************************************//**
	@struct		BULLET
	@brief		�e�̍\����
	@par		[�e�̒�`]
*//***************************************************************************/
typedef struct	
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} BULLET;

/**************************************************************************//**
	@brief		InitBlock
	@brief		�e�̏���������
	@param[in]	type		�e�N�X�`���^�C�v
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitBullet(int type);

/**************************************************************************//**
	@brief		UninitBlock
	@brief		�e�̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitBullet(void);

/**************************************************************************//**
	@brief		UpdateBlock
	@brief		�e�̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateBullet(void);

/**************************************************************************//**
	@brief		DrawBlock
	@brief		�e�̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawBullet(void);

/**************************************************************************//**
	@brief		SetBlock
	@brief		�e�̔��ːݒ�
	@param[in]	pos		�e�̍��W
	@return		ptr		�e�̐擪�A�h���X
*//***************************************************************************/
void SetBullet(D3DXVECTOR3 pos);

/**************************************************************************//**
	@brief		DrawBlock
	@brief		�e�̃A�h���X�擾
	@param[in]	no		�e�̔ԍ�
	@return		&blockWk[no] �u���b�N�ԍ��̃A�h���X
*//***************************************************************************/
BULLET *GetBullet(int no);


#endif
