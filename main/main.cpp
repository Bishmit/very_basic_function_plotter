#include <SFML/Graphics.hpp>
#include <cmath>

#define WIDTH 1000
#define HEIGHT 500

// Function definition (sine function)
float y(double x) {
    return 1.0f / (1.0f + std::exp(-x)); //sigmoid function 
    // for now you can only see the function which have one y of f(x) i.e for function like (x^2 + y^2 -1)^3 = x^2.y^3 it won't work since y has power 3 and it overloads in function 
    // to resolve this we can either take extra argument and pass it but that was causing weird behaviour so i skip that 
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sine Function Plotter");
    window.setFramerateLimit(60);

    sf::VertexArray graph(sf::LineStrip);
    sf::VertexArray grid(sf::Lines);

    // Define scale factors to fit the graph into the window
    float scaleX = WIDTH / 20.0f; // Scaling factor for the x-axis
    float scaleY = HEIGHT / 10.0f; // Scaling factor for the y-axis

    // Center of the window
    float centerX = WIDTH / 2;
    float centerY = HEIGHT / 2;

    // Add thicker lines for x and y axes
    sf::Color axisColor(255, 255, 0); 
    sf::Color gridColor(255, 255, 0, 300); 


    // Draw x-axis
    grid.append(sf::Vertex(sf::Vector2f(0, centerY), axisColor));
    grid.append(sf::Vertex(sf::Vector2f(WIDTH, centerY), axisColor));

    // Draw y-axis
    grid.append(sf::Vertex(sf::Vector2f(centerX, 0), axisColor));
    grid.append(sf::Vertex(sf::Vector2f(centerX, HEIGHT), axisColor));

    // Iterate over x-values
    for (double i = -10; i <= 10; i += 0.001) {
        // Calculate the corresponding y-value
        float x = static_cast<float>(i);
        float yVal = static_cast<float>(y(i));

        // Apply scaling and translation to match math coordinates
        x *= scaleX;
        yVal *= scaleY;
        x += centerX;
        yVal = centerY - yVal; // Invert y-axis to match math coordinates

        // Add the point to the graph
        graph.append(sf::Vertex(sf::Vector2f(x, yVal), sf::Color::White));
    }

    // Add grid lines
    for (int i = -10; i <= 10; ++i) {
        // Skip lines for the axes
        if (i == 0) continue;

        // Vertical lines
        grid.append(sf::Vertex(sf::Vector2f(centerX + i * scaleX, 0), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(centerX + i * scaleX, HEIGHT), gridColor));

        // Horizontal lines
        grid.append(sf::Vertex(sf::Vector2f(0, centerY + i * scaleY), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(WIDTH, centerY + i * scaleY), gridColor));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw grid lines
        window.draw(grid);

        // Draw graph
        window.draw(graph);

        window.display();
    }


    return 0;
}