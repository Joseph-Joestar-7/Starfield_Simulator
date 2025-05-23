#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>
#include "Star.h"
#include <algorithm>

float jmap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd) {
    return outputStart + (outputEnd - outputStart) * ((value - inputStart) / (inputEnd - inputStart));
}


int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    sf::RenderWindow window(sf::VideoMode(width, height), "Starfield Simulator");
    ImGui::SFML::Init(window);

    Star stars[800];

    sf::CircleShape circle(2.0f);
    circle.setFillColor(sf::Color::White);

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Starfield Speed");

        int speed = Star::getspeed();
        ImGui::SliderInt("Speed", &speed, 0, 20);
        Star::setspeed(speed);

        /*static float angleX = 0.0f;
        static float angleY = 0.0f;
        ImGui::SliderFloat("Angle X", &angleX, -1.0f, 1.0f);
        ImGui::SliderFloat("Angle Y", &angleY, -1.0f, 1.0f);*/

        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        ImGui::End();

        window.clear(sf::Color::Black);

        float halfW = width * 0.5f;
        float halfH = height * 0.5f;

        for (auto& star : stars)
        {
            star.Update();

            //float rotatedX = star.getx() + angleX * star.getz();
            //float rotatedY = star.gety() + angleY * star.getz();

            float invZ = 1.0f / star.getz();
            float sx = star.getx() * invZ * halfW + halfW;
            float sy = star.gety() * invZ * halfH + halfH;

            //float sx = rotatedX * invZ * halfW + halfW;
            //float sy = rotatedY * invZ * halfH + halfH;

            float invPZ = 1.0f / star.getpz();
            float px = star.getx() * invPZ * halfW + halfW;
            float py = star.gety() * invPZ * halfH + halfH;

            sf::Vertex line[] = {
                sf::Vertex({ px, py }, sf::Color::Blue),
                sf::Vertex({ sx, sy }, sf::Color::Blue)
            };
            window.draw(line, 2, sf::Lines);

            float radius = jmap(star.getz(), 0.0f, float(width), 5.0f, 0.0f);
            circle.setRadius(radius);
            circle.setPosition(sx, sy);
            window.draw(circle);
        }

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}