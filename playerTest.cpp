//=============================================================================
//
// �v���C���[���� [playerTest.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "playerTest.h"
#include "controller.h"
#include "input.h"
#include "file.h"
#include "bullet.h"
#include "checkhit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_HP	(6)
#define PLAYER_TIME_SHOT	(5)
#define MAX_DIFFUSE	(255)
#define PLAYER_INVINCIVLE	(10)
#define PLAYER_MOVE_SPEED	(2.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(VERTEX_2D *Vtx, int cntPattern);
void SetVertexPlayer(VERTEX_2D *Vtx);
void animPlayerState(int * animState);

void Invincible(void);

void FallPlayer(void);
void JumpPlayer(void);
//void IdlePlayer(void);
void AttackPlayer(void);
void PlayerMoving(void);

void Restriction(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture[STATE_MAX] = { NULL };	// �e�N�X�`���ւ̃|���S��

static PLAYER					g_player;		// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	{
		// �A�C�h�����
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PLAYER_IDLE,				// �t�@�C���̖��O
			&g_pD3DTexture[IDLE]);				// �ǂݍ��ރ������[

		// �ړ�
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PLAYER_RUN,					// �t�@�C���̖��O
			&g_pD3DTexture[RUN]);				// �ǂݍ��ރ������[

		// �W�����v
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PLAYER_JUMP,				// �t�@�C���̖��O
			&g_pD3DTexture[JUMP]);				// �ǂݍ��ރ������[
	}

	g_player.invincible = false;									// ���G��Ԃł͂Ȃ�
	g_player.pos = D3DXVECTOR3(/*i*200.0f + */200.0f, 300.0f, 0.0f);// ���W�f�[�^��������
	g_player.mapPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �}�b�v���W�f�[�^��������
	g_player.scrollPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �X�N���[�����W�f�[�^��������
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
	g_player.moveSpeed = PLAYER_MOVE_SPEED;

	// �A�j���p�^�[���ԍ��������_���ŏ�����
	g_player.animeCnt.PatternAnim = rand() % PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_X;	

	g_player.textureSize = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);
	g_player.state = IDLE;
	g_player.Texture = g_pD3DTexture[IDLE];
	g_player.animeCnt.CountAnim = 0;								// �A�j���J�E���g��������
	g_player.countShot = PLAYER_TIME_SHOT;							// �ŏ��̈ꔭ�͂������Ă�悤��
	g_player.countInvincible = 0;									// ���G�J�E���g��������
	g_player.hp = PLAYER_HP;										// HP�̏�����
	D3DXVECTOR2 temp = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);
	g_player.radius = D3DXVec2Length(&temp);									// ���a��������
	g_player.baseAngle = atan2f(PLAYER_TEXTURE_SIZE_Y, PLAYER_TEXTURE_SIZE_X);	// �p�x��������

	g_player.jumpForce = 0;										// �W�����v���Ă��Ȃ�
	g_player.dropSpeed = 0;	// �d�͉����x������
	g_player.ofsPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �I�t�Z�b�g���W��������
	g_player.direction = Right;										// �v���C���[�͉E����

	MakeVertexPlayer();

	if (FAILED(MakeVertexPlayer()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < STATE_MAX; i++)
	{
		if (g_pD3DTexture[i] != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (g_player.use)
	{
		if (g_player.hp <= 0 || g_player.pos.y > SCREEN_HEIGHT + PLAYER_TEXTURE_SIZE_Y * 5)
		{
			g_player.use = false;
		}

		g_player.countShot++;			// �A�˂̃J�E���g�p
		g_player.scrollPos.x = 0.0f;	// ��ʃX�N���[���p�̕ϐ�

		Invincible();
		if (g_player.jumpForce == 0)	// �v���C���[���W�����v���Ă��Ȃ��Ɨ�����ԂɂȂ�
		{
			g_player.state = IDLE;
		}

		// �L�[���͂ňړ� 
		if (GetInput(JUMPMOVE))	// �W�����v�֌W
		{
			if (g_player.dropSpeed > 1 && g_player.jumpForce <= 1)	//�u�n�ォ��W�����v���Ă���̈�񂾂��󒆃W�����v�v�Ɓu���ꂩ�玩�R��������̈�񂾂��󒆃W�����v�v�����邽�߂̔���
			{
				g_player.dropSpeed = 0;	//�d�͉����x��0�ɂ��邱�ƂŁA�Ăуv���C���[���㏸���͂��߂�
				g_player.jumpForce++;	// ��������jump++�ƍ��킹��jump��2�ȏ�ɂȂ�̂ŁA�ǂ̂悤�ȃ^�C�~���O�ł��u�󒆃W�����v��̓W�����v�ł��Ȃ��v
										// SE�Đ�
				//PlaySound(SOUND_LABEL_SE_jump2);
				//playerWk[1].use = true;
			}
			else
			{
				//PlaySound(SOUND_LABEL_SE_jump);
			}

			g_player.jumpForce++;		// �W�����v�̐؂�ւ��A1�ȏ�ŃW�����v��ԂɂȂ�
			g_player.state = JUMP;		// �e�N�X�`���́u�W�����v�v
		}

		PlayerMoving();

		g_player.mapPos += g_player.scrollPos;	// �ǂꂾ���X�N���[����������ێ��A�C�x���g�Ɏg�p

		Restriction();
		JumpPlayer();
		FallPlayer();

		animPlayerState(&g_player.state);
		AttackPlayer();

		SetVertexPlayer(g_player.vertexWk);
		SetTexturePlayer(g_player.vertexWk, g_player.animeCnt.PatternAnim);
	}
}

//=============================================================================
// �v���C���[�̖��G��Ԃ̊m�F
//=============================================================================
void Invincible(void)
{
	if (g_player.invincible == true)
	{
		g_player.countInvincible++;

		if (g_player.countInvincible >= PLAYER_INVINCIVLE)
		{
			g_player.invincible = false;
			g_player.countInvincible = 0;
		}
	}
}

//=============================================================================
// �v���C���[�ړ�
//=============================================================================
void PlayerMoving(void)
{
	// �E�ړ�----------------------------------------
	if (GetInput(RIGHTMOVE))
	{
		g_player.pos.x += g_player.moveSpeed;
		if (g_player.pos.x >= SCREEN_WIDTH / 2)	// �v���C���[����ʒ����ӂ�ɗ�����X�e�[�W���̂��X�N���[������
		{
			//if (playerWk[0].pos_MAP.x < boss->initialpos.x - SCREEN_CENTER_X - MAPCHIP_TEXTURE_SIZE_X - 3.0f)
			{
				g_player.scrollPos.x += g_player.moveSpeed;
			}
		}

		g_player.direction = Right;					// ���ړ�
		g_player.keyPressing = true;				// 
		g_player.state = RUN;						// �����j���Otrue

	}
	// ���ړ�-----------------------------------------
	else if (GetInput(LEFTMOVE))
	{
		g_player.pos.x -= g_player.moveSpeed;
		if (g_player.pos.x <= MAP_TEXTURE_SIZE_X * (SIZE_X / 2))	// �v���C���[����ʒ����ӂ�ɗ�����X�e�[�W���̂��X�N���[������
		{
			//if (playerWk[0].pos_MAP.x < boss->initialpos.x - SCREEN_CENTER_X - MAPCHIP_TEXTURE_SIZE_X - 3.0f)
			{
				g_player.scrollPos.x -= g_player.moveSpeed;
			}
		}

		g_player.direction = Left;					// ���ړ�
		g_player.keyPressing = true;				// 
		g_player.state = RUN;						// �����j���Otrue

	}
}


//=============================================================================
// �v���C���[�̗�������
//=============================================================================
void FallPlayer(void)
{
	MAP *mapchip = GetMapData();

	g_player.pos.y += g_player.dropSpeed * 1.0f;	// �����x�I�ɉ��ֈړ��A�d�͉����x
	g_player.dropSpeed++;

	for (int i = 0; i < (SIZE_X * SIZE_Y); i++)
	{
		if ((g_player.jumpForce < 1) || g_player.dropSpeed >= PLAYER_ACCELE)	// �u���b�N���ŃW�����v����ƃu���b�N��ӂɒ���t���o�O��}�����鏈��
		{
			if (CheckHitBB_MAP(g_player.pos, mapchip->pos, D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y),
				D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), g_player.moveSpeed) == TOP)	// �u���b�N�̏�ɗ����Ă���Ƃ�
			{
				g_player.dropSpeed = 0;		// �d�͉����x�����Z�b�g
				g_player.pos.y = mapchip->pos.y - MAP_TEXTURE_SIZE_Y - PLAYER_TEXTURE_SIZE_Y;	// �ォ��u���b�N�ɓ˂����ނƁA�u���b�N�̏�ɖ߂�
				g_player.jumpForce = 0;		// �W�����v�񐔂����Z�b�g
				g_player.rot.z = 0;			// ��]�W�����v�̉�]���Z�b�g
				break;
			}
		}
		mapchip++;
	}
}

//=============================================================================
// �v���C���[�̃W�����v����
//=============================================================================
void JumpPlayer(void)
{
	if (g_player.jumpForce >= 1)	//�W�����v�����瓙���ŏ㏸�B�������x�������x�I�ɑ�������̂Ŏ��Ԍo�߂ŗ�������
	{
		g_player.pos.y -= PLAYER_ACCELE;
		g_player.state = JUMP;		// �e�N�X�`���́u�W�����v�v

		g_player.textureSize = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);

	}

	/* ���n������W�����v���O�ɂ��ăW�����v��Ԃ���������B���̏�����FallPlayer���ɂ��� */
}


