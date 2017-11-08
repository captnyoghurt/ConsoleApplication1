#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

// Window constants
std::string WINDOW_NAME = "RPG v0.1";
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 640;
int WINDOW_X = 0;
int WINDOW_Y = 0;
int WINDOW_SLEEPTIME = 5; // ms
int WINDOW_FRAMERATES = 60;

// Graphic constants

/// Map
std::string MAP_FONT_TEXT("monofonto.ttf");
int MAP_MAX_LAYER = 6;

/// TILE
int TILE_WIDTH = 32;
int TILE_HEIGHT = 32;

/// Camera
int CAMERA_WIDTH = WINDOW_WIDTH;
int CAMERA_HEIGHT = WINDOW_HEIGHT;
int CAMERA_MOVING_X = TILE_WIDTH/4;
int CAMERA_MOVING_Y = TILE_HEIGHT/4;

/// Team moving
int TEAM_MOVING_X = 2;
int TEAM_MOVING_Y = 2;
int TEAM_MOVING_NORMAL_SPEED_X = 10000;
int TEAM_MOVING_NORMAL_SPEED_Y = 10000;

/// Animation
int ANIMATION_REFRESHING = 50; // ms
int ANIMATION_NB_LAYER = 20;

/// Menus
int MENUS_BORDER_X = 10;
int MENUS_BORDER_Y = 10;
int MENUS_GAP_BETWEEN_LINES = 25; // px

/// Ressources number texture
int RESSOURCE_TEXTURE_NUMBER_MENU = 0;
int RESSOURCE_TEXTURE_NUMBER_LIFEBAR = 1;

/// Ressources number font
int RESSOURCE_FONT_NUMBER_MONO = 0;

// Team constants

/// Walk Stand
std::string TEAM_BASIC_WALKSTAND("data/graphic/charset/001-Fighter01.png");
int TEAM_WALK_ANIMATION_REFRESH = 100; // ms
int TEAM_WALK_WIDTH = 32;
int TEAM_WALK_HEIGHT = 48;
int TEAM_WALK_FRAME_NUMBER = 4;
int TEAM_WALK_UP_POSITION_Y = 144;
int TEAM_WALK_DOWN_POSITION_Y = 0;
int TEAM_WALK_RIGHT_POSITION_Y = 96;
int TEAM_WALK_LEFT_POSITION_Y = 48;
int TEAM_WALK_LAYER = 2;
int TEAM_WALK_HITBOX_X = 1;
int TEAM_WALK_HITBOX_Y = 17;
int TEAM_WALK_HITBOX_WIDTH = 30;
int TEAM_WALK_HITBOX_HEIGHT = 30;

/// Combat
int TEAM_BATTLE_MAX_NUMBER = 5;

// Menu constants

/// Font
std::string MENU_FONT_NAME("monofonto.ttf");
sf::Color MENU_FONT_COLOR(0, 0, 0);
sf::Color MENU_FONT_COLOR_DISABLED_CHOICE(64, 64, 64);

/// Surface
std::string MENU_SURFACE_NAME("data/graphic/others/001-Blue01.png");
int MENU_SURFACE_BEGIN_X = 0;
int MENU_SURFACE_BEGIN_Y = 0;
int MENU_SURFACE_WIDTH = 128;
int MENU_SURFACE_HEIGHT = 80;

/// Simple menu
std::string MENU_SIMPLE_TEXT("data/menu/simple.m");
int MENU_SIMPLE_FONTSIZE = 18;
int MENU_SIMPLE_HEIGHT = 2*CAMERA_HEIGHT/3;
int MENU_SIMPLE_WIDTH = CAMERA_WIDTH/4;
int MENU_SIMPLE_LAYER = MAP_MAX_LAYER;

/// Dialog box
int MENU_DIALOG_BOX_FONTSIZE = 18;
int MENU_DIALOG_BOX_GAP_BETWEEN_LINES = MENUS_GAP_BETWEEN_LINES;
int MENU_DIALOG_BOX_X = 0;
int MENU_DIALOG_BOX_Y = (3*CAMERA_HEIGHT/4) - 5;
int MENU_DIALOG_BOX_WIDTH = CAMERA_WIDTH;
int MENU_DIALOG_BOX_HEIGHT = CAMERA_HEIGHT - MENU_DIALOG_BOX_Y;
int MENU_DIALOG_BOX_CHARACTER_BY_LINE = (2*(MENU_DIALOG_BOX_WIDTH-MENUS_BORDER_X) / MENU_DIALOG_BOX_FONTSIZE);
int MENU_DIALOG_BOX_LAYER = MAP_MAX_LAYER;

/// Bag
std::string MENU_BAG_TEXT("data/menu/inventaire.m");
int MENU_BAG_FONTSIZE = 26;
int MENU_BAG_LAYER = MAP_MAX_LAYER;

