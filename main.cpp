#include <iostream>
#include <sfml/Graphics.hpp>
#include <math.h>

int main() {
    float Radius = 4.0f;
    float sections = 100.0f;

    // float camera_x = 0.0f;
    // float camera_y = 0.0f;
    // float camera_z = 0.0f;

    float donut_x = 0.0f;
    float donut_y = 0.0f;
    float dunut_y = 0.0f;

    float screen_x = 0.0f;
    float screen_y = 3.0f;
    float screen_z = 0.0f;

    float viewer_x = 0.0f;
    float viewer_y = 4.0f;
    float viewer_z = 0.0f;

    float screen_width = 4.0f;
    float screen_height = 4.0f;

    float viewer_to_screen =
        (double)sqrt((viewer_x - screen_x) * (viewer_x - screen_x) +
            (viewer_y - screen_y) * (viewer_y - screen_y) +
            (viewer_z - screen_z) * (viewer_z - screen_z));

    float light_x = 0.0f;
    float light_y = -5.0f;
    float light_z = -5.0f;

    float R = 2.0f;  // big radius
    float d = 1.0f;  // small radius
    float O = 0.0f;  // theta
    float t = 0.0f;  // phi
    float A = 0.0f;  // angle_A
    float B = 0.0f;  // angle_B

    float sphere_x = 0.0f;
    float sphere_y = 0.0f;
    float sphere_z = 0.0f;
    float radius_sphere = 0.5f;

    float x, y, z, cx, cy, cz, L, S, xd, yd, zd;

    float max_L = 0.0f;

    sf::VertexArray points(sf::Points);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML 3D Simulation");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float cosA = cos(A);
        float sinA = sin(A);
        float cosB = cos(B);
        float sinB = sin(B);

        for (float j = 0; j < 6.28; j += 0.015) {
            t = j;
            float cost = cos(t);
            float sint = sin(t);

            cx = R * cosB * cost + sinB * R * sinA * sint;
            cy = R * sinA * cosB * sint - R * sinB * cost;
            cz = R * cosA * sint;

            for (float i = 0; i < 6.28; i += 0.055) {
                O = i;

                float cosO = cos(O);
                float sinO = sin(O);

                // with reduced trignometric functions

                // ! 3rd line I changed sin to cos a
                // surface normal with respect to old light source
                // surface normal with respect to light source
                L = (double)((cosO * cost * cosB +
                    sinB * (sinO * cosA + cosO * sint * sinA)) *
                    light_x +
                    (cosB * (sinO * cosA + cosO * sinA * sint) -
                        cosO * cost * cosB) *
                    light_y +
                    (cosO * sint * cosA - sinO * sinA) * light_z) /
                    sqrt(light_x * light_x + light_y * light_y +
                        light_z * light_z);

                // //condition to limit the visibility
                // if (S >= 0) {
                if (1) {
                    x = (double)(R + d * cosO) *
                        (cosB * cost + sinA * sinB * sint) -
                        d * cosA * sinB * sinO;
                    y = (double)(R + d * cosO) *
                        (cost * sinB - cosB * sinA * sint) +
                        d * cosA * cosB * sinO;
                    z = (double)cosA * (R + d * cosO) * sint + d * sinA * sinO;

                    xd = (double)(x - viewer_x) * viewer_to_screen /
                        abs(y - viewer_y);
                    zd = (double)(z - viewer_z) * viewer_to_screen /
                        abs(y - viewer_y);

                    S = (double)(((x - cx) * (x - light_x)) +
                        ((y - cy) * (y - light_y)) +
                        ((z - cz) * (z - light_z)));

                    if (xd < screen_width / 2 && xd > -screen_width / 2 &&
                        zd < screen_height / 2 && zd > -screen_height / 2) {
                        sf::Vertex point;
                        point.position = sf::Vector2f(xd * window.getSize().x / 4 + screen_width * window.getSize().x / 8,
                            zd * window.getSize().y / 4 + screen_height * window.getSize().y / 8);
                        point.color = sf::Color(255 * (y / (2 * (R + d)) + 0.5),
                            255 * (y / (2 * (R + d)) + 0.5),
                            255 * (y / (2 * (R + d)) + 0.5));
                        points.append(point);
                    }

                }
            }
        }

        // howw fast the donut rotates
        A += 0.005;
        B += 0.003;


        window.clear(sf::Color::Black);
        window.draw(points);
        window.display();
        points.clear();
    }
}
