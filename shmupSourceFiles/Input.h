//Input.h - the class that handles almost all input for the game - keys, mouse, joypad input.
#pragma once
#include "Includes.h"

namespace Advanced2D
{
	#define INPUT_DEADZONE (0.24f * FLOAT(0x7FFF))

	class Input
	{
		public:
			Input(HWND window,int numControllers);
			virtual ~Input();
			void Update();

			bool GetMouseButton(char button);
			long GetPosX()const {return position.x;}
			long GetPosY()const {return position.y;}
			long GetDeltaX()const {return mouseState.lX;}
			long GetDeltaY()const {return mouseState.lY;}
			long GetDeltaWheel()const {return mouseState.lZ;}

			char GetKeyState(int key)const {return keyState[key];}

			WORD GetButtons(int controller);
			BYTE GetLeftTrigger(int controller);
			BYTE GetRightTrigger(int controller);
			SHORT GetLeftStickX(int controller);
			SHORT GetLeftStickY(int controller);
			SHORT GetRightStickX(int controller);
			SHORT GetRightStickY(int controller);
		private:
			HWND window;
			IDirectInput8* di;
			IDirectInputDevice8* keyboard;
			XINPUT_STATE state[4];
			bool controllerConnected;
			unsigned char keyState[256];
			IDirectInputDevice8* mouse;
			DIMOUSESTATE mouseState;
			POINT position;
			int numControllers;
	};
};