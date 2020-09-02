//! @file	checkhit.h
//! @author	
//! @date	2020-06-18
//! @brief	�Փ˔���̒�`

#ifndef ___CHECKHIT_H___
#define ___CHECKHIT_H___

#include "playerTest.h"

enum CHECKBLOCK
{
	TOP,
	UNDER,
	LEFT_MAPCHIP,
	RIGHT_MAPCHIP,
	NOTTOUCHED,
	MAXCHECKBLOCK
};

/**************************************************************************//**
	@brief		CheckHitBB_MAP
	@brief		BBMAP�̏Փ˔���
	@param[in]	pos1		pos1�̍��W
	@param[in]	pos2		pos2�̍��W
	@param[in]	size1		size1�̑傫��
	@param[in]	size2		size2�̑傫��
	@param[in]	moveSpeed	�ړ����x
	@return		true	�������Ă���
				false	�������Ă��Ȃ�
*//***************************************************************************/
int CheckHitBB_MAP(D3DXVECTOR3 pos1, D3DXVECTOR3 pos_mapchip, D3DXVECTOR2 size1, D3DXVECTOR2 size_mapchip, float moveSpeed);

/**************************************************************************//**
	@brief		CheckHitBB
	@brief		BB�̏Փ˔���
	@param[in]	pos1	pos1�̍��W
	@param[in]	pos2	pos2�̍��W
	@param[in]	size1	size1�̑傫��
	@param[in]	size2	size2�̑傫��
	@return		true	�������Ă���
				false	�������Ă��Ȃ�
*//***************************************************************************/
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

/**************************************************************************//**
	@brief		CheckHitBC
	@brief		BC�̓����蔻��
	@param[in]	pos1	pos1�̍��W
	@param[in]	pos2	pos2�̍��W
	@param[in]	size1	size1�̑傫��
	@param[in]	size2	size2�̑傫��
	@return		true	pos1��pos2���������Ă���
				false	pos1��pos2���������Ă��Ȃ�
*//***************************************************************************/
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

/**************************************************************************//**
	@brief		FallCheckHitPlayer
	@brief		�v���C���[�̗��������̎��̓����蔻��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void FallCheckHitPlayer(void);

/**************************************************************************//**
	@brief		FallCheckHitSubstitute
	@brief		�g����A�C�e���̗��������̎��̓����蔻��
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void FallCheckHitSubstitute(void);

/**************************************************************************//**
	@brief		FallCheckHitEnemy
	@brief		�G�l�~�[�̗��������̎��̓����蔻��
	@param[in]	i
	@return		�Ȃ�
*//***************************************************************************/
void FallCheckHitEnemy(int i);

/**************************************************************************//**
	@brief		Restriction
	@brief		�v���C���[�̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void Restriction(void);

/**************************************************************************//**
	@brief		RestrictionEnemy
	@brief		�G�l�~�[�̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
	@param[in]	i
	@return		�Ȃ�
*//***************************************************************************/
void RestrictionEnemy(int i);

/**************************************************************************//**
	@brief		RestrictionSubstitute
	@brief		�g����A�C�e���̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
	@return		�Ȃ�
*//***************************************************************************/
void RestrictionSubstitute(void);

/**************************************************************************//**
	@brief		CheckHitItem
	@brief		�v���C���[�ƃA�C�e���Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckHitItem(void);

/**************************************************************************//**
	@brief		CheckHitEnemy
	@brief		�G�l�~�[�ƃv���C���[�Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckHitEnemy(void);

/**************************************************************************//**
	@brief		CheckEnemyBullet
	@brief		�G�l�~�[�ƃo���b�g�Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckEnemyBullet(void);

/**************************************************************************//**
	@brief		CheckPlayerBullet
	@brief		�v���C���[�ƃo���b�g�Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckPlayerBullet(void);

/**************************************************************************//**
	@brief		CheckHitWall
	@brief		�ǂƂ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckHitWall(void);

/**************************************************************************//**
	@brief		CheckHitKiller
	@brief		�v���C���[�ƃL���[�Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckHitKiller(void);

/**************************************************************************//**
	@brief		CheckHitWarp
	@brief		�v���C���[�ƃ��[�v�Q�[�g�Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		true	���[�v�Q�[�g�ƏՓ˂��Ă���
				false	���[�v�Q�[�g�ƏՓ˂��Ă��Ȃ�
*//***************************************************************************/
bool CheckHitWarp(void);

/**************************************************************************//**
	@brief		CheckSpear
	@brief		�v���C���[�Ɛj�Ƃ̏Փ˔���
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void CheckSpear(void);
void CheckHitGoal(void);

void CheckHitPlayerSubstitute(void);
void CheckHitEnemySubstitute(void);

#endif