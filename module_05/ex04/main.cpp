#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"
#include "OfficeBlock.hpp"

namespace {
	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

/* 
** 	EX04 TEST
*/
namespace {
	void BureaucracyTry(OfficeBlock& ob, const char *form, const char *target)
	{
		try {
			ob.doBureaucracy(form, target);
		}
		catch (OfficeBlock::FailedMakeFormException& e) {
			std::cout << e.what() << std::endl;
		} catch (OfficeBlock::NotFilledBlockException& e) {
			std::cout << e.what() << std::endl;
		} catch (OfficeBlock::GradeTooLowException& e) {
			std::cout << e.what() << std::endl;
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
		}		
	}
}

int main()
{
	print("TEST START");

	Intern idiotOne;
	Bureaucrat hermes = Bureaucrat("Hermes Conrad", 37);
	Bureaucrat bob = Bureaucrat("Bobby Bobson", 123);
	OfficeBlock ob;
	ob.set_m_intern(idiotOne);
	ob.set_m_signer(bob);
	print("WHEN EXECUTOR NOT SET");
	BureaucracyTry(ob, "presidential pardon", "Pigley");
	ob.set_m_executor(hermes);
	print("WHEN FORM NAME IN UNVALID");
	BureaucracyTry(ob, "mutant pig termination", "Pigley");
	print("WHEN BUREAUCRACT GRADE TOO LOW");
	BureaucracyTry(ob, "robotomy request", "Pigley");
	print("SUCCESS CASE");
	BureaucracyTry(ob, "shrubbery creation", "Pigley");
	// }
	// catch (OfficeBlock::FailedMakeFormException& e) {
	// 	std::cout << "1: " << e.what() << std::endl;
	// } catch (OfficeBlock::NotFilledBlockException& e) {
	// 	std::cout << "3: " << e.what() << std::endl;
	// } catch (OfficeBlock::GradeTooLowException& e) {
	// 	std::cout << "2: " << e.what() << std::endl;
	// } catch (std::exception & e) {
	// 	std::cout << e.what() << std::endl;
	// }

	print("TEST END");
}
