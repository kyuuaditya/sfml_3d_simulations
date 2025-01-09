#include <iostream>
#include <sfml/Graphics.hpp>
#include <math.h>

int main() {
    float camera_x = 0.0f;
    float camera_y = 0.0f;
    float camera_z = 0.0f;

    float camera_angle_x = 0.0f;
    float camera_angle_y = 0.0f;
    float camera_angle_z = 0.0f;

    float focal_length = 1.0f;

    float donut_x = 0.0f;
    float donut_y = 3.0f;
    float dunut_z = 0.0f;

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
    float A = 0.0f;  // angle_A
    float B = 0.0f;  // angle_B

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
                    camera_x -= 0.1f;
                }
                if (event.key.code == sf::Keyboard::Left) { // to select the play button
                    camera_x += 0.1f;
                }
                // if (event.key.code == sf::Keyboard::Down) { // to select the play button
                //     camera_y -= 0.1f;
                // }
                // if (event.key.code == sf::Keyboard::Down) { // to select the play button
                //     camera_y -= 0.1f;
                // }
            }
        }


        for (float j = 0; j < 6.28; j += 0.015) {
            phi = j;

            for (float i = 0; i < 6.28; i += 0.055) {
                float cosA = cos(A);
                float sinA = sin(A);
                float cosB = cos(B);
                float sinB = sin(B);

                float cosPhi = cos(phi);
                float sinPhi = sin(phi);

                theta = i;

                float cosTheta = cos(theta);
                float sinTheta = sin(theta);

                // with reduced trignometric functions

                // // ! 3rd line I changed sin to cos a
                // // surface normal with respect to old light source
                // // surface normal with respect to light source
                // L = (double)((cosTheta * cosPhi * cosB +
                //     sinB * (sinTheta * cosA + cosTheta * sinPhi * sinA)) *
                //     light_x +
                //     (cosB * (sinTheta * cosA + cosTheta * sinA * sinPhi) -
                //         cosTheta * cosPhi * cosB) *
                //     light_y +
                //     (cosTheta * sinPhi * cosA - sinTheta * sinA) * light_z) /
                //     sqrt(light_x * light_x + light_y * light_y +
                //         light_z * light_z);

                // <----------------------------------------------------------------------------->

                // x = (double)(donut_radius + donut_radius2 * cosTheta) *
                //     (cosB * cosPhi + sinA * sinB * sinPhi) -
                //     donut_radius2 * cosA * sinB * sinTheta;
                // y = (double)(donut_radius + donut_radius2 * cosTheta) *
                //     (cosPhi * sinB - cosB * sinA * sinPhi) +
                //     donut_radius2 * cosA * cosB * sinTheta;
                // z = (double)cosA * (donut_radius + donut_radius2 * cosTheta) * sinPhi + donut_radius2 * sinA * sinTheta;

                // <----------------------------------------------------------------------------->

                x = (double)(cosPhi * (donut_radius + donut_radius2 * cosTheta));
                y = (double)(donut_radius2 * sinTheta);
                z = (double)((sinPhi * (donut_radius + donut_radius2 * cosTheta)));

                x += donut_x;
                y += donut_y;
                z += dunut_z;

                screenXcords = (double)(x - camera_x) * focal_length /
                    abs(y - camera_y + focal_length);
                screenYcords = (double)(z - camera_z) * focal_length /
                    abs(y - camera_y + focal_length);

                cx = donut_radius * cosB * cosPhi + sinB * donut_radius * sinA * sinPhi;
                cy = donut_radius * sinA * cosB * sinPhi - donut_radius * sinB * cosPhi;
                cz = donut_radius * cosA * sinPhi;

                S = (double)(((x - cx) * (x - light_x)) +
                    ((y - cy) * (y - light_y)) +
                    ((z - cz) * (z - light_z)));

                if (screenXcords < screen_width / 2 && screenXcords > -screen_width / 2 &&
                    screenYcords < screen_height / 2 && screenYcords > -screen_height / 2) {
                    sf::Vertex point;
                    point.position = sf::Vector2f(screenXcords * window.getSize().x / 4 + screen_width * window.getSize().x / 8,
                        screenYcords * window.getSize().y / 4 + screen_height * window.getSize().y / 8);
                    point.color = sf::Color(255 * (y / (2 * (donut_radius + donut_radius2)) + 0.5),
                        255 * (y / (2 * (donut_radius + donut_radius2)) + 0.5),
                        255 * (y / (2 * (donut_radius + donut_radius2)) + 0.5));
                    points.append(point);
                }
            }
        }

        // howw fast the donut rotates
        // A += 0.005;
        // B += 0.003;


        window.clear(sf::Color::Black);
        window.draw(points);
        window.display();
        points.clear();
    }
}
