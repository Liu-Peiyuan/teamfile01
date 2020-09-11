//! @file	scene.cpp
//! @author	kitade mayumi
//! @date	2020-07-13
//! @brief	�V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "scene.h"
#include "titlescene.h"
#include "tutrialscene.h"
#include "gamescene.h"
#include "resultscene.h"
#include "bonusscene.h"
#include "fade.h"

// �}�N����`
#define SCENE_START	(SCENE_TITLE)
 
// �O���[�o���ϐ�
int g_scene = SCENE_START;

// ����������
void InitScene(void)
{
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitTitleScene();
		break;
	case SCENE_TUTRIAL:
		InitTutrialScene();
		break;
	case SCENE_GAME:
		InitGameScene();
		break;
	case SCENE_BONUS:
		InitBonusScene();
		break;
	case SCENE_RESULT:
		InitResultScene();
		break;
	default:
		break;
	}
	InitFade();
}

// �I������
void UninitScene(void)
{
	switch (g_scene)
	{
	case SCENE_TITLE:
		UninitTitleScene();
		break;
	case SCENE_TUTRIAL:
		UninitTutrialScene();
		break;
	case SCENE_GAME:
		UninitGameScene();
		break;
	case SCENE_BONUS:
		UninitBonusScene();
		break;
	case SCENE_RESULT:
		UninitResultScene();
		break;
	default:
		break;
	}
	UninitFade();
}

// �X�V����
void UpdateScene(void)
{
	switch (g_scene)
	{
	case SCENE_TITLE:
		UpdateTitleScene();
		break;
	case SCENE_TUTRIAL:
		UpdateTutrialScene();
		break;
	case SCENE_GAME:
		UpdateGameScene();
		break;
	case SCENE_BONUS:
		UpdateBonusScene();
		break;
	case SCENE_RESULT:
		UpdateResultScene();
		break;
	default:
		break;
	}
	UpdateFade();
}

// �`�揈��
void DrawScene(void)
{
	switch (g_scene)
	{
	case SCENE_TITLE:
		DrawTitleScene();
		break;
	case SCENE_TUTRIAL:
		DrawTutrialScene();
		break;
	case SCENE_GAME:
		DrawGameScene();
		break;
	case SCENE_BONUS:
		DrawBonusScene();
		break;
	case SCENE_RESULT:
		DrawResultScene();
		break;
	default:
		break;
	}
	DrawFade();
}

// �V�[���؂�ւ�
void SetScene(int scene)
{
	UninitScene();

	g_scene = scene;
	
	InitScene();
}

// �V�[���̎擾
int GetScene(void)
{
	return g_scene;
}
