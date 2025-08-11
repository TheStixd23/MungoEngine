#pragma once
/**
 * @file Countdown.h
 * @brief Implementa un temporizador regresivo simple para iniciar eventos, como carreras o secuencias de inicio.
 *
 * La clase permite configurar una duración inicial y realizar ticks en cada frame,
 * devolviendo cadenas como "3", "2", "1" y finalmente "GO!" cuando el conteo termina.
 *
 * @author Hannin Abarca
 */

#include <string>
#include <algorithm>

 /**
  * @class Countdown
  * @brief Temporizador regresivo con salida de texto para eventos de inicio.
  *
  * Se inicializa con una duración total en segundos y, al iniciarlo con `start()`,
  * decrementa el tiempo restante en cada llamada a `tick(dt)`. Cuando el conteo llega a cero,
  * devuelve "GO!" y marca el temporizador como finalizado.
  */
class Countdown {
public:
    /**
     * @brief Construye un temporizador regresivo.
     * @param seconds Duración total del conteo en segundos. Por defecto 3.0.
     */
    Countdown(float seconds = 3.f)
        : total_(seconds), remaining_(seconds), started_(false), finished_(false) {
    }

    ~Countdown() = default;

    /**
     * @brief Inicia el conteo regresivo desde el tiempo total configurado.
     */
    void start() {
        started_ = true;
        finished_ = false;
        remaining_ = total_;
    }

    /**
     * @brief Detiene el conteo sin reiniciarlo.
     */
    void stop() {
        started_ = false;
    }

    /**
     * @brief Indica si el conteo ha comenzado.
     * @return `true` si se ha iniciado, `false` en caso contrario.
     */
    bool isStarted() const {
        return started_;
    }

    /**
     * @brief Indica si el conteo ha terminado.
     * @return `true` si el tiempo restante ha llegado a cero.
     */
    bool isFinished() const {
        return finished_;
    }

    /**
     * @brief Actualiza el conteo regresivo y devuelve el texto correspondiente.
     *
     * @param dt Tiempo transcurrido desde el último tick (en segundos).
     * @return "3", "2", "1" según el tiempo restante, o "GO!" al finalizar.
     *         Si el conteo no está activo, devuelve una cadena vacía.
     */
    std::string tick(float dt) {
        if (!started_ || finished_) return "";
        remaining_ = std::max(0.f, remaining_ - dt);
        if (remaining_ == 0.f) {
            finished_ = true;
            started_ = false;
        }
        int num = static_cast<int>(remaining_ + 0.999f);
        if (finished_) return "GO!";
        return (num >= 1) ? std::to_string(num) : "GO!";
    }

private:
    float total_;      ///< Duración total del conteo (en segundos).
    float remaining_;  ///< Tiempo restante actual (en segundos).
    bool  started_;    ///< Indica si el conteo está activo.
    bool  finished_;   ///< Indica si el conteo ha finalizado.
};
