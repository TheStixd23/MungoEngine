#pragma once
/**
 * @file ResourceManager.h
 * @brief Clase para la gestión centralizada de recursos del motor, como texturas.
 *
 * Esta clase implementa el patrón Singleton para asegurar que los recursos
 * (especialmente texturas) se carguen una sola vez y puedan ser reutilizados
 * en distintas partes del motor sin recargar desde disco.
 *
 * Usa `EngineUtilities::TSharedPointer` para manejo seguro de memoria y
 * evitar duplicados innecesarios.
 *
 * @author Hannin Abarca
 */

#include "Prerequisites.h"
#include "ESC/Texture.h"

 /**
  * @class ResourceManager
  * @brief Administrador global de recursos como texturas.
  *
  * Permite cargar, almacenar y recuperar texturas por nombre de archivo.
  * Evita la recarga innecesaria de recursos usando un almacenamiento en memoria.
  * Implementa el patrón Singleton.
  */
class ResourceManager {
public:
	/** @brief Constructor por defecto. */
	ResourceManager() {};

	/** @brief Destructor por defecto. */
	~ResourceManager() {};

private:
	/**
	 * @brief Constructor de copia eliminado para evitar duplicación de instancias.
	 */
	ResourceManager(const ResourceManager&) = delete;

	/**
	 * @brief Operador de asignación eliminado para evitar duplicación de instancias.
	 */
	ResourceManager& operator=(const ResourceManager&) = delete;

public:
	/**
	 * @brief Obtiene la instancia única del administrador de recursos.
	 * @return Referencia a la instancia única de ResourceManager.
	 */
	static ResourceManager& getInstance() {
		static ResourceManager instance;
		return instance;
	}

	/**
	 * @brief Carga una textura desde archivo y la almacena en caché.
	 * @param filename Nombre base del archivo (sin extensión).
	 * @param extension Extensión del archivo (por defecto suele ser "png" o "jpg").
	 * @return `true` si la textura se cargó correctamente, `false` si falló.
	 */
	bool loadTexture(const std::string& filename, const std::string& extension);

	/**
	 * @brief Obtiene una textura previamente cargada.
	 * @param fileName Nombre base del archivo de textura.
	 * @return Puntero compartido a la textura. Si no existe, retorna nullptr.
	 */
	EngineUtilities::TSharedPointer<Texture> getTexture(const std::string& fileName);

private:
	/**
	 * @brief Almacén interno de texturas, indexadas por nombre de archivo.
	 */
	std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};
