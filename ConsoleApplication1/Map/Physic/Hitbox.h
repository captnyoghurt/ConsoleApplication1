#pragma once

#include <SFML/Graphics.hpp>

class Hitbox
{
public:
	Hitbox();
	Hitbox(const int &id, const int &x, const int &y, const int &w, const int &h);
	Hitbox(const int &id, const sf::Rect<int> &r);
	Hitbox(const Hitbox &hb);
	~Hitbox();

public:
	// Return the id of the Hitbox
	int getId() const;
	// Return the abciss of the Hitbox
	int getX() const;
	// Return the y position of the Hitbox
	int getY() const;
	// Return the width of the Hitbox
	int getWidth() const;
	// Return the height of the Hitbox
	int getHeight() const;

	// Modify the id of the Hitbox
	int setId(const int &id);
	// Modify the abciss of the Hitbox
	int setX(const int &x);
	// Modify the y position of the Hitbox
	int setY(const int &y);
	// Modify the width of the Hitbox
	int setWidth(const int &w);
	// Modify the height of the Hitbox
	int setHeight(const int &h);

	// Modify x & y of the Hitbox
	int move(const int &dx, const int &dy);
	// Move to a position
	int moveTo(const int &x, const int &y);

public:
	int m_id;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

