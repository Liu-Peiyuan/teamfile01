//! @file	effect.h
//! @author	�k�o�^�|
//! @date	2020-01-27
//! @brief	�G�t�F�N�g�����̒�`
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_TEXTURE			_T("data/TEXTURE/bullethit2_front.png")	// �摜
#define EFFECT_TEXTURE_FLARE	_T("data/TEXTURE/blood02.png")			// �摜

#define EFFECT_TEXTURE_SIZE_X	(128.0f / 1.5f)		// �e�N�X�`���T�C�Y
#define EFFECT_TEXTURE_SIZE_Y	(128.0f / 1.5f)		// ����

#define EFFECT_TEXTURE_SIZE_FALRE_X	(1024/2)		// �e�N�X�`���T�C�Y
#define EFFECT_TEXTURE_SIZE_FALRE_Y	(1024/2)		// ����


#define EFFECT_TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������ifX)
#define EFFECT_TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define EFFECT_ANIM_PATTERN_NUM			(EFFECT_TEXTURE_PATTERN_DIVIDE_X*EFFECT_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define EFFECT_TIME_ANIMATION			(1)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define	MAX_EXPLOSION					(128)		// �r���{�[�h�ő吔
#define EFFECT_NUM_PARTS				(10)		// �G�t�F�N�g�̍ő�p�^�[����
#define EFFECT_NUM_EFFECTS				(5)			// �G�t�F�N�g��1�i�̍ő�p�^�[����
#define EFFECT_LIFE_TIME				(15)		// �G�t�F�N�g�̍ő�p�^�[����

/**************************************************************************//**
	@struct		PARTICLE
	@brief		�G�t�F�N�g�\����
	@par		[�G�t�F�N�g�̒�`]
*//***************************************************************************/
typedef struct	
{
	D3DXVECTOR3		pos;						//!< �|���S���̈ړ���
	D3DXVECTOR3		move;						//!< �ړ���
	int				nPatternAnim;				//!< �A�j���[�V�����p�^�[���i���o�[
	int				nCountAnim;					//!< �A�j���[�V�����J�E���g

	int				nLiveTime;					//!< ��������

	LPDIRECT3DTEXTURE9	Texture;				//!< �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		//!< ���_���i�[���[�N

	bool			bIsFinish;
}PARTICLE;

typedef struct
{
	int				texType;
	int				texDivedX;
	int				texDivedY;
}EFECTTEX;

typedef struct	// �G�t�F�N�g�\����
{
	int				nUse;						//!< �g�p����Ă��邩
	int				nIsEnding;					//!< �A�j���[�V�����̏I��
	bool			bIsRemoveOnFinish;			//!< �A�j���[�V�����̏I���n�_����ړ�

	D3DXVECTOR3		pos;						//!< �|���S���̈ړ���

	int				nDuration;					//!< �G�t�F�N�g�̊J�n����I���܂ł̎���
	int				nElapsed;					//!< �G�t�F�N�g�̏I���܂ł��J�E���g
	int				nNumFinish;					//!< �G�t�F�N�g�̍ő吔�܂ł̃J�E���g

	int				nEffectCount;				//!< �G�t�F�N�g�p�^�[���̃J�E���g
	int				nEmitCounter;				//!< �G�~�b�g���J�E���g

	EFECTTEX		texture;					//!< �e�N�X�`���̐ݒ�
	PARTICLE		pParticle[EFFECT_NUM_PARTS];	//!< �p�[�e�B�N�����[�N

}EFFECT;

/**************************************************************************//**
	@brief		�G�t�F�N�g�̏���������
	@param		type	�e�N�X�`���^�C�v
	@return		S_OK	�����̐���
				E_FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitEffect(int type);

/**************************************************************************//**
	@brief		�G�t�F�N�g�̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitEffect(void);

/**************************************************************************//**
	@brief		�G�t�F�N�g�̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateEffect(void);

/**************************************************************************//**
	@brief		�G�t�F�N�g�̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawEffect(void);

/**************************************************************************//**
	@brief		�G�t�F�N�g�̔z�u����
	@param[in]	fX	X���W
	@param[in]	fY	Y���W
	@param[in]	nDuration	�A�j���[�V��������
	@return		�Ȃ�
*//***************************************************************************/
void SetEffect(float fX, float fY, int nDuration);
