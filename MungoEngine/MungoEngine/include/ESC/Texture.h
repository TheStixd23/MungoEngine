#pragma once
/**
 * @file Texture.h
 * @brief Componente para gestionar y almacenar texturas en el motor.
 *
 * La clase @c Texture carga una textura desde archivo y la pone a disposición
 * de otros componentes o sistemas que la requieran para renderizado.
 * Implementa la interfaz base @ref Component y se identifica como tipo TEXTURE.
 *
 * @author Hannin Abarca
 */

#include "../Prerequisites.h"
#include "Component.h"

 /**
  * @class Texture
  * @brief Componente encargado de cargar y almacenar una textura SFML.
  *
  * Al instanciarse, puede cargar automáticamente un archivo de textura
  * especificando nombre y extensión. El recurso cargado se almacena en un
  * objeto @c sf::Texture accesible mediante @ref getTexture().
  *
  * No realiza renderizado por sí mismo; su función principal es proveer
  * la textura a otros elementos del motor.
  */
class Texture : public Component {
public:
	/** @brief Constructor por defecto (sin carga de archivo). */
	Texture() = default;

	/**
	 * @brief Constructor que carga una textura desde archivo.
	 * @param textureName Nombre del archivo sin extensión.
	 * @param extension Extensión del archivo (por defecto "png").
	 * @note Si la carga falla, se escribe un mensaje de error en consola.
	 */
	Texture(const std::string& textureName, const std::string& extension = "png") :
		m_textureName(textureName), m_extension(extension), Component(TEXTURE) {
		if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
			std::cout << "Error de carga de textura: " << m_textureName << "." << m_extension << std::endl;
		}
	}

	/** @brief Destructor virtual por defecto. */
	virtual ~Texture() = default;

	/** @brief Inicialización del componente (no hace nada en esta implementación). */
	void start() override {}

	/** @brief Actualización del componente (no hace nada en esta implementación). */
	void update(float deltaTime) override {}

	/** @brief Renderizado del componente (no hace nada; este componente no dibuja). */
	void render(const EngineUtilities::TSharedPointer<Window>& window) override {}

	/** @brief Liberación de recursos (no implementa lógica adicional). */
	void destroy() override {}

	/**
	 * @brief Obtiene la textura SFML cargada.
	 * @return Referencia a la textura.
	 */
	sf::Texture& getTexture() { return m_texture; }

private:
	/** @brief Objeto de textura de SFML que almacena los datos cargados. */
	sf::Texture m_texture;

	/** @brief Nombre base del archivo (sin extensión). */
	std::string m_textureName;

	/** @brief Extensión del archivo de textura. */
	std::string m_extension;
};
