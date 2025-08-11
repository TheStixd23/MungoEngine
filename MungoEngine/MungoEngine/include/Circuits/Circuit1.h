#pragma once
/**
 * @file CircuitWaypoints.h
 * @brief Define y expone los puntos de control (waypoints) que conforman el circuito.
 *
 * Estos waypoints se usan para guiar a los corredores (jugador y NPCs) a lo largo de la pista.
 * La secuencia define la ruta cerrada que siguen los sistemas de seguimiento y de carrera.
 *
 * @author Hannin Abarca
 */

#include <SFML/System/Vector2.hpp>
#include <vector>

 /**
  * @brief Obtiene la lista constante de waypoints del circuito.
  *
  * Los puntos están definidos en coordenadas del mundo y se almacenan de forma estática,
  * por lo que siempre se devuelve la misma instancia (no se realizan copias).
  *
  * @return Referencia constante a un `std::vector<sf::Vector2f>` con los puntos del circuito.
  */
inline const std::vector<sf::Vector2f>& getCircuitWaypoints() {
    static const std::vector<sf::Vector2f> kCircuit = {
        {1134,432}, {1134,310}, {910,305}, {910,130}, {500,130},
        {500,500}, {680,500}, {890,435}, {890,820}, {700,820},
        {560,860}, {500,800}, {625,670}, {1132,670}, {1132,400}
    };
    return kCircuit;
}
