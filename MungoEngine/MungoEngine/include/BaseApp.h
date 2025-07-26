#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include <vector>
#include <ESC/Actor.h>

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
	EngineUtilities::TSharedPointer<CShape> m_shapePtr;
	EngineUtilities::TSharedPointer<Actor> m_ACircle;
	EngineUtilities::TSharedPointer<Actor> m_ATrack;

	std::vector<sf::Vector2f> m_waypoints;
	size_t m_currentWaypointIndex = 0;
};
