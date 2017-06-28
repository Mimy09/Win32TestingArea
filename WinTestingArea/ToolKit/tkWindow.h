// ################################################################## //
// ##							WINDOW							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 May 12 - AIE			   ## //
// ################################################################## //
#pragma once
#pragma warning(disable: 4008)
#pragma warning(disable: 4302)

/** Includes */
#include <Windows.h>
#include "tkException.h"
#include "tkObjectPool.h"
#include "tkHashTable.h"
//#include "tkIO.h"
#include "tkWinObjects.h"
#include "tkTimer.h"
#include "tkGSM.h"

/** Definitions */
#define TK_WinMain() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cCmdShow)
#define TK_WinProc() CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define TK_BtnWinProc() CALLBACK WinProcBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define TK_DEFWINPROC DefWindowProc(hwnd, msg, wParam, lParam)

#define TK_UPDATE_RECT(_hwnd_,_rect_) InvalidateRect(_hwnd_, _rect_, false);UpdateWindow(_hwnd_);

#define TK_MSG_EXIT -1
#define TK_MSG_UPDATE 0
#define TK_MSG_DISPATCH 1

#define TK_BRUSH_BLACK *m_brushPool.ReturnObjectIndex(0)
#define TK_BRUSH_WHITE *m_brushPool.ReturnObjectIndex(1)

#define TK_BRUSH_RED *m_brushPool.ReturnObjectIndex(2)
#define TK_BRUSH_GREEN *m_brushPool.ReturnObjectIndex(3)
#define TK_BRUSH_BLUE *m_brushPool.ReturnObjectIndex(4)

#define TK_BRUSH_YELLOW *m_brushPool.ReturnObjectIndex(5)
#define TK_BRUSH_PURPLE *m_brushPool.ReturnObjectIndex(6)
#define TK_BRUSH_CYAN *m_brushPool.ReturnObjectIndex(7)



#define TK_PEN_BLACK *m_penPool.ReturnObjectIndex(0)
#define TK_PEN_WHITE *m_penPool.ReturnObjectIndex(1)

#define TK_PEN_RED *m_penPool.ReturnObjectIndex(2)
#define TK_PEN_GREEN *m_penPool.ReturnObjectIndex(3)
#define TK_PEN_BLUE *m_penPool.ReturnObjectIndex(4)

#define TK_PEN_YELLOW *m_penPool.ReturnObjectIndex(5)
#define TK_PEN_PURPLE *m_penPool.ReturnObjectIndex(6)
#define TK_PEN_CYAN *m_penPool.ReturnObjectIndex(7)

namespace tk {
	namespace win {
		class Window {
		public:

			//##################################//
			// PUBLIC VARIABLES
			//##################################//
			//Stores the Bitmap of the whole screen to alow for double buffering 
			HBITMAP hBitmat;
			//The second HDC to swap to whilse double buffering 
			HDC memDC;
			//Screen Width
			int screenWidth = 0;
			//Screen Height
			int screenHeight = 0;



			//##################################//
			// CONSTRUCTOR
			//##################################//
			// Defalt constructor
			Window(){}
			// Defalt virtual deconstructor
			virtual ~Window() = 0 {}

			//##################################//
			// PUBLIC FUNCTIONS
			//##################################/

			/* ---- Create ----
			* #param className - Sets the class name of the WINCLASS 
			* #param winTitle - Sets the title of the main HWND window
			* #param winPos - Sets the position of the main HWND window */
			virtual void Create(tk::String className, tk::String winTitle, RECT winPos);
			
			/* ---- Show ---- 
			Sets the main HWND window to visable */
			virtual void Show();
			
			/* ---- Hide ----
			Set the main HWND window to hidden */
			virtual void Hide();

			/* ---- Run ---- 
			Runs the main message loop
			#return int (-1) - If WM_QUIT was posted
			#return int (0) - If all messages have been dispatched
			#return int (1) - If messages are being dispatched*/
			virtual int Run();

