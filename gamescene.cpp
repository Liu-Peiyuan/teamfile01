//! @file	gamescene.cpp
//! @author	�܂�
//! @date	2020-07-13
//! @brief	�Q�[���V�[���̎���

// �C���N���[�h�t�@�C��
#include "main.h"
#include "bullet.h"
#include "playerTest.h"
#include "file.h"
#include "life.h"
#include "score.h"
#include "timer.h"

// �}�N����`

// ����������
void InitGameScene(void)
{
	InitBullet(0);
	InitPlayer();
	InitFile();
}