//Advanced2D.cpp - implementation 
//LAST UPDATE 19/08/2011

#include <sstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "winMain.h"

namespace Advanced2D
{
	Engine::Engine()
	{
		srand(unsigned int(time(0)));
		p_maximizeProcessor = false;
		p_frameCountCore = 0;
		p_frameCountReal = 0;
		p_frameRateCore = 0;
		p_frameRateReal = 0;
		p_windowHandle = 0;
		p_pauseMode = false;
		p_versionMajor = VERSION_MAJOR;
		p_versionMinor = VERSION_MINOR;
		p_revision = REVISION;

		p_appTitle = "Advanced2D";
		p_screenWidth = 640;
		p_screenHeight = 480;
		p_colourDepth = 32;
		p_fullScreen = false;

		p_windowHandle = 0;
	}

	Engine::~Engine()
	{
		p_audio->StopAll();
		delete p_audio;
		delete p_input;
		delete p_collisionManager;
		if(p_device) p_device->Release();
		if(p_d3d) p_d3d->Release();
	}

	const std::string& Engine::GetVersionText()const
	{
		std::ostringstream s;
		s << "Advanced2D Engine v"<<p_versionMajor<<"."<<p_versionMinor<<"."<<p_revision;
		return s.str();
	}

	void Engine::Message(const std::string& message, const std::string& title)
	{
		MessageBox(0,message.c_str(),title.c_str(),0);
	}

	void Engine::FatalError(const std::string& message,const std::string& title)
	{
		Message(message,title);
		ShutDown();
	}

