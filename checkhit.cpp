//! @file	checkhit.cpp
//! @author	�܂�
//! @date	2020-06-18
//! @brief	�Փ˔���̎���

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "checkhit.h"
#include "playerTest.h"
#include "file.h"
#include "map.h"
#include "playerTest.h"
#include "item.h"
#include "life.h"
#include "score.h"
#include "enemy.h"
#include "bullet.h"
#include "controller.h"
#include "effect.h"

//=============================================================================
// �}�b�v�`�b�v�Ƃ̓����蔻��
//=============================================================================
int CheckHitBB_MAP(D3DXVECTOR3 pos1, D3DXVECTOR3 pos_mapchip, D3DXVECTOR2 size1, D3DXVECTOR2 size_mapchip, float moveSpeed)
{
	if ((pos1.x + size1.x > pos_mapchip.x - size_mapchip.x) && (pos1.x - size1.x < pos_mapchip.x + size_mapchip.x) &&
		(pos1.y + size1.y > pos_mapchip.y - size_mapchip.y) && (pos1.y + size1.y < pos_mapchip.y + size_mapchip.y))		// �Ώۂ̉��ӂ��}�b�v�`�b�v�ɐG��Ă��邩
	{
		return TOP;	// �}�b�v�`�b�v�̏�ɐG��Ă���
	}

	if ((pos1.x + size1.x > pos_mapchip.x - size_mapchip.x + moveSpeed) && (pos1.x - size1.x < pos_mapchip.x + size_mapchip.x - moveSpeed) &&	// PLAYER_MOVE���������Ă���̂́A�c�ɂȂ������u���b�N�ɑ΂��āu�����͂����Ȃ���W�����v�v���ł��Ȃ��Ȃ�o�O��}�����邽�߁B
		(pos1.y - size1.y > pos_mapchip.y - size_mapchip.y) && (pos1.y - size1.y < pos_mapchip.y + size_mapchip.y))		// �Ώۂ̏�ӂ��}�b�v�`�b�v�ɐG��Ă��邩
	{
		return UNDER;	// �}�b�v�`�b�v�̉��ɐG��Ă���
	}

	if ((pos1.x + size1.x > pos_mapchip.x - size_mapchip.x) && (pos1.x + size1.x < pos_mapchip.x + size_mapchip.x) &&
		(pos1.y + size1.y > pos_mapchip.y - size_mapchip.y) && (pos1.y - size1.y < pos_mapchip.y + size_mapchip.y)) 	// �Ώۂ̉E�ӂ��}�b�v�`�b�v�ɐG��Ă��邩
	{
		return LEFT_MAPCHIP;	// �}�b�v�`�b�v�̍��ɐG��Ă���
	}

	if ((pos1.x - size1.x > pos_mapchip.x - size_mapchip.x) && (pos1.x - size1.x < pos_mapchip.x + size_mapchip.x) &&
		(pos1.y + size1.y > pos_mapchip.y - size_mapchip.y) && (pos1.y - size1.y < pos_mapchip.y + size_mapchip.y))	// �Ώۂ̍��ӂ��}�b�v�`�b�v�ɐG��Ă��邩
	{
		return RIGHT_MAPCHIP;	// �}�b�v�`�b�v�̉E�ɐG��Ă���
	}

	return NOTTOUCHED;
}


//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	size1 /= 2.0f;	// ���T�C�Y�ɂ���
	size2 /= 2.0f;	// ����

	if (pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.y + size2.y > pos1.y - size1.y && pos1.y + size1.y > pos2.y - size2.y)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	if ((size1 + size2) * (size1 + size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y))
	{
		return true;
	}

	return false;
}

