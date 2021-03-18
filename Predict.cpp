#include "Predict.h"

Predict::Predict() :ob("20200317.csv") {}

OrderBookEntry Predict::PredictTrend(string product, string & time) {
	cout << "---------Product---------\n";
	cout << product << "\n";
	OrderBookEntry b1 = ob.getLowBid(time, product);
	OrderBookEntry a1 = ob.getHighestAsk(time, product);

	string time1 = ob.getNextTime(time);
	OrderBookEntry b2 = ob.getLowBid(time1, product);
	OrderBookEntry a2 = ob.getHighestAsk(time1, product);

	string time2 = ob.getNextTime(time1);
	OrderBookEntry b3 = ob.getLowBid(time2, product);
	OrderBookEntry a3 = ob.getHighestAsk(time2, product);


	cout << "----------Trend----------\n";
	cout << "time 1: " << time << "\n";
	cout << "b1: " << b1.price << "\n";
	cout << "a1: " << a1.price << "\n";
	
	cout << "-------------------------\n";
	
	cout << "time 2: " << time1 << "\n";
	cout << "b2: " << b2.price << "\n";
	cout << "a2: " << a2.price << "\n";

	cout << "-------------------------\n";
	
	cout << "time 3: " << time2 << "\n";
	cout << "b3: " << b3.price << "\n";
	cout << "a3: " << a3.price << "\n";
	cout << "-------Predictions-------\n";

	cout << "b1 < b2 : " << (b1.price < b2.price) << "\n";
	cout << "a1 > a2 : " << (a1.price > a2.price) << "\n";
	cout << "bV > b3 : " << (b1.price > b3.price && b2.price > b3.price) << "\n";
	cout << "aV < a3 : " << (a1.price < a3.price&& a2.price < a3.price) << "\n";
	cout << "bidV == bid3 and askV == ask3 : " << ((b2.price == b3.price) && (a2.price == a3.price)) << "\n";
	cout << "-------------------------\n";
	cout << "Recomended action: ";
	if ((b1.price < b2.price) && (a1.price > a2.price)) {

		if (b1.price > b3.price && b2.price > b3.price) {
			cout << "match ask now.(to buy)\n";
			time = time2;
			a3.timestamp = time2;
			return a3;
		}
		else if (a1.price < a3.price && a2.price < a3.price) {
			cout << "match bid now.(to sell)\n";
			time = time2;
			b3.timestamp = time2;
			return b3;
		}
		else {
			cout << "no.\n";
		}

	}
	else {		
		cout << "no action recomended.\n";
	}

	time = time2;
	OrderBookEntry o(0, 0, "", "", OrderBookType::unknown, "");
	return o;
}


