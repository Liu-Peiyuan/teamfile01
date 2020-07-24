//=============================================================================
//
// �G���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "playerTest.h"
#include "map.h"
#include "checkhit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );
void SetEnemy(void);
void DeathEnemy(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy = NULL;		// �e�N�X�`���ւ̃|���S��

static ENEMY					enemyWk[ENEMY_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE,										// �t�@�C���̖��O
			&g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^
	}


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemyWk[i].use = true;										// �g�p
		enemyWk[i].hp = 2;											// �̗�
		enemyWk[i].damage = false;									// �_���[�W����

		enemyWk[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���W�f�[�^��������
		enemyWk[i].move = D3DXVECTOR3(2.0f, 0.0f, 0.0f);			// �ړ��ʂ�������
		enemyWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�ʂ�������
		enemyWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemyWk[i].CountAnim = 0;									// �A�j���J�E���g��������
		
		D3DXVECTOR2 temp = D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y);
		enemyWk[i].Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemyWk[i].BaseAngle = atan2f(ENEMY_TEXTURE_SIZE_Y, ENEMY_TEXTURE_SIZE_X);	// �G�l�~�[�̊p�x��������
		enemyWk[i].Texture = g_pD3DTextureEnemy;

		MakeVertexEnemy(i);											// ���_���̍쐬
	}

	SetEnemy();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemyWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			enemyWk[i].CountAnim++;
			if( ( enemyWk[i].CountAnim % ENEMY_TIME_ANIMATION ) == 0 )
			{
				// �p�^�[���̐؂�ւ�
				enemyWk[i].PatternAnim = ( enemyWk[i].PatternAnim + 1 ) % ENEMY_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureEnemy( i, enemyWk[i].PatternAnim );
			}
			
			// ��]����
			if (i & 1)
			{
				enemyWk[i].rot.z += 0.05f;
			}
			else
			{
				D3DXVECTOR3 pos = GetPlayer()->pos - enemyWk[i].pos;
				enemyWk[i].rot.z = atan2f(pos.y, pos.x) - D3DX_PI / 2;
			}

			// �ړ�����
			if (i == 0)
			{	// �O�Ԃ����v���C���[���z�[�~���O����悤�ɂ��Ă݂�
				D3DXVECTOR3 pos = GetPlayer()->pos - enemyWk[i].pos;
				float rot = atan2f(pos.y, pos.x);

				enemyWk[i].pos.x += cosf(rot) * enemyWk[i].move.x/3;
				enemyWk[i].pos.y += sinf(rot) * enemyWk[i].move.x/3;

			}
			else
			{	// ���͉̂��ɓ����Ă��邾��
				enemyWk[i].pos += enemyWk[i].move;		// �ړ�������
				if ((enemyWk[i].pos.x < 0) || (enemyWk[i].pos.x > SCREEN_WIDTH))
				{										// ����ʊO�֏o����
					enemyWk[i].move.x *= -1;			// ���Ε����ֈړ�������
				}
			}

			CheckBullet();
			DeathEnemy();

			SetVertexEnemy(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}

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
	if (i & 1)
	{
		enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else
	{
		enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
		enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
		enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
		enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
	}

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
	
	enemyWk[i].vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemyWk[i].vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemyWk[i].vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemyWk[i].vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
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
	ENEMY *enemy = GetEnemy();

	for (int p = 0; p < MAP_MAXDATA * SIZE_X * SIZE_Y; p++, map++)
	{
		if (map->type == GLASS15)
		{
			enemy->pos = map->pos;
			enemy++;
		}
	}
}

//=============================================================================
// �G�l�~�[�̔j���ݒ�
//=============================================================================
void DeathEnemy(void)
{
	ENEMY *enemy = GetEnemy();
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->pos.x <= 0.0f )
		{
			enemy->use = false;
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(void)
{
	return(&enemyWk[0]);
}


