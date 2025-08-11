/**
 * @file ResourceManager.cpp
 * @brief Implementación del gestor de recursos (texturas) del engine.
 *
 * Mantiene un caché de texturas indexadas por nombre base (sin extensión).
 * Si se solicita una textura inexistente, retorna una textura por defecto.
 *
 * @author Hannin Abarca
 */

#include "ResourceManager.h"

 /**
  * @brief Carga y registra una textura si no existe ya en caché.
  *
  * Si la clave `fileName` ya está presente, no vuelve a cargar y retorna `true`.
  * En caso contrario, crea la textura (usando `extension`) y la almacena.
  *
  * @param fileName Nombre base del archivo (sin extensión), usado como clave.
  * @param extension Extensión del archivo de textura (por defecto "png").
  * @return `true` siempre que la textura esté en caché al finalizar.
  */
bool
ResourceManager::loadTexture(const std::string& fileName,
	const std::string& extension) {

	if (m_textures.find(fileName) != m_textures.end()) {
		return true;
	}

	auto texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
	m_textures[fileName] = texture;
	return true;
}

/**
 * @brief Obtiene una textura del caché por su nombre base.
 *
 * Si la textura no existe, registra una advertencia y devuelve una textura
 * por defecto bajo la clave `"Default"`. Si tampoco existe, la crea.
 *
 * @param fileName Nombre base de la textura solicitada (sin extensión).
 * @return Puntero compartido a la textura solicitada o a la textura por defecto.
 */
EngineUtilities::TSharedPointer<Texture>
ResourceManager::getTexture(const std::string& fileName) {

	auto it = m_textures.find(fileName);
	if (it != m_textures.end()) {
		return it->second;
	}

	std::cerr << "[ResourceManager] Texture not found: "
		<< fileName << ". Using default texture. \n";

	const std::string defaultKey = "Default";

	auto defaultIt = m_textures.find(defaultKey);
	if (defaultIt != m_textures.end()) {
		return defaultIt->second;
	}

	auto defaultTexture = EngineUtilities::MakeShared<Texture>(defaultKey, "png");
	m_textures[defaultKey] = defaultTexture;
	return defaultTexture;
}
