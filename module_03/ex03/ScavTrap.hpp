#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

#include <iostream>
#include <string>
#include <random>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
	private:
		int JurorsChallengeEnergy;
		int MiddlesChallengeEnergy;
		int HeatersChallengeEnergy;
	public:
		ScavTrap(char const *name);
		ScavTrap();
		~ScavTrap();
		ScavTrap(const ScavTrap& copy);
		ScavTrap& operator=(const ScavTrap& obj);
		void challengeExec(int amount);
		void jurorsChallenge(void);
		void middlesChallenge(void);
		void heatersChallenge(void);
		void challengeNewcomer(void);
};
#endif
