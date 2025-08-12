# MungoEngine

**MungoEngine** es un motor de videojuegos 2D desarrollado en **C++**, orientado a la creación de prototipos de carreras (Mario Kart).  
Está basado en una arquitectura **ECS (Entity-Component-System)**, utiliza **SFML** para el renderizado y **ImGui-SFML** para la interfaz gráfica.

---

## 🚀 Características principales

- **ECS modular**: Entidades ligeras, componentes de datos puros y sistemas especializados.
- **Extensible**: Añade actores, sistemas y pistas sin modificar el núcleo.
- **Demo incluida**: HUD, menús, cronómetro, vueltas y detección de meta.
- **IA integrada**: Algoritmos de steering (Seek, Arrive, Pursuit) y navegación por waypoints.
- **UI**: Menús, HUD y depuración con ImGui-SFML.
- **Assets centralizados**: Gestión de texturas y fuentes.

---

## 📂 Estructura del proyecto

```
MungoEngine/
│
├── include/       # Cabeceras públicas del motor (ECS, utilidades, tipos comunes)
├── src/           # Implementación del runtime y lógica de la demo
├── ECS/           # Núcleo ECS: entidades, componentes, eventos
├── Components/    # Datos puros de las entidades (Transform, CShape, Lap, etc.)
├── Systems/       # Lógica de juego (Input, IA, física, GUI, carreras)
├── Circuits/      # Datos de pistas y rutas (waypoints, checkpoints, meta)
├── Resources/     # Gestión de recursos (texturas, fuentes, cachés) - opcional
└── assets/        # Recursos del juego (imágenes, fuentes, datos)
```

---

## 🛠 Requisitos

- **C++17** (MSVC 2019/2022, x64)
- **SFML 3.0.0**
- **ImGui-SFML** compatible

---

## ⚡ Compilación en Windows

1. Clonar el repositorio:
   ```bash
   git clone https://github.com/usuario/MungoEngine.git
   ```
2. Abrir `MungoEngine.sln` en **Visual Studio 2019 o 2022**.
3. Seleccionar configuración **x64** y **Release**.
4. Configurar rutas si no se usa vendoring:
   - **C/C++ → Additional Include Directories**:
     ```
     ...\SFML\include; ...\imgui-sfml\include
     ```
   - **Linker → Additional Library Directories**:
     ```
     ...\SFML\lib
     ```
   - **Linker → Input**:
     ```
     sfml-graphics.lib; sfml-window.lib; sfml-system.lib
     ```
5. Compilar (`Ctrl + Shift + B`) y ejecutar (`F5`).
6. Asegurarse de que la carpeta `assets/` esté junto al ejecutable.

---

## 🎮 Controles

| Acción         | Tecla / Ratón |
|----------------|--------------|
| Mover          | **WASD**     |
| Salir          | **Esc**      |

