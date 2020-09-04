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
#include "enemyBullet.h"
#include "wall.h"
#include "killer.h"
#include "spear.h"
#include "substitute.h"
#include "sound.h"
#include "boss.h"
#include "fade.h"

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
			if (mapchip->use &&(mapchip->type == BLOCK1 || mapchip->type == BLOCK10 || mapchip->type == BLOCK12))
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

			if (mapchip->type == BLOCK0 || mapchip->type == BLOCK3 || mapchip->type == BLOCK16)
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

					if (mapchip->type == BLOCK3)
					{
						SlidePlayer();
					}
					if (mapchip->type == BLOCK16)
					{
						player->bogUse = true;
					}
					break;
				}
			}
		}
	}
}

//=============================================================================
// �g����A�C�e���̗��������̎��̓����蔻��
//=============================================================================
void FallCheckHitSubstitute(void)
{
	MAP *mapchip = GetMapData();
	SUBSTITUTE *substitute = GetSubstitute();
	PLAYER *player = GetPlayer();

	for (int i = 0; i < (SIZE_Y * SIZE_X * MAP_MAXDATA); i++, mapchip++)
	{
		if ((substitute->jumpForce < 1) || substitute->dropSpeed >= PLAYER_ACCELE)	// �u���b�N���ŃW�����v����ƃu���b�N��ӂɒ���t���o�O��}�����鏈��
		{
			if (mapchip->use && (mapchip->type == BLOCK1 || mapchip->type == BLOCK10 || mapchip->type == BLOCK12))
			{
				if (CheckHitBB_MAP(substitute->pos, mapchip->pos, D3DXVECTOR2(SUBSTITUTE_TEXTURE_BB_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y),
					D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), player->moveSpeed) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
				{
					substitute->dropSpeed = 0;		// �d�͉����x�����Z�b�g

					// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
					substitute->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - SUBSTITUTE_TEXTURE_SIZE_X;

					substitute->jumpForce = 0;		// �W�����v�񐔂����Z�b�g
					substitute->rot.z = 0;			// ��]�W�����v�̉�]���Z�b�g
					break;
				}
			}

			if (mapchip->type == BLOCK0 || mapchip->type == BLOCK3 || mapchip->type == BLOCK16)
			{
				if (CheckHitBB_MAP(substitute->pos, mapchip->pos, D3DXVECTOR2(SUBSTITUTE_TEXTURE_BB_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y),
					D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), player->moveSpeed) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
				{
					substitute->dropSpeed = 0;		// �d�͉����x�����Z�b�g

					// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
					// �e�N�X�`���T�C�Y�ɍ��킹�č����̕ύX���s��
					substitute->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - SUBSTITUTE_TEXTURE_SIZE_X;
					substitute->jumpForce = 0;		// �W�����v�񐔂����Z�b�g
					substitute->rot.z = 0;			// ��]�W�����v�̉�]���Z�b�g

					break;
				}
			}
		}
	}
}

