#include "Application.h"

void Application::run() {
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Petris", sf::Style::Fullscreen, getDefaultContextSettings());
    window->setFramerateLimit(128);
    initImGui();
    initCircle();
    loadAndPlayMusic();

    sf::Texture bgTexture;
    bgTexture.loadFromFile(ResourcesPath + "papieprz.png");

    sf::Sprite bg;
    bg.setTexture(bgTexture);

    while(window->isOpen()) {
        processEvents();
        iterate();

        ImGui::SFML::Update(*window, deltaClock.restart());
        setStyle();

        ImGui::Begin("", nullptr, ImVec2(0, 0), 0, ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings);

        ImGui::SetCursorPosX(1200);
        ImGui::SetCursorPosY(200);
        if(ImGui::Button("Play Game"))
            ;

        ImGui::SetCursorPosX(1200);
        ImGui::SetCursorPosY(300);
        if(ImGui::Button("Options"))
            ;

        ImGui::SetCursorPosX(1200);
        ImGui::SetCursorPosY(400);
        if(ImGui::Button("About"))
            ;

        ImGui::SetCursorPosX(1200);
        ImGui::SetCursorPosY(500);
        if(ImGui::Button("Quit Game"))
            window->close();

        ImGui::End();

        window->draw(bg);
        window->draw(circle);
        ImGui::Render();
        window->display();
    }

    delete window;
}

sf::ContextSettings Application::getDefaultContextSettings() const {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    return settings;
}

void Application::initImGui() {
    ImGui::SFML::Init(*window);
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = 5;
}

void Application::initCircle() {
    circle.setRadius(50);
    circle.setPointCount(8);
    circle.setPosition(window->getSize().x * 1.0 / 3, window->getSize().y * 2.0 / 3);
    circle.setFillColor(sf::Color(255, 0, 0, 63));
}

void Application::processEvents() {
    bool wasLAlt = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
    sf::Event event;
    while(window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if(event.type == sf::Event::Closed)
            window->close();
    }
    bool isLAlt = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
    if(!isLAlt && wasLAlt && sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
       window->close();
}

void Application::iterate() {
    if(iterationClock.getElapsedTime().asMilliseconds() < 10)
        return;
    iterationClock.restart();
    ++iteration;
    circle.move(sin(iteration / 20.0) * 10.0, cos(iteration / 10.0) * 10.0);
    circle.rotate(1);
    circle.setFillColor(sf::Color(255, 255, 0, (sin(iteration / 40.0) + 1) * 127));
    color.w += sin(iteration / 10.0) / 40.0;
    textColor.x -= sin(iteration / 10.0) / 40.0;
    textColor.y -= cos(iteration / 10.0) / 40.0;
    textColor.z -= cos(iteration / 20.0) / 40.0;
}

void Application::loadAndPlayMusic() {
    if(music.openFromFile(ResourcesPath + "TetrisThemeDubstep.ogg"))
        music.setVolume(50),
        music.setLoop(true),
        music.play();
}

void Application::setStyle() {
    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = color;
    style.Colors[ImGuiCol_ButtonHovered] = colorHovered;
    style.Colors[ImGuiCol_ButtonActive] = colorActive;
    style.Colors[ImGuiCol_Text] = textColor;
}
