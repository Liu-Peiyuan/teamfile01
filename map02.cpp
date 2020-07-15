/*******************************************************************************
* scanf ��warning�h�~
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include <stdio.h>
#include "main.h"
#include "file.h"
#include "map.h"
#include "checkhit.h"
#include "input.h"
#include "playerTest.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAP2_TEXTURE                 _T("data/TEXTURE/maptip.jpg")    // �}�b�v�`�b�v�摜

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT MakeVertexMap2(int x, int y);
void SetTexture2(int x, int y);
void SetVertexMapChip2(int y, int x);

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
static LPDIRECT3DTEXTURE9		g_pD3DTextureMap = NULL;		// �e�N�X�`���ւ̃|���S��
MAP mapBlock2[SIZE_Y][SIZE_X];


// ����������
HRESULT InitMap2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int *data2 = GetMapDataType2();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
		MAP2_TEXTURE,										// �t�@�C���̖��O
		&g_pD3DTextureMap);	// �ǂݍ��ރ������̃|�C���^

	for (int i = 0; i < SIZE_Y; i++)
	{
		for (int j = 0; j < SIZE_X; j++)
		{
			mapBlock2[i][j].use = true;
			mapBlock2[i][j].Texture = g_pD3DTextureMap;
			mapBlock2[i][j].pos = D3DXVECTOR3(MAP_TEXTURE_SIZE_X + (j * MAP_TEXTURE_SIZE_X * 2),
				MAP_TEXTURE_SIZE_Y + (i * MAP_TEXTURE_SIZE_Y * 2), 0.0f);

			mapBlock2[i][j].type = *data2;
			mapBlock2[i][j].move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);	// �ړ���
			MakeVertexMap2(j, i);
			data2++;
		}
	}
	return S_OK;
}


// �I������
void UninitMap2(void)
{
	if (g_pD3DTextureMap != NULL)
	{
		// �e�N�X�`���̊J��
		g_pD3DTextureMap->Release();
		g_pD3DTextureMap = NULL;
	}
}

// �X�V����
void UpdateMap2(void)
{
	PLAYER *player = GetPlayer();

	if (player->countScroll >= 2)
	{
		for (int i = 0; i < SIZE_Y; i++)
		{
			for (int j = 0; j < SIZE_X; j++)
			{

				//mapBlock2[i][j].pos.x -= player->scrollPos.x;
				//if (mapBlock2[i][j].type == 1)
				//{
					//mapBlock2[i][j].pos.y -= mapBlock2[i][j].move.y;
					//if (mapBlock2[i][j].pos.y < -MAP_TEXTURE_SIZE_Y)
					//{
					//	mapBlock2[i][j].pos.y = SCREEN_HEIGHT + MAP_TEXTURE_SIZE_Y * 2;
					//}
				//}
				SetVertexMapChip2(i, j);
			}
		}
	}
}

// �`�揈��
void DrawMap2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	if (player->countScroll >= 2)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < SIZE_Y; i++)
		{
			for (int j = 0; j < SIZE_X; j++)
			{
				if (mapBlock2[i][j].use == true)		// �g�p���Ă����ԂȂ�`�悷��
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, mapBlock2[i][j].Texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, mapBlock2[i][j].vertexWk, sizeof(VERTEX_2D));

				}
			}
		}
	}

}

HRESULT MakeVertexMap2(int x, int y)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_���W�̐ݒ�
	mapBlock2[y][x].vertexWk[0].vtx = D3DXVECTOR3(MAP_TEXTURE_SIZE_X + (x * MAP_TEXTURE_SIZE_X * 2) - MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y + (y * MAP_TEXTURE_SIZE_Y * 2) - MAP_TEXTURE_SIZE_Y, 0.0f);
	mapBlock2[y][x].vertexWk[1].vtx = D3DXVECTOR3(MAP_TEXTURE_SIZE_X + (x * MAP_TEXTURE_SIZE_X * 2) + MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y + (y * MAP_TEXTURE_SIZE_Y * 2) - MAP_TEXTURE_SIZE_Y, 0.0f);
	mapBlock2[y][x].vertexWk[2].vtx = D3DXVECTOR3(MAP_TEXTURE_SIZE_X + (x * MAP_TEXTURE_SIZE_X * 2) - MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y + (y * MAP_TEXTURE_SIZE_Y * 2) + MAP_TEXTURE_SIZE_Y, 0.0f);
	mapBlock2[y][x].vertexWk[3].vtx = D3DXVECTOR3(MAP_TEXTURE_SIZE_X + (x * MAP_TEXTURE_SIZE_X * 2) + MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y + (y * MAP_TEXTURE_SIZE_Y * 2) + MAP_TEXTURE_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	mapBlock2[y][x].vertexWk[0].rhw =
		mapBlock2[y][x].vertexWk[1].rhw =
		mapBlock2[y][x].vertexWk[2].rhw =
		mapBlock2[y][x].vertexWk[3].rhw = 1.0f;

	if (mapBlock2[y][x].type != -1)
	{
		// ���ˌ��̐ݒ�
		mapBlock2[y][x].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		mapBlock2[y][x].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		mapBlock2[y][x].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		mapBlock2[y][x].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	else
	{
		// ���ˌ��̐ݒ�
		mapBlock2[y][x].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
		mapBlock2[y][x].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
		mapBlock2[y][x].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
		mapBlock2[y][x].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	}

	switch (mapBlock2[y][x].type)
	{
	case BLOCK0:
		// �e�N�X�`�����W�̐ݒ�
		mapBlock2[y][x].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		mapBlock2[y][x].vertexWk[1].tex = D3DXVECTOR2(1.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		mapBlock2[y][x].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[3].tex = D3DXVECTOR2(1.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		break;

	case BLOCK1:
		// �e�N�X�`�����W�̐ݒ�
		mapBlock2[y][x].vertexWk[0].tex = D3DXVECTOR2(1.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 0.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[1].tex = D3DXVECTOR2(2.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 0.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[2].tex = D3DXVECTOR2(1.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[3].tex = D3DXVECTOR2(2.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		break;

	case BLOCK10:
		// �e�N�X�`�����W�̐ݒ�
		mapBlock2[y][x].vertexWk[0].tex = D3DXVECTOR2(0.0f, 1.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[1].tex = D3DXVECTOR2(1.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[2].tex = D3DXVECTOR2(0.0f, 2.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		mapBlock2[y][x].vertexWk[3].tex = D3DXVECTOR2(1.0f / MAP_TEXTURE_PATTERN_DIVIDE_X, 2.0f / MAP_TEXTURE_PATTERN_DIVIDE_Y);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMapChip2(int y, int x)
{
	// ���_���W�̐ݒ�
	mapBlock2[y][x].vertexWk[0].vtx.x = mapBlock2[y][x].pos.x - MAP_TEXTURE_SIZE_X;
	mapBlock2[y][x].vertexWk[0].vtx.y = mapBlock2[y][x].pos.y - MAP_TEXTURE_SIZE_Y;
	mapBlock2[y][x].vertexWk[0].vtx.z = 0.0f;

	mapBlock2[y][x].vertexWk[1].vtx.x = mapBlock2[y][x].pos.x + MAP_TEXTURE_SIZE_X;
	mapBlock2[y][x].vertexWk[1].vtx.y = mapBlock2[y][x].pos.y - MAP_TEXTURE_SIZE_Y;
	mapBlock2[y][x].vertexWk[1].vtx.z = 0.0f;

	mapBlock2[y][x].vertexWk[2].vtx.x = mapBlock2[y][x].pos.x - MAP_TEXTURE_SIZE_X;
	mapBlock2[y][x].vertexWk[2].vtx.y = mapBlock2[y][x].pos.y + MAP_TEXTURE_SIZE_Y;
	mapBlock2[y][x].vertexWk[2].vtx.z = 0.0f;

	mapBlock2[y][x].vertexWk[3].vtx.x = mapBlock2[y][x].pos.x + MAP_TEXTURE_SIZE_X;
	mapBlock2[y][x].vertexWk[3].vtx.y = mapBlock2[y][x].pos.y + MAP_TEXTURE_SIZE_Y;
	mapBlock2[y][x].vertexWk[3].vtx.z = 0.0f;
}



void SetTexture2(int x, int y)
{
	// ���ˌ��̐ݒ�
	mapBlock2[y][x].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	mapBlock2[y][x].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	mapBlock2[y][x].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	mapBlock2[y][x].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
}

MAP *GetMapData2(void)
{
	return &mapBlock2[0][0];
}