//=============================================================================
// �G�l�~�[�̗��������̎��̓����蔻��
//=============================================================================
void FallCheckHitEnemy(int i)
{
	MAP *mapchip = GetMapData();
	ENEMY *enemy = GetEnemy();

	enemy += i;
	for (int j = 0; j < (SIZE_Y * SIZE_X * MAP_MAXDATA); j++, mapchip++)
	{
		if (mapchip->use && (mapchip->type == BLOCK1 || mapchip->type == BLOCK10 || mapchip->type == BLOCK12))
		{
			if (CheckHitBB_MAP(enemy->pos, mapchip->pos, D3DXVECTOR2(ENEMY_TEXTURE_BB_SIZE_X, ENEMY_TEXTURE_SIZE_Y),
				D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), ENEMY_MOVE_SPEED) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
			{
				enemy->dropSpeed = 0;		// �d�͉����x�����Z�b�g

				// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
				enemy->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - ENEMY_TEXTURE_SIZE_X;
				break;
			}
		}

		if (mapchip->type == BLOCK0 || mapchip->type == BLOCK3 || mapchip->type == BLOCK16)
		{
			if (CheckHitBB_MAP(enemy->pos, mapchip->pos, D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y),
				D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), ENEMY_MOVE_SPEED) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
			{
				enemy->dropSpeed = 0;		// �d�͉����x�����Z�b�g

				// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
				enemy->pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - ENEMY_TEXTURE_SIZE_X;
				break;
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
		if (mapchip->type != -1 && mapchip->use &&
			(mapchip->type == BLOCK0 || mapchip->type == BLOCK1 
			|| mapchip->type == BLOCK3 || mapchip->type == BLOCK10
			|| mapchip->type == BLOCK12 || mapchip->type == BLOCK16))
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

	if (player->countScroll < (2 * MAP_MAXDATA - 1))
	{
		if (player->pos.x >= SCREEN_WIDTH)	//��ʒ������E�ɍs���Ȃ��悤�ɂ���
		{
			player->scroll = true;
		}
	}
	else if(player->countScroll >= (2 * MAP_MAXDATA - 1)
		&&player->pos.x >= SCREEN_WIDTH - MAP_TEXTURE_SIZE_X)
	{
		player->pos.x = SCREEN_WIDTH - MAP_TEXTURE_SIZE_X;
	}
}

//=============================================================================
// �g����A�C�e���̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
//=============================================================================
void RestrictionSubstitute(void)
{
	MAP *mapchip = GetMapData();
	SUBSTITUTE *substitute = GetSubstitute();
	PLAYER *player = GetPlayer();

	for (int j = 0; j < SIZE_X * SIZE_Y * MAP_MAXDATA; j++, mapchip++)
	{
		if (mapchip->type != -1 &&
			(mapchip->type == BLOCK0 || mapchip->type == BLOCK1
				|| mapchip->type == BLOCK3 || mapchip->type == BLOCK10
				|| mapchip->type == BLOCK12 || mapchip->type == BLOCK16))
		{
			switch (CheckHitBB_MAP(substitute->pos, mapchip->pos, D3DXVECTOR2(SUBSTITUTE_TEXTURE_BB_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_Y),
				D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), 0.0f))		// �u���b�N�̂ǂ��ɐG��Ă��邩
			{
			case LEFT_MAPCHIP:
				substitute->pos.x = mapchip->pos.x - MAP_TEXTURE_SIZE_X - SUBSTITUTE_TEXTURE_SIZE_X;	// ������u���b�N�ɓ˂����ނƃu���b�N�̍��ɖ߂�
				break;
			case RIGHT_MAPCHIP:
				substitute->pos.x = mapchip->pos.x + MAP_TEXTURE_SIZE_X + SUBSTITUTE_TEXTURE_SIZE_X;	// �E����u���b�N�ɓ˂����ނƃu���b�N�̉E�ɖ߂�
				break;
			case UNDER:
				substitute->pos.y = mapchip->pos.y + MAP_TEXTURE_SIZE_Y + SUBSTITUTE_TEXTURE_SIZE_Y;	// ������u���b�N�ɓ˂����ނƃu���b�N�̉��ɖ߂�
				break;
			}
		}
	}
}

//=============================================================================
// �G�l�~�[�̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
//=============================================================================
void RestrictionEnemy(int i)
{
	MAP *mapchip = GetMapData();
	ENEMY *enemy = GetEnemy();
	PLAYER *player = GetPlayer();

	enemy += i;
	for (int j = 0; j < SIZE_X * SIZE_Y * MAP_MAXDATA; j++, mapchip++)
	{
		if (mapchip->type != -1 && mapchip->use &&
			(mapchip->type == BLOCK0 || mapchip->type == BLOCK1
			|| mapchip->type == BLOCK3 || mapchip->type == BLOCK10
			|| mapchip->type == BLOCK12 || mapchip->type == BLOCK16))
		{
			switch (CheckHitBB_MAP(enemy->pos, mapchip->pos, D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y),
				D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), ENEMY_MOVE_SPEED))	// �u���b�N�̂ǂ��ɐG��Ă��邩
			{
			case LEFT_MAPCHIP:
				enemy->pos.x = mapchip->pos.x - MAP_TEXTURE_SIZE_X - ENEMY_TEXTURE_SIZE_X;	// ������u���b�N�ɓ˂����ނƃu���b�N�̍��ɖ߂�
				break;
			case RIGHT_MAPCHIP:
				enemy->pos.x = mapchip->pos.x + MAP_TEXTURE_SIZE_X + ENEMY_TEXTURE_SIZE_X;	// �E����u���b�N�ɓ˂����ނƃu���b�N�̉E�ɖ߂�
				break;
			case UNDER:
				enemy->pos.y = mapchip->pos.y + MAP_TEXTURE_SIZE_Y + ENEMY_TEXTURE_SIZE_Y;	// ������u���b�N�ɓ˂����ނƃu���b�N�̉��ɖ߂�
				break;
			}
		}
	}

	D3DXVECTOR3 vec;
	D3DXVec3Subtract(&vec, &player->pos, &enemy->pos);
	fabs(vec.x);

	if (player->scroll)	// ��ʉE�ɍs���Ȃ��悤�ɂ���
	{
		if (vec.x <= (float)(SCREEN_WIDTH / 8) && vec.x >= 0.0f)
		{
			enemy->use = false;
		}
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

				//�̗͉񕜏���
				ChangeLife(1);

				if (player->partsState != PERFECT)
				{
					player->partsState++;
				}

				if (player->hp != PLAYER_HP)
				{
					player->hp++;
					SetEffect(player->pos.x, player->pos.y, EFFECT_LIFE_TIME, ITEM_HEAL);
				}
				else
				{
					SetEffect(player->pos.x, player->pos.y, EFFECT_LIFE_TIME, ITEM_GET);
				}
				if (item->type == STAR)
				{
					player->superInvincible = true;
					item->use = false;
				}
				ChangeScore(item->point * 10);		// �X�R�A���Z
				PlaySound(SOUND_LABEL_SE_ITEM);

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
			if (!player->superInvincible)
			{
				player->invincible = true;
				// �v���C���[��HP����������
				player->hp--;
				life--;
				ChangeLife(-1);
				// ���C�t�̌���
				ChangeScore(-SCORE_SNIPER_ENEMY);
				damage = false;
				SetEffect(player->pos.x, player->pos.y, EFFECT_LIFE_TIME, PLAYER_BLOOD);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
		}
	}
}

