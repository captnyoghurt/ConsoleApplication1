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
 *  A choice in the menu choice.
 *
 */

#include "M_choice.h"
#include "../Error/InitializationException.h"
#include "../Error/ValueException.h"
#include "../constants.h"

M_choice::M_choice() {
  m_initialized = false;
  m_shown = false;
  m_enabled = true;
  m_x = 0;
  m_y = 0;
}

M_choice::M_choice(const M_choice &ch) {
  m_initialized = ch.getInitialized();
  m_shown = ch.getShown();
  m_enabled = true;
  m_x = 0;
  m_y = 0;
}

M_choice::~M_choice() {}

M_choice &M_choice::operator=(const M_choice &ch) {
  m_initialized = ch.getInitialized();
  m_shown = ch.getShown();
  m_enabled = true;
  m_x = ch.getX();
  m_y = ch.getY();

  return *this;
}

// Return if the choice has been initialized
bool M_choice::getInitialized() const { return m_initialized; }

// Return if the choice should be shown
bool M_choice::getShown() const { return m_shown; }

// Return if the choice is enabled
bool M_choice::getEnabled() const { return m_enabled; }

// Return the surface of the choice
std::list<
    std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator
M_choice::getSurface() {
  return m_textureManager.getRenderTextureSurface();
}

// Return the action made by the choice
IG_Action M_choice::getAction() const { return m_action; }

// Return the position X of the choice on the screen
int M_choice::getX() const {
  if (!m_initialized) THROW_INIT("getter");
  return m_x;
}

// Return the position Y of the choice on the screen
int M_choice::getY() const {
  if (!m_initialized) THROW_INIT("getter");
  return m_y;
}

// Return the surface of the choice with modifying possibilities
std::list<
    std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator &
M_choice::getRealSurface() {
  return m_textureManager.getRealRenderTextureSurface();
}

// Return the render texture manager with modifying possibilities
ManageRenderTexture &M_choice::getRealRenderTextureManager() {
  return m_textureManager;
}

// Modify if the choice should be shown
int M_choice::setShown(const bool &b, const int &dx, const int &dy) {
  m_shown = b;
  m_textureManager.getRealRenderTextureSurface()->second->setDimensions(
      m_x + dx, m_y + dy,
      m_textureManager.getRealRenderTextureSurface()->second->getWidth(),
      m_textureManager.getRealRenderTextureSurface()->second->getHeight());
  m_textureManager.getRealRenderTextureSurface()->second->setEnable(b);
  return 0;
}

// Modify if the choice should be enabled
int M_choice::setEnabled(const bool &b) {
  m_enabled = b;

  return 0;
}

// Modify the action made by the choice
int M_choice::setAction(IG_Action &act) {
  m_action.setAction(act.getAction());

  return 0;
}

// Modify the position X of the choice on the screen
int M_choice::setX(const int &x) {
  m_x = x;
  return 0;
}

// Modify the position Y of the choice on the screen
int M_choice::setY(const int &y) {
  m_y = y;
  return y;
}

// Load the choice
int M_choice::load(ManageSurfaces &surf, const std::string &str, sf::Font &f,
                   const int &x, const int &y, const bool &sh, IG_Action &act,
                   const int &w, const int &h) {
  if (m_initialized) THROW_INIT("Already initiate");

  m_x = x;
  m_y = y;

  setAction(act);
  auto surfaceText = surf.addSurface(ManageSurfaces::e_thing::TEXT,
                                     std::make_shared<SurfaceText>());
  std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)->setString(str);
  std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)->setFont(f);
  std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)
      ->setCharacterSize(MENU_SIMPLE_FONTSIZE);
  std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)
      ->setDimensions(
          x, y,
          int(std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)
                  ->getLocalBounds()
                  .width),
          int(std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)
                  ->getLocalBounds()
                  .height));
  std::dynamic_pointer_cast<SurfaceText>(surfaceText->second)
      ->setPosition(0.0, 0.0);

  m_textureManager.load(surf, x, y, MAX(w, surfaceText->second->getWidth()),
                        MAX(h, MENUS_GAP_BETWEEN_LINES));
  m_textureManager.add(surfaceText);

  m_shown = sh;
  m_textureManager.update();

  m_initialized = true;

  return 0;
}

// Clear the surfaces of the choice
int M_choice::clear(ManageSurfaces &surf) {
  return m_textureManager.clear(surf);
}