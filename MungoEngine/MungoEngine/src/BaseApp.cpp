#include "BaseApp.h"


BaseApp::~BaseApp() {}

int BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp", "run", "Initialization failed. Please check method validations.");
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
    m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "MungoEngine");
    if (!m_windowPtr) {
        ERROR("BaseApp", "init", "Failed to create window pointer, check memory allocation");
        return false;
    }

    m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
    if (m_ACircle) {
        m_ACircle->getComponent<CShape>()->createShape(CIRCLE);
        m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::Red);
        m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(100.f, 150.f));
    }

    m_waypoints.push_back(sf::Vector2f(600.f, 150.f));
    m_waypoints.push_back(sf::Vector2f(400.f, 300.f));
    m_waypoints.push_back(sf::Vector2f(300.f, 200.f));
    m_waypoints.push_back(sf::Vector2f(300.f, 150.f));

    m_currentWaypointIndex = 0;

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
                m_ACircle->getComponent<Transform>()->seek(
                    targetPos, 100.f, m_windowPtr->deltaTime.asSeconds(), 10.f);
            }
        }
    }
}

void BaseApp::render() {
    if (!m_windowPtr) return;

    m_windowPtr->clear();

    if (m_shapePtr) m_shapePtr->render(m_windowPtr);
    if (m_ACircle)  m_ACircle->render(m_windowPtr);

    m_windowPtr->display();
}

void BaseApp::destroy() {}
