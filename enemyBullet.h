//! @file	enemyBullet.h
//! @author	�܂�
//! @date	2020-08-04
//! @brief	�G�l�~�[�p�̒e�̒�`

#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAME_ENEMY_BULLET		_T("data/TEXTURE/lightning_ball.png")	// �摜
#define TEXTURE_PATTERN_DIVIDE_X_ENEMY_BULLET	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY_BULLET	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����

/**************************************************************************//**
	@struct		ENEMYBULLET
	@brief		�G�l�~�[�p�̒e�̍\����
	@par		[�e�̒�`]
*//***************************************************************************/
typedef struct	
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	D3DXVECTOR3		vec;						// �x�N�g���̌���
	D3DXVECTOR3		move;						// �ړ���
	float			speed;						// �ړ����x

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

} ENEMYBULLET;

/**************************************************************************//**
	@brief		InitEnemyBullet
	@brief		�e�̏���������
	@param[in]	type		�e�N�X�`���^�C�v
	@return			S_OK	�����̐���
					E-FAIL	�����̎��s
*//***************************************************************************/
HRESULT InitEnemyBullet(int type);

/**************************************************************************//**
	@brief		UninitEnemyBullet
	@brief		�e�̏I������
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UninitEnemyBullet(void);

/**************************************************************************//**
	@brief		UpdateEnemyBullet
	@brief		�e�̍X�V����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void UpdateEnemyBullet(void);

/**************************************************************************//**
	@brief		DrawEnemyBullet
	@brief		�e�̕`�揈��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void DrawEnemyBullet(void);

/**************************************************************************//**
	@brief		SetEnemyBullet
	@brief		�e�̔��ːݒ�
	@param[in]	pos		�e�̍��W
	@param[in]	type	�e�̌���
	@return		ptr		�e�̐擪�A�h���X
*//***************************************************************************/
void SetEnemyBullet(D3DXVECTOR3 enemyPos, D3DXVECTOR3 playerPos, int enemyType, int *countShot);

/**************************************************************************//**
	@brief		GetEnemyBullet
	@brief		�e�̃A�h���X�擾
	@param[in]	no		�e�̔ԍ�
	@return		&blockWk[no] �u���b�N�ԍ��̃A�h���X
*//***************************************************************************/
ENEMYBULLET *GetEnemyBullet(int no);

bool FallEnemyBullet(void);
#endif
