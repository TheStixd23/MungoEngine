/**
 * @file ActorSerializer.cpp
 * @brief Implementación de utilidades para serializar y deserializar actores a/desde archivo de texto.
 *
 * Formato actual (por línea): `NombreActor,px,py,sx,sy`
 * donde (px,py) es posición y (sx,sy) es escala. Solo persiste datos básicos del Transform.
 *
 * @author Hannin Abarca
 */
#include "ActorSerializer.h"
#include <fstream>

 /**
  * @brief Guarda una lista de actores en un archivo de texto.
  *
  * Recorre cada actor y escribe su nombre, posición y escala (del componente Transform)
  * en formato CSV simple por línea: `Nombre,px,py, sx,sy`.
  *
  * @param filename Ruta del archivo de salida.
  * @param actors   Vector de actores a serializar.
  * @return `true` si se pudo abrir y escribir el archivo; `false` en caso contrario.
  * @note Si un actor no tiene Transform, solo se escribe su nombre y se omiten los campos numéricos.
  */
bool
ActorSerializer::saveActorsToFile(const std::string& filename, const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    for (auto& actor : actors) {
        file << actor->getName() << ","; // Nombre
        auto transform = actor->getComponent<Transform>();
        if (transform) {
            auto pos = transform->getPosition();
            auto scale = transform->getScale();
            file << pos.x << "," << pos.y << "," << scale.x << "," << scale.y << "\n";
        }
    }
    file.close();
    return true;
}

/**
 * @brief Carga actores desde un archivo de texto al vector proporcionado.
 *
 * Lee cada línea con el formato `Nombre,px,py,sx,sy`, crea un Actor con ese nombre y
 * establece su Transform (posición y escala). Reemplaza el contenido del vector `actors`.
 *
 * @param filename Ruta del archivo de entrada.
 * @param actors   Vector donde se almacenarán los actores reconstruidos.
 * @return `true` si se pudo abrir y leer el archivo; `false` en caso contrario.
 * @warning No valida tipos ni rangos: asume que el archivo contiene datos bien formados.
 * @note Requiere que el constructor de Actor y sus componentes estén disponibles.
 */
bool
ActorSerializer::loadActorsFromFile(const std::string& filename, std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    actors.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        float px, py, sx, sy;
        if (std::getline(ss, name, ',') &&
            (ss >> px) && ss.ignore(1) &&
            (ss >> py) && ss.ignore(1) &&
            (ss >> sx) && ss.ignore(1) &&
            (ss >> sy)) {
            auto actor = EngineUtilities::MakeShared<Actor>(name);
            actor->getComponent<Transform>()->setPosition(sf::Vector2f(px, py));
            actor->getComponent<Transform>()->setScale(sf::Vector2f(sx, sy));
            actors.push_back(actor);
        }
    }
    file.close();
    return true;
}
