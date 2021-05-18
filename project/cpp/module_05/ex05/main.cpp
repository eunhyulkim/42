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
#include "CentralBureaucracy.hpp"

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

	std::string get_random_name()
	{
		std::string alpha_list = "bcdfghjklmnpqrstvwxyz";
		std::string name_list[] = {
			"ohn", "ane", "amy", "ujan", "om",
			"ohnson", "ack", "ella", "anca", "onita",
			"ono", "ana", "ior", "oris", "emma",
			"erica", "ace", "abel", "ali", "yra"
		};
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> first_dis(0, 20);
		std::uniform_int_distribution<int> last_dis(0, 19);
		return (alpha_list[first_dis(gen)] + name_list[last_dis(gen)]);
	}

	int get_random_grade()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> grade_dis(1, 150);
		return (grade_dis(gen));
	}

	void multipleQueueUp(CentralBureaucracy& central, int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
				central << get_random_name();
			else
				central.queueUp(get_random_name());			
		}		
		std::cout << "wating person count: " << central.get_m_queue_count() << std::endl;
	}
}

int main()
{

	print("NobodyTargetExceptionError Test");
	{
		CentralBureaucracy central;
		try {
			central.doBureaucracy();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	print("EmptyOfficeExceptionError Test");
	{
		CentralBureaucracy central;
		try {
			multipleQueueUp(central, 10);
			central.doBureaucracy();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			std::cout << "wating person count: " << central.get_m_queue_count() << std::endl;
		}
	}

	print("FulledOfficeException Test");
	{
		CentralBureaucracy central;
		multipleQueueUp(central, 10);
		Bureaucrat *worker[41];
		for (int i = 0; i < 41; i++)
			worker[i] = new Bureaucrat(get_random_name(), get_random_grade());
		try {
			for (int i = 0; i < 41; i++)
				central << *worker[i];
			central.doBureaucracy();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			std::cout << "wating person count: " << central.get_m_queue_count() << std::endl;
		}
		for (int i = 0; i < 41; i++)
			delete worker[i];
	}

	print("Succeess Case Test");
	{
		CentralBureaucracy central;
		Bureaucrat *worker[20];
		for (int i = 0; i < 20; i++)
		{
			worker[i] = new Bureaucrat(get_random_name(), get_random_grade());
			if (i < 10)
				central.feed(*worker[i]);
			else
				central << *worker[i];
		}
		try {
			multipleQueueUp(central, 10);
			central.doBureaucracy();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		for (int i = 0; i < 20; i++)
			delete worker[i];
		std::cout << "wating person count: " << central.get_m_queue_count() << std::endl;
	}

	print("Succeess Big Case Test");
	{
		CentralBureaucracy central;
		Bureaucrat *worker[40];
		for (int i = 0; i < 40; i++)
		{
			worker[i] = new Bureaucrat(get_random_name(), get_random_grade());
			if (i < 10)
				central.feed(*worker[i]);
			else
				central << *worker[i];
		}
		try {
			multipleQueueUp(central, 1000);
			central.doBureaucracy();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		for (int i = 0; i < 40; i++)
			delete worker[i];
		std::cout << "wating person count: " << central.get_m_queue_count() << std::endl;
	}
	print("TEST END");
}
