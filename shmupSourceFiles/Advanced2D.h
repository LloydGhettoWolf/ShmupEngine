//Advanced2D.h - this is the header file for the main engine in the game, all the hard work is done here and rendering is handled as well
//although a future version of the engine will move rendering into another class so that we can have rendering in directX or openGL
//Various external function declarations are made here in this file - without these being defined in the main app the game will not run!


//LAST UPDATE 24/08/11 - changed the timestep so that floats and dt are used to calculate positions

#pragma once
#include <lua.hpp>
#include "Includes.h"
#include "Timer.h"
#include "Input.h"
#include "Audio.h"
#include "Rect.h"
#include "CollisionManager.h"
#include "EntityManager.h"
#include "Sprite.h"


//version info
#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define REVISION 0
#define START_BUTTON_VALUE 0x1000

//external variables and functions
extern bool gameOver;

//main game init/shutdown and run functions,rendering calls
extern bool GamePreload();
extern bool GameInit(HWND);
extern void GameUpdate(float dt);
extern void GameEnd();
extern void GameRender2D();

//input handling functions - can be removed if you don't intend to use mouse input for example.
extern void GameKeyPress(int key);
extern void GameKeyRelease(int key);
extern void GameLeftThumbstickMove(SHORT stickValueX,SHORT stickValueY);
extern void GameRightThumbstickMove(SHORT stickValueX,SHORT stickValueY);
extern void GameLeftTrigger(BYTE trigVal);
extern void GameRightTrigger(BYTE trigVal);
extern void GamePadButtonPress(WORD buttons);
extern void GamePadButtonRelease(WORD buttons);
extern void GameMouseButton(int button);
extern void GameMouseMotion(int x,int y);
extern void GameMouseMove(int x,int y);
extern void GameMouseWheel(int wheel);

//Game dependent entity management code - the engine sends signals to these functions and then the
//resulting logic is handled in game
extern void GameEntityCollision(unsigned int objID1,unsigned int objID2);


namespace Advanced2D
{

	class Engine
	{
		public:
			Engine();
			virtual ~Engine();

			int Init(int width,int height,int colourDepth,bool fullScreen,int numControllers = 0);
			void Close();
			void Update(float dt);
			void ShutDown();
			void Message(const std::string& message, const std::string& title = "ADVANCED 2D");
			void FatalError(const std::string& message, const std::string& title = "FATAL ERROR");
			
			void ClearScene(D3DCOLOR colour);
			int Release();

			//accessors
			bool IsPaused() {return p_pauseMode;}
	
			//Direct 9 device stuff - in a future revision of the engine
			//this will be removed to make it graphics API independent
			LPDIRECT3DDEVICE9 GetDevice() const {return p_device;}
			LPDIRECT3DSURFACE9 GetBackBuffer() const {return p_backBuffer;}
			LPD3DXSPRITE GetSpriteHandler() const {return p_spriteHandler;}
			
			//Simple accessors for engine version info
			const std::string& GetAppTitle()const {return p_appTitle;}		
			HWND GetWindowHandle()const {return p_windowHandle;}
			int GetVersionMajor()const {return p_versionMajor;}
			int GetVersionMinor()const  {return p_versionMinor;}
			int GetRevison() {return p_revision;}
			const std::string& GetVersionText()const;
			
			//frame rate info accessors
			long GetFrameRateCore()const {return p_frameRateCore;}
			long GetFrameRateReal()const {return p_frameRateReal;}
			
			//app info accessors
			int GetScreenWidth()const {return p_screenWidth;}
			int GetScreenHeight()const {return p_screenHeight;}
			int GetColourDepth()const {return p_colourDepth;}
			bool GetFullScreen()const{return p_fullScreen;}
			bool GetMaximizeProcessor() {return p_maximizeProcessor;}
			int GetNumberControllers()const {return p_numControllers;}
			
			//Mutator
			//pause the game
			void SetPaused(bool value) {p_pauseMode = value;}

			//point the app window handle to the one passed in
			void SetWindowHandle(HWND hwnd) { p_windowHandle = hwnd;}
			
			//App dependent accessors for basic app info
			void SetAppTitle(const std::string& value) {p_appTitle = value;}
			void SetScreenWidth(int value) {p_screenWidth = value;}
			void SetScreenHeight(int value){p_screenHeight = value;}
			void SetColourDepth(int value) {p_colourDepth = value;}
			void SetFullScreen(bool value) {p_fullScreen = value;}
			
			void SetMaximizeProcessor(bool value) {p_maximizeProcessor = value;}

			//Set the number of controllers in the game
			void SetNumberControllers(int num) {p_numControllers = num;}
			
			//find out if an entity is in screen or not
			bool IsInScreen(Sprite* entity);

			void DealWithCollision(unsigned int ent1,unsigned int ent2);

			//public audio handler
			Audio* p_audio;
			CollisionManager* p_collisionManager;

		private:
			int p_versionMajor, p_versionMinor, p_revision;
			HWND p_windowHandle;

			//NOTE - will replace the below with a renderer
			LPDIRECT3D9 p_d3d;
			LPDIRECT3DDEVICE9 p_device;
			LPDIRECT3DSURFACE9 p_backBuffer;
			LPD3DXSPRITE p_spriteHandler;

			//app info
			std::string p_appTitle;
			bool p_fullScreen;
			int p_screenWidth;
			int p_screenHeight;
			int p_colourDepth;
			int p_numControllers;
			bool p_pauseMode;

			//framerate and processor info
			bool p_maximizeProcessor;
			Timer p_coreTimer;
			long p_frameCountCore;
			long p_frameRateCore;
			Timer p_realTimer;
			long p_frameCountReal;
			long p_frameRateReal;

			//timers for engine use
			Timer p_collisionTimer;
			Timer timedUpdate;
			

			//input handler for the input devices
			Input* p_input;

			//private functions for internal use by engine
			//input handling
			void UpdateKeyboard();
			void UpdateMouse();
			void UpdateControllers();

			//rendering
			int RenderStart();
			int RenderStop();
			int Render2DStart();
			int Render2DStop();
	};
};

extern Advanced2D::Engine* g_engine;
