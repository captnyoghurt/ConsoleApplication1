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
 *  Menu on the sides of the battle.
 *
 */

#include "MenuBattleSide.h"
#include <functional>
#include "../Battle/Fighters/Enemies.h"
#include "../Battle/Fighters/TeamBattle.h"
#include "../Battle/Status/Health.h"
#include "../Battle/Status/Mana.h"
#include "../Battle/Status/SkillPoints.h"
#include "../Error/InitializationException.h"
#include "../Error/ValueException.h"
#include "../Game.h"
#include "../Map/ManageSurfaces.h"
#include "../Map/SurfaceText.h"
#include "../constants.h"

MenuBattleSide::MenuBattleSide(ManageRessources& ress, ManageSurfaces& surf,
                               int lastEventLayer, int type)
    : Menu(ress, surf, lastEventLayer) {
  m_barType = type;

  m_cursorSurfaceRight = surf.addSurface(ManageSurfaces::e_thing::SPRITE,
                                         std::make_shared<SurfaceSprite>());

  std::dynamic_pointer_cast<SurfaceSprite>(m_cursorSurfaceRight->second)
      ->setTexture(ress.getTheTexture(RESSOURCE_TEXTURE_NUMBER_MENU));
  std::dynamic_pointer_cast<SurfaceSprite>(m_cursorSurfaceRight->second)
      ->setTextureRect(sf::IntRect(
          MENU_SURFACE_CURSOR_RIGHT_BEGIN_X, MENU_SURFACE_CURSOR_RIGHT_BEGIN_Y,
          MENU_SURFACE_CURSOR_RIGHT_WIDTH, MENU_SURFACE_CURSOR_RIGHT_HEIGHT));

  m_selectedChoice = 0;
  m_initialized = false;
  m_numberMaxChoices = TEAM_BATTLE_MAX_NUMBER;
}

MenuBattleSide::~MenuBattleSide() {}

// Return the cursor for the right surface
std::list<
    std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface> > >::iterator
MenuBattleSide::getCursor() {
  return m_cursorSurfaceRight;
}

// Return the current selected choice
int MenuBattleSide::getSelectedChoice() const { return m_selectedChoice; }

// Return the maximum number of choices
int MenuBattleSide::getNumberMaxChoices() const { return m_numberMaxChoices; }

// Return all the choices with modifying possibilities
std::vector<std::shared_ptr<M_choice> >& MenuBattleSide::getChoices() {
  return m_choices;
}

// Modify if the menu should be shown or not
int MenuBattleSide::setShown(const bool& b) {
  if (b) {
    int temp = 0;
    while (!m_choices.at(temp)->getEnabled()) {
      temp++;
      if ((unsigned)temp >= m_choices.size()) return -1;
    }
    setSelectedChoice(temp);
  }

  return m_cursorSurfaceRight->second->setEnable(b);
}

// Modify the current selected choice
int MenuBattleSide::setSelectedChoice(const int& s) {
  if ((unsigned)s < m_choices.size()) {
    int temp = s;
    // Set choices to down
    if (m_selectedChoice < s) {
      while (!m_choices.at(temp)->getEnabled()) {
        temp++;
        if ((unsigned)temp >= m_choices.size()) return -1;
      }
    }
    // Set choices to up
    else if (m_selectedChoice > s) {
      while (!m_choices.at(temp)->getEnabled()) {
        temp--;
        if (temp < 0) return -1;
      }
    } else {
      while (!m_choices.at(temp)->getEnabled()) {
        temp++;
        if ((unsigned)temp >= m_choices.size()) temp = 0;
        if (temp == s) return -1;
      }
    }

    m_selectedChoice = temp;

    m_cursorSurfaceRight->second->setDimensions(
        m_choices.at(temp)->getX() - MENU_SURFACE_CURSOR_RIGHT_WIDTH,
        m_choices.at(temp)->getY(),
        (int)std::dynamic_pointer_cast<SurfaceSprite>(
            m_cursorSurfaceRight->second)
            ->getGlobalBounds()
            .width,
        (int)std::dynamic_pointer_cast<SurfaceSprite>(
            m_cursorSurfaceRight->second)
            ->getGlobalBounds()
            .height);

    return 0;
  }

  return -1;
}

