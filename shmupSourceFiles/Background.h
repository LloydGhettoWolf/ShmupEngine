//Background.h - this represents a layer of a scrolling background in the game - used to be an entity but not now
//as it is hard to control the 'layering' of background, sprites and foreground in the game in the app
//the way it is curretnly handled by the engine

#pragma once

#include "Sprite.h"
#include "Timer.h"


namespace Advanced2D
{

	enum Direction
	{UP = 0,LEFT,DOWN,RIGHT};

	class Background 
	{
		public:
			Background(int scrollDelay,int numTilesX,int numTilesY,int tileXSize,int tileYSize,bool isScrolling = false,
				bool wrap = false);
			virtual ~Background();

			bool Init(std::string filenames[]);
			void SetSpeed(float xSpeed,float ySpeed);
			void SetSpeedX(float xSpeed);
			void SetSpeedY(float ySpeed);
			void ScrollHorizontally(int xVal);
			void ScrollVertically(int yVal);

			void Start();
			void Stop();
			void Draw();
			void Update();

			//checks if the background can physically scroll anymore
			bool CanScroll(Direction dir)const;

		private:
			int maxYVal,maxXVal,tileXSize,tileYSize;
			float scrollSpeedX,scrollSpeedY;
			Sprite* backgroundTiles;
			int numTilesX,numTilesY,minDimension,maxDimension;
			bool wrap,isScrolling,canScrollLeft,canScrollRight,canScrollUp,canScrollDown;
			Timer scrollTimer;
			int scrollDelay;

	};
};