//! @file	gamescene.cpp
//! @author	�܂�
//! @date	2020-07-13
//! @brief	�Q�[���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "bullet.h"
#include "playerTest.h"
#include "file.h"
#include "map01.h"
#include "life.h"
#include "score.h"
#include "timer.h"
#include "enemy.h"
#include "item.h"
#include "bg.h"
#include "effect.h"
#include "enemyBullet.h"
#include "wall.h"
#include "killer.h"
#include "sound.h"
#include "spear.h"

// �}�N����`

// �V�[���̏���������
void InitGameScene(void)
{
	PLAYER *player = GetPlayer();

	// �e�̏���������
	InitBullet(0);

	// �G�l�~�[�p�̒e�̏���������
	InitEnemyBullet(0);

	// �v���C���[�̏���������
	InitPlayer();

	// �t�@�C���̓ǂݍ���
	OpenFile();

	// �}�b�v�̏���������
	InitMap();

	// �w�i�̏���������
	InitBg(GAME_BG);

	// �A�C�e���̏���������
	InitItem(0);

	// �G�l�~�[�̏���������
	InitEnemy();

	// �ǂ̏���������
	InitWall();

	if (!player->warpUse)
	{
		// ���C�t�̏���������
		InitLife();

		// �X�R�A�̏���������
		InitScore();

		// �^�C�}�[�̏���������
		InitTimer();
	}

	// �j�̏���������
	InitSpear(0);

	// �G�t�F�N�g�̏���������
	InitEffect(0);

	// �L���[�̏���������
	InitKiller(0);

	// �T�E���h�̊J�n
	PlaySound(SOUND_LABEL_BGM_sample001);
}

// �V�[���̏I������
void UninitGameScene(void)
{
	PLAYER *player = GetPlayer();

	// �L���[�̏I������
	UninitKiller();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �j�̏I������
	UninitSpear();

	// �G�l�~�[�p�̒e�̏I������
	UninitEnemyBullet();

	// �e�̏I������
	UninitBullet();
	
	// �v���C���[�̏I������
	UninitPlayer();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �w�i�̏I������
	UninitBg();

	// �}�b�v�̏I������
	UninitMap();

	// �ǂ̏I������
	UninitWall();

	// �A�C�e���̏I������
	UninitItem();

	if (!player->warpUse)
	{
		// ���C�t�̏I������
		UninitLife();

		//// �X�R�A�̏I������
		//UninitScore();

		// �^�C�}�[�̏I������
		UninitTimer();
	}

	// �T�E���h�̏I������
	StopSound(SOUND_LABEL_BGM_sample001);

}

// �V�[���̍X�V����
void UpdateGameScene(void)
{
	// �}�b�v�̍X�V����
	UpdateMap();

	// �w�i�̍X�V����
	UpdateBg();

	// �L���[�̍X�V����
	UpdateKiller();

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �ǂ̍X�V����
	UpdateWall();

	// �j�̍X�V����
	UpdateSpear();

	// �G�l�~�[�̍X�V����
	UpdateEnemy();

	// �A�C�e���̍X�V����
	UpdateItem();

	// �e�̍X�V����
	UpdateBullet();

	// �G�l�~�[�p�̒e�̍X�V����
	UpdateEnemyBullet();

	// �G�t�F�N�g�̍X�V����
	UpdateEffect();

	// ���C�t�̍X�V����
	UpdateLife();

	// �^�C�}�[�̍X�V����
	UpdateTimer();

	// �X�R�A�̍X�V����
	UpdateScore();
}

// �V�[���̕`�揈��
void DrawGameScene(void)
{
	// �w�i�̕`�揈��
	DrawBg();

	// �j�̕`�揈��
	DrawSpear();

	// �}�b�v�̕`�揈��
	DrawMap();

	// �L���[�̕`�揈��
	DrawKiller();

	// �ǂ̕`�揈��
	DrawWall();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// ���C�t�̕`�揈��
	DrawLife();

	// �A�C�e���̕`�揈��
	DrawItem();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �o���b�g�̕`�揈��
	DrawBullet();

	// �G�l�~�[�p�̒e�̕`�揈��
	DrawEnemyBullet();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();
}