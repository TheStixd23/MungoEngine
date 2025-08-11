#include "Systems/PlayerInputSystem.h"
#include "ESC/Transform.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

/**
 * @brief Calcula la longitud (magnitud) de un vector 2D.
 * @param v Vector 2D.
 * @return Longitud del vector.
 */
static inline float vecLength(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief Normaliza un vector 2D.
 * @param v Vector 2D.
 * @return Vector normalizado. Si la longitud es muy pequeña, retorna (0,0).
 */
static inline sf::Vector2f vecNormalize(const sf::Vector2f& v) {
    float L = vecLength(v);
    if (L <= 1e-6f) return { 0.f, 0.f };
    return { v.x / L, v.y / L };
}

/**
 * @brief Actualiza el sistema de entrada del jugador.
 *
 * Llama a la rutina de control directo o de seguimiento de objetivo,
 * según el modo configurado en el jugador.
 *
 * @param dt Tiempo delta (en segundos) desde el último frame.
 */
void PlayerInputSystem::update(float dt) {
    if (!cfg.player) return;
    if (cfg.player->getControlMode() == PlayerControlMode::Direct) updateDirect(dt);
    else updateTargetSeek();
}

/**
 * @brief Procesa la entrada en modo de control directo (teclas WASD o flechas).
 *
 * Aplica aceleración en función de las teclas presionadas y fricción
 * cuando no hay entrada. Limita la velocidad máxima y actualiza
 * la posición y velocidad del jugador.
 *
 * @param dt Tiempo delta (en segundos) desde el último frame.
 */
void PlayerInputSystem::updateDirect(float dt) {
    sf::Vector2f a(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        a.y -= cfg.player->getAcceleration();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        a.y += cfg.player->getAcceleration();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        a.x -= cfg.player->getAcceleration();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        a.x += cfg.player->getAcceleration();

    auto v = cfg.player->getVelocity();
    v += a * dt;

    if (a.x == 0.f && a.y == 0.f) {
        v *= std::max(0.f, 1.f - cfg.player->getFriction() * dt);
    }

    float sp = vecLength(v);
    if (sp > cfg.player->getMaxSpeed()) v = vecNormalize(v) * cfg.player->getMaxSpeed();

    auto p = cfg.player->getPosition();
    p += v * dt;

    cfg.player->setVelocity(v);
    cfg.player->setPosition(p);
}

/**
 * @brief Procesa la entrada en modo de seguimiento de objetivo (TargetSeek).
 *
 * Si se hace clic izquierdo, establece el objetivo del jugador en
 * la posición del mouse en coordenadas de mundo.
 */
void PlayerInputSystem::updateTargetSeek() {
    if (!cfg.renderWindow) return;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        auto mp = sf::Mouse::getPosition(*cfg.renderWindow);
        auto world = cfg.renderWindow->mapPixelToCoords(mp);
        cfg.player->setTarget({ world.x, world.y });
    }
}
