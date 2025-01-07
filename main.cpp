#include <iostream>
#include <sfml/Graphics.hpp>
#include <math.h>
#include <array>

// Function to compute the cross product of two vectors
sf::Vector3f crossProduct(const sf::Vector3f& a, const sf::Vector3f& b) {
    return sf::Vector3f(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// Function to compute the dot product of two vectors
float dotProduct(const sf::Vector3f& a, const sf::Vector3f& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to normalize a vector
sf::Vector3f normalize(const sf::Vector3f& v) {
    float magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return sf::Vector3f(v.x / magnitude, v.y / magnitude, v.z / magnitude);
}

// Function to compute (u, v) coordinates for projection
std::pair<float, float> computeUV(const sf::Vector3f& point, const sf::Vector3f& center,
    const sf::Vector3f& basisU, const sf::Vector3f& basisV) {
    sf::Vector3f vectorToPoint = sf::Vector3f(point.x - center.x, point.y - center.y, point.z - center.z);
    int u = dotProduct(vectorToPoint, basisU);
    int v = dotProduct(vectorToPoint, basisV);
    return { u, v };
}

int main() {
    float camera_x = 0.0f;
    float camera_y = 0.0f;
    float camera_z = 0.0f;

    float camera_angle_x = 0.0f;
    float camera_angle_y = 0.0f;
    float camera_angle_z = 0.0f;

    float focal_length = 1.0f;

    float donut_x = 0.0f;
    float donut_y = 4.0f;
    float dunut_y = 0.0f;

    float donut_angle_x = 0.0f;
    float donut_angle_y = 0.0f;
    float donut_angle_z = 0.0f;

    float donut_radius = 3.0f;
    float donut_radius2 = 1.0f;

    float screen_width = 4.0f;
    float screen_height = 4.0f;

    // float viewer_to_screen =
    //     (double)sqrt((viewer_x - screen_x) * (viewer_x - screen_x) +
    //         (viewer_y - screen_y) * (viewer_y - screen_y) +
    //         (viewer_z - screen_z) * (viewer_z - screen_z));

    float light_x = 0.0f;
    float light_y = -5.0f;
    float light_z = -5.0f;

    // teamporary values
    float O = 0.0f;  // theta
    float t = 0.0f;  // phi
    float A = 0.0f;  // angle_A
    float B = 0.0f;  // angle_B

    float x, y, z, cx, cy, cz, L, S, xd, yd, zd;

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

            cx = donut_radius * cosB * cost + sinB * donut_radius * sinA * sint;
            cy = donut_radius * sinA * cosB * sint - donut_radius * sinB * cost;
            cz = donut_radius * cosA * sint;

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

                x = (double)(donut_radius + donut_radius2 * cosO) *
                    (cosB * cost + sinA * sinB * sint) -
                    donut_radius2 * cosA * sinB * sinO;
                y = (double)(donut_radius + donut_radius2 * cosO) *
                    (cost * sinB - cosB * sinA * sint) +
                    donut_radius2 * cosA * cosB * sinO;
                z = (double)cosA * (donut_radius + donut_radius2 * cosO) * sint + donut_radius2 * sinA * sinO;

                xd = (double)(x - camera_x) * focal_length /
                    abs(y - camera_y);
                zd = (double)(z - camera_z) * focal_length /
                    abs(y - camera_y);

                S = (double)(((x - cx) * (x - light_x)) +
                    ((y - cy) * (y - light_y)) +
                    ((z - cz) * (z - light_z)));

                if (xd < screen_width / 2 && xd > -screen_width / 2 &&
                    zd < screen_height / 2 && zd > -screen_height / 2) {
                    sf::Vertex point;
                    point.position = sf::Vector2f(xd * window.getSize().x / 4 + screen_width * window.getSize().x / 8,
                        zd * window.getSize().y / 4 + screen_height * window.getSize().y / 8);
                    point.color = sf::Color(255 * (y / (2 * (donut_radius + donut_radius2)) + 0.5),
                        255 * (y / (2 * (donut_radius + donut_radius2)) + 0.5),
                        255 * (y / (2 * (donut_radius + donut_radius2)) + 0.5));
                    points.append(point);
                }

                sf::Vector3f normalVector(x - 1, y - 1, z - 8);
                sf::Vector3f arbitraryVector = (normalVector.x != 0) ? sf::Vector3f(1, 0, 0) : sf::Vector3f(0, 1, 0);

                // Compute basis vectors
                sf::Vector3f basisU = normalize(crossProduct(normalVector, arbitraryVector));
                sf::Vector3f basisV = normalize(crossProduct(normalVector, basisU));

                sf::Vector3f centerPoint(1, 1, 8);

                sf::Vector3f pointIn3d(x, y, z);

                auto uv1 = computeUV(pointIn3d, centerPoint, basisU, basisV);

                // std::cout << "UV: (" << uv1.first << ", " << uv1.second << ")\n";
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