// Modify the maximum number of choices
int MenuBattleSide::setNumberMaxChoices(const int& c) {
  if ((unsigned)c < (unsigned)TEAM_BATTLE_MAX_NUMBER) {
    m_numberMaxChoices = c;

    if (m_selectedChoice >= m_numberMaxChoices) m_selectedChoice = c - 1;

    return 0;
  }

  return -1;
}

// Update the surfaces according to the ressource given
int MenuBattleSide::updateBar(int n, MenuBattleSide::e_menuBattleSideItems type,
                              int act, int max) {
  double ratio = (double)(act) / (double)(max);

  if (ratio < 0.0) ratio = 0;

  if (!((unsigned)n < m_choices.size()))
    THROW_GAME("Bad value " + std::to_string(n));
  if ((type != MenuBattleSide::e_menuBattleSideItems::HP_IMAGE) &&
      (type != MenuBattleSide::e_menuBattleSideItems::MP_IMAGE) &&
      (type != MenuBattleSide::e_menuBattleSideItems::TP_IMAGE))
    THROW_VALUE(std::to_string(type));

  // Update the bar surface
  std::dynamic_pointer_cast<SurfaceSprite>(m_choices.at(n)
                                               ->getRealRenderTextureManager()
                                               .getTheSurface((int)type)
                                               ->second)
      ->setTextureRect(sf::IntRect((int)((1.0 - ratio) * HEALTH_SURFACE_WIDTH),
                                   std::dynamic_pointer_cast<SurfaceSprite>(
                                       m_choices.at(n)
                                           ->getRealRenderTextureManager()
                                           .getTheSurface((int)type)
                                           ->second)
                                       ->getTextureRect()
                                       .top,
                                   std::dynamic_pointer_cast<SurfaceSprite>(
                                       m_choices.at(n)
                                           ->getRealRenderTextureManager()
                                           .getTheSurface((int)type)
                                           ->second)
                                       ->getTextureRect()
                                       .width,
                                   std::dynamic_pointer_cast<SurfaceSprite>(
                                       m_choices.at(n)
                                           ->getRealRenderTextureManager()
                                           .getTheSurface((int)type)
                                           ->second)
                                       ->getTextureRect()
                                       .height));

  // Update the text surface
  std::string text;

  if (type == MenuBattleSide::e_menuBattleSideItems::HP_IMAGE)
    text = HEALTH_NAME;
  else if (type == MenuBattleSide::e_menuBattleSideItems::MP_IMAGE)
    text = MANA_NAME;
  else
    text = SKILLPOINTS_NAME;

  text = text + " " + std::to_string(act) + "/" + std::to_string(max);

  std::dynamic_pointer_cast<SurfaceText>(m_choices.at(n)
                                             ->getRealRenderTextureManager()
                                             .getTheSurface((int)(type - 1))
                                             ->second)
      ->setString(text);

  return 0;
}

// Update health bar & text
int MenuBattleSide::updateHealth(int n, const Health& hp) {
  return updateBar(n, MenuBattleSide::e_menuBattleSideItems::HP_IMAGE,
                   hp.getPoints(), hp.getMaxPoints());
}

// Update mana bar & text
int MenuBattleSide::updateMana(int n, const Mana& mp) {
  return updateBar(n, MenuBattleSide::e_menuBattleSideItems::MP_IMAGE,
                   mp.getPoints(), mp.getMaxPoints());
}

// Update skillpoints bar & text
int MenuBattleSide::updateSkillPoints(int n, const SkillPoints& sp) {
  return updateBar(n, MenuBattleSide::e_menuBattleSideItems::TP_IMAGE,
                   sp.getPoints(), sp.getMaxPoints());
}

