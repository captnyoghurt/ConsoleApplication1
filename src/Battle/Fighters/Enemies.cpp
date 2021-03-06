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
 *  Enemi team.
 *
 */

#include "Enemies.h"

Enemies::Enemies() { m_numberFighterAlive = 0; }

Enemies::Enemies(const Enemies& enemie, int number) {
  m_numberFighterAlive = enemie.getNumberFighterAlive();
}

Enemies::~Enemies() {}

// Return the number of team mate alive
int Enemies::getNumberFighterAlive() const {
  int n = 0;

  for (unsigned int i(0); i < m_fighters.size(); i++) {
    if (m_fighters.at(i)->getHealth().getPoints() > 0) n++;
  }

  return n;
}

// Return the team mate vector
std::vector<std::shared_ptr<Fighter>> Enemies::getTeam() { return m_fighters; }

// Return the team mate vector with modifying possibilities
std::vector<std::shared_ptr<Fighter>>& Enemies::getRealTeam() {
  return m_fighters;
}

// Add a new member
int Enemies::addMember(Fighter m) {
  m_fighters.push_back(std::make_shared<Fighter>(m));

  return 0;
}
int Enemies::addMember(std::shared_ptr<Fighter> f) {
  m_fighters.push_back(f);

  return 0;
}

// Update the team batttle
int Enemies::update() {
  // [TODO]

  return 0;
}

// Clear the enemy team
int Enemies::clear() {
  m_fighters.clear();

  return 0;
}