#pragma once
#include "OrderBook.h"
#include "MerkelMain.h"
#include <iostream>
using namespace std;

class TradeBot {
	OrderBook ob;
	MerkelMain app;
	std::vector<std::string> log;
	std::vector<std::string> wallet_condition;
public:

	TradeBot();
	void Start();
	OrderBookEntry PredictTrend(string product, string& time);
	OrderBook getOrderBook() {
		return ob;
	}
	void printLogs();

};