	int Engine::Init(int width,int height,int colourDepth,bool fullScreen,int numControllers)
	{
		p_screenHeight = height;
		p_screenWidth = width;
		p_fullScreen = fullScreen;
		p_colourDepth = colourDepth;
		p_numControllers = numControllers;


		//this below will all be moved into a renderer class in an update
		p_d3d = Direct3DCreate9(D3D_SDK_VERSION);

		if(p_d3d == NULL)
			return 0;

		D3DDISPLAYMODE dm;
		p_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dm);

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp,sizeof(d3dpp));
		d3dpp.Windowed = (!fullScreen);
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferFormat = dm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferWidth = p_screenWidth;
		d3dpp.BackBufferHeight = p_screenHeight;
		d3dpp.hDeviceWindow = p_windowHandle;

		p_d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			p_windowHandle,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&p_device);

		if(p_device == NULL) return 0;

		ClearScene(D3DCOLOR_XRGB(0,0,0));
		p_device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&p_backBuffer);

		p_device->SetRenderState(D3DRS_ZENABLE,TRUE);
		p_device->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		p_device->SetRenderState(D3DRS_LIGHTING,FALSE);

		HRESULT result = D3DXCreateSprite(p_device,&p_spriteHandler);
		if(result != D3D_OK) return 0;

		p_input = new Input(p_windowHandle,p_numControllers);
		p_audio = new Audio;
		p_collisionManager = new CollisionManager;

		if(!p_audio->Init()) 
		{   Message("Error init audio");
			return 0;
		}

		if(!GameInit(p_windowHandle)) 
		{	
			Message("Error init game");
			return 0;
		}
	

		return 1;

	}

	
	void Engine::ClearScene(D3DCOLOR colour)
	{
		p_device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,colour,1.0f,0);
	}


	int Engine::RenderStart()
	{
		if(!p_device)return 0;
		if(!p_device->BeginScene() != D3D_OK) return 0;
		return 1;
	}

	int Engine::RenderStop()
	{
		if(!p_device)return 0;
		if(p_device->EndScene()!=D3D_OK) return 0;
		if(p_device->Present(NULL,NULL,NULL,NULL) != D3D_OK) return 0;
		return 1;
	}

	int Engine::Render2DStart()
	{
		if(p_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND) != D3D_OK)
			return 0;
		else
			return 1;
	}

	int Engine::Render2DStop()
	{
		p_spriteHandler->End();
		return 1;
	}

	void Engine::ShutDown()
	{
		gameOver = true;
	}

	void Engine::Update(float dt)
	{
		static float t = 0.0f;

		//calculate framerate
		p_frameCountCore++;

		if(p_coreTimer.StopWatch(999))
		{
			p_frameRateCore = p_frameCountCore;
			p_frameCountCore = 0;
		}
		
		GameUpdate(dt);


		//collison
		if(!p_pauseMode && p_collisionTimer.StopWatch(70))
		{
			p_collisionManager->Update();
		}

		
		p_frameCountReal++;
		if(p_realTimer.StopWatch(999))
		{
			p_frameRateReal = p_frameCountReal;
			p_frameCountReal = 0;
		}

		//update controller states and update the engine
		p_input->Update();
		UpdateKeyboard();
		UpdateMouse();
		UpdateControllers();

		//update the audio system
		p_audio->Update();

		//now start rendering
		RenderStart();
		Render2DStart();
		GameRender2D();
		Render2DStop();
		RenderStop();

	}

	void Engine::UpdateKeyboard()
	{
		static char oldKeys[256];

		for(int key = 0; key < 255; key++)
		{
			if(p_input->GetKeyState(key) & 0x80)
			{
				GameKeyPress(key);
				oldKeys[key] = p_input->GetKeyState(key);
			}
			else if(oldKeys[key] & 0x80)
			{
				GameKeyRelease(key);
				oldKeys[key] = p_input->GetKeyState(key);
			}
		}
	}

	void Engine::UpdateMouse()
	{
		static int oldPosX = 0;
		static int oldPosY = 0;
		int deltaX = p_input->GetDeltaX();
		int deltaY = p_input->GetDeltaY();

		for(int button = 0; button < 3; button++)
		{
			if(p_input->GetMouseButton(button))
				GameMouseButton(button);

		}

		if(p_input->GetPosX() != oldPosX || p_input->GetPosY() != oldPosY)
		{
			GameMouseMove(p_input->GetPosX(),p_input->GetPosY());
			oldPosX = p_input->GetPosX();
			oldPosY = p_input->GetPosY();
		}

		if(deltaX != 0 ||deltaY)
		{
			GameMouseMotion(deltaX,deltaY);
		}

		int wheel = p_input->GetDeltaWheel();
		if(wheel != 0)
		{
			GameMouseWheel(wheel);
		}
	}

	void Engine::UpdateControllers()
	{
		static XINPUT_STATE oldStates[4];

		for(int controller = 0; controller < p_numControllers; controller++)
		{
			WORD buttons = p_input->GetButtons(controller);

			//use the fact that the values of the macros double to minimize code - e.g
			//XINPUT_GAMEPAD_A = 0x1000, XINPUT_GAMEPAD_B = 0x2000 etc
			//and use a similar strategy for the other buttons and thumbsticks

			for(int button = XINPUT_GAMEPAD_A; button <= XINPUT_GAMEPAD_Y; button *= 2)
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end face buttons buttons

			for(int button = XINPUT_GAMEPAD_START; button <= XINPUT_GAMEPAD_RIGHT_THUMB; button *= 2 )
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end 2nd set of face buttons

			for(int button = XINPUT_GAMEPAD_DPAD_UP; button <= XINPUT_GAMEPAD_DPAD_RIGHT; button *= 2 )
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end 3rd set of face buttons

			for(int button = XINPUT_GAMEPAD_LEFT_SHOULDER; button <= XINPUT_GAMEPAD_RIGHT_SHOULDER; button *= 2 )
			{
				if(buttons & button)
				{
					GamePadButtonPress(button);
					oldStates[controller].Gamepad.wButtons |= p_input->GetButtons(controller);
				}
				else if(oldStates[controller].Gamepad.wButtons & button)
				{
					GamePadButtonRelease(button);
					oldStates[controller].Gamepad.wButtons ^= button;
				}
			}//end 4th set of buttons

			
			SHORT stickValX = p_input->GetLeftStickX(controller);
			SHORT stickValY = p_input->GetLeftStickY(controller);

			GameLeftThumbstickMove(stickValX,stickValY);

			stickValX = p_input->GetRightStickX(controller);
			stickValY = p_input->GetRightStickY(controller);

			GameRightThumbstickMove(stickValX,stickValY);
		}//end controllers


	}

	void Engine::DealWithCollision(unsigned int ent1,unsigned ent2)
	{
		GameEntityCollision(ent1,ent2);
	}

	bool Engine::IsInScreen(Sprite* sprite)
	{
		Vector2 pos = sprite->GetPosition();

		float xPos = pos.GetX();
		float yPos = pos.GetY();

		if(xPos + sprite->GetWidth() < 0 || xPos > p_screenWidth ||
		   yPos + sprite->GetHeight() < 0 || yPos > p_screenHeight )
		   return false;

		return true;
	}


	void Engine::Close()
	{
		try
		{
			gameOver = true;
		}
		catch(...)
		{

		}

	}
};