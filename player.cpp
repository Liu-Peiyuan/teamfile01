//=============================================================================
//
// �|���S������ [Player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "controller.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer( int cntPattern );	
void SetVertexPlayer(void);					
void PlayerController(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S�� 

PLAYER g_player;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.oldPos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);

	g_player.countAnim = 0;
	g_player.patternAnim = 0;

	// �e�N�X�`���̓ǂݍ���  
	if(type == 0)	// ����̂ݓǂݍ���
	{
		D3DXCreateTextureFromFile( pDevice,	// �f�o�C�X�̃|�C���^
			PLAYER_TEXTURE,					// �t�@�C���̖��O
			&g_pD3DTexturePlayer );			// �ǂݍ��ރ������̃|�C���^
	}

	// ���_���̍쐬
	MakeVertexPlayer();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if( g_pD3DTexturePlayer != NULL )	// 
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	// �A�j���[�V����  
	g_player.countAnim++;
	if( ( g_player.countAnim % PLAYER_TIME_ANIMATION ) == 0 )
	{
		// �p�^�[���̐؂�ւ�
		g_player.patternAnim = ( g_player.patternAnim + 1 ) % PLAYER_ANIM_PATTERN_NUM;

		// �e�N�X�`�����W��ݒ�
		SetTexturePlayer( g_player.patternAnim );
	}
	g_player.oldPos = g_player.pos;

	PlayerController();

	SetVertexPlayer();	// �ړ���̍��W�Œ��_��ݒ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�  
	pDevice->SetTexture( 0, g_pD3DTexturePlayer );

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexPlayer();

	// rhw�̐ݒ�
	g_player.vertexWk[0].rhw =
	g_player.vertexWk[1].rhw =
	g_player.vertexWk[2].rhw =
	g_player.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�  
	g_player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�  
	g_player.vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	g_player.vertexWk[1].tex = D3DXVECTOR2( 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	g_player.vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_Y );
	g_player.vertexWk[3].tex = D3DXVECTOR2( 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_X, 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_Y );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;
	g_player.vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	g_player.vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	g_player.vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	g_player.vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(void)
{
	// ���_���W�̐ݒ� 
	g_player.vertexWk[0].vtx.x = g_player.pos.x - PLAYER_TEXTURE_SIZE_X;
	g_player.vertexWk[0].vtx.y = g_player.pos.y - PLAYER_TEXTURE_SIZE_Y;
	g_player.vertexWk[0].vtx.z = 0.0f;

	g_player.vertexWk[1].vtx.x = g_player.pos.x + PLAYER_TEXTURE_SIZE_X;
	g_player.vertexWk[1].vtx.y = g_player.pos.y - PLAYER_TEXTURE_SIZE_Y;
	g_player.vertexWk[1].vtx.z = 0.0f;

	g_player.vertexWk[2].vtx.x = g_player.pos.x - PLAYER_TEXTURE_SIZE_X;
	g_player.vertexWk[2].vtx.y = g_player.pos.y + PLAYER_TEXTURE_SIZE_Y;
	g_player.vertexWk[2].vtx.z = 0.0f;

	g_player.vertexWk[3].vtx.x = g_player.pos.x + PLAYER_TEXTURE_SIZE_X;
	g_player.vertexWk[3].vtx.y = g_player.pos.y + PLAYER_TEXTURE_SIZE_Y;
	g_player.vertexWk[3].vtx.z = 0.0f;
}

/**************************************************************************//**
	@brief		���̓R�}���h����
	@param		�Ȃ�
	@return		�Ȃ�
*//***************************************************************************/
void PlayerController(void)
{
	// �R�}���h���́A�R���g���[���[���͑���
	if (GetInput(DOWNMOVE))
	{
		g_player.pos.y += 2.0f;
	}
	else if (GetInput(RIGHTMOVE))
	{
		g_player.pos.y -= 2.0f;
	}
	else if (GetInput(LEFTMOVE))
	{
		g_player.pos.x -= 2.0f;
	}
	else if (GetInput(UPMOVE))
	{
		g_player.pos.y -= 2.0f;
	}

}

PLAYER *GetPlayer(void)
{
	return &g_player;
}