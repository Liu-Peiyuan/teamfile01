//=============================================================================
//
// �G���� [enemy.cpp]
// Author : kitade mayumi
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "playerTest.h"
#include "map.h"
#include "checkhit.h"
#include "enemyBullet.h"
#include <math.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_TIME_SHOT	(100)
#define ENEMY_DIRECTION_ATTACK (30)
#define ENEMY_LIMIT_WALL	(100)
#define ENEMY_DIERECTION_DISCOVERY	(200)

enum ENEMY_STATE_ANIME
{
	IDLE,
	ATTACK,
	DEATH,
	STATE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ReadEnemyTexture(void);
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );
void SetEnemy(void);

bool SearchPlayerDiscovery(int i);

void MovingEnemy(int i);
void AttackEnemy(int i);
void DeathEnemy(int i);
void FallEnemy(int i);

void UpdateSniperEnemy(int i);
void UpdateTrackerEnemy(int i);
void UpdateGuardianEnemy(int i);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy[ENEMYTYPEMAX][STATE_MAX] = { NULL };		// �e�N�X�`���ւ̃|���S��

static ENEMY					enemyWk[ENEMY_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	// �G�l�~�[�̃e�N�X�`���̓ǂݍ���
	ReadEnemyTexture();

	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemyWk[i].use = false;										// �g�p
		enemyWk[i].hp = 2;											// �̗�
		enemyWk[i].damage = false;									// �_���[�W����
		enemyWk[i].type = SNIPER;									// �G�l�~�[�^�C�v�̏�����
		enemyWk[i].countShot = 0;									// �J�E���g�V���b�g�̏�����
		enemyWk[i].direction = Left;								// �G�l�~�[�̌����Ă������
		enemyWk[i].state = IDLE;									// �G�l�~�[�̏�ԏ�����
		enemyWk[i].dropSpeed = 0;									// �G�l�~�[�̗�������

		enemyWk[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���W�f�[�^��������
		enemyWk[i].move = D3DXVECTOR3(ENEMY_MOVE_SPEED, 0.0f, 0.0f);// �ړ��ʂ�������
		enemyWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�ʂ�������
		enemyWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemyWk[i].CountAnim = 0;									// �A�j���J�E���g��������
		
		D3DXVECTOR2 temp = D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y);
		enemyWk[i].Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemyWk[i].BaseAngle = atan2f(ENEMY_TEXTURE_SIZE_Y, ENEMY_TEXTURE_SIZE_X);	// �G�l�~�[�̊p�x��������
		// ���_���̍쐬
		MakeVertexEnemy(i);
	}

	SetEnemy();

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
void ReadEnemyTexture(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	for (int i = 0; i < ENEMYTYPEMAX; i++)
	{
		for (int j = 0; j < STATE_MAX; j++)
		{
			// �X�i�C�p�[�^�̃e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_SNIPER_IDLE_TEXTURE,							// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SNIPER][IDLE]);					// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_SNIPER_ATTACK_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SNIPER][ATTACK]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_SNIPER_DEATH_TEXTURE,							// �t�@�C���̖��O
				&g_pD3DTextureEnemy[SNIPER][DEATH]);				// �ǂݍ��ރ������̃|�C���^

			// �g���b�J�[�^�̃e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_TRACKER_IDLE_TEXTURE,							// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TRACKER][IDLE]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_TRACKER_ATTACK_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TRACKER][ATTACK]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_TRACKER_DEATH_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[TRACKER][DEATH]);				// �ǂݍ��ރ������̃|�C���^


			// �K�[�f�B�A���^�̃e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_GUARDIAN_IDLE_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[GUARDIAN][IDLE]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_GUARDIAN_ATTACK_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[GUARDIAN][ATTACK]);				// �ǂݍ��ރ������̃|�C���^

			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				ENEMY_GUARDIAN_DEATH_TEXTURE,						// �t�@�C���̖��O
				&g_pD3DTextureEnemy[GUARDIAN][DEATH]);				// �ǂݍ��ރ������̃|�C���^

		}
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMYTYPEMAX; i++)
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

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemyWk[i].use = false;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	PLAYER *player = GetPlayer();
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		D3DXVECTOR3 vec = player->pos - enemyWk[i].pos;
		fabsf(vec.x);
		if (enemyWk[i].use == true)
		{
			// �A�j���[�V����
			enemyWk[i].CountAnim++;

			if ((enemyWk[i].CountAnim % ENEMY_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemyWk[i].PatternAnim = (enemyWk[i].PatternAnim + 1) % ENEMY_ANIM_PATTERN_NUM;
			}

			if (vec.x <= SCREEN_WIDTH && enemyWk[i].pos.x <= SCREEN_WIDTH)
			{
				// ���ꂼ��̃^�C�v�ʂ��Ƃ̃G�l�~�[�̍X�V����
				UpdateSniperEnemy(i);
				UpdateTrackerEnemy(i);
				UpdateGuardianEnemy(i);
			}

			AttackEnemy(i);

			CheckEnemyBullet();
			DeathEnemy(i);

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEnemy(i);						
			// �e�N�X�`�����W��ݒ�
			SetTextureEnemy(i, enemyWk[i].PatternAnim);

		}
	}
}