// Load with an allie team
int MenuBattleSide::loadWithEnemies(ManageRessources& ress,
                                    ManageSurfaces& surf, Enemies& enemies) {
  if (m_barType != MenuBattleSide::e_menuBattleSideBarType::MENU_BATTLE_ENEMIE)
    THROW_VALUE(std::to_string(m_barType));

  std::vector<std::shared_ptr<Fighter> >& tm(enemies.getRealTeam());

  for (unsigned int i(0); i < tm.size(); i++) {
    m_choices.push_back(std::make_shared<M_choice>());

    // NAME
    IG_Action actionBattleSideEnemyEnter(
        std::bind(&af_MenuBattleSideEnemyEnter, i, std::placeholders::_1));

    m_choices.back()->load(
        surf, tm.at(i)->getName(), ress.getTheFont(0),
        m_background->second->getX() + MENUS_BORDER_X,
        m_background->second->getY() + (i * (MENU_SIMPLE_FONTSIZE * 3)), true,
        actionBattleSideEnemyEnter, CAMERA_WIDTH / 5, CAMERA_HEIGHT);
    // HP_TEXT
    auto hptext = surf.addSurface(ManageSurfaces::e_thing::TEXT,
                                  std::make_shared<SurfaceText>());
    std::dynamic_pointer_cast<SurfaceText>(hptext->second)
        ->setFont(ress.getTheFont(0));
    std::dynamic_pointer_cast<SurfaceText>(hptext->second)
        ->setCharacterSize(MENU_SIMPLE_FONTSIZE - 2);
    m_choices.back()->getRealRenderTextureManager().add(
        hptext, HEALTH_TEXT_POSITION_X, HEALTH_TEXT_POSITION_Y);
    // HP_IMAGE
    auto hpimg = surf.addSurface(ManageSurfaces::e_thing::SPRITE,
                                 std::make_shared<SurfaceSprite>());
    std::dynamic_pointer_cast<SurfaceSprite>(hpimg->second)
        ->setTexture(ress.getTheTexture(1));
    std::dynamic_pointer_cast<SurfaceSprite>(hpimg->second)
        ->setTextureRect(
            sf::IntRect(HEALTH_SURFACE_BEGIN_X, HEALTH_SURFACE_BEGIN_Y,
                        HEALTH_SURFACE_WIDTH, HEALTH_SURFACE_HEIGHT));
    m_choices.back()->getRealRenderTextureManager().add(
        hpimg, HEALTH_IMAGE_POSITION_X, HEALTH_IMAGE_POSITION_Y);

    updateHealth(i, tm.at(i)->getHealth());
    m_choices.back()->getRealRenderTextureManager().update();
  }

  return 0;
}

