#include "BaseApp.h"
#include "Window.h"
#include "CShape.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <cmath>

BaseApp::~BaseApp() {}

int BaseApp::run() {
	if (!init()) {
		ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
	}

	while (m_windowPtr->isOpen()) {
		m_windowPtr->handleEvents();
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

	m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
	if (m_ACircle) {
		m_ACircle->getComponent<CShape>()->createShape(CIRCLE);
		m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(899.f, 855.f));
		m_ACircle->getComponent<Transform>()->setScale(sf::Vector2f(2.f, 2.f));

		if (!resourceMan.loadTexture("sprites/mushroom", "png")) {
			MESSAGE("BaseApp", "Init", "cant load the texture")
		}
		m_ACircle->setTexture(resourceMan.getTexture("sprites/mushroom"));
	}

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
	m_currentWaypointIndex = 0;

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

	return true;
}

void BaseApp::update() {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->update();
	}

	if (!m_ACircle.isNull()) {
		m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

		if (m_currentWaypointIndex < m_waypoints.size()) {
			sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];
			float distanceToTarget = std::sqrt(
				std::pow(targetPos.x - m_ACircle->getComponent<Transform>()->getPosition().x, 2) +
				std::pow(targetPos.y - m_ACircle->getComponent<Transform>()->getPosition().y, 2)
			);

			if (distanceToTarget < 10.0f) {
				m_currentWaypointIndex++;
			}
			else {
				m_ACircle->getComponent<Transform>()->seek(targetPos, 100.f, m_windowPtr->deltaTime.asSeconds(), 10.f);
			}
		}
	}

	if (!m_ATrack.isNull()) {
		m_ATrack->update(m_windowPtr->deltaTime.asSeconds());
	}
}

void BaseApp::render() {
	if (!m_windowPtr) return;

	m_windowPtr->clear();

	if (m_shapePtr) {
		m_shapePtr->render(m_windowPtr);
	}

	if (m_ATrack) {
		m_ATrack->getComponent<CShape>()->render(m_windowPtr);
	}

	if (m_ACircle) {
		m_ACircle->getComponent<CShape>()->render(m_windowPtr);
	}

	m_windowPtr->display();
}

void BaseApp::destroy() {}
