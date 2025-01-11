#include <iostream>
#include <sfml/Graphics.hpp>
#include <math.h>

int main() {
    float camera_x = 0.0f;
    float camera_y = -1.0f;
    float camera_z = 0.0f;

    float camera_angle_x = 0.0f;
    float camera_angle_y = 0.0f;
    float camera_angle_z = 0.0f;

    float focal_length = 1.0f;

    float donut_x = 0.0f;
    float donut_y = 3.0f;
    float donut_z = 0.0f;

    float donut_angle_x = 0.0f;
    float donut_angle_y = 0.0f;
    float donut_angle_z = 0.0f;

    float donut_radius = 3.0f;
    float donut_radius2 = 1.0f;

    float screen_width = 4.0f;
    float screen_height = 4.0f;

    float light_x = 0.0f;
    float light_y = 0.0f;
    float light_z = 5.0f;

    // teamporary values
    float theta = 0.0f;  // theta
    float phi = 0.0f;  // phi

    float x, y, z, cx, cy, cz, L, S, screenXcords, yd, screenYcords;

    float max_L = 0.0f;

    sf::VertexArray points(sf::Points);

    // render window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML 3D Simulation");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) { // key events
                if (event.key.code == sf::Keyboard::Up) { // to toggle fullscreen
                    camera_y += 0.1f;
                }
                if (event.key.code == sf::Keyboard::Down) { // to select the play button
                    camera_y -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::Right) { // to select the play button
                    camera_x += 0.1f;
                }
                if (event.key.code == sf::Keyboard::Left) { // to select the play button
                    camera_x -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::Numpad8) { // to select the play button
                    camera_z -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::Numpad2) { // to select the play button
                    camera_z += 0.1f;
                }

                // <------------------------------------------------------------------->
                // donut rotation
                if (event.key.code == sf::Keyboard::I) {
                    donut_angle_x += 0.1f;
                }
                if (event.key.code == sf::Keyboard::K) {
                    donut_angle_x -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::L) {
                    donut_angle_y += 0.1f;
                }
                if (event.key.code == sf::Keyboard::J) {
                    donut_angle_y -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::U) {
                    donut_angle_z += 0.1f;
                }
                if (event.key.code == sf::Keyboard::O) {
                    donut_angle_z -= 0.1f;
                }
                // <------------------------------------------------------------------->
                // camera rotation
                if (event.key.code == sf::Keyboard::W) {
                    camera_angle_x -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::S) {
                    camera_angle_x += 0.1f;
                }
                if (event.key.code == sf::Keyboard::D) {
                    camera_angle_z -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::A) {
                    camera_angle_z += 0.1f;
                }
            }
        }


        float cosX = cos(donut_angle_x);
        float sinX = sin(donut_angle_x);
        float cosY = cos(donut_angle_y);
        float sinY = sin(donut_angle_y);
        float cosZ = cos(donut_angle_z);
        float sinZ = sin(donut_angle_z);
        // int count = 0;
        float cosCamX = cos(camera_angle_x);
        float sinCamX = sin(camera_angle_x);
        float cosCamY = 1;
        float sinCamY = 0;
        float cosCamZ = cos(camera_angle_z);
        float sinCamZ = sin(camera_angle_z);

        for (float j = 0; j < 6.28; j += 0.02) {
            phi = j;

            for (float i = 0; i < 6.28; i += 0.08) {

                float cosPhi = cos(phi);
                float sinPhi = sin(phi);

                theta = i;

                float cosTheta = cos(theta);
                float sinTheta = sin(theta);

                // local cordinates of the donut
                // x = (double)(cosPhi * (donut_radius + donut_radius2 * cosTheta));
                x = (double)(cosZ * (cosPhi * cosY * (donut_radius2 * cosTheta + donut_radius) - sinY * (sinPhi * cosX * (donut_radius2 * cosTheta + donut_radius) - donut_radius2 * sinTheta * sinX)) + sinZ * (donut_radius2 * sinTheta * cosX + sinPhi * sinX * (donut_radius2 * cosTheta + donut_radius)));
                // y = (double)(donut_radius2 * sinTheta);
                y = (double)(cosZ * (donut_radius2 * sinTheta * cosX + sinPhi * sinX * (donut_radius2 * cosTheta + donut_radius)) + sinZ * (cosPhi * cosY * (donut_radius2 * cosTheta + donut_radius) - donut_radius2 * sinTheta * sinX));
                // z = (double)((sinPhi * (donut_radius + donut_radius2 * cosTheta)));
                z = (double)(cosPhi * sinY * (donut_radius2 * cosTheta + donut_radius) + cosY * (sinPhi * cosX * (donut_radius2 * cosTheta + donut_radius) - donut_radius2 * sinTheta * sinX));

                // count++;

                // adjusting local donut cordinates with reference to the camera
                x += donut_x;
                y += donut_y;
                z += donut_z;

                float tempX = x;
                float tempY = y;
                float tempZ = z;

                // adjusting the donut cordinates with reference to the camera
                x = (double)(cosCamZ * ((tempX - camera_x) * cosCamY - sinCamY * ((tempZ - camera_z) * cosCamX - (tempY - camera_y + focal_length) * sinCamX)) + sinCamZ * ((tempY - camera_y + focal_length) * cosCamX + (tempZ - camera_z) * sinCamX));
                y = (double)(cosCamZ * ((tempY - camera_y + focal_length) * cosCamX + (tempZ - camera_z) * sinCamX) - sinCamZ * ((tempX - camera_x) * cosCamY - sinCamY * ((tempZ - camera_z) * cosCamX - (tempY - camera_y + focal_length) * sinCamX)));
                z = (double)((tempX - camera_x) * sinCamY + cosCamY * ((tempZ - camera_z) * cosCamX - (tempY - camera_y + focal_length) * sinCamX));

                // screen cordinates of the donut
                // if (y - camera_y >= 0) {
                if (1) {

                    // continue;
                    screenXcords = (double)(x - camera_x) * focal_length /
                        abs(y - camera_y + focal_length);
                    screenYcords = (double)(z - camera_z) * focal_length /
                        abs(y - camera_y + focal_length);

                    if (screenXcords < screen_width / 2 && screenXcords > -screen_width / 2 &&
                        screenYcords < screen_height / 2 && screenYcords > -screen_height / 2
                        ) {
                        sf::Vertex point;
                        point.position = sf::Vector2f(screenXcords * window.getSize().x / 4 + screen_width * window.getSize().x / 8,
                            screenYcords * window.getSize().y / 4 + screen_height * window.getSize().y / 8);
                        point.color = sf::Color(255, 255, 255);
                        points.append(point);
                    }
                }
            }
        }


        window.clear(sf::Color::Black);
        window.draw(points);
        window.display();
        points.clear();
    }
}