// Load with an enemie team
int MenuBattleSide::loadWithAllies(ManageRessources& ress, ManageSurfaces& surf,
                                   TeamBattle& allies) {
  if (m_barType != MenuBattleSide::e_menuBattleSideBarType::MENU_BATTLE_ALLIE)
    THROW_VALUE(std::to_string(m_barType));

  std::vector<std::shared_ptr<TeamMate> >& tm(allies.getRealTeam());

  for (unsigned int i(0); i < tm.size(); i++) {
    m_choices.push_back(std::make_shared<M_choice>());

    // NAME
    IG_Action actionAllyEnter(
        std::bind(&af_MenuBattleSideAllyEnter, i, std::placeholders::_1));
    m_choices.back()->load(
        surf, tm.at(i)->getName(), ress.getTheFont(0),
        m_background->second->getX() + MENUS_BORDER_X,
        m_background->second->getY() + (i * (MENU_SIMPLE_FONTSIZE * 7)), true,
        actionAllyEnter, CAMERA_WIDTH / 5, CAMERA_HEIGHT);
    // HP_TEXT
    auto hptext = surf.addSurface(ManageSurfaces::e_thing::TEXT,
                                  std::make_shared<SurfaceText>());
    std::dynamic_pointer_cast<SurfaceText>(hptext->second)
        ->setFont(ress.getTheFont(0));
    std::dynamic_pointer_cast<SurfaceText>(hptext->second)
        ->setCharacterSize(MENU_SIMPLE_FONTSIZE - 2);
    m_choices.back()->getRealRenderTextureManager().add(
        hptext, HEALTH_TEXT_POSITION_X, HEALTH_TEXT_POSITION_Y);
    // HP_IMAGE
    auto hpimg = surf.addSurface(ManageSurfaces::e_thing::SPRITE,
                                 std::make_shared<SurfaceSprite>());
    std::dynamic_pointer_cast<SurfaceSprite>(hpimg->second)
        ->setTexture(ress.getTheTexture(1));
    std::dynamic_pointer_cast<SurfaceSprite>(hpimg->second)
        ->setTextureRect(
            sf::IntRect(HEALTH_SURFACE_BEGIN_X, HEALTH_SURFACE_BEGIN_Y,
                        HEALTH_SURFACE_WIDTH, HEALTH_SURFACE_HEIGHT));
    m_choices.back()->getRealRenderTextureManager().add(
        hpimg, HEALTH_IMAGE_POSITION_X, HEALTH_IMAGE_POSITION_Y);

    // MP_TEXT
    auto mptext = surf.addSurface(ManageSurfaces::e_thing::TEXT,
                                  std::make_shared<SurfaceText>());
    std::dynamic_pointer_cast<SurfaceText>(mptext->second)
        ->setFont(ress.getTheFont(0));
    std::dynamic_pointer_cast<SurfaceText>(mptext->second)
        ->setCharacterSize(MENU_SIMPLE_FONTSIZE - 2);
    m_choices.back()->getRealRenderTextureManager().add(
        mptext, MANA_TEXT_POSITION_X, MANA_TEXT_POSITION_Y);
    // MP_IMAGE
    auto mpimg = surf.addSurface(ManageSurfaces::e_thing::SPRITE,
                                 std::make_shared<SurfaceSprite>());
    std::dynamic_pointer_cast<SurfaceSprite>(mpimg->second)
        ->setTexture(ress.getTheTexture(1));
    std::dynamic_pointer_cast<SurfaceSprite>(mpimg->second)
        ->setTextureRect(sf::IntRect(MANA_SURFACE_BEGIN_X, MANA_SURFACE_BEGIN_Y,
                                     MANA_SURFACE_WIDTH, MANA_SURFACE_HEIGHT));
    m_choices.back()->getRealRenderTextureManager().add(
        mpimg, MANA_IMAGE_POSITION_X, MANA_IMAGE_POSITION_Y);

    // TP_TEXT
    auto tptext = surf.addSurface(ManageSurfaces::e_thing::TEXT,
                                  std::make_shared<SurfaceText>());
    std::dynamic_pointer_cast<SurfaceText>(tptext->second)
        ->setFont(ress.getTheFont(0));
    std::dynamic_pointer_cast<SurfaceText>(tptext->second)
        ->setCharacterSize(MENU_SIMPLE_FONTSIZE - 2);
    m_choices.back()->getRealRenderTextureManager().add(
        tptext, SKILLPOINTS_TEXT_POSITION_X, SKILLPOINTS_TEXT_POSITION_Y);
    // TP_IMAGE
    auto tpimg = surf.addSurface(ManageSurfaces::e_thing::SPRITE,
                                 std::make_shared<SurfaceSprite>());
    std::dynamic_pointer_cast<SurfaceSprite>(tpimg->second)
        ->setTexture(ress.getTheTexture(1));
    std::dynamic_pointer_cast<SurfaceSprite>(tpimg->second)
        ->setTextureRect(sf::IntRect(
            SKILLPOINTS_SURFACE_BEGIN_X, SKILLPOINTS_SURFACE_BEGIN_Y,
            SKILLPOINTS_SURFACE_WIDTH, SKILLPOINTS_SURFACE_HEIGHT));
    m_choices.back()->getRealRenderTextureManager().add(
        tpimg, SKILLPOINTS_IMAGE_POSITION_X, SKILLPOINTS_IMAGE_POSITION_Y);

    updateHealth(i, tm.at(i)->getHealth());
    updateMana(i, tm.at(i)->getMana());
    updateSkillPoints(i, tm.at(i)->getSkillPoints());
    m_choices.back()->getRealRenderTextureManager().update();
  }

  return 0;
}

// Load the menu
int MenuBattleSide::load(ManageRessources& ress, ManageSurfaces& surf,
                         const int& x, const int& y, const int& w,
                         const int& h) {
  if (m_initialized) THROW_INIT("Already initiate");

  std::dynamic_pointer_cast<SurfaceSprite>(m_background->second)
      ->setEnable(true);
  std::dynamic_pointer_cast<SurfaceSprite>(m_background->second)
      ->setScale(
          w / std::dynamic_pointer_cast<SurfaceSprite>(m_background->second)
                  ->getGlobalBounds()
                  .width,
          h / std::dynamic_pointer_cast<SurfaceSprite>(m_background->second)
                  ->getGlobalBounds()
                  .height);
  m_background->second->setDimensions(x, y, w, h);

  m_initialized = true;

  return 0;
}

