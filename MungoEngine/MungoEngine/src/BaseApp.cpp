/**
 * @file BaseApp.cpp
 * @brief Ciclo de vida principal del juego y orquestación de sistemas (ventana, GUI, actores, IA y carrera).
 * @details
 * - Crea y gestiona la ventana y la GUI.
 * - Instancia pista, jugador y NPC (formas, texturas, transform).
 * - Configura sistemas: entrada del jugador, seguimiento de waypoints, steering y sistema de carrera.
 * - Controla estados de carrera: armado, cuenta regresiva, carrera en vivo y fin.
 * - Dibuja HUD (vuelta/posición/tiempos) y overlays (countdown/finish).
 * @author Hannin Abarca
 */

#include "BaseApp.h"
#include "Window.h"
#include "CShape.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "ActorPicker.h"
#include "ActorSerializer.h"
#include "Circuits/Circuit1.h"
#include "../include/Systems/RaceSystem.h"

 /**
  * @brief Destructor por defecto. La liberación de recursos se realiza por RAII (smart pointers).
  */
BaseApp::~BaseApp() {}

/**
 * @brief Bucle principal de la aplicación.
 * @details
 * 1) Llama a @ref init(). Si falla, aborta con mensaje de error.
 * 2) Mientras la ventana esté abierta: procesa eventos, actualiza lógica (@ref update) y renderiza (@ref render).
 * 3) Al salir del bucle, invoca @ref destroy() y retorna 0.
 * @return Código de salida del programa (0 si todo fue bien).
 */
int BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp", "run", "Initialization failed.");
    }
    while (m_windowPtr->isOpen()) {
        m_windowPtr->handleEvents(m_engineGUI);
        ImGui::SFML::Update(*m_windowPtr->m_windowPtr, m_windowPtr->deltaTime);
        update();
        render();
    }
    destroy();
    return 0;
}

/**
 * @brief Inicializa ventana, GUI, actores, waypoints y sistemas del juego.
 * @details
 * - Crea la ventana y setea la GUI.
 * - Crea la pista, el jugador y el NPC; asigna texturas y transform iniciales.
 * - Carga los waypoints del circuito y configura los sistemas:
 *   - @c PlayerInputSystem para el jugador.
 *   - @c WaypointFollowSystem y @c SteeringSystem para el NPC.
 *   - @c RaceSystem para progreso/vueltas/tiempos.
 * - Arranca el @c Countdown y establece flags de carrera iniciales.
 * @return @c true si todo se configuró correctamente; @c false si falló la ventana.
 */
