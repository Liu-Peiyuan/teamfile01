//=============================================================================
//
// �{�X�̏��� [boss.cpp]
// Author : kitade mayumi
//! @date	2020-08-28
//! @brief	�{�X�̎���
//=============================================================================
#include "main.h"
#include "boss.h"
#include "playerTest.h"
#include "map.h"
#include "checkhit.h"
#include "enemyBullet.h"
#include "effect.h"
#include <math.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOSS_TIME_SHOT	(100)
#define BOSS_DIRECTION_ATTACK (60)
#define BOSS_LIMIT_WALL	(100)
#define BOSS_DIERECTION_DISCOVERY	(200)
#define BOSS_MAX_HP	(10)
#define BOSS_MAX_ATTACKTYPE	(4)
#define BOSS_MAX_COLOR_ALPHA	(255)

#define BOSS_ALPHA_CHANGE_TIME	(60)
#define BOSS_DAMAGE_TIME	(2 * 60)

// #define BOSS_STAGE_APPEAR	(MAP_MAXDATA * player->scrollCount)
enum BOSS_STATE_ANIME
{
	IDLE,
	ATTACK,
	RUN,
	DEATH,
	STATE_MAX,
};

enum BOSSTYPE
{
	SINGLE,
	TWIN,
	BOSSTYPEMAX
};

enum ATTACKTYPE
{
	TWINSLASH,
	DOWNSLASH,
	TWINFAIR,
	SINGLESLASH,
	MAX_ATTACKTYPE
};

