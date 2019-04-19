#pragma once


namespace dae 
{
	struct Vec2
	{
		Vec2() : x(0), y(0){}
		Vec2(float xpos, float ypos) : x(xpos), y(ypos) {}
		Vec2(int xpos, int ypos) : x((float)xpos), y((float)ypos){}
		float x;
		float y; 
	};
	struct Line {
		Vec2 Pos1;
		Vec2 Pos2;
	};
	 enum Levels
	{
		DEMO, 
		Level1,
		Level2
	};

	 enum TileValue
	 {
		 Low, 
		 Mid, 
		 High, 
		 Max
	};

	 enum CmpType
	 {
		 allComps, 
		 posComp,
		 moveComp,
		 inputComp ,
		 AIComp,
		 textureComp,
		 textComp,
		 fpsComp, 
		 physicsComp

	 };
	 enum Orientation
	 {
		 Right = 0, 
		 Bottom = 1,
		 Left = 2, 
		 Top = 3
	 };
	 enum CollisionFlags 
	 {
		 NoCollision = 0,
		 Player = 1, 
		 Static = 2,
		 Enemy = 3
	 };
	
	 struct Tile
	 {
		 Vec2 Position; 
		 TileValue Value; 
		 bool isDug = false;
	 };
	 const float g_runspeed = 100.0f; 
	 const unsigned int g_empty_top_rows = 3; 
	 const unsigned int g_empty_bottom_rows = 1; 
	 const unsigned int g_scale = 2;
	 const unsigned int g_blocksize = g_scale * 16;
	 const unsigned int g_horizontal_blocks = 14;
	 const unsigned int g_vertical_blocks = 18;
	 const unsigned int g_vertical_map_blocks = g_vertical_blocks - g_empty_top_rows - g_empty_bottom_rows; 
	 const unsigned int g_width = g_horizontal_blocks * g_blocksize;
	 const unsigned int g_height = g_vertical_blocks * g_blocksize;
}