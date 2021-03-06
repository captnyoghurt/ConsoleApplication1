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
 *  Mana of a fighter.
 *
 */

#pragma once

#include <list>
#include "EffectOnCharacteristic.h"

class Spell;

class Mana {
 public:
  Mana();
  Mana(const Mana &mana);
  explicit Mana(const int &max);
  ~Mana();

  Mana &operator=(const Mana &mana);

 public:
  /**
   * \brief Return the number of mana points	.
   *
   * \return int object.
   */
  int getPoints() const;
  /**
   * \brief Return the maximum number of mana points	.
   *
   * \return int object.
   */
  int getMaxPoints() const;
  /**
   * \brief Return all the actual effects	.
   *
   * \return std::list<EffectOnCharacteristic> object.
   */
  std::list<EffectOnCharacteristic> getEffects() const;
  /**
   * \brief Return all the actual adding effects	.
   *
   * \return std::list<EffectOnCharacteristic> object.
   */
  std::list<EffectOnCharacteristic> getAddingEffects() const;

  /**
   * \brief Modify the number of mana points	.
   *
   * \param p The new value.
   * \return int object.
   */
  int setPoints(const int &p);
  /**
   * \brief Modify the maximum number of mana	.
   *
   * \param maxp The new value.
   * \return int object.
   */
  int setMaxPoints(const int &maxp);

  /**
   * \brief Say if a spell can be used	.
   *
   * \return bool object.
   */
  bool canCastSpell(const Spell &sp);
  /**
   * \brief Say if there is enought mana	.
   *
   * \return bool object.
   */
  bool enoughFor(const int &points);

  /**
   * \brief Use some mana points	.
   *
   * \return int object.
   */
  int use(const int &points);
  int use(const Spell &sp);
  /**
   * \brief Get some mana points	.
   *
   * \return int object.
   */
  int recharge(const int &points);

 private:
  int m_maxPoints;
  int m_points;
};
