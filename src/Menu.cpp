#include "Menu.h"

Menu::Menu(Model &model, Controller *controller, sf::RenderWindow &window)
    : model(model)
    , controller(*controller)
    , window(window) {
    initCircle();
    loadFont();
    loadBackground();
}

Menu::~Menu() {
}

void Menu::newFrame() {
    animate();
    window.draw(bg);
    window.draw(circle);
    drawGUI();
    window.display();
}

void Menu::initCircle() {
    circle.setRadius(50);
    circle.setPointCount(8);
    circle.setPosition(io.DisplaySize.x * 1.0 / 2, io.DisplaySize.y * 2.0 / 3);
}

void Menu::loadFont() {
    io.Fonts->ClearFonts();
    io.Fonts->AddFontFromFileTTF((ResourcesPath + "SF Atarian System.ttf").c_str(), 48);
    ImGui::SFML::createFontTexture(fontTexture);
    ImGui::SFML::setFontTexture(fontTexture);
}

void Menu::loadBackground() {
    bgTexture.loadFromFile(ResourcesPath + "background.png");
    bg.setTexture(bgTexture);
}

void Menu::animate() {
    if(iterationClock.getElapsedTime().asMilliseconds() < 10)
        return;
    iterationClock.restart();
    ++iteration;
    circle.move(sin(iteration / 20.0) * 10.0, cos(iteration / 10.0) * 10.0);
    circle.rotate(1);
    circle.setFillColor(sf::Color(255, 255, 0, (sin(iteration / 40.0) + 1) / 2 * 255));
    color.w += sin(iteration / 10.0) / 40.0;
    textColor.x -= sin(iteration / 10.0) / 40.0;
    textColor.y -= cos(iteration / 10.0) / 40.0;
    textColor.z -= cos(iteration / 20.0) / 40.0;
}

void Menu::drawGUI() {
    ImGui::SFML::Update(window, deltaClock.restart());
    setStyle();
    ImGui::Begin("", nullptr, ImVec2(0, 0), 0, ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings);
    if(menu == 0)
        drawMenu();
    else if(menu == 1)
        drawOptions();
    ImGui::End();
    ImGui::Render();
}

void Menu::setStyle() {
    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = color;
    style.Colors[ImGuiCol_ButtonHovered] = colorHovered;
    style.Colors[ImGuiCol_ButtonActive] = colorActive;
    style.Colors[ImGuiCol_Text] = textColor;
    style.Colors[ImGuiCol_SliderGrab] = colorHovered;
    style.Colors[ImGuiCol_SliderGrabActive] = colorActive;
    style.Colors[ImGuiCol_FrameBg] = color;
    x = 200;
    y = 150;
    delta = 100;
}

void Menu::drawMenu() {
    nextItem();
        if(ImGui::Button("Play", ImVec2(500, 75)))
            ;
    nextItem();
        if(ImGui::Button("Options", ImVec2(500, 75)))
            menu = 1;
    nextItem();
        if(ImGui::Button("Quit", ImVec2(500, 75)))
            controller.processEvent("Quit");
}

void Menu::drawOptions() {
    nextItem();
        ImGui::PushItemWidth(240);
        int volume = model.music.getVolume();
        if(ImGui::SliderInt("Music Volume", &volume, 0, 100))
            controller.processEvent("Volume " + std::to_string(volume));
        if(volume == 0) {
            ImGui::SetCursorPosX(x);
            ImGui::SetCursorPosY(y / 2);
            ImGui::TextColored(ImColor(0, 255, 0), "Antycommunistico!");
        }
    nextItem();
        ImGui::PushStyleColor(ImGuiCol_Button, colorHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
        if(ImGui::Button("Return", ImVec2(500, 60)))
            menu = 0;
        ImGui::PopStyleColor(2);
}

void Menu::nextItem() {
    y += delta;
    ImGui::SetCursorPosX(x);
    ImGui::SetCursorPosY(y);
}
