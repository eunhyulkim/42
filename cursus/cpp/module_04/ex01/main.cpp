#include "AWeapon.hpp"
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "Enemy.hpp"
#include "SuperMutant.hpp"
#include "RadScorpion.hpp"
#include "Character.hpp"

# define BASIC_TEST     true

void	print(std::string msg) {
    std::cout << std::endl
    << "\033[1;37;41m" << msg << "\033[0m"
    << std::endl;
}

int main()
{
    if (BASIC_TEST)
    {
        Character* me = new Character("me");
        std::cout << *me;
        Enemy* b = new RadScorpion();
        AWeapon* pr = new PlasmaRifle();
        AWeapon* pf = new PowerFist();
        me->equip(pr);
        std::cout << *me;
        me->equip(pf);
        me->attack(b);
        std::cout << *me;make
        me->equip(pr);
        std::cout << *me;
        me->attack(b);
        std::cout << *me;
        me->attack(b);
        std::cout << *me;
    }
    else
    {
        Character *me = new Character("eunhkim");
        print("CHARACTER INITIALIZE");
        std::cout << *me;
        AWeapon *pr = new PlasmaRifle();
        AWeapon *pf = new PowerFist();

        print("CREATE RAD SCORPION");
        Enemy *scorpionOne = new RadScorpion();
        std::cout << scorpionOne->get_m_type() << "(HP: " << scorpionOne->get_m_hp() << ")" << std::endl;
        print("CREATE SUPER MUTANT");
        Enemy *mutantOne = new SuperMutant();
        std::cout << mutantOne->get_m_type() << "(HP: " << mutantOne->get_m_hp() << ")" << std::endl;

        print("ATTACK WITHOUT WEAPON(EXPECT NOTHING)");
        me->attack(scorpionOne);
        std::cout << "Scorpion HP: " << scorpionOne->get_m_hp() << std::endl;
        print("EQUIP FIST AND ATTACK SCORPION");
        me->equip(pf);
        me->attack(scorpionOne);
        std::cout << scorpionOne->get_m_type() << "(HP: " << scorpionOne->get_m_hp() << ")" << std::endl;
        print("EQUIP RIFLE AND ATTACK");
        me->equip(pr);
        me->attack(mutantOne);
        std::cout << mutantOne->get_m_type() << "(HP: " << mutantOne->get_m_hp() << ")" << std::endl;

        print("RE-EQUIP FIST");
        me->equip(pf);
        print("CREATE NEW CHARACTER AND EQUIP RIFLE");
        Character* you = new Character("friend");
        you->equip(pr);
        print("NON-STOP ATTACKING...");
        for (int i = 0; i < 5; i++)
        {
            me->attack(mutantOne);
            you->attack(mutantOne);
        }
        print("DELETE SCOLPION AND OTHER DATA...");
        delete scorpionOne;
        delete me;
        delete you;
        delete pf;
        delete pr;

    }

    return 0;
}