enum TWINTYPE
{
	ZEROTYPE,
	ONETYPE,
	TWOTYPE,
	MAX_TWINTYPE
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ReadBossTexture(void);
HRESULT MakeVertexBoss( int no );
void SetTextureBoss( int no, int cntPattern );
void SetVertexBoss( int no );
void SetBoss(int i);

void MovingBoss(int i);
void AttackBoss(int i);
void DamageBoss(int i);

void UpdateSingleBoss(int i);
void UpdateTwinBoss(int i);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy[BOSSTYPEMAX][STATE_MAX] = { NULL };		// �e�N�X�`���ւ̃|���S��

static BOSS					g_boss[BOSS_MAX];				// �G�l�~�[�\����
static int					g_countAttack;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss(void)
{
	// �{�X�̃e�N�X�`���̓ǂݍ���
	ReadBossTexture();
	g_countAttack = 0;
	// �{�X�̏���������
	for (int i = 0; i < BOSS_MAX; i++)
	{
		g_boss[i].use = false;									// �g�p
		g_boss[i].vecUse = false;								// �����̏����ݒ�
		g_boss[i].downUse = false;
		g_boss[i].start = false;								// �X�^�[�g�ʒu
		g_boss[i].lenghtUse = false;							// �������菉����
		g_boss[i].attackUse = false;

		g_boss[i].hp = BOSS_MAX_HP;								// �̗�
		g_boss[i].damage = false;								// �_���[�W����
		g_boss[i].type = SINGLE;								// �G�l�~�[�^�C�v�̏�����
		g_boss[i].countShot = 0;								// �J�E���g�V���b�g�̏�����
		g_boss[i].colorCnt = 0.0f;								// ���l�̐F�̕ύX�J�E���g
		g_boss[i].direction = Left;								// �{�X�̌����Ă������
		g_boss[i].state = IDLE;									// �{�X�̏�ԏ�����

		g_boss[i].attackPtn = 0;
		g_boss[i].damageCnt = 0;
		g_boss[i].lenght = 0.0f;

		g_boss[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���W�f�[�^��������
		g_boss[i].move = D3DXVECTOR3(BOSS_MOVE_SPEED, 0.0f, 0.0f);// �ړ��ʂ�������
		g_boss[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�ʂ�������
		g_boss[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		g_boss[i].CountAnim = 0;									// �A�j���J�E���g��������
		
		D3DXVECTOR2 temp = D3DXVECTOR2(BOSS_TEXTURE_SIZE_X, BOSS_TEXTURE_SIZE_Y);
		g_boss[i].Radius = D3DXVec2Length(&temp);					// �{�X�̔��a��������
		g_boss[i].BaseAngle = atan2f(BOSS_TEXTURE_SIZE_Y, BOSS_TEXTURE_SIZE_X);	// �{�X�̊p�x��������
		// ���_���̍쐬
		MakeVertexBoss(i);
	}
	for (int i = 0; i < BOSS_MAX; i++)
	{
		SetBoss(i);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
void ReadBossTexture(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	for (int i = 0; i < BOSSTYPEMAX; i++)
	{
		for (int j = 0; j < STATE_MAX; j++)
		{
			// �X�i�C�p�[�^�̃e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_SINGLE_IDLE_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SINGLE][IDLE]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_SINGLE_ATTACK_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SINGLE][ATTACK]);			// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_SINGLE_RUN_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SINGLE][RUN]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_SINGLE_DEATH_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SINGLE][DEATH]);			// �ǂݍ��ރ������̃|�C���^

			// �g���b�J�[�^�̃e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_TWIN_IDLE_TEXTURE,							// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TWIN][IDLE]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_TWIN_ATTACK_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TWIN][ATTACK]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_TWIN_RUN_TEXTURE,							// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TWIN][RUN]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�̃|�C���^
				BOSS_TWIN_DEATH_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TWIN][DEATH]);				// �ǂݍ��ރ������̃|�C���^

		}
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{
	for (int i = 0; i < BOSSTYPEMAX; i++)
	{
		for (int j = 0; j < STATE_MAX; j++)
		{
			if (g_pD3DTextureEnemy[i][j] != NULL)
			{	// �e�N�X�`���̊J��
				g_pD3DTextureEnemy[i][j]->Release();
				g_pD3DTextureEnemy[i][j] = NULL;
			}
		}
	}

	for (int i = 0; i < BOSS_MAX; i++)
	{
		g_boss[i].use = false;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	PLAYER *player = GetPlayer();
	for (int i = 0; i < BOSS_MAX; i++)
	{
		D3DXVECTOR3 vec = player->pos - g_boss[i].pos;
		vec.x =fabsf(vec.x);
		if (g_boss[i].use == true)
		{
			// �A�j���[�V����
			g_boss[i].CountAnim++;

			if ((g_boss[i].CountAnim % BOSS_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				g_boss[i].PatternAnim = (g_boss[i].PatternAnim + 1) % BOSS_ANIM_PATTERN_NUM;
			}

			if (player->pos.x >= SCREEN_CENTER_X
				&& player->pos.x <= SCREEN_WIDTH 
				&& player->countScroll >= (2 * MAP_MAXDATA - 1))
			{
				for (int j = 0; j < BOSS_MAX; j++)
				{
					g_boss[j].start = true;
				}
			}

		}
		if (g_boss[i].start)
		{
			// �U���p�^�[���̍X�V
			g_boss[i].attackPtn = g_countAttack;

			// ���ꂼ��̃^�C�v�ʂ��Ƃ̃{�X�̍X�V����
			UpdateSingleBoss(i);
			UpdateTwinBoss(i);

			AttackBoss(i);

			DamageBoss(i);

			CheckEnemyBullet(); // �{�X�̂�ɕς��� + �v���C���[�ƃ{�X�Ƃ̔�������
		}

		if (g_boss[i].use == true)
		{
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexBoss(i);
			// �e�N�X�`�����W��ݒ�
			SetTextureBoss(i, g_boss[i].PatternAnim);
		}
	}
}

//=============================================================================
// boss[1][2]�c�C���^�C�v�̍X�V����
//=============================================================================
void UpdateTwinBoss(int i)
{
	// 0�̃^�C�v�ȊO�̍U���X�V
	if (g_boss[i].type != SINGLE && i != SINGLE)					// �g�p���Ă����ԂȂ�X�V����
	{
		g_boss[i].countShot++;
		// �U���p�^�[����0�̎��X�V
		if (g_boss[i].attackPtn == TWINSLASH)
		{
			if (!g_boss[i].lenghtUse)
			{
				g_boss[i].lenght = GetPlayer()->pos.x - g_boss[i].pos.x;
				g_boss[i].lenghtUse = true;
				g_boss[i].use = true;
			}

			if (g_boss[i].lenght <= 0)
			{
				g_boss[i].direction = Left;
				g_boss[i].pos.x -= g_boss[i].move.x * 3.0f;
				if (g_boss[i].pos.x <= ((float)SCREEN_CENTER_X + (BOSS_TEXTURE_SIZE_X * 2)))
				{
					SetEffect(g_boss[i].pos.x, g_boss[i].pos.y, BOSS_MAX_HP);
					SetBoss(i);
					g_boss[i].use = false;
				}
			}
			else if(g_boss[i].lenght > 0)
			{
				g_boss[i].direction = Right;
				g_boss[i].pos.x += g_boss[i].move.x * 3.0f;
				if (g_boss[i].pos.x >= ((float)SCREEN_CENTER_X - (BOSS_TEXTURE_SIZE_X * 2)))
				{
					SetEffect(g_boss[i].pos.x, g_boss[i].pos.y, BOSS_MAX_HP);
					SetBoss(i);
					g_boss[i].use = false;
				}
			}
			if (!g_boss[1].use && !g_boss[2].use)
			{
				g_countAttack++;
				for (int j = 1; j < BOSS_MAX; j++)
				{
					g_boss[j].lenghtUse = false;
				}
			}
		}
		// �U���p�^�[����2�̎��X�V
		else if (g_boss[i].attackPtn == TWINFAIR)
		{
			if (!g_boss[i].vecUse)
			{
				g_boss[i].use = true;
				g_boss[i].pos.y -= SCREEN_CENTER_Y;
				D3DXVECTOR3 pos = D3DXVECTOR3(GetPlayer()->pos.x, 
					(SCREEN_WIDTH - BOSS_TEXTURE_SIZE_X), 0.0f) - g_boss[i].pos;
				// ��������
				if (pos.x > 0)
				{
					g_boss[i].direction = Right;
				}
				else if(pos.x < 0)
				{
					g_boss[i].direction = Left;
				}
				else
				{
					g_boss[i].direction = Down;
				}

				// ��]����
				if (g_boss[i].direction == Right)
				{
					g_boss[i].rot.z = atan2f(pos.y, pos.x);
				}
				else if(g_boss[i].direction == Left)
				{
					g_boss[i].rot.z = atan2f(pos.y, pos.x) - D3DX_PI;
				}
				else
				{
					g_boss[i].rot.z = 0.0f;
				}

				// �ړ�����
				float rot = atan2f(pos.y, pos.x);
				g_boss[i].vecUse = true;
				if (g_boss[i].direction == Right)
				{
					g_boss[i].pos.x += cosf(rot) * g_boss[i].move.x * 2.0f;
					g_boss[i].pos.y += sinf(rot) * g_boss[i].move.x * 2.0f;
				}
				else if (g_boss[i].direction == Left)
				{
					g_boss[i].pos.x -= cosf(rot) * g_boss[i].move.x * 2.0f;
					g_boss[i].pos.y += sinf(rot) * g_boss[i].move.x * 2.0f;
				}
				else
				{
					g_boss[i].pos.x += g_boss[i].move.x * 2.0f;
					g_boss[i].pos.y += g_boss[i].move.x * 2.0f;
				}
			}
			if(g_boss[i].pos.y < ((float)SCREEN_HEIGHT - (MAP_TEXTURE_SIZE_Y * 4)))
			{
				if (g_boss[i].attackUse && GetEnemyBullet(i - 1)->pos.y >= SCREEN_HEIGHT)
				{
					if (g_boss[i].direction == Right)
					{
						g_boss[i].pos.x += g_boss[i].move.x * 3.0f;
					}
					else
					{
						g_boss[i].pos.x -= g_boss[i].move.x * 3.0f;
					}
					g_boss[i].pos.y += g_boss[i].move.x * 3.0f;
				}
			}
			else if(g_boss[i].pos.y >= ((float)SCREEN_HEIGHT - (MAP_TEXTURE_SIZE_Y * 4)))
			{
				SetBoss(i);
				g_boss[i].use = false;
			}
			if (!g_boss[1].use && !g_boss[2].use)
			{
				g_countAttack++;
				for (int j = 1; j < BOSS_MAX; j++)
				{
					g_boss[j].vecUse = false;
					g_boss[j].rot.z = 0;
				}
			}
		}
		else
		{
			return;
		}
	}
}

//=============================================================================
// boss[0]�V���O���^�C�v�̍X�V����
//=============================================================================
void UpdateSingleBoss(int i)
{
	float vec;
	// 0�̃^�C�v�̍U���X�V
	if (g_boss[i].type == SINGLE && i == SINGLE)					// �g�p���Ă����ԂȂ�X�V����
	{
		// �U���p�^�[��1�̎��̍X�V
		if (g_boss[i].attackPtn == DOWNSLASH)
		{
			g_boss[i].use = true;
			if (!g_boss[i].downUse)
			{
				g_boss[i].pos.x = GetPlayer()->pos.x;
				g_boss[i].downUse = true;
				g_boss[i].direction = UNDER;
			}
			if (g_boss[i].pos.y <= ((float)SCREEN_HEIGHT - (MAP_TEXTURE_SIZE_Y * 4)))
			{
				g_boss[i].pos.y += g_boss[i].move.x * 5.0f;
			}
			else
			{
				g_countAttack++;
				g_boss[i].downUse = false;
				SetBoss(i);
				g_boss[i].use = false;
			}
		}
		// �U���p�^�[��3�̎��̍X�V
		if (g_boss[i].attackPtn == SINGLESLASH)
		{
			g_boss[i].use = true;

			if (!g_boss[i].downUse)
			{
				g_boss[i].pos.y = ((float)SCREEN_HEIGHT - (MAP_TEXTURE_SIZE_Y * 4));
				g_boss[i].pos.x = (float)SCREEN_WIDTH - (MAP_TEXTURE_SIZE_Y * 2);
				vec = GetPlayer()->pos.x - g_boss[i].pos.x;
				g_boss[i].downUse = true;
				if (vec < 0)
				{
					g_boss[i].direction = Left;
				}
				else
				{
					g_boss[i].direction = Right;
				}
			}
			if (g_boss[i].direction == Left && g_boss[i].pos.x >= (0.0f - BOSS_TEXTURE_SIZE_X))
			{
				g_boss[i].pos.x -= g_boss[i].move.x * 5.0f;
			}
			else if (g_boss[i].direction == Right && g_boss[i].pos.x <= (SCREEN_WIDTH + BOSS_TEXTURE_SIZE_X))
			{
				g_boss[i].pos.x += g_boss[i].move.x * 5.0f;
			}
			else
			{
				g_countAttack = 0;
				SetBoss(i);
				g_boss[i].downUse = false;
				g_boss[i].use = false;
				g_boss[i].attackUse = false;
			}
		}
	}
}

//=============================================================================
// �{�X�̃_���[�W�̏�ԑJ��
//=============================================================================
void DamageBoss(int i)
{
	if (g_boss[i].damage == true)
	{
		g_boss[i].damageCnt++;

		if (g_boss[i].damageCnt >= BOSS_DAMAGE_TIME)
		{
			g_boss[i].damage = false;
			g_boss[i].damageCnt = 0;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS_MAX; i++)
	{
		if (g_boss[i].use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_boss[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_boss[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss( int i )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexBoss( i );

	// rhw�̐ݒ�
	g_boss[i].vertexWk[0].rhw =
	g_boss[i].vertexWk[1].rhw =
	g_boss[i].vertexWk[2].rhw =
	g_boss[i].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_boss[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	g_boss[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	g_boss[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	g_boss[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	// �e�N�X�`�����W�̐ݒ�
	g_boss[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_boss[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / BOSS_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	g_boss[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / BOSS_TEXTURE_PATTERN_DIVIDE_Y);
	g_boss[i].vertexWk[3].tex = D3DXVECTOR2( 1.0f/ BOSS_TEXTURE_PATTERN_DIVIDE_X, 1.0f/BOSS_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss( int i, int cntPattern )
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % BOSS_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / BOSS_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / BOSS_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / BOSS_TEXTURE_PATTERN_DIVIDE_Y;
	
	if (g_boss[i].direction == Left)
	{
		g_boss[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_boss[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		g_boss[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		g_boss[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else
	{
		g_boss[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_boss[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		g_boss[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		g_boss[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}


	int flashing = (g_boss[i].damageCnt + 1) % 2;

	if (g_boss[i].start)
	{
		if (g_boss[i].colorCnt <= 1.0f)
		{
			g_boss[i].colorCnt += (1.0f - 0.1f) / (float)BOSS_ALPHA_CHANGE_TIME;
		}

		// ���ˌ��̐ݒ�
		g_boss[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, (int)(255 /** g_boss[i].colorCnt*/ * flashing));
		g_boss[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, (int)(255 /** g_boss[i].colorCnt*/ * flashing));
		g_boss[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, (int)(255 /** g_boss[i].colorCnt*/ * flashing));
		g_boss[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, (int)(255 /** g_boss[i].colorCnt*/ * flashing));
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss( int i )
{
	// ���_���W�̐ݒ�
	g_boss[i].vertexWk[0].vtx.x = g_boss[i].pos.x - cosf(g_boss[i].BaseAngle + g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[0].vtx.y = g_boss[i].pos.y - sinf(g_boss[i].BaseAngle + g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[0].vtx.z = 0.0f;

	g_boss[i].vertexWk[1].vtx.x = g_boss[i].pos.x + cosf(g_boss[i].BaseAngle - g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[1].vtx.y = g_boss[i].pos.y - sinf(g_boss[i].BaseAngle - g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[1].vtx.z = 0.0f;

	g_boss[i].vertexWk[2].vtx.x = g_boss[i].pos.x - cosf(g_boss[i].BaseAngle - g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[2].vtx.y = g_boss[i].pos.y + sinf(g_boss[i].BaseAngle - g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[2].vtx.z = 0.0f;

	g_boss[i].vertexWk[3].vtx.x = g_boss[i].pos.x + cosf(g_boss[i].BaseAngle + g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[3].vtx.y = g_boss[i].pos.y + sinf(g_boss[i].BaseAngle + g_boss[i].rot.z) * g_boss[i].Radius;
	g_boss[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �{�X�̈ʒu�ݒ�֐�
//=============================================================================
void SetBoss(int i)
{
	MAP *map = GetMapData();

	for (int p = 0; p < MAP_MAXDATA * SIZE_X * SIZE_Y; p++, map++)
	{
		switch(map->type)
		{
		case BOSS1:
			if (i == SINGLE)
			{
				g_boss[i].type = SINGLE;
				g_boss[i].Texture = g_pD3DTextureEnemy[SINGLE][IDLE];
				g_boss[i].pos = map->pos;
				g_boss[i].use = true;
			}
			break;

		case BOSS2:
			if (i == ONETYPE)
			{
				g_boss[i].type = TWIN;
				g_boss[i].Texture = g_pD3DTextureEnemy[TWIN][IDLE];
				g_boss[i].pos = map->pos;
				g_boss[i].use = true;
				break;
			}
		case BOSS3:
			if (i == TWOTYPE)
			{
				g_boss[i].type = TWIN;
				g_boss[i].Texture = g_pD3DTextureEnemy[TWIN][IDLE];
				g_boss[i].pos = map->pos;
				g_boss[i].use = true;
				break;
			}

		default:
			break;
		}
	}
}

//=============================================================================
// �{�X�̈ړ��ݒ�
//=============================================================================
void MovingBoss(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;

	D3DXVec3Subtract(&vec, &player->pos, &g_boss[i].pos);
	if (vec.x <= 0)
	{
		g_boss[i].direction = Left;
	}
	else
	{
		g_boss[i].direction = Right;
	}
}

//=============================================================================
// �{�X�̍U���ݒ�
//=============================================================================
void AttackBoss(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;
	float lenght = 0.0f;

	switch (g_boss[i].type)
	{
	case ZEROTYPE:
		// �v���C���[�ƃ{�X�̋������v�Z����B
		D3DXVec3Subtract(&vec, &player->pos, &g_boss[i].pos);

		if (g_boss[i].attackPtn == DOWNSLASH)
		{
			lenght = fabsf(vec.x);
		}
		else if (g_boss[i].attackPtn == SINGLESLASH)
		{
			lenght = fabsf(vec.y);
		}

		// �������Βl�Ƃ��A���������ɂȂ�����U�����[�V�������J�n����
		if (lenght <= BOSS_DIRECTION_ATTACK)
		{
			g_boss[i].state = ATTACK;
			g_boss[i].Texture = g_pD3DTextureEnemy[g_boss[i].type][g_boss[i].state];
		}
		else
		{
			g_boss[i].state = RUN;  // �����𑖂��Ă郂�[�V�����ɂ���
			g_boss[i].Texture = g_pD3DTextureEnemy[g_boss[i].type][g_boss[i].state];
		}
		break;

	case ONETYPE:
	case TWOTYPE:
		if (g_countAttack == TWINFAIR && !g_boss[i].attackUse)
		{
			SetEnemyBullet(g_boss[i].pos,GetPlayer()->pos,
				g_boss[i].type, &g_boss[i].countShot);
			g_boss[i].state = ATTACK;
			g_boss[i].Texture = g_pD3DTextureEnemy[g_boss[i].type][g_boss[i].state];
			g_boss[i].attackUse = true;
		}

		if (g_boss[i].attackUse)
		{
			// �v���C���[�ƃ{�X�̋������v�Z����B
			D3DXVec3Subtract(&vec, &player->pos, &g_boss[i].pos);
			lenght = fabsf(vec.x);

			// �������Βl�Ƃ��A���������ɂȂ�����U�����[�V�������J�n����
			if (lenght <= BOSS_DIRECTION_ATTACK)
			{
				g_boss[i].state = ATTACK;
				g_boss[i].Texture = g_pD3DTextureEnemy[g_boss[i].type][g_boss[i].state];
			}
			else
			{
				g_boss[i].state = RUN; // �����𑖂��Ă郂�[�V�����ɂ���
				g_boss[i].Texture = g_pD3DTextureEnemy[g_boss[i].type][g_boss[i].state];
			}
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �{�X�̃A�h���X�擾�֐�
//=============================================================================
BOSS *GetBoss(void)
{
	return(&g_boss[0]);
}


