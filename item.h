//! @file	item.h
//! @author	�܂�
//! @date	2020-06-19
//! @brief	�A�C�e���̒�`

#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_ITEM		(2)					// �|���S����

#define TEXTURE_ITEM_SIZE_X	(50/2) // �e�N�X�`���T�C�Y
#define TEXTURE_ITEM_SIZE_Y	(50/2) // ����

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ITEM_MAX					(3) // �A�C�e���̍ő吔
#define ITEM_KIND_MAX				(3)	//�A�C�e���̎�ނ̍ő吔
#define ITEM_POINT_ICE				(10) //�X�̃|�C���g
#define ITEM_POINT_SALT_PEPPER		(10) //���R�V���E�̃|�C���g
#define ITEM_POINT_HERB				(20) //�n�[�u�̃|�C���g

/**************************************************************************//**
	@struct		ITEM
	@brief		�A�C�e���̍\����
	@par		[�A�C�e���̒�`]
*//***************************************************************************/
typedef struct	
{
	bool			use;						// true:�g�p  false:���g�p
	bool			grape_use;					// �u�h�E���g�p����Ă��邩
	bool			delete_use;					// �g�p���Ă������̂�����
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �A�C�e���̔��a
	float			BaseAngle;					// �A�C�e���̊p�x
	int				Texturenum;					//�e�N�X�`���[�ԍ�
	int				point;						//�A�C�e���̓_��
	float			speed;						//�A�C�e���̑��x

} ITEM;

/**************************************************************************//**
	@brief		InitItem
	@brief		�A�C�e���̏���������
	@param[in]	type		�e�N�X�`���^�C�v
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitItem(int type);

/**************************************************************************//**
	@brief		UninitItem
	@brief		�A�C�e���̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitItem(void);

/**************************************************************************//**
	@brief		UpdateItem
	@brief		�A�C�e���̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateItem(void);

/**************************************************************************//**
	@brief		DrawItem
	@brief		�A�C�e���̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawItem(void);

/**************************************************************************//**
	@brief		DrawItem
	@brief		�A�C�e���̃A�h���X�擾
	@param[in]	no		�A�C�e���̔ԍ�
	@return		&itemWk[no] �A�C�e���̔ԍ��̃A�h���X
*//***************************************************************************/
ITEM *GetItem(int no);

/**************************************************************************//**
	@brief		SetItem
	@brief		�A�C�e���̍��W�ݒ�
	@param[in]	pos		�A�C�e���̍��W
	@param[in]	speed	�A�C�e���̈ړ��X�s�[�h
	@return		item	�A�C�e���̐擪�A�h���X
*//***************************************************************************/
ITEM *SetItem(D3DXVECTOR3 pos, float speed);

#endif
