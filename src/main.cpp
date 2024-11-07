#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  // Include for audio functionality
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

int windowWidth = 1000;
int windowHeight = 560;


// Define the SnakeSegment struct
struct SnakeSegment {
    sf::CircleShape shape;            // The graphical representation of the segment (circle instead of rectangle)
    int direction;                   // Direction of movement: 0 = up, 1 = down, 2 = left, 3 = right
    sf::Vector2f previousPosition;   // The previous position of the segment
    sf::Vector2f targetPosition;     // The position the segment is trying to reach
};

// Function to spawn the food at a random position
sf::Vector2f getRandomPosition(const std::vector<std::string>& map, int cellWidth, int cellHeight) {
    int rows = map.size();
    int cols = map[0].size();
    int x, y;

    do {
        x = rand() % cols;
        y = rand() % rows;
    } while (map[y][x] == '#'); // Ensure food does not spawn on walls

    return sf::Vector2f(x * cellWidth, y * cellHeight);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Snake", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    std::vector<std::string> map;
    std::ifstream file("map.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file map.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }

    if (map.empty()) {
        std::cerr << "Error: No map data available. Exiting the program." << std::endl;
        return 1;
    }

    int cellWidth = windowWidth / map[0].size();
    int cellHeight = windowHeight / map.size();

    // Load wall and grass textures
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("resources/8bit-water-texture-sq.png")) {
        std::cerr << "Failed to load the wall texture." << std::endl;
        return 1;
    }
    wallTexture.setSmooth(true);

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("resources/grass.png")) {
        std::cerr << "Failed to load the grass texture." << std::endl;
        return 1;
    }
    grassTexture.setSmooth(true);

    sf::Sprite grassSprite(grassTexture);

    // Initialize snake with a head and a few segments
    int initialSnakeLength = 3;
    std::vector<SnakeSegment> snake;
    SnakeSegment head;
    head.shape.setRadius(cellWidth / 2); // Set radius to half of the cell width
    head.shape.setFillColor(sf::Color::Green);
    head.shape.setPosition(100, 100);
    head.direction = 3;
    snake.push_back(head);

    for (int i = 1; i < initialSnakeLength; ++i) {
        SnakeSegment segment;
        segment.shape.setRadius(cellWidth / 2); // Set radius to half of the cell width
        segment.shape.setFillColor(sf::Color::Yellow);
        segment.shape.setPosition(100 - i * cellWidth, 100);
        segment.direction = 3;
        snake.push_back(segment);
    }

    int snakeDirection = 3;
    sf::Clock clock;
    float moveInterval = 0.1f;

    // Initialize food item with apple texture
    sf::Texture appleTexture;
    if (!appleTexture.loadFromFile("resources/apple.png")) {
        std::cerr << "Failed to load apple texture." << std::endl;
        return 1;
    }

    sf::RectangleShape food(sf::Vector2f(cellWidth, cellHeight));
    food.setTexture(&appleTexture);
    food.setPosition(getRandomPosition(map, cellWidth, cellHeight));

    // Initialize score collectible item
    sf::Texture scoreTexture;
    if (!scoreTexture.loadFromFile("resources/score.png")) {
        std::cerr << "Failed to load score item texture." << std::endl;
        return 1;
    }

    sf::RectangleShape scoreItem(sf::Vector2f(cellWidth, cellHeight));
    scoreItem.setTexture(&scoreTexture);
    scoreItem.setPosition(getRandomPosition(map, cellWidth, cellHeight));

    // Initialize shrink item (new collectible)
    sf::Texture shrinkTexture;
    if (!shrinkTexture.loadFromFile("resources/shrink.png")) {
        std::cerr << "Failed to load shrink item texture." << std::endl;
        return 1;
    }

    sf::RectangleShape shrinkItem(sf::Vector2f(cellWidth, cellHeight));
    shrinkItem.setTexture(&shrinkTexture);
    shrinkItem.setPosition(getRandomPosition(map, cellWidth, cellHeight));

    // Load background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("resources/fresh-water-fulldemo.mp3")) {
        std::cerr << "Error: Could not load background music" << std::endl;
        return 1;
    }
    backgroundMusic.setLoop(true);  // Loop the music
    backgroundMusic.play();  // Start the music

    int score = 0;

    // Create text to display score and snake length
    sf::Font font;
    if (!font.loadFromFile("resources/font.ttf")) {
        std::cerr << "Error: Could not load font." << std::endl;
        return 1;
    }

    sf::Text scoreText("Score: 0", font, 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth - 200, 20);

    sf::Text lengthText("Length: 3", font, 24);
    lengthText.setFillColor(sf::Color::White);
    lengthText.setPosition(windowWidth - 200, 50);

    // Define two rectangle shapes
    sf::RectangleShape horizontalRect(sf::Vector2f(100.f, 20.f)); // Horizontal rectangle
    horizontalRect.setFillColor(sf::Color::Red);
    horizontalRect.setPosition(50.f, windowHeight / 2.f); // Starting position

    sf::RectangleShape verticalRect(sf::Vector2f(20.f, 100.f)); // Vertical rectangle
    verticalRect.setFillColor(sf::Color::Blue);
    verticalRect.setPosition(windowWidth / 2.f, 50.f); // Starting position

    // Set initial speeds for both rectangles
    float horizontalSpeed = 5.f;
    float verticalSpeed = 3.f;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && snakeDirection != 1) {
                    snakeDirection = 0;
                }
                else if (event.key.code == sf::Keyboard::Down && snakeDirection != 0) {
                    snakeDirection = 1;
                }
                else if (event.key.code == sf::Keyboard::Left && snakeDirection != 3) {
                    snakeDirection = 2;
                }
                else if (event.key.code == sf::Keyboard::Right && snakeDirection != 2) {
                    snakeDirection = 3;
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() >= moveInterval) {
            clock.restart(); // Restart clock for next move interval

            sf::Vector2f newHeadPosition = snake[0].shape.getPosition();
            switch (snakeDirection) {
            case 0: newHeadPosition.y -= cellHeight; break; // Move up
            case 1: newHeadPosition.y += cellHeight; break; // Move down
            case 2: newHeadPosition.x -= cellWidth; break;  // Move left
            case 3: newHeadPosition.x += cellWidth; break;  // Move right
            }

            // Check for collision with walls
            int headRow = newHeadPosition.y / cellHeight;
            int headCol = newHeadPosition.x / cellWidth;
            if (headRow >= 0 && headRow < map.size() && headCol >= 0 && headCol < map[0].size() && map[headRow][headCol] == '#') {
                std::cout << "Game Over! The snake hit a wall." << std::endl;
                window.close();
                break;
            }

            // Check if snake hits its own body
            for (size_t i = 1; i < snake.size(); ++i) {  // Start from 1 to avoid checking the head against itself
                if (snake[0].shape.getGlobalBounds().intersects(snake[i].shape.getGlobalBounds())) {
                    std::cout << "Game Over! The snake hit its own body." << std::endl;
                    window.close();
                    break;
                }
            }

            // Check if snake eats the food
            if (snake[0].shape.getGlobalBounds().intersects(food.getGlobalBounds())) {
                SnakeSegment newSegment;
                newSegment.shape.setRadius(cellWidth / 2); // Set radius to half of the cell width
                newSegment.shape.setFillColor(sf::Color::Yellow);
                newSegment.shape.setPosition(snake.back().shape.getPosition());
                snake.push_back(newSegment);
                food.setPosition(getRandomPosition(map, cellWidth, cellHeight));  // Reposition food
            }

            // Check if snake eats the score item
            if (snake[0].shape.getGlobalBounds().intersects(scoreItem.getGlobalBounds())) {
                score += 10;  // Increase score by 10 points
                scoreItem.setPosition(getRandomPosition(map, cellWidth, cellHeight));  // Reposition score item
            }

            // Check if snake eats the shrink item
            if (snake[0].shape.getGlobalBounds().intersects(shrinkItem.getGlobalBounds())) {
                if (snake.size() > 1) {
                    snake.pop_back();  // Shrink snake by removing the last segment
                }
                shrinkItem.setPosition(getRandomPosition(map, cellWidth, cellHeight));  // Reposition shrink item
            }

            // Update snake segments (move body segments)
            for (size_t i = snake.size() - 1; i > 0; --i) {
                snake[i].shape.setPosition(snake[i - 1].shape.getPosition());
            }
            snake[0].shape.setPosition(newHeadPosition);  // Update head position

            // Move the rectangles
            horizontalRect.move(horizontalSpeed, 0);  // Move horizontally
            verticalRect.move(0, verticalSpeed);     // Move vertically

            // Check if the rectangles hit the window boundaries and reverse their direction if so
            if (horizontalRect.getPosition().x + horizontalRect.getSize().x > windowWidth || horizontalRect.getPosition().x < 0) {
                horizontalSpeed = -horizontalSpeed;  // Reverse horizontal direction
            }
            if (verticalRect.getPosition().y + verticalRect.getSize().y > windowHeight || verticalRect.getPosition().y < 0) {
                verticalSpeed = -verticalSpeed;  // Reverse vertical direction
            }

            // Check for collision with moving rectangles
            if (snake[0].shape.getGlobalBounds().intersects(horizontalRect.getGlobalBounds())) {
                std::cout << "Game Over! The snake hit the horizontal rectangle." << std::endl;
                window.close();
                break; // End the game loop
            }

            if (snake[0].shape.getGlobalBounds().intersects(verticalRect.getGlobalBounds())) {
                std::cout << "Game Over! The snake hit the vertical rectangle." << std::endl;
                window.close();
                break; // End the game loop
            }

            // Update score and snake length display
            scoreText.setString("Score: " + std::to_string(score));
            lengthText.setString("Length: " + std::to_string(snake.size()));
        }


        window.clear();

        // Draw the map with walls and grass
        for (int y = 0; y < windowHeight; y += grassTexture.getSize().y) {
            for (int x = 0; x < windowWidth; x += grassTexture.getSize().x) {
                grassSprite.setPosition(x, y);
                window.draw(grassSprite);
            }
        }

        for (size_t y = 0; y < map.size(); ++y) {
            for (size_t x = 0; x < map[y].size(); ++x) {
                if (map[y][x] == '#') {
                    sf::RectangleShape wall(sf::Vector2f(cellWidth, cellHeight));
                    wall.setPosition(x * cellWidth, y * cellHeight);
                    wall.setTexture(&wallTexture);
                    window.draw(wall);
                }
            }
        }

        // Draw food, shrink item, and score collectible item
        window.draw(food);
        window.draw(shrinkItem);
        window.draw(scoreItem);

        // Draw the snake
        for (const auto& segment : snake) {
            window.draw(segment.shape);
        }

        
        window.draw(horizontalRect);
        window.draw(verticalRect);
        // Draw score and length text
        window.draw(scoreText);
        window.draw(lengthText);

        window.display();
    }

    return 0;
}
