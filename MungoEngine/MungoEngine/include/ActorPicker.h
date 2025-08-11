#pragma once
/**
 * @file ActorPicker.h
 * @brief Utilidad para seleccionar un actor en la escena usando la posición del ratón.
 *
 * Proporciona un método estático para identificar el índice de un actor cuya forma
 * contenga la posición actual del cursor en coordenadas del mundo.
 *
 * @author Hannin Abarca
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include "./ESC/Actor.h"
#include "CShape.h"

 /**
  * @class ActorPicker
  * @brief Clase de utilidad para determinar qué actor está bajo el puntero del ratón.
  */
class ActorPicker {
public:
    /**
     * @brief Busca un actor bajo el cursor del ratón en la ventana indicada.
     *
     * Itera sobre todos los actores recibidos y verifica, a través de su componente
     * CShape, si el cursor (convertido a coordenadas de mundo) se encuentra dentro
     * de los límites globales de su forma.
     *
     * @param windowPtr Puntero a la ventana SFML para obtener la posición del ratón
     *                  y el sistema de coordenadas del mundo.
     * @param actors Lista de actores a verificar.
     * @return Índice del primer actor encontrado bajo el cursor, o -1 si ninguno coincide.
     */
    static int pickActorUnderMouse(sf::RenderWindow* windowPtr, const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*windowPtr);               ///< Posición del ratón en píxeles (ventana).
        sf::Vector2f mouseWorld = windowPtr->mapPixelToCoords(mousePos);          ///< Conversión a coordenadas del mundo.

        for (int i = 0; i < actors.size(); ++i) {                                 ///< Itera sobre todos los actores.
            auto shape = actors[i]->getComponent<CShape>();                       ///< Obtiene componente de forma.
            if (shape) {
                auto shapePtr = shape->getShapePtr();                              ///< Puntero a la forma SFML.
                if (shapePtr && shapePtr->getGlobalBounds().contains(mouseWorld)) {///< Verifica colisión con cursor.
                    return i;                                                      ///< Retorna índice del actor encontrado.
                }
            }
        }
        return -1;
    }
};
