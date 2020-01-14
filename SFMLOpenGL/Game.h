#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <Vector3.h>
#include <Matrix3.h>




class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	sf::Clock clock;
	sf::Time elapsed;
	float scale{0.0f};
	vector3 translation{0,0,0};
	vector3 rotation{0,0,0};
	float rotationAngle = 1.0f;
};