//=============================================================================
// �X�i�C�p�[�^�̍X�V����
//=============================================================================
void UpdateSniperEnemy(int i)
{
	if (enemyWk[i].type == SNIPER)					// �g�p���Ă����ԂȂ�X�V����
	{
		enemyWk[i].countShot++;
		
		// ��]����
		D3DXVECTOR3 pos = GetPlayer()->pos - enemyWk[i].pos;
		enemyWk[i].rot.z = atan2f(pos.y, pos.x) - D3DX_PI / 2;

		// �ړ�����
		float rot = atan2f(pos.y, pos.x);

		enemyWk[i].pos.x += cosf(rot) * enemyWk[i].move.x/3;
		enemyWk[i].pos.y += sinf(rot) * enemyWk[i].move.x/3;		

	}
}

//=============================================================================
// �ǔ��^�̍X�V����
//=============================================================================
void UpdateTrackerEnemy(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;

	// �v���C���[��ǐՂ���
	if (enemyWk[i].type == TRACKER)
	{
		D3DXVec3Subtract(&vec, &player->pos, &enemyWk[i].pos);

		if (vec.x <= 0)
		{
			enemyWk[i].pos.x -= enemyWk[i].move.x;
		}
		else
		{
			enemyWk[i].pos.x += enemyWk[i].move.x;
		}
		MovingEnemy(i);
		RestrictionEnemy(i);
		FallEnemy(i);
	}
}

//=============================================================================
// �ǔ��^�̍X�V����
//=============================================================================
void UpdateGuardianEnemy(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;

	if (enemyWk[i].type == GUARDIAN)
	{
		// �v���C���[�𔭌�������A�v���C���[��ǐՂ���
		if (SearchPlayerDiscovery(i))
		{
			D3DXVec3Subtract(&vec, &player->pos, &enemyWk[i].pos);
			enemyWk[i].move.x = 1.0f;
			if (vec.x <= 0)
			{
				enemyWk[i].pos.x -= enemyWk[i].move.x;
			}
			else
			{
				enemyWk[i].pos.x += enemyWk[i].move.x;
			}
		}
		else
		{
			//// �ړ�����
			//enemyWk[i].pos.x += enemyWk[i].move.x;
			//// ����ʊO�֏o����
			//if ((enemyWk[i].pos.x < ENEMY_LIMIT_WALL)
			//	|| (enemyWk[i].pos.x > (SCREEN_WIDTH - ENEMY_LIMIT_WALL)))
			//{
			//	enemyWk[i].move.x *= -1;			// ���Ε����ֈړ�������
			//}
		}
		MovingEnemy(i);
		RestrictionEnemy(i);
		FallEnemy(i);
	}
}

