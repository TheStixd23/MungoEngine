/**
 * @file BaseApp.cpp
 * @brief Implementación de la clase BaseApp, encargada del ciclo de vida principal de la aplicación.
 * @author Hannin Abarca
 */

#include "BaseApp.h"

 /**
  * @brief Destructor de BaseApp. Libera recursos si es necesario.
  */
BaseApp::~BaseApp() {
}

/**
 * @brief Ejecuta el ciclo principal de la aplicación.
 *
 * Inicializa los recursos, entra en el bucle principal y destruye todo al finalizar.
 * @return Código de salida (0 si fue exitoso).
 */
int
BaseApp::run() {
	if (!init()) {
		ERROR("BaseApp",
			"run",
			"Initializes result on a false statemente, check method validations");
	}

	while (m_windowPtr->isOpen()) {
		m_windowPtr->handleEvents();
		update();
		render();
	}

	destroy();
	return 0;
}

/**
 * @brief Inicializa la aplicación: crea la ventana, figuras y actores necesarios.
 * @return true si la inicialización fue exitosa, false en caso contrario.
 */
bool
BaseApp::init() {
	m_windowPtr = EngineUtilities
		::MakeShared<Window>(1920, 1080, "MungoEngine");
	if (!m_windowPtr) {
		ERROR("BaseApp",
			"init",
			"Failed to create window pointer, check memory allocation");
		return false;
	}

	m_shapePtr = EngineUtilities::MakeShared<CShape>();
	if (m_shapePtr)
	{
		m_shapePtr->createShape(ShapeType::CIRCLE);
		m_shapePtr->setFillColor(sf::Color::Green);
		m_shapePtr->setPosition(200.f, 150.f);
	}

	//circle actor
	m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
	if (m_ACircle) {
		m_ACircle->getComponent<CShape>()->createShape(CIRCLE);
		m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::Red);
		m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2(100.f, 150.f));
	}
	return true;
}

/**
 * @brief Actualiza los actores de la escena.
 */
void
BaseApp::update() {
	if (!m_ACircle.isNull()) {
		m_ACircle->update(0);
	}
}

/**
 * @brief Renderiza los elementos visibles en la ventana.
 */
void
BaseApp::render() {
	if (!m_windowPtr) {
		return;
	}
	m_windowPtr->clear();
	if (m_shapePtr) {
		m_shapePtr->render(m_windowPtr);
	}
	if (m_ACircle) {
		m_ACircle->render(m_windowPtr);
	}
	m_windowPtr->display();
}

/**
 * @brief Método de limpieza de recursos, llamado al finalizar la aplicación.
 */
void
BaseApp::destroy() {
}