/// Spells
int MENU_SPELLS_FONTSIZE = MENU_SIMPLE_FONTSIZE;
int MENU_SPELLS_LAYER = MAP_MAX_LAYER;
int MENU_SPELLS_DIALOG_BOX_X = 0;
int MENU_SPELLS_DIALOG_BOX_Y = 0;
int MENU_SPELLS_DIALOG_BOX_WIDTH = CAMERA_WIDTH;
int MENU_SPELLS_DIALOG_BOX_HEIGHT = CAMERA_HEIGHT / 6;
int MENU_SPELLS_CHOICES_X = 0;
int MENU_SPELLS_CHOICES_Y = CAMERA_HEIGHT / 6;
int MENU_SPELLS_CHOICES_WIDTH = CAMERA_WIDTH;
int MENU_SPELLS_CHOICES_HEIGHT = 5 * CAMERA_HEIGHT / 6;
sf::Color MENU_SPELLS_COLOR_HP(0, 255, 0);
sf::Color MENU_SPELLS_COLOR_MP(0, 0, 255);
sf::Color MENU_SPELLS_COLOR_TP(255, 0, 0);

/// Cursor
//// Up
int MENU_SURFACE_CURSOR_UP_BEGIN_X = 154;
int MENU_SURFACE_CURSOR_UP_BEGIN_Y = 16;
int MENU_SURFACE_CURSOR_UP_WIDTH = 12;
int MENU_SURFACE_CURSOR_UP_HEIGHT = 10;
//// Down
int MENU_SURFACE_CURSOR_DOWN_BEGIN_X = 154;
int MENU_SURFACE_CURSOR_DOWN_BEGIN_Y = 40;
int MENU_SURFACE_CURSOR_DOWN_WIDTH = 12;
int MENU_SURFACE_CURSOR_DOWN_HEIGHT = 10;
//// Right
int MENU_SURFACE_CURSOR_RIGHT_BEGIN_X = 166;
int MENU_SURFACE_CURSOR_RIGHT_BEGIN_Y = 26;
int MENU_SURFACE_CURSOR_RIGHT_WIDTH = 10;
int MENU_SURFACE_CURSOR_RIGHT_HEIGHT = 12;
//// Left
int MENU_SURFACE_CURSOR_LEFT_BEGIN_X = 144;
int MENU_SURFACE_CURSOR_LEFT_BEGIN_Y = 26;
int MENU_SURFACE_CURSOR_LEFT_WIDTH = 10;
int MENU_SURFACE_CURSOR_LEFT_HEIGHT = 12;

/// Selected
int MENU_SURFACE_SELECTED_BEGIN_X = 129;
int MENU_SURFACE_SELECTED_BEGIN_Y = 64;
int MENU_SURFACE_SELECTED_WIDTH = 30;
int MENU_SURFACE_SELECTED_HEIGHT = 32;


// Battle constants

/// General
std::string MENU_BATTLE_SURFACE_BAR("data/graphic/others/001-Bar01.png");
std::string MENU_BATTLE_CHOICE_TEXT("data/menu/battle.m");
int BATTLE_MIN_LAYER = MENU_BAG_LAYER;
int BATTLE_NUMBER_OF_LAYER = 4;
int BATTLE_MAX_LAYER = BATTLE_MIN_LAYER + BATTLE_NUMBER_OF_LAYER;
int BATTLE_KEY_EVENT_LAYER = 5;

/// Health
std::string HEALTH_NAME("PV");
int HEALTH_MAX_POINTS = 999999;
int HEALTH_SURFACE_BEGIN_X = 0;
int HEALTH_SURFACE_BEGIN_Y = 0;
int HEALTH_SURFACE_WIDTH = 100;
int HEALTH_SURFACE_HEIGHT = 10;
int HEALTH_TEXT_POSITION_X = MENUS_BORDER_X;
int HEALTH_TEXT_POSITION_Y = MENU_SIMPLE_FONTSIZE;
int HEALTH_TEXT_WIDTH = CAMERA_WIDTH / 5;
int HEALTH_TEXT_HEIGHT = MENU_SIMPLE_FONTSIZE;
int HEALTH_IMAGE_POSITION_X = 0;
int HEALTH_IMAGE_POSITION_Y = 2 * MENU_SIMPLE_FONTSIZE;
int HEALTH_IMAGE_WIDTH = CAMERA_WIDTH / 5;
int HEALTH_IMAGE_HEIGHT = HEALTH_SURFACE_HEIGHT;

