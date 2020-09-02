//! @file	bonusscene.cpp
//! @author	kitade mayumi
//! @date	2020-08-09
//! @brief	�{�[�i�X�V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "scene.h"
#include "bonusscene.h"
#include "file.h"
#include "playerTest.h"
#include "item.h"
#include "bg.h"
#include "map01.h"
#include "score.h"
#include "timer.h"
#include "life.h"
#include "effect.h"
#include "sound.h"

// �V�[���̏���������
void InitBonusScene(void)
{
	OpenBonusFile();
	InitBg(BONUS_BG);
	InitMap();
	InitItem(0);
	InitPlayer();
	InitEffect(0);
	PlaySound(SOUND_LABEL_BGM_BOSS_STAGE);
}

// �V�[���̏I������
void UninitBonusScene(void)
{
	UninitEffect();
	UninitMap();
	UninitBg();
	UninitItem();
	UninitPlayer();
	StopSound(SOUND_LABEL_BGM_BOSS_STAGE);
}

// �V�[���̍X�V����
void UpdateBonusScene(void)
{
	UpdateMap();
	UpdatePlayer();
	UpdateBg();
	UpdateItem();
	UpdateEffect();
	UpdateScore();
	UpdateLife();
	UpdateTimer();
}

// �V�[���̕`�揈��
void DrawBonusScene(void)
{
	DrawBg();
	DrawMap();
	DrawScore();
	DrawLife();
	DrawTimer();
	DrawItem();
	DrawPlayer();
	DrawEffect();
}
