#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
using namespace std;

class MerkelMain
{
public:
	MerkelMain();
	/** Call this to start the sim */
	void init();
	void initialize();
	bool EnterAsk(std::string Prod, std::string price, std::string amount);
	bool EnterBid(std::string Prod, std::string price, std::string amount);
	void serCurrentTime(std::string time);
	void gotoNextTimeframe();
	std::string getWallet();
private:
	void printMenu();
	void printHelp();
	void printMarketStats();
	void enterAsk();
	void enterBid();
	void printWallet();
	int getUserOption();
	void processUserOption(int userOption);

	std::string currentTime;

	OrderBook orderBook{ "20200317.csv" };

	Wallet wallet;

};
