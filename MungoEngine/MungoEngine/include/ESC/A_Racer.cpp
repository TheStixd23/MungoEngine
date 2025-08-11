#include "./A_Racer.h"
#include "./Transform.h"

/**
 * @brief Constructor de A_Racer.
 * @param name Nombre lógico del actor (aparece en jerarquía/depurador).
 */
A_Racer::A_Racer(const std::string& name)
    : Actor(name) {
}

/**
 * @brief Actualiza el estado del corredor.
 *
 * Sincroniza la posición lógica (`logicPosition`) con el componente
 * `Transform`, si está presente, y luego llama a `Actor::update()`
 * para procesar el resto de la lógica y componentes.
 *
 * @param deltaTime Tiempo transcurrido desde el último frame (en segundos).
 */
void
A_Racer::update(float deltaTime) {

    if (auto tr = getComponent<Transform>()) {
        tr->setPosition(sf::Vector2f(logicPosition.x, logicPosition.y));
    }
    Actor::update(deltaTime);
}
