#include <memory>
#include "MenuBattle.h"
#include "../constants.h"
#include "../Game.h"
#include "MenuBattleSide.h"
#include "MenuDialogBox.h"


MenuBattle::MenuBattle(Battle *b, ManageRessources &ress, ManageSurfaces &surf)
{
	m_updated = true;
	m_isBlocking = false;
	m_activeMenu = 0;
}


MenuBattle::~MenuBattle()
{
}


// Return if the MenuBattle is updated
bool MenuBattle::getUpdated() const
{
	return m_updated;
}


// Return if this menu is currently waiting for an action
bool MenuBattle::getIsBlocking() const
{
	return m_isBlocking;
}


// Return the current active menu
int MenuBattle::getActiveMenu() const
{
	return m_activeMenu;
}


// Return the menus with modifying possibilities
std::vector<Menu*>& MenuBattle::getRealMenus()
{
	return m_menus;
}


// Modify the current menu
int MenuBattle::setActiveMenu(const int &am)
{
	if (!((unsigned)am < MenuBattle::BM_TOTAL))
		return -1;

	m_activeMenu = am;

	gotUpdated();

	return 0;
}


// Modify if this menu is currently waiting for an action
int MenuBattle::setIsBlocking(const bool &b)
{
	m_isBlocking = b;

	return 0;
}


// Tell the MenuBattle that it's updated
int MenuBattle::gotUpdated()
{
	m_updated = true;

	return 0;
}


// All the action functions for the menus
int MenuBattle::af_MenuBattleDown(Game &g)
{
	if (m_activeMenu != MenuBattle::BM_LEFT && m_activeMenu != MenuBattle::BM_RIGHT)
		return 1;

	if ((unsigned)static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getSelectedChoice() <= static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getChoices().size() - 1)
	{
		static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->setSelectedChoice(static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getSelectedChoice() + 1);

		gotUpdated();
	}

	return 0;
}


int MenuBattle::af_MenuBattleUp(Game &g)
{
	if (m_activeMenu != MenuBattle::BM_LEFT && m_activeMenu != MenuBattle::BM_RIGHT)
		return 1;

	if (static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getSelectedChoice() > 0)
	{
		static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->setSelectedChoice(static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getSelectedChoice() - 1);

		gotUpdated();
	}

	return 0;
}


int MenuBattle::af_MenuBattleEnter(Game &g)
{
	int ret(0);

	m_isBlocking = false;

	if (m_activeMenu == MenuBattle::BM_LEFT || m_activeMenu == MenuBattle::BM_RIGHT)
	{
		ret = static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getChoices().at(static_cast<MenuBattleSide*>(m_menus.at(m_activeMenu))->getSelectedChoice())->getAction().getAction()(g);
	}
	else if (m_activeMenu == MenuBattle::BM_DIALOG)
	{
		ret = static_cast<MenuDialogBox*>(m_menus.at(m_activeMenu))->continueText(g.getRealRessourceManager(RESSOURCE_TEXTURE_NUMBER_MENU), g.getRealSurfaceManager(MENU_DIALOG_BOX_LAYER));

		if (ret == 0)
			m_isBlocking = true;
	}

	return ret;
}