			/* ---- Update ----
			virtual Update loop
			#param deltaTime - The delta time of the app*/
			virtual void Update(double deltaTime);

			/* ---- RunWindow ----
			Runs the update loop for the window*/
			virtual void RunWindow();

			/* ---- ScreenRectWidth ----
			Gets the Screen width
			#return int - Returns the screen width*/
			virtual inline int ScreenRectWidth() { GetClientRect(m_hwnd, &m_rc); return m_rc.right - m_rc.left; }

			/* ---- ScreenRectHeight ----
			Gets the Screen height
			#return int - Returns the screen height*/
			virtual inline int ScreenRectHeight() { GetClientRect(m_hwnd, &m_rc); return m_rc.bottom - m_rc.top; }

			// Sets the WinProc as a friend of this class
			friend LRESULT TK_WinProc();

			/* ---- hwnd ----
			Gets the hwnd
			#return HWND - Returns the hwnd*/
			inline HWND hwnd() { return m_hwnd; }

			/* ---- UpdateTime ----
			Updates the prevTime of the deltaTime */
			inline void UpdateTime() { prevTime = m_timer.elapsed(); }

			void MessageSend(tk::String winClass, tk::String winName, UINT msg, ULONG dataMsg);
		protected:
			//##################################//
			// POLYMOPHIC FUNCTIONS
			//##################################//

			/* ---- OnCreate ----
			Called when the WM_CREATE message is dispatched
			#param hwnd - The window handle of the current window
			#return bool (true) - If no error in window
			#return bool (false) - If error in window*/
			virtual bool OnCreate(HWND hwnd) { return true; } // return false if error / close window


			/* ---- OnDestroy ----
			Called when the WM_DESTROY message is dispatched
			#defalt body - PostQuitMessage(0); */
			virtual void OnDestroy() { PostQuitMessage(0); }

			/* ---- OnClose ----
			Called when the WM_CLOSE message is dispatched*/
			virtual void OnClose() {}


			/* ---- OnPaint ----
			Called when the WM_PAINT message is dispatched
			#param hdc - The device context*/
			virtual void OnPaint(HDC hdc) {}
			
			/* ---- OnMessage ----
			Called when reciving a message
			#param param - The messgage that was recieved*/
			virtual void OnMessage( UINT message, ULONG dataMsg) {}
			
			// ---- MOUSE EVENTS ----
			virtual void OnMouseDown(int x, int y, UINT param) {}
			virtual void OnMouseUp(int x, int y, UINT param) {}
			virtual void OnMouseMove(int x, int y, UINT param) {}
			virtual void OnMouseDClick(int x, int y, UINT param) {}
			
			// ---- BUTTON EVENTS ----
			virtual void OnBtnClicked(HWND wndHandle) {}
			virtual void OnBtnDBClicked(HWND wndHandle) {}
			virtual void OnBtnPushed(HWND wndHandle) {}
			virtual void OnBtnUnpushed(HWND wndHandle) {}

			// ---- KEYBOARD EVENTS ----
			virtual void OnKeyDown(UINT key) {}
			virtual void OnKeyUp(UINT key) {}

			// ---- WINDOW EVENTS ----
			virtual void OnWindowMinamize() {}
			virtual void OnWindowMaximize() {}
			virtual void OnScreenSave(){}
			virtual void OnWindowMove(){}
			virtual void OnWindowStopMoving(){}
			virtual void OnWindowResize(){}

			// ---- GSM EVENTS ----
			virtual void GSMUpdate(double deltaTime) {}
			virtual void GSMDraw(HDC hdc) {}

			tk::std::ObjectPool<HPEN> m_penPool;
			tk::std::ObjectPool<HBRUSH> m_brushPool;
			tk::String m_version;
			tk::Timer m_timer;

			tk::GSM m_gsm;

		private:
			MSG m_msg;
			RECT m_rc;
			HWND m_hwnd;
			WNDCLASSEX m_wc;
			COPYDATASTRUCT pcds;

			//tk::IO m_versionFile;

			double prevTime = 0;
		};
	}
}