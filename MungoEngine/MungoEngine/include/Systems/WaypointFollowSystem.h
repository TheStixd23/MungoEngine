#pragma once
/**
 * @file WaypointFollowSystem.h
 * @brief Sistema que gestiona el seguimiento de waypoints por corredores IA: lookahead, errores, ruido y desaceleración en curvas.
 * @author Hannin Abarca
 */

#include <vector>
#include <limits>
#include <random>
#include <algorithm>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "Prerequisites.h"
#include "../ESC/A_Racer.h"

 /**
  * @struct WaypointFollowConfig
  * @brief Parámetros de configuración para el seguimiento de waypoints.
  */
struct WaypointFollowConfig {
    /** @brief Corredores controlados por el sistema. */
    std::vector<EngineUtilities::TSharedPointer<A_Racer>> racers;
    /** @brief Ruta de la pista expresada como lista de waypoints. */
    const std::vector<sf::Vector2f>* waypoints = nullptr;
    /** @brief Distancia mínima para considerar alcanzado el waypoint y avanzar. */
    float arriveRadiusForAdvance = 12.f;
    /** @brief Retardo de reacción al cambiar de objetivo. */
    float reactionDelay = 0.18f;
    /** @brief Radio de ruido aleatorio aplicado al objetivo. */
    float waypointNoiseRadius = 8.f;
    /** @brief Cantidad de waypoints por delante que se usan como objetivo. */
    int   lookAhead = 1;
    /** @brief Probabilidad de cometer un “error” de elección de objetivo. */
    float mistakeProb = 0.05f;
    /** @brief Tiempo mínimo entre errores consecutivos. */
    float mistakeCooldown = 2.0f;
    /** @brief Ancho del corredor virtual para validar cruce de segmento. */
    float corridorWidth = 80.f;
    /** @brief Activa la reducción de velocidad en curvas. */
    bool  cornerSlowdownEnabled = true;
    /** @brief Ángulo (°) desde el cual empieza a reducir velocidad. */
    float cornerMinAngleDeg = 25.f;
    /** @brief Ángulo (°) a partir del cual se aplica la reducción máxima. */
    float cornerMaxAngleDeg = 95.f;
    /** @brief Factor mínimo de velocidad en curva cerrada. */
    float cornerMinFactor = 0.82f;
};

/**
 * @class WaypointFollowSystem
 * @brief Actualiza el objetivo de cada corredor para seguir la ruta, aplicando lookahead, errores, ruido y slowdown en curvas.
 */
class WaypointFollowSystem {
public:
    /**
     * @brief Crea el sistema con la configuración indicada.
     * @param cfg Referencia a la configuración (corredores, ruta y parámetros).
     */
    WaypointFollowSystem(const WaypointFollowConfig& cfg)
        : cfg(cfg),
        indices(cfg.racers.size(), 0),
        reactTimers(cfg.racers.size(), 0.f),
        mistakeTimers(cfg.racers.size(), 0.f),
        rng(std::random_device{}()),
        uni(-1.f, 1.f),
        uni01(0.f, 1.f) {
    }

    /** @brief Destructor por defecto. */
    ~WaypointFollowSystem() = default;

    /**
     * @brief Inicializa el índice y objetivo de cada corredor tomando el waypoint más cercano a su posición actual.
     */
    void primeFromPositions() {
        if (!cfg.waypoints || cfg.waypoints->empty()) return;
        const auto& W = *cfg.waypoints;
        for (size_t i = 0; i < cfg.racers.size(); ++i) {
            auto& r = cfg.racers[i];
            if (!r) continue;
            sf::Vector2f p = r->getPosition();
            float best = std::numeric_limits<float>::max();
            size_t bestIdx = 0;
            for (size_t k = 0; k < W.size(); ++k) {
                float d = length(W[k] - p);
                if (d < best) { best = d; bestIdx = k; }
            }
            indices[i] = bestIdx;
            reactTimers[i] = 0.f;
            mistakeTimers[i] = 0.f;
            r->setTarget(W[bestIdx]);
        }
    }

