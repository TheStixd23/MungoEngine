#pragma once
/**
 * @file WaypointManager.h
 * @brief Clase encargada de almacenar y proveer una lista de waypoints para el sistema de navegación.
 *
 * Esta clase actúa como un contenedor simple de puntos de referencia (waypoints) en el mundo,
 * utilizados comúnmente en sistemas de IA para guiar actores a través de un circuito o recorrido.
 *
 * @author Hannin Abarca
 */

#include <vector>
#include <SFML/System/Vector2.hpp>

 /**
  * @class WaypointManager
  * @brief Administra una lista de puntos de referencia (waypoints) en coordenadas 2D.
  *
  * Ofrece métodos para establecer y consultar la secuencia de puntos que conforman un recorrido.
  */
class WaypointManager {
public:
    /**
     * @brief Asigna una nueva lista de waypoints.
     * @param pts Vector de puntos en coordenadas de mundo.
     *
     * Reemplaza cualquier lista previa de waypoints almacenada.
     */
    void setWaypoints(const std::vector<sf::Vector2f>& pts) {
        waypoints_ = pts;
    }

    /**
     * @brief Obtiene la lista actual de waypoints.
     * @return Referencia constante al vector de puntos en coordenadas de mundo.
     */
    const std::vector<sf::Vector2f>& waypoints() const { return waypoints_; }

private:
    /**
     * @brief Almacén interno de los puntos de referencia.
     */
    std::vector<sf::Vector2f> waypoints_;
};
