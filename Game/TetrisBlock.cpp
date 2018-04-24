#include "TetrisBlock.h"
#include "TetrisSprite.h"

namespace tetris
{
	TetrisBlock::TetrisBlock(TetrisBlockType _type, kodi::math::vec3 _position)
	{
		tetrisSprites.reserve(4 * sizeof(TetrisSprite *));
		switch (_type)
		{
		case TetrisBlockType::el_block:
			break;
		case TetrisBlockType::long_block:
			break;
		case TetrisBlockType::four_block:
			break;
		case TetrisBlockType::square_block:
			break;
		default:
			break;
		}

	}
}