bool BaseApp::init() {
    ResourceManager& resourceMan = ResourceManager::getInstance();

    m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "MungoEngine");
    if (m_windowPtr.isNull()) {
        ERROR("BaseApp", "init", "Failed to create window pointer.");
        return false;
    }

    m_engineGUI.init(m_windowPtr);

    m_ATrack = EngineUtilities::MakeShared<Actor>("Track Actor");
    if (m_ATrack) {
        m_ATrack->getComponent<CShape>()->createShape(RECTANGLE);
        m_ATrack->getComponent<CShape>()->setFillColor(sf::Color::White);
        m_ATrack->getComponent<Transform>()->setPosition(sf::Vector2f(450.f, 0.f));
        m_ATrack->getComponent<Transform>()->setScale(sf::Vector2f(10.f, 19.5f));
        if (!resourceMan.loadTexture("sprites/Track", "png")) {
            MESSAGE("BaseApp", "Init", "Can't load texture.");
        }
        m_ATrack->setTexture(resourceMan.getTexture("sprites/Track"));
    }

    m_player = EngineUtilities::MakeShared<A_Player>("Player");
    if (m_player) {
        m_player->getComponent<CShape>()->createShape(CIRCLE);
        m_player->getComponent<CShape>()->setFillColor(sf::Color::White);
        m_player->getComponent<Transform>()->setScale(sf::Vector2f(2.f, 2.f));
        m_player->setPosition(sf::Vector2f(1160.f, 450.f));
        m_player->setControlMode(PlayerControlMode::Direct);
        m_player->setAcceleration(700.f);
        m_player->setFriction(6.f);
        m_player->setMaxSpeed(m_sharedMaxSpeed);
        if (!resourceMan.loadTexture("sprites/Mario", "png")) {
            MESSAGE("BaseApp", "Init", "Can't load texture.");
        }
        m_player->setTexture(resourceMan.getTexture("sprites/Mario"));
    }

    m_racerNPC = EngineUtilities::MakeShared<A_Racer>("NPC_1");
    if (m_racerNPC) {
        m_racerNPC->getComponent<CShape>()->createShape(CIRCLE);
        m_racerNPC->getComponent<CShape>()->setFillColor(sf::Color::White);
        m_racerNPC->getComponent<Transform>()->setScale(sf::Vector2f(2.f, 2.f));
        if (!resourceMan.loadTexture("sprites/Luigui", "png")) {
            MESSAGE("BaseApp", "Init", "Can't load texture.");
        }
        m_racerNPC->setTexture(resourceMan.getTexture("sprites/Luigui"));
        m_racerNPC->setSpeed(m_sharedMaxSpeed);
        m_racerNPC->setArriveRadius(40.f);
        m_racerNPC->setMode(SteeringMode::Arrive);
        m_racerNPC->enableSteering(false);
        m_racerNPC->setPosition(sf::Vector2f(1134.f, 432.f));
    }
    m_npcs.clear();
    if (!m_racerNPC.isNull()) m_npcs.push_back(m_racerNPC);

    m_waypoints = getCircuitWaypoints();
    {
        const auto n = m_waypoints.size();
        const auto f = m_waypoints.empty() ? sf::Vector2f(0.f, 0.f) : m_waypoints.front();
        const auto l = m_waypoints.empty() ? sf::Vector2f(0.f, 0.f) : m_waypoints.back();
        MESSAGE("BaseApp", "init",
            ("WP count: " + std::to_string(n) +
                " first: (" + std::to_string(f.x) + "," + std::to_string(f.y) + ")" +
                " last: (" + std::to_string(l.x) + "," + std::to_string(l.y) + ")").c_str());
    }

    {
        PlayerInputConfig pic;
        pic.player = m_player;
        pic.renderWindow = m_windowPtr->m_windowPtr.get();
        m_playerInputSystem = EngineUtilities::MakeUnique<PlayerInputSystem>(pic);
    }

    {
        WaypointFollowConfig wfc;
        wfc.racers = m_npcs;
        wfc.waypoints = &m_waypoints;
        wfc.arriveRadiusForAdvance = 8.f;
        wfc.corridorWidth = 24.f;
        wfc.lookAhead = 0;
        wfc.waypointNoiseRadius = 0.f;
        wfc.mistakeProb = 0.f;
        wfc.reactionDelay = 0.14f;
        wfc.cornerSlowdownEnabled = true;
        wfc.cornerMinAngleDeg = 25.f;
        wfc.cornerMaxAngleDeg = 95.f;
        wfc.cornerMinFactor = 0.78f;
        m_waypointFollowSystem = EngineUtilities::MakeUnique<WaypointFollowSystem>(wfc);
        m_waypointFollowSystem->primeFromPositions();
        m_waypointFollowSystem->update(0.016f);
    }

    {
        SteeringConfig sc;
        sc.racers = m_npcs;
        sc.seekRange = 10.f;
        m_steeringSystem = EngineUtilities::MakeUnique<SteeringSystem>(sc);
    }

    {
        RaceConfig rc;
        rc.actors.clear();
        if (!m_player.isNull())   rc.actors.push_back(m_player);
        for (auto& npc : m_npcs)  rc.actors.push_back(npc);
        rc.waypoints = &m_waypoints;
        rc.checkpointRadius = 12.f;
        m_raceSystem = EngineUtilities::MakeUnique<RaceSystem>(rc);
    }

    m_countdown.start();
    m_raceArmed = true;
    m_raceLive = false;
    m_raceFinished = false;
    m_finalPlace = -1;
    m_npcFinished = false;

    return true;
}

/**
 * @brief Actualización por frame: entrada, IA, carrera, HUD y overlays.
 * @details
 * - Gestiona la cuenta regresiva y el arranque de la carrera (activa timing y steering del NPC).
 * - Aplica input del jugador cuando la carrera está activa.
 * - Actualiza WaypointFollow, Steering y RaceSystem.
 * - Comprueba fin de carrera (por número de vueltas) y determina la posición final.
 * - Presenta el overlay de countdown y el HUD de vueltas/posición/tiempos.
 */
