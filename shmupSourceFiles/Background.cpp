//background.cpp
#pragma once

#include "Background.h"
#include "Advanced2D.h"

namespace Advanced2D
{
	Background::Background(int scrollDelay,int numTilesX,int numTilesY,int tileSzX,int tileSzY,bool scrolling,bool wrap) 
	{
		this->numTilesX = numTilesX;
		this->numTilesY = numTilesY;
		tileXSize = tileSzX;
		tileYSize = tileSzY;
		this->wrap = wrap;
		isScrolling = scrolling;
		maxXVal = numTilesX * tileXSize;
		maxYVal = numTilesY * tileYSize;
		this->scrollDelay = scrollDelay;

		if(numTilesX <= numTilesY)
		{
			maxDimension = numTilesY;
			minDimension = numTilesX;
		}
		else
		{
			maxDimension = numTilesX;
			minDimension = numTilesY;
		}
	}

	Background::~Background()
	{
		delete [] backgroundTiles;
	}

	bool Background::Init(std::string filenames[])
	{
		//create the array of sprite tiles for background
		backgroundTiles = new Sprite[numTilesX * numTilesY];

	
			//load the images and set their x/y values
			for(int tileAxis1 = 0; tileAxis1 < maxDimension; tileAxis1++)
			{
				for (int tileAxis2 = 0; tileAxis2 < minDimension; tileAxis2++)
				{
					int index = (tileAxis1 * minDimension) + tileAxis2;
					if(!backgroundTiles[index].LoadImg(filenames[index]))
					{
						g_engine->Message("Could not load image");
						return false;
					}

					if(numTilesX > numTilesY)
					{
						backgroundTiles[index].SetPosition(0 + tileAxis1 * tileXSize,0 - tileAxis2 * tileYSize);
					}
					else
					{
						backgroundTiles[index].SetPosition(0 + tileAxis2 * tileXSize,0 - tileAxis1 * tileYSize);
					}
				}
			}
		
		return true;
	}

	void Background::SetSpeed(float speedX,float speedY)
	{
		scrollSpeedX = speedX;
		scrollSpeedY = speedY;
	}

	void Background::SetSpeedX(float speedX)
	{
		scrollSpeedX = speedX;
	}

	void Background::SetSpeedY(float speedY)
	{
		scrollSpeedY = speedY;
	}

	void Background::ScrollHorizontally(int value)
	{
		if(value < 0 && !canScrollLeft) return;
		if(value > 0 && !canScrollRight) return;

		
		for(int tileAxis1 = 0; tileAxis1 < maxDimension; tileAxis1++)
		{
			for(int tileAxis2 = 0; tileAxis1 < minDimension; tileAxis2++)
			{
				int index = (tileAxis1 * minDimension) + tileAxis2;
				backgroundTiles[index].SetX(backgroundTiles[index].GetX() + value);
			}
		}
	}

	void Background::ScrollVertically(int value)
	{
		if(value < 0 && !canScrollUp) return;
		if(value > 0 && !canScrollDown) return;


		for(int tileAxis1 = 0; tileAxis1 < maxDimension; tileAxis1++)
		{
			for(int tileAxis2 = 0; tileAxis2 < minDimension; tileAxis2++)
			{
				int index = (tileAxis1 * minDimension) + tileAxis2;
				backgroundTiles[index].SetY(backgroundTiles[index].GetY() + value);
			}
		}
		
	}

	void Background::Update()
	{
		if(scrollTimer.StopWatch(scrollDelay))
		{
			//if the game is auto scrolling update the positions of all the tiles based on their
			//x/y speed vals


			if(isScrolling && canScrollUp && canScrollDown)
			{
				
				for(int tileAxis1 = 0; tileAxis1 < maxDimension; tileAxis1++)
				{
					for(int tileAxis2 = 0; tileAxis2 < minDimension; tileAxis2++)
					{
						int index = (tileAxis1 * minDimension) + tileAxis2;
						backgroundTiles[index].SetPosition(backgroundTiles[index].GetX() + scrollSpeedX,backgroundTiles[index].GetY() + scrollSpeedY);
					}
				}
				
			}

			//if the game is set to 'wrap' you will need to change the x/y values of the tiles appropriately
			if(wrap)
			{
				
					for(int tileAxis1 = 0; tileAxis1 < maxDimension; tileAxis1++)
					{
						for(int tileAxis2 = 0; tileAxis2 < minDimension; tileAxis2++)
						{
							int index = (tileAxis1 * minDimension) + tileAxis2;

							if(backgroundTiles[index].GetX() + tileXSize < 0)
							{
								backgroundTiles[index].SetX(backgroundTiles[index].GetX() + maxXVal);
							}

							if(backgroundTiles[index].GetY()  > g_engine->GetScreenHeight())
							{
								backgroundTiles[index].SetY(backgroundTiles[index].GetY() - maxYVal);
							}
						}//end for loop2

					}//end for loop1

			}//end if statement for wrap
			
			
			//need to check if scrolling any more is possible if wrap not enabled - and update
			//the boolean values accordingly
			else
			{
				if(backgroundTiles[0].GetX() <= 0) 
				{
					canScrollRight = false;
				}
				else
				{
					canScrollRight = true;
				}

				if(backgroundTiles[numTilesX].GetX() + tileXSize >= g_engine->GetScreenWidth()) 
				{
					canScrollLeft = false;
				}
				else
				{
					canScrollLeft = true;
				}

				if(backgroundTiles[numTilesY].GetY()  <= 0) 
				{
					canScrollDown = false;
				}
				else
				{
					canScrollDown = true;
				}

				if(backgroundTiles[0].GetY() + tileYSize <= g_engine->GetScreenHeight()) 
				{
					canScrollUp = false;
				}
				else
				{
					canScrollUp = true;
				}

			}
		}
	}


	void Background::Draw()
	{
		
		for(int tileAxis1 = 0; tileAxis1 < maxDimension; tileAxis1++)
		{
			for(int tileAxis2 = 0; tileAxis2 < minDimension; tileAxis2++)
			{
				int index = (tileAxis1 * minDimension) + tileAxis2;
				backgroundTiles[index].Draw();
			}
		}
		
	
	}

	void Background::Stop()
	{
		isScrolling = false;
	}

	void Background::Start()
	{
		isScrolling = true;
	}

	bool Background::CanScroll(Direction dir)const
	{
		switch(dir)
		{
		case UP:
			return canScrollUp;
			break;
		case LEFT:
			return canScrollLeft;
			break;
		case DOWN:
			return canScrollDown;
			break;
		case RIGHT:
			return canScrollRight;
			break;
		}
	}
};
