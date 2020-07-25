// ************************************************************************** //
//                                                                            //
//                Account.class.cpp for GlobalBanksters United                //
//                Created on  : Sat Jul 25 14:35:08 2020                      //
//                Last update : Sat Jul 25 14:54:06 2020                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //

#include "Account.class.hpp"
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace ch = std::chrono;

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

void	Account::_displayTimestamp( void )
{
	std::time_t	t = std::time(0);
	std::tm* now = std::localtime(&t);
	std::cout << '[' << (now->tm_year + 1900);
	std::cout << std::setw(2) << std::setfill('0') << (now->tm_mon + 1);
	std::cout << std::setw(2) << std::setfill('0') << now->tm_mday << "_";
	std::cout << std::setw(2) << std::setfill('0') << now->tm_hour;
	std::cout << std::setw(2) << std::setfill('0') << now->tm_min;
	std::cout << std::setw(2) << std::setfill('0') << now->tm_sec;
	std::cout << ']';
}

Account::Account( int initial_deposit ){
	_displayTimestamp();
	_accountIndex = getNbAccounts();
	std::cout << " index" << getNbAccounts() << ";";
	Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	std::cout << "amount" << _amount << ";";
	std::cout << "created" << std::endl;
}

Account::~Account( void ){
	_displayTimestamp();
	std::cout << " index" << _accountIndex << ";";
	std::cout << "amount" << _amount << ";";
	std::cout << "closed" << std::endl;
}

int		Account::checkAmount( void ) const
{
	return (_amount);
}

int		Account::getNbAccounts( void )
{
	return (Account::_nbAccounts);
}

int		Account::getTotalAmount( void )
{
	return (Account::_totalAmount);
}

int		Account::getNbDeposits( void )
{
	return (Account::_totalNbDeposits);
}

int		Account::getNbWithdrawals( void )
{
	return (Account::_totalNbWithdrawals);
}

/*
** [19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
*/

void Account::displayAccountsInfos()
{
	_displayTimestamp();
	std::cout << " accounts:" << getNbAccounts() << ";";
	std::cout << "total:" << getTotalAmount() << ";";
	std::cout << "deposits:" << Account::getNbDeposits() << ";";
	std::cout << "withdrawals:" << Account::getNbWithdrawals();
	std::cout << std::endl;
}

void	Account::displayStatus( void ) const
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";";
	std::cout << "amount:" << checkAmount() << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals;
	std::cout << std::endl;
}

/*
** [19920104_091532] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
*/

void	Account::makeDeposit( int deposit )
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";";
	std::cout << "p_amount:" << checkAmount() << ";";
	std::cout << "deposits:" << deposit << ";";

	_nbDeposits += 1;
	Account::_totalNbDeposits += 1;
	_amount += deposit;
	Account::_totalAmount += deposit;

	std::cout << "amount:" << checkAmount() << ";";
	std::cout << "nb_deposits:" << _nbDeposits;
	std::cout << std::endl;
};

bool	Account::makeWithdrawal( int deposit )
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";";
	std::cout << "p_amount:" << checkAmount() << ";";
	std::cout << "withdrawal:" << deposit << ";";

	if (deposit > checkAmount())
	{
		std::cout << "refused" << std::endl;
		return (false);
	}
	_nbWithdrawals += 1;
	Account::_totalNbWithdrawals += 1;
	_amount -= deposit;
	Account::_totalAmount -= deposit;

	std::cout << "amount:" << _amount << ";";
	std::cout << "nb_withdrawals:" << _nbWithdrawals;
	std::cout << std::endl;
	return (true);
};
// ************************************************************************** //
//                               Account Class                                //
// ************************************************************************** //
// ************************************************************************** //
// vim: set ts=4 sw=4 tw=80 noexpandtab:                                      //
// -*- indent-tabs-mode:t;                                                   -*-
// -*- mode: c++-mode;                                                       -*-
// -*- fill-column: 75; comment-column: 75;                                  -*-
// Brad is a dick                                                             //
// ************************************************************************** //
