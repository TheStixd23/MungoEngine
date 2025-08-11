#pragma once
/**
 * @file Lap.h
 * @brief Estructura que almacena la información de vueltas y tiempos en una carrera.
 *
 * Contiene datos como el número de vuelta actual, tiempos de vuelta,
 * progreso entre checkpoints y métricas relacionadas al rendimiento del corredor.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"

 /**
  * @struct Lap
  * @brief Almacena los datos de progreso de un corredor en una carrera.
  *
  * Guarda información sobre el número de vuelta, tiempos, checkpoint actual
  * y progreso relativo dentro del segmento de pista.
  */
struct Lap {
	int   lap = 0;  ///< Número de vuelta actual (0 = primera vuelta).
	float currentLapTime = 0.f; ///< Tiempo acumulado en la vuelta actual (segundos).
	float bestLapTime = std::numeric_limits<float>::infinity(); ///< Mejor tiempo registrado en una vuelta.
	float totalTime = 0.f; ///< Tiempo total desde el inicio de la carrera.

	size_t checkpoint = 0; ///< Índice del checkpoint actual en la pista.
	float  progressAlongSegment = 0.f; ///< Progreso fraccional dentro del segmento actual (0.0 a 1.0).
};
