MungoEngine
Motor de videojuegos 2D desarrollado en C++ enfocado a la creación de prototipos de juegos de carreras y simulaciones.
Utiliza una arquitectura ECS (Entity-Component-System), renderizado mediante SFML y una interfaz gráfica de usuario integrada con ImGui-SFML.

Descripción general
Entidades ligeras: Cada objeto del juego es una entidad con un identificador único.

Componentes de datos: Información pura asociada a las entidades, sin lógica de ejecución.

Sistemas especializados: Conjuntos de reglas y procesos que actúan sobre entidades con componentes específicos.

Incluye una demo que presenta un HUD, menús, cronómetro, conteo de vueltas y detección de meta.

Diseñado para ser extensible, permitiendo añadir nuevos actores, sistemas y pistas sin necesidad de modificar el núcleo del motor.

Estructura de carpetas (dentro del módulo MungoEngine/)
Carpeta	Rol principal	Contenido y ejemplos
include/	Cabeceras públicas del motor	Interfaces de ECS, utilidades generales, tipos de datos comunes y funciones auxiliares
src/	Implementación del runtime	Lógica central del motor y de la demo, inicialización y conexión de sistemas
ECS/	Núcleo de la arquitectura ECS	Definición de entidades e IDs, registro de componentes, sistema de mensajería y eventos
Components/	Datos asociados a entidades	Ejemplos: Transform, CShape, Lap, datos físicos, entrada de usuario, etiquetas
Systems/	Lógica que procesa conjuntos de componentes	Ejemplos: PlayerInputSystem, WaypointFollowSystem, SteeringSystem, RaceSystem, GUI
Circuits/	Datos de pistas y rutas	Waypoints, checkpoints, meta y configuraciones de trazado
Resources/ (opcional)	Abstracción para recursos externos	Carga y gestión de texturas, fuentes y cachés

Módulos clave
ECS: Gestión de entidades, componentes y bucle principal del juego.

Gameplay: Control de vueltas, posiciones, cuenta regresiva y detección de meta.

IA: Movimiento y navegación mediante waypoints y algoritmos de steering (Seek, Arrive, Pursuit).

UI: Menús, HUD y herramientas de depuración con ImGui-SFML.

Assets: Sistema centralizado para la carga de texturas y fuentes.

Instrucciones para compilar (Windows)
Abrir MungoEngine.sln en Visual Studio 2019 o 2022.

Configurar la compilación como x64 y Release.

Si no se usan dependencias integradas (vendoring):

En C/C++ → Additional Include Directories: añadir rutas a SFML\include y imgui-sfml\include.

En Linker → Additional Library Directories: añadir ruta a SFML\lib.

En Linker → Input: añadir sfml-graphics.lib, sfml-window.lib, sfml-system.lib y cualquier otra requerida.

Compilar con Ctrl + Shift + B y ejecutar con F5.

Asegurarse de que la carpeta assets/ esté junto al ejecutable.

Controles en la demo
WASD: Movimiento.

Ratón: Control de cámara.

F1: Mostrar/Ocultar HUD.

Esc: Salir.

Cómo extender el motor
Nuevo actor: Crear una clase que herede de Actor y añadir los componentes necesarios (por ejemplo, Transform, CShape).

Nuevo sistema: Implementar una clase que itere sobre entidades con componentes específicos y registrarla en el bucle de actualización.

Nueva pista: Definir los waypoints en la carpeta Circuits/ y seleccionarla desde la demo.

Requisitos técnicos
C++17 (MSVC 2019/2022, x64).

SFML 3.0.0.

Versión compatible de ImGui-SFML.

Consejos
Si la interfaz no aparece: verificar la inicialización y el ciclo new frame → draw → render de ImGui-SFML.

Si faltan DLLs: colocar las correspondientes de SFML junto al ejecutable.

Usar rutas relativas para cargar los assets desde la carpeta assets/.

Licencia
Licencia MIT (ver archivo LICENSE para más detalles).