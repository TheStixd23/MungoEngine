#include "EngineGUI.h"
#include "Window.h"
#include "../include/ESC/Actor.h"

void EngineGUI::init(const EngineUtilities::TSharedPointer<Window>& window) {
	ImGui::SFML::Init(*window->m_windowPtr);
	SetupMungoEngineGUIStyle();
}

void EngineGUI::update(const EngineUtilities::TSharedPointer<Window>& window, sf::Time deltaTime) {
	ImGui::SFML::Update(*window->m_windowPtr, deltaTime);
}

void EngineGUI::render(const EngineUtilities::TSharedPointer<Window>& window) {
	ImGui::SFML::Render(*window->m_windowPtr);
}

void EngineGUI::processEvent(const sf::Window& window, const sf::Event& event) {
	ImGui::SFML::ProcessEvent(window, event);
}

void EngineGUI::destroy() {
	ImGui::SFML::Shutdown();
}

void EngineGUI::SetupMungoEngineGUIStyle() {
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowRounding = 6.0f;
	style.FrameRounding = 4.0f;
	style.GrabRounding = 4.0f;
	style.ScrollbarRounding = 4.0f;
	style.TabRounding = 3.0f;
	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.WindowPadding = ImVec2(12, 10);
	style.FramePadding = ImVec2(8, 4);
	style.ItemSpacing = ImVec2(8, 6);
	style.ItemInnerSpacing = ImVec2(6, 4);

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_Text] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.90f, 0.92f, 0.95f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.94f, 0.95f, 0.97f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.75f, 0.75f, 0.85f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.05f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.85f, 0.88f, 0.92f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.70f, 0.80f, 0.95f, 0.90f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.65f, 0.78f, 0.95f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.82f, 0.85f, 0.92f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.75f, 0.82f, 0.95f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.90f, 0.92f, 0.95f, 0.75f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.90f, 0.92f, 0.96f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.92f, 0.93f, 0.95f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.75f, 0.85f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.65f, 0.72f, 0.85f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.60f, 0.68f, 0.85f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.20f, 0.40f, 0.70f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.50f, 0.80f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 0.55f, 0.90f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.72f, 0.78f, 0.88f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.60f, 0.70f, 0.85f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.55f, 0.65f, 0.85f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.65f, 0.70f, 0.85f, 0.80f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.60f, 0.65f, 0.85f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.60f, 0.85f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.60f, 0.65f, 0.85f, 0.60f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.60f, 0.70f, 0.90f, 0.80f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.60f, 0.70f, 0.95f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.75f, 0.80f, 0.90f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.65f, 0.75f, 0.95f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.60f, 0.70f, 0.90f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.55f, 0.85f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.35f, 0.50f, 0.80f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.50f, 0.60f, 0.80f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.45f, 0.55f, 0.85f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.60f, 0.70f, 0.90f, 0.40f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.25f, 0.45f, 0.75f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.30f, 0.50f, 0.85f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.30f, 0.50f, 0.85f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.90f, 0.90f, 0.95f, 0.30f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.90f, 0.90f, 0.95f, 0.60f);
}

void EngineGUI::outliner() {}
