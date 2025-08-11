/**
 * @file SteeringSystem.cpp
 * @brief Implementación del sistema de steering (Seek, Arrive, Pursuit) para corredores.
 *
 * Actualiza la posición (lógica y Transform) de cada corredor según su modo de steering.
 * Incluye helpers vectoriales locales y funciones internas arrive_L y pursuit_L.
 *
 * @author Hannin Abarca
 */

#include "Systems/SteeringSystem.h"
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>

namespace {
    // Helpers vectoriales locales (suma, resta, escalado, longitud y normalización).
    inline sf::Vector2f vadd(const sf::Vector2f& a, const sf::Vector2f& b) { return { a.x + b.x, a.y + b.y }; }
    inline sf::Vector2f vsub(const sf::Vector2f& a, const sf::Vector2f& b) { return { a.x - b.x, a.y - b.y }; }
    inline sf::Vector2f vscale(const sf::Vector2f& a, float s) { return { a.x * s, a.y * s }; }
    inline float vlen(const sf::Vector2f& a) { return std::sqrt(a.x * a.x + a.y * a.y); }
    inline sf::Vector2f vnorm(const sf::Vector2f& a) {
        float L = vlen(a); if (L <= 1e-6f) return { 0.f,0.f }; return { a.x / L, a.y / L };
    }
}

/**
 * @brief Recorre los corredores y aplica el modo de steering configurado.
 * @param dt Tiempo transcurrido desde el último frame (segundos).
 *
 * - Seek: usa Transform::seek hacia el target.
 * - Arrive: calcula una velocidad proporcional a la distancia (desacelera al acercarse).
 * - Pursuit: predice la posición futura del objetivo; si no hay objetivo, hace Seek al target.
 */
void SteeringSystem::update(float dt) {
    for (auto& r : cfg.racers) {
        if (!r || !r->isSteeringEnabled()) continue;

        const float speed = r->getSpeed();
        const sf::Vector2f target = r->getTarget();
        auto tr = r->getComponent<Transform>();

        switch (r->getMode()) {
        case SteeringMode::Seek: {
            if (tr) {
                tr->seek(target, speed, dt, cfg.seekRange);
                r->setPosition(tr->getPosition());
            }
            break;
        }
        case SteeringMode::Arrive: {
            sf::Vector2f posL = r->getPosition();
            sf::Vector2f vel = arrive_L(posL, target, speed, r->getArriveRadius());
            posL = vadd(posL, vscale(vel, dt));
            r->setPosition(posL);
            if (tr) tr->setPosition(posL);
            break;
        }
        case SteeringMode::Pursuit: {
            sf::Vector2f posL = r->getPosition();
            if (auto t = r->getPursuitTarget().lock()) {
                sf::Vector2f vel = pursuit_L(*r, *t, speed, r->getMaxPrediction());
                posL = vadd(posL, vscale(vel, dt));
                r->setPosition(posL);
                if (tr) tr->setPosition(posL);
            }
            else if (tr) {
                tr->seek(target, speed, dt, cfg.seekRange);
                r->setPosition(tr->getPosition());
            }
            break;
        }
        }
    }
}

/**
 * @brief Cálculo de velocidad para modo Arrive (desaceleración dentro de arriveRadius).
 * @param pos Posición actual.
 * @param target Objetivo.
 * @param speed Velocidad máxima.
 * @param arriveRadius Radio dentro del cual se reduce la velocidad hasta cero en el objetivo.
 * @return Vector velocidad deseada (dirección y magnitud).
 */
sf::Vector2f SteeringSystem::arrive_L(const sf::Vector2f& pos,
    const sf::Vector2f& target,
    float speed, float arriveRadius) {
    sf::Vector2f toT = vsub(target, pos);
    float d = vlen(toT);
    if (d < 1e-4f) return { 0.f, 0.f };
    float s = (d < arriveRadius) ? speed * (d / std::max(1e-4f, arriveRadius)) : speed;
    return vscale(vnorm(toT), s);
}

/**
 * @brief Cálculo de velocidad para modo Pursuit (predicción limitada por maxPrediction).
 * @param self Corredor que persigue.
 * @param target Corredor objetivo.
 * @param speed Velocidad máxima del perseguidor.
 * @param maxPrediction Tiempo máximo de predicción (s).
 * @return Vector velocidad deseada hacia la posición futura estimada.
 */
sf::Vector2f SteeringSystem::pursuit_L(const A_Racer& self,
    const A_Racer& target,
    float speed, float maxPrediction) {
    sf::Vector2f toT = vsub(target.getPosition(), self.getPosition());
    float d = vlen(toT);
    float pred = std::min(maxPrediction, d / std::max(1.f, target.getSpeed()));
    sf::Vector2f futDir = vnorm(toT);
    sf::Vector2f fut = vadd(target.getPosition(), vscale(futDir, target.getSpeed() * pred));

    sf::Vector2f aim = vsub(fut, self.getPosition());
    float L = vlen(aim);
    if (L < 1e-4f) return { 0.f, 0.f };
    return vscale(vnorm(aim), speed);
}
