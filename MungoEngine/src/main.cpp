#include <SFML/Graphics.hpp>

sf::RenderWindow* window;
sf::CircleShape* circle;

void init() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mungo Engine");
    circle = new sf::CircleShape(100.f);
    circle->setFillColor(sf::Color::Green);
    circle->setPosition(200.f, 150.f);
}

void handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void update() {
    // Aquí puedes agregar lógica de juego si es necesario
}

void render() {
    window->clear();
    window->draw(*circle);
    window->display();
}

void destroy() {
    delete window;
    delete circle;
}

int main() {
    init();

    while (window->isOpen()) {
        handleEvents();
        update();
        render();
    }

    destroy();

    return 0;
}
