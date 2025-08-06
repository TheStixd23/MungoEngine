#pragma once
#include "Actor.h"
#include <SFML/System/Vector2.hpp>

class A_Racer : public Actor {
public:
	A_Racer(const std::string& name);

	void update(float deltaTime) override;

	void setPlace(int newPlace);
	int getPlace() const;

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;

	void setSpeed(float s);
	float getSpeed() const;

	void setTarget(const sf::Vector2f& waypoint);
	sf::Vector2f getTarget() const;

	void enableSteering(bool enabled);
	void setArriveRadius(float radius);

protected:
	int place = 0;
	float speed = 100.f;
	sf::Vector2f logicPosition;
	sf::Vector2f logicTarget;
	bool steeringEnabled = true;
	float arriveRadius = 10.f;
};