//=============================================================================
// ��������
//=============================================================================
bool SearchPlayerDiscovery(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;
	float lenght;
	// �v���C���[�ƃG�l�~�[�̋������v�Z����B
	D3DXVec3Subtract(&vec, &player->pos, &enemyWk[i].pos);
	lenght = fabsf(vec.x);

	// �������Βl�Ƃ��A���������ɂȂ�����v���C���[�𔭌�
	if (lenght <= ENEMY_DIERECTION_DISCOVERY)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �G�l�~�[�̗�������
//=============================================================================
void FallEnemy(int i)
{
	enemyWk[i].pos.y += enemyWk[i].dropSpeed * 1.0f;	// �����x�I�ɉ��ֈړ��A�d�͉����x
	enemyWk[i].dropSpeed++;

	FallCheckHitEnemy(i);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemyWk[i].use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemyWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemyWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy( int i )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexEnemy( i );

	// rhw�̐ݒ�
	enemyWk[i].vertexWk[0].rhw =
	enemyWk[i].vertexWk[1].rhw =
	enemyWk[i].vertexWk[2].rhw =
	enemyWk[i].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemyWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	enemyWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y);
	enemyWk[i].vertexWk[3].tex = D3DXVECTOR2( 1.0f/ ENEMY_TEXTURE_PATTERN_DIVIDE_X, 1.0f/ENEMY_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy( int i, int cntPattern )
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % ENEMY_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / ENEMY_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y;
	
	if (enemyWk[i].type != SNIPER)
	{
		if (enemyWk[i].direction == Left)
		{
			enemyWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			enemyWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			enemyWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			enemyWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		}
		else
		{
			enemyWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			enemyWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			enemyWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			enemyWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		}
	}

	else
	{
		enemyWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		enemyWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		enemyWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		enemyWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy( int i )
{
	// ���_���W�̐ݒ�
	enemyWk[i].vertexWk[0].vtx.x = enemyWk[i].pos.x - cosf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[0].vtx.y = enemyWk[i].pos.y - sinf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[0].vtx.z = 0.0f;

	enemyWk[i].vertexWk[1].vtx.x = enemyWk[i].pos.x + cosf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[1].vtx.y = enemyWk[i].pos.y - sinf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[1].vtx.z = 0.0f;

	enemyWk[i].vertexWk[2].vtx.x = enemyWk[i].pos.x - cosf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[2].vtx.y = enemyWk[i].pos.y + sinf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[2].vtx.z = 0.0f;

	enemyWk[i].vertexWk[3].vtx.x = enemyWk[i].pos.x + cosf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[3].vtx.y = enemyWk[i].pos.y + sinf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
	enemyWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�̈ʒu�ݒ�֐�
//=============================================================================
void SetEnemy(void)
{
	MAP *map = GetMapData();
	int i = 0;

	for (int p = 0; p < MAP_MAXDATA * SIZE_X * SIZE_Y; p++, map++)
	{
		switch(map->type)
		{
		case BLOCK13:
			enemyWk[i].type = SNIPER;
			enemyWk[i].Texture = g_pD3DTextureEnemy[SNIPER][IDLE];
			enemyWk[i].pos = map->pos;
			enemyWk[i].use = true;
			i++;
			break;

		case GLASS14:
			enemyWk[i].type = TRACKER;
			enemyWk[i].Texture = g_pD3DTextureEnemy[TRACKER][IDLE];
			enemyWk[i].pos = map->pos;
			enemyWk[i].use = true;
			i++;
			break;

		case GLASS15:
			enemyWk[i].type = GUARDIAN;
			enemyWk[i].Texture = g_pD3DTextureEnemy[GUARDIAN][IDLE];
			enemyWk[i].pos = map->pos;
			enemyWk[i].use = true;
			i++;
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// �G�l�~�[�̈ړ��ݒ�
//=============================================================================
void MovingEnemy(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;

	D3DXVec3Subtract(&vec, &player->pos, &enemyWk[i].pos);
	if (vec.x <= 0)
	{
		enemyWk[i].direction = Left;
	}
	else
	{
		enemyWk[i].direction = Right;
	}
}

//=============================================================================
// �G�l�~�[�̍U���ݒ�
//=============================================================================
void AttackEnemy(int i)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 vec;
	float lenght;

	switch (enemyWk[i].type)
	{
	case SNIPER:
		if (enemyWk[i].countShot >= ENEMY_TIME_SHOT)
		{
			SetEnemyBullet(enemyWk[i].pos, player->pos, enemyWk[i].type, &enemyWk[i].countShot);
			enemyWk[i].state = ATTACK;
			enemyWk[i].Texture = g_pD3DTextureEnemy[enemyWk[i].type][enemyWk[i].state];
		}
		break;

	case TRACKER:
	case GUARDIAN:
		// �v���C���[�ƃG�l�~�[�̋������v�Z����B
		D3DXVec3Subtract(&vec, &player->pos, &enemyWk[i].pos);
		lenght = fabsf(vec.x);
		
		// �������Βl�Ƃ��A���������ɂȂ�����U�����[�V�������J�n����
		if (lenght <= ENEMY_DIRECTION_ATTACK)
		{
			enemyWk[i].state = ATTACK;
			enemyWk[i].Texture = g_pD3DTextureEnemy[enemyWk[i].type][enemyWk[i].state];
		}
		else
		{
			enemyWk[i].state = IDLE;
			enemyWk[i].Texture = g_pD3DTextureEnemy[enemyWk[i].type][enemyWk[i].state];
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �G�l�~�[�̔j���ݒ�
//=============================================================================
void DeathEnemy(int i)
{
	if (enemyWk[i].pos.x <= 0.0f )
	{
		enemyWk[i].use = false;
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(void)
{
	return(&enemyWk[0]);
}


