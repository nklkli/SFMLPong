module;
#include "pch.h"
export module Pong;
import Bat;
import Ball;
import std;
using namespace sf;

void log(std::string&& msg) {
	static auto tz = std::chrono::current_zone();
	auto tp = tz->to_local(std::chrono::system_clock::now());
	std::println("{:%H:%M:%S} {}", tp, msg);
}


export
int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	sf::RenderWindow window(
		//sf::VideoMode(desktop.size, desktop.bitsPerPixel)
		sf::VideoMode({ 800, 600 })
		, "Pong"
		, sf::Style::Default
		//, sf::State::Fullscreen
	);

	window.setVerticalSyncEnabled(true);



	int score = 0;
	int lives = 3;

	// Create a bat at the bottom center of the screen
	Bat bat{ window.getSize().x / 2.f, window.getSize().y - 20.f };

	Ball ball{ window.getSize().x / 2.f, 30 };

	// A cool retro-style font
	Font font{ "assets/fonts/DS-DIGIT.TTF" };

	// We will add a ball in the next chapter
	// Create a Text object called HUD
	Text hud{ font };
	// Make it nice and big
	hud.setCharacterSize(40);
	// Choose a color
	hud.setFillColor(Color::White);
	hud.setPosition({ 20, 20 });

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		****************************
		****************************
		****************************
		*/
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			if (const auto kp = event->getIf<Event::KeyPressed>())
			{
				// Handle the player quitting
				if (kp->scancode == Keyboard::Scancode::Escape)
				{
					window.close();
				}
			}			
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			bat.moveLeft();
		}else
		{
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}


		
		// Update the bat, the ball and the HUD
		
		
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);

		// Update the HUD text
		hud.setString(std::format("Score: {}    Lives: {}", score, lives));

		// Handle ball hitting the bottom
		if (ball.getPosition().position.y > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();
			// Remove a life
			lives--;
			// Check for zero lives
			if (lives < 1) {
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
			}
			log("reboundBottom");
		}

		// Handle ball hitting top
		if (ball.getPosition().position.y < 0)
		{
			ball.reboundBatOrTop();
			// Add a point to the players score
			score++;
			log("reboundBatOrTop");
		}

		// Handle ball hitting sides
		if (ball.getPosition().position.x < 0 ||
			ball.getPosition().position.x + ball.getPosition().size.x > window.getSize().x)
		{
			ball.reboundSides();
			log("reboundSides");
		}

		// Has the ball hit the bat?
		const auto& r = 
			ball.getPosition().findIntersection(bat.getPosition());

		auto r1 = bat.getPosition();
		auto r2 = ball.getPosition();

		//auto r = r1.findIntersection(r2);

		if (r.has_value())
		{			
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
			log("Ball hits Bat; reboundBatOrTop");
			/*std::println("x={}; y={}; w={}; h={}", 
				r->position.x, r->position.y,
				r->size.x, r->size.y);*/
		}


		/*
		Draw the bat, the ball and the HUD
		*****************************
		*****************************
		*****************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();


	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
