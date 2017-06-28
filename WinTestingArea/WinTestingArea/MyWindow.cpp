#include "MyWindow.h"

// ---- CONSTRUCTOR / DECONSTRUCTOR ----
MyWindow::MyWindow() {
	m_gsm.SetSize(10);
	m_gsm.addState("Init", 0);
	m_gsm.addState("Game", 1);
	m_gsm.addState("GameUI", 2);
	m_gsm.addState("Menu", 1);
	m_gsm.addState("Options", 1);
	m_gsm.addState("Background", 0);
	m_gsm.addState("SplashScreen", 1);
	m_gsm.SetState("Init");
}
MyWindow::~MyWindow() {
	TK_SAFE_DELETE(m_enemy);
	TK_SAFE_DELETE(m_enemy1);
}

// ---- KEY / MOUSE EVENTS ----
void MyWindow::OnKeyDown(UINT key) {

	if (key == VK_ESCAPE) {
		ply.Reset();
		m_gsm.SetState(2, "Menu", "Background");
	}
	for (int i = 0; i < m_gsm.Size(); i++) {
		if (m_gsm.GetState()[i] == NULL) break;
		if (m_gsm.GetState()[i] == TK_HASH("Game")) { ply.OnKeyDown(key); }
	}
}
void MyWindow::OnKeyUp(UINT key) {
	for (int i = 0; i < m_gsm.Size(); i++) {
		if (m_gsm.GetState()[i] == NULL) break;
		if (m_gsm.GetState()[i] == TK_HASH("Game")) { ply.OnKeyUp(key); }
	}
}
void MyWindow::OnMouseDown(int x, int y, UINT param) {
	for (int i = 0; i < m_gsm.Size(); i++) {
		if (m_gsm.GetState()[i] == NULL) break;
		if (m_gsm.GetState()[i] == TK_HASH("Menu")) {
			RECT mousePos = { x - 1, y - 1, x + 1, y + 1 };
			if (tk::graphics::Rect::IntersectBox(mousePos, m_start_rect)) {
				m_gsm.SetState(3, "Game", "GameUI", "Background");
			}
			else if (tk::graphics::Rect::IntersectBox(mousePos, m_options_rect)) {
				m_gsm.SetState(2, "Options", "Background");
			}
			else if (tk::graphics::Rect::IntersectBox(mousePos, m_exit_rect)) {
				PostQuitMessage(0);
			}
		}
	}
}

// ---- WINDOW UPDATE ----
void MyWindow::Update(double deltaTime) {
	Window::Update(deltaTime);
	m_timer.calcFPS();

	TK_UPDATE_RECT(hwnd(), NULL);
}
void MyWindow::OnPaint(HDC hdc) {
	SelectObject(hdc, TK_BRUSH_BLACK);
	PatBlt(hdc, 0, 0, ScreenRectWidth(), ScreenRectHeight(), PATCOPY);
	SelectObject(hdc, TK_BRUSH_WHITE);

	TK_UPDATE_RECT(hwnd(), NULL);
}

void MyWindow::GSMUpdate(double deltaTime) {
	for (int i = 0; i < m_gsm.Size(); i++) {
		if (m_gsm.GetState()[i] == NULL) return;
		if (m_gsm.GetState()[i] == TK_HASH("Init")) { Init(); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("Game")) { Game(deltaTime); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("Menu")) { Menu(deltaTime); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("GameUI")) { GameUI(deltaTime); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("Options")) { Options(deltaTime); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("Background")) { Background(deltaTime); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("SplashScreen")) { SplashScreen(deltaTime); continue; }
	}
}
void MyWindow::GSMDraw(HDC hdc) {
	for (int i = 0; i < m_gsm.Size(); i++) {
		if (m_gsm.GetState()[i] == NULL) return;
		if (m_gsm.GetState()[i] == TK_HASH("Init")) { continue; }
		if (m_gsm.GetState()[i] == TK_HASH("Game")) {
			Game(hdc); continue;
		}
		if (m_gsm.GetState()[i] == TK_HASH("Menu")) { Menu(hdc); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("GameUI")) {
			GameUI(hdc); continue;
		}
		if (m_gsm.GetState()[i] == TK_HASH("Options")) { Options(hdc); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("Background")) { Background(hdc); continue; }
		if (m_gsm.GetState()[i] == TK_HASH("SplashScreen")) { SplashScreen(hdc); continue; }
	}
}

