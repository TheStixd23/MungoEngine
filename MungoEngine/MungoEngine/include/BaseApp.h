#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include <vector>
#include <ESC/Actor.h>
#include "EngineGUI.h"
#include "./ESC/A_Racer.h"

class BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	int run();
	bool init();
	void update();
	void render();
	void destroy();

private:
	EngineUtilities::TSharedPointer<Window> m_windowPtr;
	EngineUtilities::TSharedPointer<Actor> m_ACircle;
	EngineUtilities::TSharedPointer<Actor> m_ATrack;

	std::vector<sf::Vector2f> m_waypoints;

	size_t m_currentWaypointIndex_Circle = 0;
	size_t m_currentWaypointIndex_NPC = 0;

	EngineGUI m_engineGUI;
	EngineUtilities::TSharedPointer<A_Racer> m_racerNPC;
};