//=============================================================================
// �{�X�ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
void CheckHitBoss(void)
{
	PLAYER *player = GetPlayer();
	BOSS *boss = GetBoss();
	CHANGE_LIFE *life = GetLifeState();

	bool damage = false;
	if (player->use)
	{
		for (int i = 0; i < BOSS_MAX; i++, boss++)
		{
			if (boss->use == false)
			{
				continue;
			}

			// �G�l�~�[�Ƃ̏Փ˔�����s��
			if (CheckHitBC(player->pos, boss->pos, PLAYER_TEXTURE_BB_SIZE_X, BOSS_TEXTURE_SIZE_X))
			{
				damage = true;
				break;
			}
		}

		if (damage && player->invincible == false)
		{
			if (!player->superInvincible)
			{
				player->invincible = true;
				// �v���C���[��HP����������
				player->hp--;
				life--;
				ChangeLife(-1);
				// ���C�t�̌���
				ChangeScore(-SCORE_SNIPER_ENEMY);
				damage = false;
				SetEffect(player->pos.x, player->pos.y, EFFECT_LIFE_TIME, PLAYER_BLOOD);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
		}
	}
}


//=============================================================================
// �j�ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
void CheckSpear(void)
{
	PLAYER *player = GetPlayer();
	SPEAR *spear = GetSpear(0);
	CHANGE_LIFE *life = GetLifeState();

	bool damage = false;

	for (int i = 0; i < SPEAR_MAX; i++, spear++)
	{
		if(spear->use)
		{ 
			if (CheckHitBC(player->pos, spear->pos, PLAYER_TEXTURE_BB_SIZE_X, TEXTURE_SPEAR_SIZE_X))
			{
				damage = true;
			}
		}
	}
	if (damage)
	{
		if (player->invincible == false)
		{
			// �v���C���[��HP����������
			player->hp--;
			player->invincible = true;
			life--;
			ChangeLife(-1);
			// ���C�t�̌���
			ChangeScore(-SPEAR_DAMAGE_SCORE);
			PlaySound(SOUND_LABEL_SE_HIT);
		}
		damage = false;
		SetEffect(spear->pos.x, spear->pos.y, EFFECT_LIFE_TIME, PLAYER_BLOOD);
	}
}

//=============================================================================
// �G�l�~�[�ƃo���b�g�Ƃ̏Փ˔���
//=============================================================================
void CheckEnemyBullet(void)
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
				ChangeScore(SCORE_SNIPER_ENEMY);
				enemy->use = false;
				SetEffect(enemy->pos.x, enemy->pos.y, EFFECT_LIFE_TIME, ENEMY_BLOOD);
				PlaySound(SOUND_LABEL_SE_HIT);

			}
		}
	}
}