// ---- UPDATING ----
void MyWindow::Init() {

	m_title.SetFont(72);
	m_start.SetFont(46);
	m_options.SetFont(46);
	m_exit.SetFont(46);

	m_score = 0;
	comp_stats = ""; dev_version = "";
	ply_pos = ""; ply_score = ""; enemy_stats = ""; ply_stats = "";
	m_enemys.push_back(m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY));

	m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
	m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
	m_enemy1->rect() = tk::graphics::Rect(75, 75, 100, 100);

	m_gsm.SetState(2, "SplashScreen", "Background");
}
void MyWindow::Menu(double deltaTime) {
	m_title_rect = { 0, 50, ScreenRectWidth(), 60 };
	m_exit_rect = { 0, 400, ScreenRectWidth(), 60 };
	m_start_rect = { 0, 200, ScreenRectWidth(), 60 };
	m_options_rect = { 0, 300, ScreenRectWidth(), 60 };
}
void MyWindow::Options(double deltaTime) {
	v1 = mat * tk::math::Vec3{ -100, -100, 1 };
	v2 = mat * tk::math::Vec3{ 100, -100, 1 };
	v3 = mat * tk::math::Vec3{ 100,  100, 1 };
	v4 = mat * tk::math::Vec3{ -100,  100, 1 };

	mat.SetRotateZ((float)m_timer.elapsed() / 4);
	rect_1 = {
		tk::math::Vec2{ v1.x + ScreenRectWidth() / 2, v1.y + ScreenRectHeight() / 2 },
		tk::math::Vec2{ v2.x + ScreenRectWidth() / 2, v2.y + ScreenRectHeight() / 2 },
		tk::math::Vec2{ v3.x + ScreenRectWidth() / 2, v3.y + ScreenRectHeight() / 2 },
		tk::math::Vec2{ v4.x + ScreenRectWidth() / 2, v4.y + ScreenRectHeight() / 2 }
	};
}
void MyWindow::Game(double deltaTime) {
	ply.Update();
	ply.UpdatePlayer(deltaTime, ScreenRectWidth(), ScreenRectHeight());
	m_enemy->Update();
	m_enemy->UpdateEnemy(ply, deltaTime);
	m_enemy1->Update();

	if (tk::graphics::Rect::IntersectBox(m_enemy1->rect().convertRECT(), ply.rect().convertRECT())) {
		if (m_enemy->Health() > 0) m_enemy->Health(m_enemy->Health() - (10 * (float)deltaTime));
	}

	if (ply.Health() <= 0) {
		ply.Reset();
		m_gsm.SetState(2, "Menu", "Background");
	}
	if (m_enemy != nullptr) {
		if (m_enemy->Health() <= 0) {
			m_score++;
			ply.Fuel() += 10;
			ply.Health(ply.Health() + 25);

			TK_SAFE_DELETE(m_enemy);
			TK_SAFE_DELETE(m_enemy1);

			int i = (int)(rand() % 3);
			switch (i) {
			case 1:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY); break;
			case 2:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::MEDIUM);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::MEDIUM); break;
			case 3:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::HARD);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::HARD); break;
			default:
				m_enemy1 = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY);
				m_enemy = m_enemyFactory.CreateEnemy(game::EnemyFactory::EASY); break;
			}
			int randX = rand() % 750, randY = rand() % 550;
			m_enemy1->rect() = tk::graphics::Rect((float)randX - 25.f, (float)randY - 25.f, 100.f, 100.f);
			m_enemy->rect() = tk::graphics::Rect((float)randX, (float)randY, 50.f, 50.f);
		}
	}
}
void MyWindow::GameUI(double deltaTime) {
	ply_pos = (tk::String)"   x: " + ply.rect().x;
	ply_pos += (tk::String)"   y: " + ply.rect().y;
	ply_pos += (tk::String)"   Y_vel: " + ply.m_vel_y;
	ply_pos += (tk::String)"   X_vel: " + ply.m_vel_x;
	ply_score = (tk::String)"   Score: " + m_score;
	ply_score += (tk::String)"   Fuel: " + ply.Fuel();
	enemy_stats = (tk::String)"   Time: " + (int)m_enemy->Health();
	ply_stats = (tk::String)"   Health: " + (int)ply.Health();
}
void MyWindow::SplashScreen(double deltaTime) {
	m_title_rect = { 0, ScreenRectHeight() / 2 - 60, ScreenRectWidth(), 60 };
	if (m_timer.elapsed() > 3) {
		m_gsm.SetState(2, "Menu", "Background");
	}
}
void MyWindow::Background(double deltaTime) {
	comp_stats = (tk::String)"   FPS: " + m_timer.GetFPS();
	comp_stats += (tk::String)"   DT: " + deltaTime;
	comp_stats += (tk::String)"   Test: " + tk::math::Maths::sin(1);
	dev_version = m_version;
}

// ---- DRAWING ----
void MyWindow::Menu(HDC hdc) {
	/* ---- TITLE ---- */
	SetTextColor(hdc, RGB(200, 50, 50));
	m_title.Draw(hdc, "SPACE GAME", m_title_rect);

	/* ---- START ---- */
	SetTextColor(hdc, RGB(255, 255, 255));
	m_start.Draw(hdc, "START", m_start_rect);

	/* ---- OPTIONS ---- */
	m_options.Draw(hdc, "OPTIONS", m_options_rect);

	/* ---- EXIT ---- */
	m_exit.Draw(hdc, "EXIT", m_exit_rect);
}
void MyWindow::Options(HDC hdc) {
	rect_1.Draw(hdc, TK_PEN_WHITE);
}
void MyWindow::Game(HDC hdc) {
	m_enemy1->Draw(hdc, TK_PEN_BLUE);
	m_enemy->Draw(hdc, TK_PEN_RED);
	ply.Draw(hdc, TK_PEN_GREEN);
}
void MyWindow::GameUI(HDC hdc) {
	TextOut(hdc, 10, 30, ply_pos.data, ply_pos.length());
	TextOut(hdc, 10, 50, ply_score.data, ply_score.length());
	TextOut(hdc, (int)m_enemy->rect().x, (int)m_enemy->rect().y, enemy_stats.data, enemy_stats.length());
	TextOut(hdc, (int)ply.rect().x, (int)ply.rect().y, ply_stats.data, ply_stats.length());
}
void MyWindow::SplashScreen(HDC hdc) {
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(200, 50, 50));
	m_title.Draw(hdc, "SPACE GAME", m_title_rect);
}
void MyWindow::Background(HDC hdc) {
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 10, comp_stats.data, comp_stats.length());
	TextOut(hdc, 20, ScreenRectHeight() - 30, dev_version.data, dev_version.length());
}
