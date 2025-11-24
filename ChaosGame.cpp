// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

   // Load font on screen
    Font font;
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        cout << "ERROR: Could not load arial.ttf\n";
    }

    // Instruction text
    Text instructions;
    instructions.setFont(font);
    instructions.setFillColor(Color::White);
    instructions.setCharacterSize(24);
    instructions.setPosition(20, 20);
    instructions.setString("Click 3 times to set triangle vertices.\n"
        "Click 4th time to start Chaos Game.");

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    //Random Number Generator
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(0, 2);  // picks a vertex index 0..2

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "Left Click at ("
                        << event.mouseButton.x << ", "
                        << event.mouseButton.y << ")\n";

                    //First 3 clicks for triangle vertices
                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }

                    // 4th click for starting point
                    else if (points.size() == 0)
                    {
                        // Insert the starting point for Chaos Game
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */

        
        // Only run the Chaos Game if the user has clicked:
        //   3 vertices + 1 starting point
        if (points.size() > 0 && vertices.size() == 3)
        {
            // Generate multiple points per frame for speed
            for (int i = 0; i < 1000; i++)  
            {
                // pick a random vertex index 0..2
                int idx = dist(rng);

                // last generated point
                Vector2f last = points.back();

                // chosen vertex
                Vector2f v = vertices[idx];

                // midpoint formula for Chaos Game
                // nextPoint = (last + vertex) / 2
                Vector2f next((last.x + v.x) / 2.0f,
                    (last.y + v.y) / 2.0f);

                points.push_back(next);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // Draw instructions text
        window.draw(instructions);

        // Draw vertices (BLUE SQUARES)
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

       //Draw chaos points
        for (int i = 0; i < points.size(); i++)
        {
            CircleShape dot(1);
            dot.setFillColor(Color::White);
            dot.setPosition(points[i]);
            window.draw(dot);
        }

        window.display();
    }
}