//=============================================================================
// �v���C���[�ƃG�l�~�[�o���b�g�Ƃ̏Փ˔���
//=============================================================================
void CheckPlayerBullet(void)
{
	PLAYER *player = GetPlayer();
	CHANGE_LIFE *life = GetLifeState();
	ENEMYBULLET *bullet = GetEnemyBullet(0);
	bool damage = false;

	for (int j = 0; j < BULLET_MAX; j++, bullet++)
	{
		if (bullet[j].use == false) continue;

		if (player->use == false) continue;

		if (CheckHitBB(player->pos, bullet->pos,
			D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y),
			D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y)))
		{
			bullet[j].use = false;
			ChangeScore(-SCORE_SNIPER_ENEMY);
			SetEffect(player->pos.x, player->pos.y, EFFECT_LIFE_TIME, PLAYER_BLOOD);
			PlaySound(SOUND_LABEL_SE_HIT);
			damage = true;

		}

		if (damage)
		{
			if (player->invincible == false)
			{
				// �v���C���[��HP����������
				player->hp--;
				player->invincible = true;
				life--;
				ChangeLife(-1);
				// ���C�t�̌���
				ChangeScore(-SPEAR_DAMAGE_SCORE);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
			damage = false;
		}

	}
}

//=============================================================================
// �ǂƂ̏Փ˔���
//=============================================================================
void CheckHitWall(void)
{
	PLAYER *player = GetPlayer();
	WALL *wall = GetWall();
	ENEMY *enemy = GetEnemy();
	ITEM *item = GetItem(0);

	if (player->use)
	{
		if (wall->pos.x >= player->pos.x)
		{
			SetEffect(player->pos.x, player->pos.y, EFFECT_LIFE_TIME, PLAYER_BLOOD);
			player->use = false;
			PlaySound(SOUND_LABEL_SE_HIT);
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == false) continue;

		if (wall->pos.x >= enemy->pos.x)
		{
			enemy->damage = true;
			enemy->use = false;
			SetEffect(enemy->pos.x, enemy->pos.y, EFFECT_LIFE_TIME, ENEMY_BLOOD);
		}
	}

	for (int i = 0; i < ITEM_MAX; i++, item++)
	{
		if (item->use == false) continue;

		if (wall->pos.x >= item->pos.x)
		{
			item->use = false;
			SetEffect(item->pos.x, item->pos.y, EFFECT_LIFE_TIME, ITEM_HEAL);

		}
	}

	if (GetSubstitute()->use)
	{
		if (wall->pos.x >= GetSubstitute()->pos.x)
		{
			GetSubstitute()->use = false;
			SetEffect(GetSubstitute()->pos.x, GetSubstitute()->pos.y, EFFECT_LIFE_TIME, ITEM_HEAL);
		}
	}

}


