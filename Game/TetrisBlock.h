#pragma once
#include <vector>
#include "../Source/Math/vec3.h"


namespace tetris
{

	class TetrisSprite;

	enum TetrisBlockType
	{
		long_block,		/*___-*/
		square_block,	/* Naalugu spritelu*/
		four_block,		/*_|- laantidhi*/
		el_block		/*L laaga vundedhi.*/
	};

	/* A Class that contains several of square sprites combined into a shape in the Class Tetris Game. */
	class TetrisBlock
	{

	private:

		TetrisBlockType	type;
		std::vector<TetrisSprite *> tetrisSprites;

	public:

		TetrisBlock(TetrisBlockType _type, kodi::math::vec3 _position);

	};

}