//=============================================================================
// �v���C���[�̍U��
//=============================================================================
void AttackPlayer(void)
{
	if (GetInput(ATTACK))
	{
		D3DXVECTOR3 pos = g_player.pos;
		if (g_player.countShot >= PLAYER_TIME_SHOT || g_player.jumpForce > 1)	// �A�˗p�̃J�E���g���K��l�𒴂��Ă��邩�A��i�W�����v���Ȃ�e����
		{
			//SetBullet(pos, g_player.direction, g_player.jumpForce);		// 
			g_player.countShot = 0;	// 

			//PlaySound(SOUND_LABEL_SE_shot2);
		}
	}
}

//=============================================================================
// �v���C���[�̃X�e�[�^�X�ɂ��e�N�X�`����ԕω�
//=============================================================================
void animPlayerState(int * animState)
{
	switch (*animState)
	{
	case IDLE:
		// Idle�A�j���[�V����
		g_player.Texture = g_pD3DTexture[IDLE];
		g_player.animeCnt.PatDivX = PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_X;
		g_player.animeCnt.PatDivY = PLAYER_IDLE_TEXTURE_PATTERN_DIVIDE_Y;
		g_player.animeCnt.AnimPatNum = PLAYER_IDLE_ANIM_PATTERN_NUM;
		g_player.animeCnt.TimeAnim = PLAYER_IDLE_TIME_ANIMATION;

		g_player.textureSize = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);
		break;

	case RUN:
		// Run�A�j���[�V����
		g_player.Texture = g_pD3DTexture[RUN];
		g_player.animeCnt.PatDivX = PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_X;
		g_player.animeCnt.PatDivY = PLAYER_RUN_TEXTURE_PATTERN_DIVIDE_Y;
		g_player.animeCnt.AnimPatNum = PLAYER_RUN_ANIM_PATTERN_NUM;
		g_player.animeCnt.TimeAnim = PLAYER_RUN_TIME_ANIMATION;

		g_player.textureSize = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);
		break;

	case JUMP:
		// Jump�A�j���[�V����
		g_player.Texture = g_pD3DTexture[JUMP];
		g_player.animeCnt.PatDivX = PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_X;
		g_player.animeCnt.PatDivY = PLAYER_JUMP_TEXTURE_PATTERN_DIVIDE_Y;
		g_player.animeCnt.AnimPatNum = PLAYER_JUMP_ANIM_PATTERN_NUM;
		g_player.animeCnt.TimeAnim = PLAYER_JUMP_TIME_ANIMATION;

		break;

	default:
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.use == true)			// �g�p���Ă����ԂȂ�`�悷��
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_player.Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_player.vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	g_player.vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	g_player.vertexWk[1].vtx = D3DXVECTOR3(100.0f + PLAYER_TEXTURE_SIZE_X, 100.0f, 0.0f);
	g_player.vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f + PLAYER_TEXTURE_SIZE_Y, 0.0f);
	g_player.vertexWk[3].vtx = D3DXVECTOR3(100.0f + PLAYER_TEXTURE_SIZE_X, 100.0f + PLAYER_TEXTURE_SIZE_Y, 0.0f);

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

	SetTexturePlayer(g_player.vertexWk, g_player.animeCnt.PatternAnim);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�ݒ�
