/**
 *  @file
 *  @author  Paul Coignet
 *  @date    11 / 11 / 2017
 *  @version 0.1
 *
 *  @brief Class header.
 *
 *  @section DESCRIPTION
 *
 *  Mother class of surfaces.
 *
 */

#include "Surface.h"
#include "../Error/debugFunctions.h"

Surface::Surface() {
  m_enable = true;
  m_x = 0;
  m_y = 0;
  m_width = 0;
  m_height = 0;
#ifdef DEBUG_MODE_ON
  DEB_ALLOCATED_SURFACE++;
#endif  // DEBUG_MODE_ON
}

Surface::~Surface() {
#ifdef DEBUG_MODE_ON
  DEB_ALLOCATED_SURFACE--;
#endif  // DEBUG_MODE_ON
}

// Return if it should be printed
bool Surface::getEnable() const { return m_enable; }

// Return the abciss of the Surface
int Surface::getX() const { return m_x; }

// Return the y position of the Surface
int Surface::getY() const { return m_y; }

// Return the width of the Surface
int Surface::getWidth() const { return m_width; }

// Return the height of the Surface
int Surface::getHeight() const { return m_height; }

// Modify if it should be printed
int Surface::setEnable(const bool &e) {
  m_enable = e;
  return 0;
}

// Modify the abciss of the Surface
int Surface::setX(const int &x) {
  if (x < 0) return -1;

  m_x = x;
  return 0;
}

// Modify the y position of the Surface
int Surface::setY(const int &y) {
  if (y < 0) return -1;

  m_y = y;
  return 0;
}

// Modify the width of the Surface
int Surface::setWidth(const int &w) {
  if (w < 0) return -1;

  m_width = w;
  return 0;
}

// Modify the height of the Surface
int Surface::setHeight(const int &h) {
  if (h < 0) return -1;

  m_height = h;
  return 0;
}

// Modify everything
int Surface::setDimensions(const int &x, const int &y, const int &w,
                           const int &h) {
  int ret = setX(x) + setY(y);

  if (w != -1) ret += setWidth(w);
  if (h != -1) ret += setHeight(h);

  return ret;
}