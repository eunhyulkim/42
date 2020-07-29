#include "ScavTrap.hpp"

typedef void	(ScavTrap::* func_member)(void);

ScavTrap::ScavTrap(char const *name)  : ClapTrap(name, 100, 50, 20, 15, 3)
{
	this->JurorsChallengeEnergy = 40;
	this->MiddlesChallengeEnergy = 25;
	this->HeatersChallengeEnergy = 10;
	std::cout << "[FR4G-TP-CONS] ScavTrap" << std::endl;
}

ScavTrap::ScavTrap() : ClapTrap()
{
	this->JurorsChallengeEnergy = 0;
	this->MiddlesChallengeEnergy = 0;
	this->HeatersChallengeEnergy = 0;
	std::cout << "[FR4G-TP-CONS] ScavTrap" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& copy) : ClapTrap(copy)
{
	this->JurorsChallengeEnergy = copy.JurorsChallengeEnergy;
	this->MiddlesChallengeEnergy = copy.MiddlesChallengeEnergy;
	this->HeatersChallengeEnergy = copy.HeatersChallengeEnergy;
}

ScavTrap&
ScavTrap::operator=(const ScavTrap& obj) {
	this->ScavTrap::operator=(obj);
	this->JurorsChallengeEnergy = obj.JurorsChallengeEnergy;
	this->MiddlesChallengeEnergy = obj.MiddlesChallengeEnergy;
	this->HeatersChallengeEnergy = obj.HeatersChallengeEnergy;
	return (*this);
}


ScavTrap::~ScavTrap() {
	std::cout << "[FR4G-TP-DES] ScavTrap" << std::endl;
}


/*
** FR4G-TP <name> attacks <target> at range, causing <damage> points of damage!
*/

namespace {
	func_member	member[3] = {
		&ScavTrap::jurorsChallenge,
		&ScavTrap::middlesChallenge, &ScavTrap::heatersChallenge
	};

	int get_random_challenge_id(void)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> challenge_dis(0, 2);
		return (challenge_dis(gen));
	}

	int get_random_challenge_result(void)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> result_dis(0, 1);
		return (result_dis(gen));
	}
}

void ScavTrap::challengeExec(int amount)
{
	if (get_random_challenge_result() == 1)
	{
		this->EnergyPoints += amount;
		if (this->EnergyPoints > 100)
			this->EnergyPoints = 100;
		std::cout << "[FR4G-TP] \033[37;42m"
		<< "-> Congraturations! Your challenge is success!"
		<< "\033[0m" << std::endl;
	}
	else
	{
		this->EnergyPoints -= amount;
		if (this->EnergyPoints < 0)
			this->EnergyPoints = 0;
		std::cout << "[FR4G-TP] \033[37;42m"
		<< "-> Sorry. Your challenge is failed!"
		<< "\033[0m" << std::endl;
	}
}

void
ScavTrap::jurorsChallenge(void) {
	std::cout << "[FR4G-TP] \033[37;42m"
	<< "The jurors appear vaguely stranded and at loose ends, uprooted from their routines and livelihoods."
	<< "\033[0m" << std::endl;
	challengeExec(this->JurorsChallengeEnergy);
}

void
ScavTrap::middlesChallenge(void) {
	std::cout << "[FR4G-TP] \033[37;42m"
	<< "I like middles ... It is in middles that extremes clash, where ambiguity restlessly rules."
	<< "\033[0m" << std::endl;
	challengeExec(this->MiddlesChallengeEnergy);
}

void
ScavTrap::heatersChallenge(void) {
	std::cout << "[FR4G-TP] \033[37;42m"
	<< "I love 'Heathers', and I loved doing that movie. I'm very proud of it, so if it gets brought up, I'm happy."
	<< "\033[0m" << std::endl;
	challengeExec(this->HeatersChallengeEnergy);
}

void
ScavTrap::challengeNewcomer(void) {
	(this->*member[get_random_challenge_id()])();
}