//=============================================================================
void SetTexturePlayer(VERTEX_2D *Vtx, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % g_player.animeCnt.PatDivX;
	int y = cntPattern / g_player.animeCnt.PatDivX;
	float sizeX = 1.0f / g_player.animeCnt.PatDivX;
	float sizeY = 1.0f / g_player.animeCnt.PatDivY;

	if (g_player.direction == Right)
	{
		Vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		Vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		Vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		Vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
	else if (g_player.direction == Left)
	{
		Vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		Vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		Vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		Vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}

	// �c��HP�ɉ����ăv���C���[���Ԃ��Ȃ� && ���G���Ԓ��̓_��
	int nokoriHP = MAX_DIFFUSE / PLAYER_HP;
	int amari = MAX_DIFFUSE % PLAYER_HP;

	int flashing = (g_player.countInvincible + 1) % 2;

	Vtx[0].diffuse = D3DCOLOR_RGBA(255, (nokoriHP* g_player.hp) + amari, (nokoriHP* g_player.hp) + amari, flashing * 255);
	Vtx[1].diffuse = D3DCOLOR_RGBA(255, (nokoriHP* g_player.hp) + amari, (nokoriHP* g_player.hp) + amari, flashing * 255);
	Vtx[2].diffuse = D3DCOLOR_RGBA(255, (nokoriHP* g_player.hp) + amari, (nokoriHP* g_player.hp) + amari, flashing * 255);
	Vtx[3].diffuse = D3DCOLOR_RGBA(255, (nokoriHP* g_player.hp) + amari, (nokoriHP* g_player.hp) + amari, flashing * 255);

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(VERTEX_2D *Vtx)
{
	D3DXVECTOR3 pos = g_player.pos + g_player.ofsPos;

	// ���_���W�̐ݒ�

	Vtx[0].vtx.x = g_player.pos.x - cosf(g_player.baseAngle + g_player.rot.z) * g_player.radius;
	Vtx[0].vtx.y = g_player.pos.y - sinf(g_player.baseAngle + g_player.rot.z) * g_player.radius;
	Vtx[0].vtx.z = 0.0f;

	Vtx[1].vtx.x = g_player.pos.x + cosf(g_player.baseAngle - g_player.rot.z) * g_player.radius;
	Vtx[1].vtx.y = g_player.pos.y - sinf(g_player.baseAngle - g_player.rot.z) * g_player.radius;
	Vtx[1].vtx.z = 0.0f;

	Vtx[2].vtx.x = g_player.pos.x - cosf(g_player.baseAngle - g_player.rot.z) * g_player.radius;
	Vtx[2].vtx.y = g_player.pos.y + sinf(g_player.baseAngle - g_player.rot.z) * g_player.radius;
	Vtx[2].vtx.z = 0.0f;

	Vtx[3].vtx.x = g_player.pos.x + cosf(g_player.baseAngle + g_player.rot.z) * g_player.radius;
	Vtx[3].vtx.y = g_player.pos.y + sinf(g_player.baseAngle + g_player.rot.z) * g_player.radius;
	Vtx[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(void)
{
	return(&g_player);
}

//=============================================================================
// �v���C���[�̉��ړ��ŉ�ʊO��u���b�N���ђʂ��Ȃ����߂̏���
//=============================================================================
void Restriction(void)
{
	MAP *mapchip = GetMapData();
	//int *scene = GetScene();

	for (int j = 0; j < SIZE_X * SIZE_Y; j++)
	{

		switch (CheckHitBB_MAP(g_player.pos, mapchip->pos, D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y),
			D3DXVECTOR2(MAP_TEXTURE_SIZE_X, MAP_TEXTURE_SIZE_Y), g_player.moveSpeed))	// �u���b�N�̂ǂ��ɐG��Ă��邩
		{
		case LEFT_MAPCHIP:
			g_player.pos.x = mapchip[j].pos.x - MAP_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X;	// ������u���b�N�ɓ˂����ނƃu���b�N�̍��ɖ߂�
			break;
		case RIGHT_MAPCHIP:
			g_player.pos.x = mapchip[j].pos.x + MAP_TEXTURE_SIZE_X + PLAYER_TEXTURE_SIZE_X;	// �E����u���b�N�ɓ˂����ނƃu���b�N�̉E�ɖ߂�
			break;
		case UNDER:
			g_player.pos.y = mapchip[j].pos.y + MAP_TEXTURE_SIZE_Y + PLAYER_TEXTURE_SIZE_Y;	// ������u���b�N�ɓ˂����ނƃu���b�N�̉��ɖ߂�
			break;
		}
		mapchip++;
	}

	//if (*scene == SCENE_TUTORIAL || playerWk[0].pos_MAP.x >= boss->initialpos.x - SCREEN_CENTER_X - MAPCHIP_TEXTURE_SIZE_X - 3.0f)
	//{
	//	if (g_player.pos.x <= PLAYER_TEXTURE_SIZE_X)	//�`���[�g���A����&�{�X��͉�ʂ����ς��ɓ�������
	//	{
	//		g_player.pos.x = PLAYER_TEXTURE_SIZE_X;
	//	}

	//	if (g_player.pos.x >= SCREEN_WIDTH - PLAYER_TEXTURE_SIZE_X)	//�`���[�g���A����&�{�X��͉�ʂ����ς��ɓ�������
	//	{
	//		g_player.pos.x = SCREEN_WIDTH - PLAYER_TEXTURE_SIZE_X;
	//	}

	//}
	/*else*/
	{
		if (g_player.pos.x <= MAP_TEXTURE_SIZE_X * (SIZE_X / 2))	//��ʍ���荶�ɍs���Ȃ��悤�ɂ���
		{
			g_player.pos.x = MAP_TEXTURE_SIZE_X * (SIZE_X / 2);
		}

		if (g_player.pos.x >= SCREEN_WIDTH / 2)	//��ʒ������E�ɍs���Ȃ��悤�ɂ���
		{
			g_player.pos.x = SCREEN_WIDTH / 2;
		}
	}
}

