#pragma once
#include <tkWindow.h>
#include <tkHashMap.h>
#include <tkMacros.h>
#include <tkTree.h>
#include "EnemyFactory.h"
#include "tkGraphics.h"
#include "Player.h"


class MyWindow : public tk::win::Window {
public:
	MyWindow();
	~MyWindow();

	virtual bool OnCreate(HWND hwnd) { 
		return true;
	}

	virtual void OnKeyDown(UINT key);
	virtual void OnKeyUp(UINT key);
	virtual void OnMouseDown(int x, int y, UINT param);
	virtual void OnPaint(HDC hdc);

	virtual void Update(double deltaTime);

	void Init();

	void Menu(HDC hdc);
	void Options(HDC hdc);
	void Game(HDC hdc);
	void GameUI(HDC hdc);
	void SplashScreen(HDC hdc);
	void Background(HDC hdc);

	void Menu(double deltaTime);
	void Options(double deltaTime);
	void Game(double deltaTime);
	void GameUI(double deltaTime);
	void SplashScreen(double deltaTime);
	void Background(double deltaTime);

	virtual void GSMUpdate(double deltaTime);
	virtual void GSMDraw(HDC hdc);

	//virtual void GameStateUpdate(tk::String state, double deltaTime);
	//virtual void GameStateDraw(tk::String state, HDC hdc);
private:

	// Title Text
	tk::win::WinText m_title;
	RECT m_title_rect;

	// Start Text
	tk::win::WinText m_start;
	RECT m_start_rect;

	// Options Text
	tk::win::WinText m_options;
	RECT m_options_rect;

	// Exit Text
	tk::win::WinText m_exit;
	RECT m_exit_rect;

	/* ---- Options Stuff ---- */
	tk::math::Mat3 mat;
	tk::math::Vec3 v1;
	tk::math::Vec3 v2;
	tk::math::Vec3 v3;
	tk::math::Vec3 v4;
	Player ply;

	/* ---- Game ---- */
	tk::String ply_pos, ply_score, enemy_stats, ply_stats;
	tk::std::LinkedList<game::Enemy*> m_enemys;
	tk::String* gsm_game;
	game::Enemy* m_enemy1;
	game::Enemy* m_enemy;
	int m_score;

	/* ---- Dev Stuff ---- */
	tk::String comp_stats, dev_version;

	/* ---- TESTING ---- */
	game::EnemyFactory m_enemyFactory;
	tk::graphics::gRectange rect_1;
};