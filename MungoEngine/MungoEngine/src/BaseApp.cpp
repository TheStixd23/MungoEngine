#include "BaseApp.h"
#include "Window.h"
#include "CShape.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../include/BaseApp.h"

BaseApp::~BaseApp() {}

int BaseApp::run() {
	if (!init()) {
		ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations");
	}

	while (m_windowPtr->isOpen()) {
		m_windowPtr->handleEvents(m_engineGUI);
		update();
		render();
	}

	destroy();
	return 0;
}

bool BaseApp::init() {
	ResourceManager& resourceMan = ResourceManager::getInstance();

	m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "MungoEngine");
	if (!m_windowPtr) {
		ERROR("BaseApp", "init", "Failed to create window pointer, check memory allocation");
		return false;
	}

	m_engineGUI.init(m_windowPtr);

	m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
	if (m_ACircle) {
		m_ACircle->getComponent<CShape>()->createShape(CIRCLE);
		m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(899.f, 855.f));
		m_ACircle->getComponent<Transform>()->setScale(sf::Vector2f(2.f, 2.f));

		if (!resourceMan.loadTexture("sprites/mushroom", "png")) {
			MESSAGE("BaseApp", "Init", "cant load the texture");
		}
		m_ACircle->setTexture(resourceMan.getTexture("sprites/mushroom"));
	}

	m_ATrack = EngineUtilities::MakeShared<Actor>("Track Actor");
	if (m_ATrack) {
		m_ATrack->getComponent<CShape>()->createShape(RECTANGLE);
		m_ATrack->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_ATrack->getComponent<Transform>()->setPosition(sf::Vector2f(450.f, 0.f));
		m_ATrack->getComponent<Transform>()->setScale(sf::Vector2f(10.f, 19.5f));

		if (!resourceMan.loadTexture("sprites/Track", "png")) {
			MESSAGE("BaseApp", "Init", "cant load the texture");
		}
		m_ATrack->setTexture(resourceMan.getTexture("sprites/Track"));
	}

	m_racerNPC = EngineUtilities::MakeShared<A_Racer>("NPC_1");
	if (m_racerNPC) {
		m_racerNPC->getComponent<CShape>()->createShape(CIRCLE);
		m_racerNPC->getComponent<CShape>()->setFillColor(sf::Color::Green);
		m_racerNPC->getComponent<Transform>()->setScale(sf::Vector2f(2.f, 2.f));

		if (!resourceMan.loadTexture("sprites/mushroom", "png")) {
			MESSAGE("BaseApp", "Init", "cant load the texture");
		}
		m_racerNPC->setTexture(resourceMan.getTexture("sprites/mushroom"));

		m_racerNPC->setSpeed(120.f);
		m_racerNPC->setPosition(sf::Vector2f(999.f, 955.f));
		m_racerNPC->setTarget(sf::Vector2f(1320.f, 855.f));
	}

	m_currentWaypointIndex_NPC = 0;

	m_waypoints.clear();
	m_waypoints.push_back(sf::Vector2f(1320.f, 855.f));
	m_waypoints.push_back(sf::Vector2f(1320.f, 600.f));
	m_waypoints.push_back(sf::Vector2f(1100.f, 400.f));
	m_waypoints.push_back(sf::Vector2f(750.f, 350.f));
	m_waypoints.push_back(sf::Vector2f(600.f, 470.f));
	m_waypoints.push_back(sf::Vector2f(550.f, 700.f));
	m_waypoints.push_back(sf::Vector2f(750.f, 850.f));
	m_waypoints.push_back(sf::Vector2f(950.f, 950.f));
	m_waypoints.push_back(sf::Vector2f(1320.f, 855.f));

	return true;
}

void BaseApp::update() {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->update();
	}
	m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);

	ImGui::ShowDemoWindow();

	if (!m_ACircle.isNull()) {
		m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

		if (m_currentWaypointIndex_Circle < m_waypoints.size()) {
			sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex_Circle];
			sf::Vector2f currentPos = m_ACircle->getComponent<Transform>()->getPosition();

			float dx = targetPos.x - currentPos.x;
			float dy = targetPos.y - currentPos.y;
			float distanceToTarget = std::sqrt(dx * dx + dy * dy);

			if (distanceToTarget < 10.0f) {
				m_currentWaypointIndex_Circle++;
			}
			else {
				m_ACircle->getComponent<Transform>()->seek(
					targetPos,
					100.f,
					m_windowPtr->deltaTime.asSeconds(),
					10.f
				);
			}
		}
	}

	if (m_racerNPC) {
		m_racerNPC->update(m_windowPtr->deltaTime.asSeconds());

		sf::Vector2f npcPos = m_racerNPC->getPosition();
		sf::Vector2f target = m_waypoints[m_currentWaypointIndex_NPC];

		float dx = target.x - npcPos.x;
		float dy = target.y - npcPos.y;
		float distance = std::sqrt(dx * dx + dy * dy);

		if (distance < 10.0f) {
			m_currentWaypointIndex_NPC++;
			if (m_currentWaypointIndex_NPC >= m_waypoints.size())
				m_currentWaypointIndex_NPC = 0;
			m_racerNPC->setTarget(m_waypoints[m_currentWaypointIndex_NPC]);
		}
	}

	if (!m_ATrack.isNull()) {
		m_ATrack->update(m_windowPtr->deltaTime.asSeconds());
	}
}

void BaseApp::render() {
	if (!m_windowPtr) return;

	m_windowPtr->clear();

	if (m_ATrack) {
		m_ATrack->getComponent<CShape>()->render(m_windowPtr);
	}
	if (m_ACircle) {
		m_ACircle->getComponent<CShape>()->render(m_windowPtr);
	}
	if (m_racerNPC) {
		m_racerNPC->getComponent<CShape>()->render(m_windowPtr);
	}

	m_windowPtr->render();
	m_engineGUI.render(m_windowPtr);
	m_windowPtr->display();
}

void BaseApp::destroy() {
	m_engineGUI.destroy();
}
