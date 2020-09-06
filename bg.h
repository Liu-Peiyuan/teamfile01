//! @file	bg.h
//! @author	�܂�
//! @date	2020-07-13
//! @brief	�^�C�g���w�i�̒�`

#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(-100)							// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(800)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(600)							// �^�C�g���̍���
#define	TITLELOGO_POS_X		(100)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(100)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(300)							// �^�C�g�����S�̍���


#define	RESULTLOGO_POS_X		(80)						// �^�C�g�����S�̕\���ʒu
#define	RESULTLOGO_POS_Y		(60)						// �^�C�g�����S�̕\���ʒu
#define	RESULTLOGO_SIZE_X		(480)						// �^�C�g�����S�̕�
#define	RESULTLOGO_SIZE_Y		(360)						// �^�C�g�����S�̍���

enum BG_TEXTURE_TYPE
{
	TITLE_BG,
	TUTRIAL_BG,
	GAME_BG,
	BONUS_BG,
	RESULT_BG,
	MAX_TEXTURE_TYPE
};

/**************************************************************************//**
	@brief		InitBg
	@brief		�^�C�g���̏���������
	@param[in]	type
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitBg(int type);

/**************************************************************************//**
	@brief		UninitBg
	@brief		�^�C�g���̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitBg(void);

/**************************************************************************//**
	@brief		UpdateBg
	@brief		�^�C�g���̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateBg(void);

/**************************************************************************//**
	@brief		DrawBg
	@brief		�^�C�g���̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawBg(void);

#endif