/// Skill Points
std::string SKILLPOINTS_NAME("PT");
int SKILLPOINTS_MAX_POINTS = 100;
int SKILLPOINTS_SURFACE_BEGIN_X = 0;
int SKILLPOINTS_SURFACE_BEGIN_Y = 30;
int SKILLPOINTS_SURFACE_WIDTH = 100;
int SKILLPOINTS_SURFACE_HEIGHT = 10;
int SKILLPOINTS_TEXT_POSITION_X = MENUS_BORDER_X;
int SKILLPOINTS_TEXT_POSITION_Y = 5 * MENU_SIMPLE_FONTSIZE;
int SKILLPOINTS_TEXT_WIDTH = CAMERA_WIDTH / 5;
int SKILLPOINTS_TEXT_HEIGHT = MENU_SIMPLE_FONTSIZE;
int SKILLPOINTS_IMAGE_POSITION_X = 0;
int SKILLPOINTS_IMAGE_POSITION_Y = 6 * MENU_SIMPLE_FONTSIZE;
int SKILLPOINTS_IMAGE_WIDTH = CAMERA_WIDTH / 5;
int SKILLPOINTS_IMAGE_HEIGHT = SKILLPOINTS_SURFACE_HEIGHT;

/// Mana
std::string MANA_NAME("MP");
int MANA_MAX_POINTS = 999999;
int MANA_SURFACE_BEGIN_X = 0;
int MANA_SURFACE_BEGIN_Y = 15;
int MANA_SURFACE_WIDTH = 100;
int MANA_SURFACE_HEIGHT = 10;
int MANA_TEXT_POSITION_X = MENUS_BORDER_X;
int MANA_TEXT_POSITION_Y = 3* MENU_SIMPLE_FONTSIZE;
int MANA_TEXT_WIDTH = CAMERA_WIDTH / 5;
int MANA_TEXT_HEIGHT = MENU_SIMPLE_FONTSIZE;
int MANA_IMAGE_POSITION_X = 0;
int MANA_IMAGE_POSITION_Y = 4 * MENU_SIMPLE_FONTSIZE;
int MANA_IMAGE_WIDTH = CAMERA_WIDTH / 5;
int MANA_IMAGE_HEIGHT = MANA_SURFACE_HEIGHT;

/// Characteristics
int CHARACTERISTIC_STRENGH_MAX = 9999;
int CHARACTERISTIC_INTELLIGENCE_MAX = 9999;
int CHARACTERISTIC_VITALITY_MAX = 9999;
int CHARACTERISTIC_AGILITY_MAX = 9999;
int CHARACTERISTIC_SPEED_MAX = 9999;
int CHARACTERISTIC_REGEN_MP_MAX = 999;
int CHARACTERISTIC_ATTACK_PHYSIC_MAX = 9999;
int CHARACTERISTIC_ATTACK_MAGIC_MAX = 9999;
int CHARACTERISTIC_DEFENSE_PHYSIC_MAX = 9999;
int CHARACTERISTIC_DEFENSE_MAGIC_MAX = 9999;
int CHARACTERISTIC_RESISTANCE_SLEEP_MAX = 100;
int CHARACTERISTIC_RESISTANCE_POISON_MAX = 100;
int CHARACTERISTIC_RESISTANCE_PARALYSIS_MAX = 100;
int CHARACTERISTIC_RESISTANCE_MUTE_MAX = 100;

/// Team
std::string TEAM_BATTLE_CHAR1_NAME("data/graphic/battleset/001-f01.png");
int TEAM_BATTLE_CHAR1_X = 550;
int TEAM_BATTLE_CHAR1_Y = 230;

std::string TEAM_BATTLE_CHAR2_NAME("data/graphic/battleset/001-f02.png");
int TEAM_BATTLE_CHAR2_X = 580;
int TEAM_BATTLE_CHAR2_Y = 280;


// Database constants

/// Json
std::string DATABASE_JSON_NAME_MONSTERS("data/jdb/monsters.json");
std::string DATABASE_JSON_NAME_MONSTERS_SPELLS("data/jdb/monsters-spells.json");
std::string DATABASE_JSON_NAME_SPELLS("data/jdb/spells.json");
std::string DATABASE_JSON_NAME_SPELLS_EFFECTS("data/jdb/spells-effects.json");
std::string DATABASE_JSON_NAME_EFFECTS("data/jdb/effects.json");
std::string DATABASE_JSON_NAME_ITEMS("data/jdb/items.json");
std::string DATABASE_JSON_NAME_ITEMS_EFFECTS("data/jdb/items-effects.json");
std::string DATABASE_JSON_NAME_CHARCOURB("data/jdb/courb.json");
std::string DATABASE_JSON_NAME_TEAMMATE("data/jdb/team_mate.json");
std::string DATABASE_JSON_NAME_TEAMMATE_SPELLS("data/jdb/team_mate-spell.json");


// Character

int CHARACTER_LEVEL_MAX = 100;