// Update surfaces
int MenuBattleSide::update(Game& g) {
  // [TODO]

  for (unsigned int i(0); i < m_choices.size(); i++) {
    useCorrectFont(i, g);
    if (m_barType == MENU_BATTLE_ALLIE) {
      updateHealth(i,
                   g.getRealBattle().getAllies().getTeam().at(i)->getHealth());
      updateMana(i, g.getRealBattle().getAllies().getTeam().at(i)->getMana());
      updateSkillPoints(
          i, g.getRealBattle().getAllies().getTeam().at(i)->getSkillPoints());
    } else {
      updateHealth(
          i, g.getRealBattle().getRealEnemies().getTeam().at(i)->getHealth());
    }
    m_choices.at(i)->getRealRenderTextureManager().gotUpdated();
    m_choices.at(i)->getRealRenderTextureManager().update();
  }

  return 0;
}

// Close the menu
int MenuBattleSide::close(ManageSurfaces& surf) {
  for (unsigned int i(0); i < m_choices.size(); i++) {
    m_choices.at(i)->clear(surf);
  }

  m_choices.clear();

  surf.deleteSurface(m_background);
  surf.deleteSurface(m_cursorSurfaceRight);

  return 0;
}

int MenuBattleSide::useCorrectFont(int i, Game& g) {
  if (!m_initialized || m_choices.size() < (unsigned)i)
    THROW_INIT("Bad initiate or bad value : " + std::to_string(i));

  if (m_barType == MENU_BATTLE_ALLIE) {
    if (m_choices.at(i)->getEnabled() && g.getRealBattle()
                                                 .getRealAllies()
                                                 .getTeam()
                                                 .at(i)
                                                 ->getHealth()
                                                 .getPoints() <= 0) {
      m_choices.at(i)->setEnabled(false);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(NAME)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR_DISABLED_CHOICE);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(HP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR_DISABLED_CHOICE);

      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(MP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR_DISABLED_CHOICE);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(TP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR_DISABLED_CHOICE);
    } else if (!m_choices.at(i)->getEnabled() && g.getRealBattle()
                                                         .getRealAllies()
                                                         .getTeam()
                                                         .at(i)
                                                         ->getHealth()
                                                         .getPoints() > 0) {
      m_choices.at(i)->setEnabled(true);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(NAME)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(HP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR);

      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(MP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(TP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR);
    }
  } else {
    if (m_choices.at(i)->getEnabled() && g.getRealBattle()
                                                 .getRealEnemies()
                                                 .getTeam()
                                                 .at(i)
                                                 ->getHealth()
                                                 .getPoints() <= 0) {
      m_choices.at(i)->setEnabled(false);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(NAME)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR_DISABLED_CHOICE);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(HP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR_DISABLED_CHOICE);
    } else if (!m_choices.at(i)->getEnabled() && g.getRealBattle()
                                                         .getRealEnemies()
                                                         .getTeam()
                                                         .at(i)
                                                         ->getHealth()
                                                         .getPoints() > 0) {
      m_choices.at(i)->setEnabled(true);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(NAME)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR);
      std::dynamic_pointer_cast<SurfaceText>(m_choices.at(i)
                                                 ->getRealRenderTextureManager()
                                                 .getRealSurfaces()
                                                 .at(HP_TEXT)
                                                 ->second)
          ->setFillColor(MENU_FONT_COLOR);
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////

#include <iostream>

int af_MenuBattleSideAllyEnter(int n, Game& g) {
  g.getRealBattle().getRealBattleEventManager().addDestinationForEvent(
      g.getRealBattle().getRealAllies().getRealTeam().at(n), g);

  return 0;
}

int af_MenuBattleSideEnemyEnter(int n, Game& g) {
  g.getRealBattle().getRealBattleEventManager().addDestinationForEvent(
      g.getRealBattle().getRealEnemies().getRealTeam().at(n), g);

  return 0;
}