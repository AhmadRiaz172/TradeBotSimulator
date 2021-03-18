#include "TradeBot.h"

TradeBot::TradeBot() :ob("20200317.csv") {}

OrderBookEntry TradeBot::PredictTrend(string product, string& time) {
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
            app.serCurrentTime(time2);
            cout << "Bot about to perform recomended action.\n";
            if (app.EnterBid(a3.product, to_string(a3.price), to_string(a3.amount))) {
                log.push_back(a3.product + "," + to_string(a3.price) + "," + to_string(a3.amount));
            }
            time = time2;
            return a3;
        }
        else if (a1.price < a3.price && a2.price < a3.price) {
            cout << "match bid now.(to sell)\n";
            app.serCurrentTime(time2);
            cout << "Bot about to perform recomended action.\n";
            if (app.EnterAsk(b3.product, to_string(b3.price), to_string(b3.amount))) {
                log.push_back(b3.product + "," + to_string(b3.price) + "," + to_string(b3.amount));
            }
            time = time2;
            return b3;
        }
        else {
            cout << "no.\n";
        }
    }
    else {
        cout << "no action recomended.\n";
    }


    OrderBookEntry o(0, 0, "", "", OrderBookType::unknown, "");
    return o;
}

void TradeBot::printLogs() {

    for (int i = 0; i < log.size(); i ++) {
        cout << "Trade "<< i+1<<": " << log[i] << "\n" << "Wallet after trade "<< i+ 1 << ":- \n" << wallet_condition[i]<<"\n";
    }

}

void TradeBot::Start() {
    cout << "----------------------------- TRADE BOT -----------------------------\n";
    cout << "Starting bot .....\n";
    string pr;
    cout << "Enter product you want to trade: ";
    cin >> pr;

    app.initialize();
    string time = getOrderBook().getEarliestTime();
    PredictTrend(pr, time);
    system("pause");
    app.gotoNextTimeframe();
    wallet_condition.push_back(app.getWallet());
    int a;

    cout << "Press: -\n 1. to print trade log.\n 2. to continue trade.\n";
    cin >> a;
    
    while ( a == 1 ) {
        printLogs();
        cout << "Press: -\n 1. to print trade log.\n 2. to continue trade.\n";
        cin >> a;

    }
    
    
    if ( a == 2 ){
        system("CLS");
        PredictTrend(pr, time);
        system("pause");

        app.gotoNextTimeframe();
        wallet_condition.push_back(app.getWallet());

        cout << "--------------------------------------------------------------------\n";
        cout << "Ending trade as no more time frames left\n";
        cout << "Displaying final trade log: \n";
        printLogs();
    }


}