void BaseApp::update() {
    if (!m_windowPtr.isNull()) {
        m_windowPtr->update();
    }
    const float dt = m_windowPtr->deltaTime.asSeconds();

    std::string cdText;
    if (m_raceArmed && !m_raceLive) {
        cdText = m_countdown.tick(dt);
        if (m_countdown.isFinished()) {
            m_raceLive = true;
            m_raceArmed = false;
            if (!m_raceSystem.isNull()) {
                m_raceSystem->setLapOwnerIndex(0);
                m_raceSystem->armLapCounter(true);
                m_raceSystem->setTimingActive(true);
            }
            if (!m_racerNPC.isNull()) {
                m_racerNPC->enableSteering(true);
            }
        }
    }

    if (!m_player.isNull()) {
        float playerMax = m_player->getMaxSpeed();
        if (playerMax <= 0.f) playerMax = m_sharedMaxSpeed;
        m_player->setMaxSpeed(playerMax);

        if (!m_racerNPC.isNull()) {
            float npcMax = playerMax * m_npcSpeedFactor;
            m_racerNPC->setSpeed(npcMax);
        }
    }

    if (m_raceLive && !m_raceFinished) {
        if (!m_playerInputSystem.isNull()) { m_playerInputSystem->update(dt); }
    }
    if (!m_waypointFollowSystem.isNull()) { m_waypointFollowSystem->update(dt); }
    if (!m_steeringSystem.isNull()) { m_steeringSystem->update(dt); }
    if (!m_raceSystem.isNull()) { m_raceSystem->update(dt); }

    if (!m_raceFinished && !m_raceSystem.isNull()) {
        int playerLap = m_raceSystem->getLapData(0).lap;
        int npcLap = m_raceSystem->getLapData(1).lap;

        if (!m_npcFinished && npcLap >= m_lapsToWin) {
            m_npcFinished = true;
            if (!m_racerNPC.isNull()) {
                m_racerNPC->enableSteering(false);
                m_racerNPC->setSpeed(0.f);
            }
        }

        if (playerLap >= m_lapsToWin) {
            m_raceFinished = true;
            m_raceLive = false;
            std::vector<int> order = m_raceSystem->getStandings();
            m_finalPlace = -1;
            for (size_t k = 0; k < order.size(); ++k) {
                if (order[k] == 0) { m_finalPlace = (int)k + 1; break; }
            }
        }
    }

    /**
     * @brief Overlay de cuenta regresiva (presentación simple).
     * @details Muestra el texto devuelto por @c Countdown::tick() centrado en la pantalla
     * mientras la carrera está armada pero todavía no activa.
     */
    if (!m_raceLive && !m_raceFinished && !cdText.empty()) {
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::SetNextWindowPos(
            ImVec2((float)m_windowPtr->m_windowPtr->getSize().x * 0.5f,
                (float)m_windowPtr->m_windowPtr->getSize().y * 0.35f),
            ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("##countdown_overlay", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoInputs |
            ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%s", cdText.c_str());
        ImGui::End();
    }

    /**
     * @brief HUD de carrera: vuelta/posición y tiempos (mejor y actual).
     */
    if (!m_raceSystem.isNull() && !m_raceFinished) {
        std::vector<int> order = m_raceSystem->getStandings();
        int place = -1;
        for (size_t k = 0; k < order.size(); ++k) {
            if (order[k] == 0) { place = (int)k + 1; break; }
        }
        int lapHUD_real = m_raceSystem->getLapData(0).lap;
        int lapHUD = lapHUD_real + 1;

        auto fmt = [](float sec) -> std::string {
            if (sec < 0.f) return std::string("--:--.--");
            int total_ms = (int)(sec * 1000.f + 0.5f);
            int minutes = total_ms / 60000;
            int seconds = (total_ms / 1000) % 60;
            int hundred = (total_ms % 1000) / 10;
            char buf[32];
            std::snprintf(buf, sizeof(buf), "%02d:%02d.%02d", minutes, seconds, hundred);
            return std::string(buf);
            };
        float bestLap = m_raceSystem->getPlayerBestLapTime();
        float currLap = m_raceSystem->getPlayerCurrentLapTime();

        ImGui::SetNextWindowBgAlpha(0.3f);
        ImGui::SetNextWindowPos(ImVec2(40.f, 40.f), ImGuiCond_Always);
        ImGui::Begin("##race_hud_lappos", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoInputs |
            ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Lap: %d / %d", lapHUD, m_lapsToWin);
        if (place > 0) ImGui::Text("Position: %d", place);
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();
        ImGui::Text("Best:    %s", fmt(bestLap).c_str());
        ImGui::Text("Current: %s", fmt(currLap).c_str());
        ImGui::End();
    }

    /**
     * @brief Overlay de fin de carrera con resultado y botón de reintento.
     */
    if (m_raceFinished) {
        ImGui::SetNextWindowBgAlpha(0.2f);
        ImGui::SetNextWindowPos(
            ImVec2((float)m_windowPtr->m_windowPtr->getSize().x * 0.5f,
                (float)m_windowPtr->m_windowPtr->getSize().y * 0.5f),
            ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("##finish_overlay", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SetWindowFontScale(3.0f);
        if (m_finalPlace == 1) {
            ImGui::Text("Ganaste! 1ro");
        }
        else if (m_finalPlace > 0) {
            ImGui::Text("Terminaste %do", m_finalPlace);
        }
        else {
            ImGui::Text("Carrera terminada");
        }
        ImGui::SetWindowFontScale(1.2f);
        ImGui::Spacing();
        if (ImGui::Button("Reintentar", ImVec2(240.f, 60.f))) {
            resetRace();
        }
        ImGui::End();
    }

    if (!m_ATrack.isNull())    m_ATrack->update(dt);
    if (!m_player.isNull())    m_player->update(dt);
    if (!m_racerNPC.isNull())  m_racerNPC->update(dt);

    actorsVector.clear();
    if (!m_ATrack.isNull())    actorsVector.push_back(m_ATrack);
    if (!m_player.isNull())    actorsVector.push_back(m_player);
    if (!m_racerNPC.isNull())  actorsVector.push_back(m_racerNPC);

    m_engineGUI.menuBar();
    m_engineGUI.hierarchy(actorsVector);
    m_engineGUI.inspector(actorsVector);
    m_engineGUI.console();
    m_engineGUI.fileManagerPanel(actorsVector);
}

/**
 * @brief Render por frame: limpia, dibuja actores y GUI, y presenta en pantalla.
 */
void BaseApp::render() {
    if (m_windowPtr.isNull()) return;
    m_windowPtr->clear();
    if (m_ATrack)    m_ATrack->getComponent<CShape>()->render(m_windowPtr);
    if (m_player)    m_player->getComponent<CShape>()->render(m_windowPtr);
    if (m_racerNPC)  m_racerNPC->getComponent<CShape>()->render(m_windowPtr);
    m_engineGUI.drawSelectedOutline(m_windowPtr->m_windowPtr.get(), actorsVector);
    m_windowPtr->render();
    m_engineGUI.render(m_windowPtr);
    m_windowPtr->display();
}

/**
 * @brief Libera recursos asociados a la GUI (los demás se gestionan por RAII).
 */
void BaseApp::destroy() {
    m_engineGUI.destroy();
}

/**
 * @brief Reinicia la carrera y estados asociados.
 * @details
 * - Recoloca jugador y NPC (y desactiva su steering).
 * - Reinstancia @c WaypointFollowSystem y @c RaceSystem con la configuración actual.
 * - Reinicia el contador y desactiva el cronómetro hasta el siguiente arranque.
 */
void BaseApp::resetRace() {
    if (!m_player.isNull()) {
        m_player->setPosition(sf::Vector2f(1160.f, 450.f));
    }
    if (!m_racerNPC.isNull()) {
        m_racerNPC->setPosition(sf::Vector2f(1134.f, 432.f));
        m_racerNPC->enableSteering(false);
    }
    {
        WaypointFollowConfig wfc;
        wfc.racers = m_npcs;
        wfc.waypoints = &m_waypoints;
        wfc.arriveRadiusForAdvance = 8.f;
        wfc.corridorWidth = 24.f;
        wfc.lookAhead = 0;
        wfc.waypointNoiseRadius = 0.f;
        wfc.mistakeProb = 0.f;
        wfc.reactionDelay = 0.14f;
        wfc.cornerSlowdownEnabled = true;
        wfc.cornerMinAngleDeg = 25.f;
        wfc.cornerMaxAngleDeg = 95.f;
        wfc.cornerMinFactor = 0.78f;
        m_waypointFollowSystem = EngineUtilities::MakeUnique<WaypointFollowSystem>(wfc);
        m_waypointFollowSystem->primeFromPositions();
        m_waypointFollowSystem->update(0.016f);
    }
    {
        RaceConfig rc;
        rc.actors.clear();
        if (!m_player.isNull())   rc.actors.push_back(m_player);
        for (auto& npc : m_npcs)  rc.actors.push_back(npc);
        rc.waypoints = &m_waypoints;
        rc.checkpointRadius = 12.f;
        m_raceSystem = EngineUtilities::MakeUnique<RaceSystem>(rc);
    }
    m_countdown = Countdown{ 3.f };
    m_countdown.start();
    m_raceArmed = true;
    m_raceLive = false;
    m_raceFinished = false;
    m_finalPlace = -1;
    m_npcFinished = false;
    if (!m_raceSystem.isNull()) {
        m_raceSystem->setTimingActive(false);
    }
}
