//Sprite.h - The sprite class represents an entity that, shock horror, is a sprite! Can be initialised with an already loaded image or 
//handle the image loading itself
//Last update 15/08/11

#pragma once
#include "Vector2.h"
#include "Texture.h"
#include "Timer.h"

namespace Advanced2D
{


	class Sprite 
	{
		public:
			Sprite();
			virtual ~Sprite();
			bool LoadImg(std::string filename, D3DCOLOR transColour = D3DCOLOR_XRGB(255,0,255));
			void SetImage(Texture* img);
			virtual void Update();
			virtual void Draw();
			void Transform();

			const Vector2&	GetPosition()const {return position;}
			float			GetX()const {return position.GetX();}
			float			GetY()const {return position.GetY();}
			int				GetWidth() const {return width;}
			int				GetHeight()const {return height;}
			bool			IsVisible()const {return visible;}
			int				GetState()const {return state;}
			int				GetColumns()const {return animColumns;}
			const D3DCOLOR&	GetColour()const{return colour;}
			int				GetFrameTimer()const {return frameTimer;}
			int				GetCurrentFrame()const {return curFrame;}
			int				GetAnimationDirection()const {return animDir;}
			float			GetRotation()const {return rotation;}
			float			GetScale()const {return scaling;}
			bool			IsCollidable()const {return collidable;}

			void  SetPosition(const Vector2& pos){position = pos;}
			void  SetPosition(float x,float y){position.SetX(x);position.SetY(y);}
			void  SetX(float value){position.SetX(value);}
			void  SetY(float value){position.SetY(value);}
			void  SetWidth(int value){width = value;}
			void  SetHeight(int value){height = value;}
			void  SetVisiblity(bool value) {visible = value;}
			void  SetState(int value) {state = value;}
			void  SetColumns(int value) {animColumns = value;}
			void  SetColour(D3DCOLOR col) {colour = col;}
			void  SetFrameTimer(int value){frameTimer = value;}
			void  SetCurrentFrame(int value){curFrame = value;}
			void  SetAnimationDirection(int value){animDir = value;}
			void  SetRotation(float value){rotation = value;}
			void  SetScale(float value){scaling = value;}
			void  SetTotalFrames(int value) {totalFrames = value;}
			void  SetCollidability(bool value){collidable = value;}
			void  SetSize(int w,int h){width = w;height = h;}

		protected:
			bool visible;
			bool alive;
			int lifeTimeLength;
			Timer lifeTimeTimer;
			int objectType;
			Vector2 position;
			bool imageLoaded;
			int state;
			Texture *image;
			int width,height;
			int animColumns;
			int frameStart,frameTimer;
			bool collidable;
			int curFrame,totalFrames,animDir;
			float faceAngle;
			int animStartX,animStartY;
			float rotation,scaling;

			//this may have to be changed when movng rendering to another part of the engine
			D3DXMATRIX matRotate;
			D3DXMATRIX matScale;
			D3DCOLOR colour;

			//new update to the class - an array of AABBs for collision

			virtual void Animate();

	};
};