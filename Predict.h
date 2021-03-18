#pragma once
#include "OrderBook.h"
#include <iostream>
using namespace std;

class Predict {
	OrderBook ob;


public:

	Predict();
	OrderBookEntry PredictTrend( string product, string &time );
	OrderBook getOrderBook() {
		return ob;
	}

};

