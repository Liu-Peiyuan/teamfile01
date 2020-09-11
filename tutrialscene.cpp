//! @file	tutrialscene.cpp
//! @author	kitade mayumi
//! @date	2020-09-05
//! @brief	�`���[�g���A���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "scene.h"
#include "tutrialscene.h"
#include "bullet.h"
#include "file.h"
#include "playerTest.h"
#include "bullet.h"
#include "item.h"
#include "bg.h"
#include "map01.h"
#include "enemy.h"
#include "enemyBullet.h"
#include "substitute.h"
#include "score.h"
#include "timer.h"
#include "life.h"
#include "effect.h"
#include "sound.h"

// �}�N����`

//�O���[�o���ϐ�

// ����������
void InitTutrialScene(void)
{
	OpenTutrialFile();
	InitBg(TUTRIAL_BG);
	InitMap();
	InitItem(0);
	InitPlayer();
	InitEffect(0);
	InitBullet(0);
	InitEnemy();
	InitEnemyBullet(0);
	InitSubstitute();

	InitLife();
	InitScore();
	InitTimer();

	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM_TUTRIAL);
}

// �I������
void UninitTutrialScene(void)
{
	UninitLife();
	UninitScore();
	UninitTimer();

	UninitSubstitute();
	UninitEnemy();
	UninitEnemyBullet();
	UninitBullet();
	UninitEffect();
	UninitMap();
	UninitBg();
	UninitItem();
	UninitPlayer();
	// BGM��~
	StopSound(SOUND_LABEL_BGM_TUTRIAL);

}

// �X�V����
void UpdateTutrialScene(void)
{
	UpdateLife();
	UpdateTimer();
	UpdateScore();

	UpdateSubstitute();
	UpdateEnemyBullet();
	UpdateEnemy();
	UpdateBullet();
	UpdateMap();
	UpdatePlayer();
	UpdateBg();
	UpdateItem();
	UpdateEffect();
}

// �`�揈��
void DrawTutrialScene(void)
{
	DrawBg();
	DrawMap();
	DrawScore();
	DrawTimer();
	DrawLife();

	DrawItem();
	DrawEnemy();
	DrawSubstitute();
	DrawPlayer();
	DrawBullet();
	DrawEnemyBullet();
	DrawEffect();
}