//=============================================================================
// �v���C���[�̗��������̎��̓����蔻��
//=============================================================================
void FallCheckHitPlayer (void)
{
	MAP *mapchip = GetMapData();
	PLAYER *player = GetPlayer();

	for (int i = 0; i < (SIZE_Y * SIZE_X * MAP_MAXDATA); i++, mapchip++)
	{
		if ((player->jumpForce < 1) || player->dropSpeed >= PLAYER_ACCELE)	// �u���b�N���ŃW�����v����ƃu���b�N��ӂɒ���t���o�O��}�����鏈��
		{
			if (mapchip->type == 1 || mapchip->type == 10)
			{
				if (CheckHitBB_MAP(player->pos, mapchip->pos, D3DXVECTOR2(PLAYER_TEXTURE_BB_SIZE_TOP_X, PLAYER_TEXTURE_SIZE_Y),
					D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), player->moveSpeed) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
				{
					player->dropSpeed = 0;		// �d�͉����x�����Z�b�g

					// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
					// �e�N�X�`���T�C�Y�ɍ��킹�č����̕ύX���s��
					// �n�ʂƓ����u���b�N�̈ʒu���ꏏ�ɂȂ����ꍇ�����Ă��܂��̂�h�����߂̕�������
					if (player->partsState <= TWO && mapchip->pos.y < (SCREEN_HEIGHT - (MAP_TEXTURE_SIZE_Y * 3.0f + PLAYER_TEXTURE_BB_SIZE_TOP_X)))
					{
						player->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y -
							(PLAYER_TEXTURE_SIZE_X / (MAXPARTS - player->partsState - (0.5f * player->partsState)
								+ (5.0f * (TWO - player->partsState))));
					}
					else
					{
						player->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - PLAYER_TEXTURE_SIZE_X;
					}
					player->jumpForce = 0;		// �W�����v�񐔂����Z�b�g
					player->rot.z = 0;			// ��]�W�����v�̉�]���Z�b�g
					break;
				}
			}

			if (mapchip->type == 0)
			{
				if (CheckHitBB_MAP(player->pos, mapchip->pos, D3DXVECTOR2(PLAYER_TEXTURE_BB_SIZE_X, PLAYER_TEXTURE_SIZE_Y),
					D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), player->moveSpeed) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
				{
					player->dropSpeed = 0;		// �d�͉����x�����Z�b�g

					// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
					// �e�N�X�`���T�C�Y�ɍ��킹�č����̕ύX���s��
					if (player->partsState <= TWO)
					{
						player->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y -
							(PLAYER_TEXTURE_SIZE_X / (MAXPARTS - player->partsState - (0.5f * player->partsState)
								+ (5.0f * (TWO - player->partsState))));
					}
					else
					{
						player->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - PLAYER_TEXTURE_SIZE_X;
					}
					player->jumpForce = 0;		// �W�����v�񐔂����Z�b�g
					player->rot.z = 0;			// ��]�W�����v�̉�]���Z�b�g
					break;
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[�̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
//=============================================================================
void Restriction(void)
{
	MAP *mapchip = GetMapData();
	PLAYER *player = GetPlayer();

	for (int j = 0; j < SIZE_X * SIZE_Y * MAP_MAXDATA; j++, mapchip++)
	{
		if (mapchip->type != -1 && mapchip->type != 15 && mapchip->type != 2)
		{
			switch (CheckHitBB_MAP(player->pos, mapchip->pos, D3DXVECTOR2(PLAYER_TEXTURE_BB_SIZE_X, PLAYER_TEXTURE_SIZE_Y),
				D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), player->moveSpeed))	// �u���b�N�̂ǂ��ɐG��Ă��邩
			{
			case LEFT_MAPCHIP:
				player->pos.x = mapchip->pos.x - MAP_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X;	// ������u���b�N�ɓ˂����ނƃu���b�N�̍��ɖ߂�
				break;
			case RIGHT_MAPCHIP:
				player->pos.x = mapchip->pos.x + MAP_TEXTURE_SIZE_X + PLAYER_TEXTURE_SIZE_X;	// �E����u���b�N�ɓ˂����ނƃu���b�N�̉E�ɖ߂�
				break;
			case UNDER:
				player->pos.y = mapchip->pos.y + MAP_TEXTURE_SIZE_Y + PLAYER_TEXTURE_SIZE_Y;	// ������u���b�N�ɓ˂����ނƃu���b�N�̉��ɖ߂�
				break;
			}
		}
	}

	if (player->pos.x <= MAP_TEXTURE_SIZE_X)	//��ʍ���荶�ɍs���Ȃ��悤�ɂ���
	{
		player->pos.x = MAP_TEXTURE_SIZE_X;
	}

	if (player->pos.x == SCREEN_WIDTH)	//��ʒ������E�ɍs���Ȃ��悤�ɂ���
	{
		player->scroll = true;
		player->countScroll++;
	}
}

//=============================================================================
// �A�C�e���ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
void CheckHitItem(void)
{
	// �A�C�e���ƃv���C���[(BC)
	ITEM *item = GetItem(0);
	PLAYER *player = GetPlayer();


	if (player->use)
	{
		for (int j = 0; j < ITEM_MAX; j++, item++)
		{
			if (item->use == false)
			{
				continue;		//���g�p�Ȃ珈���Ȃ�
			}
			if (CheckHitBC(player->pos, item->pos, PLAYER_TEXTURE_BB_SIZE_X, TEXTURE_ITEM_SIZE_X))
			{
				item->use = false;		 // �A�C�e���̏��ŏ������s��
				item->delete_use = true; // 

				if (item->grape_use == true)
				{
					//�̗͉񕜏���
					ChangeLife(1);
				}

				ChangeScore(item->point * 10);		// �X�R�A���Z
			}
		}
	}
}

//=============================================================================
// �G�l�~�[�ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
void CheckHitEnemy(void)
{
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	CHANGE_LIFE *life = GetLifeState();

	bool damage = false;
	if (player->use)
	{
		for (int i = 0; i < ENEMY_MAX; i++, enemy++)
		{
			if (enemy->use == false)
			{
				continue;
			}

			// �G�l�~�[�Ƃ̏Փ˔�����s��
			if (CheckHitBC(player->pos, enemy->pos, PLAYER_TEXTURE_BB_SIZE_X, ENEMY_TEXTURE_SIZE_X))
			{
				damage = true;
				break;
			}
		}

		if (damage && player->invincible == false)
		{
			// �v���C���[��HP����������
			player->hp--;
			player->invincible = true;
			life--;
			ChangeLife(-1);
			// ���C�t�̌���
			ChangeScore(-100);
			damage = false;
		}
	}
}

//=============================================================================
// �o���b�g�Ƃ̏Փ˔���
//=============================================================================
void CheckBullet(void)
{
	ENEMY *enemy = GetEnemy();
	CHANGE_LIFE *life = GetLifeState();
	BULLET *bullet = GetBullet(0);

	for (int j = 0; j < BULLET_MAX; j++, bullet++)
	{
		if (bullet[j].use == false) continue;

		for (int i = 0; i < ENEMY_MAX; i++, enemy++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBB(enemy->pos, bullet->pos, 
				D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y), 
				D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y)))
			{
 				enemy->damage = true;
				bullet[j].use = false;
				ChangeScore(100);
				enemy->use = false;
				SetEffect(enemy->pos.x, enemy->pos.y, 15);
			}
		}
	}


}

