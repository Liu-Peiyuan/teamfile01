//=============================================================================
//
// �}�b�v�t�@�C������ [map.h]
// Author : kitade mayumi
//
//=============================================================================

#include "main.h"

#define SIZE_X	(40)
#define SIZE_Y	(15)
#define MAP_MAXDATA	(4)
#define MAP_BONUS_MAXDATA	(4)

//#define MAP_TEXTURE_SIZE_BB_X			(16.0f/2.0f)		    // �e�N�X�`���T�C�Y
//#define MAP_TEXTURE_SIZE_BB_Y			(16.0f/2.0f)		    // ����

#define MAP_TEXTURE_SIZE_X			(16.0f)		    // �e�N�X�`���T�C�Y
#define MAP_TEXTURE_SIZE_Y			(16.0f)		    // ����
#define MAP_TEXTURE_PATTERN_DIVIDE_X	(2)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define MAP_TEXTURE_PATTERN_DIVIDE_Y	(2)			// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define MAP_TEXTURE_PATTERN_BOG_DIVIDE_X	(4)			// �D���̃e�N�X�`�����������iX)
#define MAP_TEXTURE_PATTERN_BOG_DIVIDE_Y	(4)			// �D���̃e�N�X�`�����������iY)
enum BLOCKTYPE
{
	BLOCK0,
	BLOCK1,
	BLOCK2,
	BLOCK3,
	BLOCK4,
	BLOCK5,
	BLOCK6,
	BLOCK7,
	BLOCK8,
	BLOCK9,
	BLOCK10,
	BLOCK11,
	BLOCK12,
	BLOCK13,
	GLASS14,
	GLASS15,
	BLOCK16,
	ITEM17,
	ITEM18,
	BOSS1,
	BOSS2,
	BOSS3,
	MAXTYPE
};

typedef struct
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				type;
	int				popCnt;						// ���Ƀ|�b�v����܂ł̃J�E���g
	float			countPos;
	D3DXVECTOR3		move;						// �|���S���̈ړ���

	bool			scroll;						// �X�N���[���̔���
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
}MAP;

MAP *GetMapData(void);