//=============================================================================
// �L���[�ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
void CheckHitKiller(void)
{
	PLAYER *player = GetPlayer();
	KILLER *killer = GetKiller(0);
	CHANGE_LIFE *life = GetLifeState();

	bool damage = false;
	if (player->use)
	{
		for (int i = 0; i < KILLER_MAX; i++, killer++)
		{
			if (killer->use == false)
			{
				continue;
			}

			// �L���[�Ƃ̏Փ˔�����s��
			if (CheckHitBC(player->pos, killer->pos, PLAYER_TEXTURE_BB_SIZE_X, TEXTURE_KILLER_SIZE_X))
			{
				damage = true;
				break;
			}
		}

		if (damage)
		{
			if (player->invincible == false)
			{
				// �v���C���[��HP����������
				player->hp--;
				player->invincible = true;
				life--;
				ChangeLife(-1);
				// ���C�t�̌���
				ChangeScore(-SCORE_SNIPER_ENEMY);
				PlaySound(SOUND_LABEL_SE_HIT);

			}
			damage = false;
			SetEffect(killer->pos.x, killer->pos.y, EFFECT_LIFE_TIME, KILLER_APPEAR);
			killer->use = false;
			killer->dead = true;
		}
	}
}

//=============================================================================
// ���[�v�Q�[�g�ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
bool CheckHitWarp(void)
{
	PLAYER *player = GetPlayer();
	MAP * map = GetMapData();

	if (player->use)
	{
		for (int i = 0; i < SIZE_X * SIZE_Y * MAP_MAXDATA; i++, map++)
		{
			if (map->type == BLOCK6)
			{
				// ���[�v�G���A�Ƃ̏Փ˔�����s��
				if (CheckHitBC(player->pos, map->pos, PLAYER_TEXTURE_BB_SIZE_X, SIZE_X))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//=============================================================================
// �S�[���ƃv���C���[�Ƃ̏Փ˔���
//=============================================================================
void CheckHitGoal(void)
{
	PLAYER *player = GetPlayer();
	MAP * map = GetMapData();

	if (player->use)
	{
		for (int i = 0; i < SIZE_X * SIZE_Y * MAP_MAXDATA; i++, map++)
		{
			if (map->type == GOAL)
			{
				// ���[�v�G���A�Ƃ̏Փ˔�����s��
				if (CheckHitBC(player->pos, map->pos, PLAYER_TEXTURE_BB_SIZE_TOP_X, SIZE_GOAL_X))
				{
					PlaySound(SOUND_LABEL_SE_WARP);
					SetFade(FADE_OUT, SCENE_RESULT, SOUND_LABEL_BGM_GAMESTAGE);
					player->use = false;
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[�Ɛg����A�C�e���̏Փ˔���
//=============================================================================
void CheckHitPlayerSubstitute(void)
{
	PLAYER *player = GetPlayer();
	SUBSTITUTE *substitute = GetSubstitute();
	if (player->use)
	{
		// �g����A�C�e���Ƃ̏Փ˔�����s��
		if (CheckHitBC(player->pos, substitute->pos, PLAYER_TEXTURE_BB_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_X))
		{
			if (!substitute->attackUse)
			{
				substitute->sticking = true;
				substitute->releaseUse = false;
				SetPosSubstitute();
				PlaySound(SOUND_LABEL_SE_ITEM);
			}
		}
	}
}

//=============================================================================
// �G�l�~�[�Ɛg����A�C�e���̏Փ˔���
//=============================================================================
void CheckHitEnemySubstitute(void)
{
	ENEMY *enemy = GetEnemy();
	SUBSTITUTE *substitute = GetSubstitute();

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == false)
		{
			continue;
		}
		// �g����A�C�e���Ƃ̏Փ˔�����s��
		if (CheckHitBC(enemy->pos, substitute->pos, ENEMY_TEXTURE_SIZE_X, SUBSTITUTE_TEXTURE_SIZE_X))
		{
			if (substitute->attackUse)
			{
				SetEffect(substitute->pos.x, substitute->pos.y, EFFECT_LIFE_TIME, PLAYER_BLOOD);
				//substitute->use = false;
				enemy->use = false;
				PlaySound(SOUND_LABEL_SE_HIT);
			}
		}
	}
}