    /**
     * @brief Actualiza objetivos por corredor considerando distancia, lookahead, prob. de error, ruido y curva.
     * @param dt Tiempo transcurrido desde el último frame (s).
     */
    void update(float dt) {
        if (!cfg.waypoints || cfg.waypoints->empty()) return;
        const auto& W = *cfg.waypoints;
        if (W.empty()) return;

        for (size_t i = 0; i < cfg.racers.size(); ++i) {
            auto& r = cfg.racers[i];
            if (!r) continue;

            reactTimers[i] -= dt;
            if (reactTimers[i] > 0.f) continue;

            size_t idx = indices[i];
            size_t nextIdx = (idx + 1) % W.size();
            size_t nextNextIdx = (nextIdx + 1) % W.size();

            sf::Vector2f pos = r->getPosition();
            sf::Vector2f wp = W[idx];
            sf::Vector2f wpN = W[nextIdx];
            sf::Vector2f wpNN = W[nextNextIdx];

            sf::Vector2f seg = wpN - wp;
            float segLen2 = seg.x * seg.x + seg.y * seg.y;
            if (segLen2 <= 1e-4f) segLen2 = 1.f;

            int la = std::max(0, std::min(cfg.lookAhead, 2));
            size_t tgtIdx = (idx + static_cast<size_t>(la)) % W.size();
            sf::Vector2f target = W[tgtIdx];

            mistakeTimers[i] -= dt;
            if (mistakeTimers[i] <= 0.f && uni01(rng) < cfg.mistakeProb) {
                int sign = (uni01(rng) < 0.5f) ? -1 : 1;
                size_t wrong = (tgtIdx + W.size() + static_cast<size_t>(sign)) % W.size();
                target = W[wrong];
                mistakeTimers[i] = cfg.mistakeCooldown;
            }

            if (cfg.waypointNoiseRadius > 0.f) {
                target.x += uni(rng) * cfg.waypointNoiseRadius;
                target.y += uni(rng) * cfg.waypointNoiseRadius;
            }

            float d_to_wp = length(wp - pos);
            float d_to_target = length(target - pos);

            sf::Vector2f rel = pos - wp;
            float t = dot(rel, seg) / segLen2;
            float tClamped = std::max(0.f, std::min(1.f, t));

            sf::Vector2f proj = { wp.x + seg.x * tClamped, wp.y + seg.y * tClamped };
            float distToLine = length(proj - pos);

            bool crossedForward = (t > 0.6f) && (distToLine <= cfg.corridorWidth);
            bool shouldAdvance =
                (d_to_wp < cfg.arriveRadiusForAdvance) ||
                (d_to_target < (cfg.arriveRadiusForAdvance * 0.7f)) ||
                crossedForward;

            if (shouldAdvance) {
                indices[i] = (idx + 1) % W.size();
                reactTimers[i] = cfg.reactionDelay;
                size_t nidx = indices[i];
                size_t ntgt = (nidx + static_cast<size_t>(la)) % W.size();
                sf::Vector2f ntarget = W[ntgt];
                if (cfg.waypointNoiseRadius > 0.f) {
                    ntarget.x += uni(rng) * cfg.waypointNoiseRadius;
                    ntarget.y += uni(rng) * cfg.waypointNoiseRadius;
                }
                r->setTarget(ntarget);
            }
            else {
                r->setTarget(target);
            }

            if (cfg.cornerSlowdownEnabled) {
                sf::Vector2f v1 = normalize(wpN - wp);
                sf::Vector2f v2 = normalize(wpNN - wpN);
                float dotp = dot(v1, v2);
                dotp = std::max(-1.f, std::min(1.f, dotp));
                float angleRad = std::acos(dotp);
                float angleDeg = angleRad * 57.2957795f;

                float f = 1.f;
                if (angleDeg >= cfg.cornerMaxAngleDeg) {
                    f = cfg.cornerMinFactor;
                }
                else if (angleDeg <= cfg.cornerMinAngleDeg) {
                    f = 1.f;
                }
                else {
                    float tspan = (angleDeg - cfg.cornerMinAngleDeg) /
                        std::max(1.f, (cfg.cornerMaxAngleDeg - cfg.cornerMinAngleDeg));
                    f = 1.f + (cfg.cornerMinFactor - 1.f) * tspan;
                }

                float baseSpd = r->getSpeed();
                float limited = baseSpd * std::min(1.f, std::max(cfg.cornerMinFactor, f));
                if (limited < baseSpd) {
                    r->setSpeed(limited);
                }
            }
        }
    }

private:
    /**
     * @brief Longitud euclidiana de un vector.
     * @param v Vector 2D.
     * @return Magnitud de v.
     */
    static float length(const sf::Vector2f& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    /**
     * @brief Vector normalizado (o cero si su longitud es muy pequeña).
     * @param v Vector 2D.
     * @return v / |v| o (0,0) si |v|?0.
     */
    static sf::Vector2f normalize(const sf::Vector2f& v) {
        float len = length(v);
        if (len <= 1e-5f) return { 0.f, 0.f };
        return { v.x / len, v.y / len };
    }

    /**
     * @brief Producto punto entre dos vectores.
     * @param a Vector A.
     * @param b Vector B.
     * @return a·b.
     */
    static float dot(const sf::Vector2f& a, const sf::Vector2f& b) {
        return a.x * b.x + a.y * b.y;
    }

    /** @brief Configuración del sistema. */
    WaypointFollowConfig cfg;
    /** @brief Índice de waypoint actual por corredor. */
    std::vector<size_t> indices;
    /** @brief Temporizador de reacción por corredor. */
    std::vector<float>  reactTimers;
    /** @brief Temporizador de “errores” por corredor. */
    std::vector<float>  mistakeTimers;
    /** @brief RNG para ruido y errores. */
    std::mt19937 rng;
    /** @brief Distribución uniforme en [-1,1] para ruido. */
    std::uniform_real_distribution<float> uni;
    /** @brief Distribución uniforme en [0,1] para probabilidades. */
    std::uniform_real_distribution<float> uni01;
};
