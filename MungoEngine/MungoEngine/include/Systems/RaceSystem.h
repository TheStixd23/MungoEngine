#pragma once
/**
 * @file RaceSystem.h
 * @brief Sistema que gestiona el progreso, vueltas y tiempos de los participantes en una carrera.
 *
 * Controla el conteo de vueltas, tiempos por vuelta, clasificación de corredores y
 * detección de pasos por checkpoints.
 *
 * @author Hannin Abarca
 */

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "Prerequisites.h"
#include "../ESC/Actor.h"
#include "../ESC/Transform.h"
#include "../Components/Lap.h"
#include "../ESC/A_Racer.h"
#include <vector>

 /**
  * @struct RaceConfig
  * @brief Configuración necesaria para inicializar un sistema de carreras.
  */
struct RaceConfig {
    std::vector<EngineUtilities::TSharedPointer<Actor>> actors; ///< Lista de actores participantes.
    const std::vector<sf::Vector2f>* waypoints = nullptr;       ///< Puntero a lista de waypoints del circuito.
    float checkpointRadius = 12.f;                              ///< Radio de detección de checkpoint.
};

/**
 * @class RaceSystem
 * @brief Gestiona el estado y la lógica de una carrera.
 *
 * Calcula posiciones relativas, vueltas completadas, tiempos por vuelta y
 * determina el orden de llegada de los participantes.
 */
class RaceSystem {
public:
    /**
     * @brief Constructor del sistema de carrera.
     * @param cfg Configuración inicial (actores, waypoints, radio de checkpoint).
     */
    RaceSystem(const RaceConfig& cfg);

    /** @brief Destructor por defecto. */
    ~RaceSystem() = default;

    /**
     * @brief Actualiza el estado de la carrera.
     * @param dt Tiempo transcurrido en segundos desde el último frame.
     */
    void update(float dt);

    /**
     * @brief Devuelve el orden actual de los corredores.
     * @return Vector con índices ordenados por posición en carrera.
     */
    std::vector<int> getStandings() const;

    /**
     * @brief Obtiene los datos de vuelta de un corredor específico.
     * @param i Índice del corredor.
     * @return Referencia a la estructura Lap correspondiente.
     */
    const Lap& getLapData(size_t i) const { return laps[i]; }

    /** @brief Activa o desactiva el conteo de tiempos. */
    void setTimingActive(bool b) { timingActive = b; }

    /** @brief Devuelve el tiempo actual de la vuelta del jugador. */
    float getPlayerCurrentLapTime() const { return playerLapTime; }

    /**
     * @brief Devuelve el mejor tiempo de vuelta del jugador.
     * @return Mejor tiempo en segundos o -1 si no existe.
     */
    float getPlayerBestLapTime() const { return (bestLapValid ? playerBestLap : -1.f); }

    /** @brief Indica si existe un mejor tiempo de vuelta válido. */
    bool hasBestLap() const { return bestLapValid; }

    /** @brief Arma o desarma el contador de vueltas. */
    void armLapCounter(bool armed);

    /** @brief Establece el índice del corredor que controla el conteo de vueltas. */
    void setLapOwnerIndex(int idx);

private:
    RaceConfig cfg;                  ///< Configuración de la carrera.
    std::vector<Lap> laps;            ///< Datos de vueltas por corredor.
    std::vector<float> progress;      ///< Progreso total en pista por corredor.
    std::vector<float> elapsed;       ///< Tiempo total por corredor.
    std::vector<float> lastS;         ///< Última posición medida en la pista (en metros).
    int lapOwnerIndex = 0;            ///< Índice del corredor que activa el conteo de vueltas.
    float lapDebounceSec = 0.35f;     ///< Tiempo mínimo entre detecciones de vuelta.
    float lapCooldown = 0.f;          ///< Temporizador interno para debounce.
    bool lapArmed = false;            ///< Indica si el sistema está listo para contar vuelta.
    bool timingActive = false;        ///< Indica si los tiempos están activos.
    float playerLapTime = 0.f;        ///< Tiempo de la vuelta actual del jugador.
    float playerBestLap = 0.f;        ///< Mejor tiempo de vuelta del jugador.
    bool bestLapValid = false;        ///< Bandera de validez del mejor tiempo.
    std::vector<float> prefix;        ///< Longitudes acumuladas de segmentos.
    float totalLen = 0.f;              ///< Longitud total del circuito.
    bool closedLoop = true;           ///< Indica si el circuito está cerrado.

    /** @brief Obtiene la posición mundial de un actor. */
    static sf::Vector2f getActorPos(const EngineUtilities::TSharedPointer<Actor>& a);

    /**
     * @brief Calcula el progreso a lo largo de un segmento.
     * @param p Posición a evaluar.
     * @param a Inicio del segmento.
     * @param b Fin del segmento.
     */
    float segProgress(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b) const;

    /**
     * @brief Calcula la distancia total recorrida sobre el circuito.
     * @param p Posición a evaluar.
     */
    float sAlongPath(const sf::Vector2f& p) const;

    /** @brief Construye las longitudes acumuladas del circuito. */
    void buildCircuitMeter();

    /**
     * @brief Calcula la distancia entre dos puntos.
     * @param A Punto A.
     * @param B Punto B.
     * @return Distancia en unidades del sistema (px o metros).
     */
    static float dist(const sf::Vector2f& A, const sf::Vector2f& B) {
        float dx = B.x - A.x, dy = B.y - A.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};
