#include "BalanceSheetFormatter.hpp"

#include <sstream>
#include <vector>

std::string BalanceSheetFormatter::getLineItem(std::string itemName,
                                               int itemWidth,
                                               double itemValue) {
    std::stringstream valueStream;
    valueStream << itemValue;
    std::string valueString = valueStream.str();
    int valueWidth = valueString.length();

    int streamWidth = itemWidth - valueWidth;

    std::stringstream itemStream;
    itemStream.width(streamWidth);
    itemStream << std::left << itemName << itemValue;

    return itemStream.str();

}

std::string BalanceSheetFormatter::makeBlank(int itemWidth) {

    std::stringstream blankStream;
    blankStream.width(itemWidth);

    blankStream << std::left << " ";

    return blankStream.str();
}

std::string BalanceSheetFormatter::format(
        const BankBalanceSheet &balanceSheet) {

    const int streamWidth = 31;

    std::vector<std::string> leftSide;
    std::vector<std::string> rightSide;

    int leftSideCount = 0;
    int rightSideCount = 0;

    std::stringstream ss;

    ss <<
       "----------------------------------------------------------------"
       << std::endl;

    double liquidity = balanceSheet.getLiquidAssets();
    if (liquidity > 0.0) {
        leftSide.push_back(getLineItem("Liquid Assets: ",
                                       streamWidth,
                                       liquidity));
        leftSideCount++;
    }

    double credit = balanceSheet.getLoansToFirms();
    if (credit > 0.0) {
        leftSide.push_back(getLineItem("Loans to Firms: ",
                                       streamWidth,
                                       credit));
        leftSideCount++;
    }

    double interbankCredit = balanceSheet.getLoansToBanks();
    if (interbankCredit > 0.0) {
        leftSide.push_back(getLineItem("Loans to Banks: ",
                                       streamWidth,
                                       interbankCredit));
        leftSideCount++;
    }

    double deposits = balanceSheet.getDeposits();
    if (deposits > 0.0) {
        rightSide.push_back(getLineItem("| Deposits: ",
                                        streamWidth,
                                        deposits));
        rightSideCount++;
    }

    double interbankDebtor = balanceSheet.getBankLoansPayable();
    if (interbankDebtor > 0.0) {
        rightSide.push_back(getLineItem("| Bank Loans Payable: ",
                                        streamWidth,
                                        interbankDebtor));
        rightSideCount++;
    }

    int index = 0;

    while ((index < leftSideCount) && (index < rightSideCount)) {
        ss << leftSide[index] << rightSide[index] << std::endl;
        index++;
    }


    if ((index == leftSideCount) && (index == rightSideCount)){
        std::stringstream filler;
        filler.width(streamWidth);
        ss <<
           "                              |-------------------------------"
           << std::endl;
        ss << "                              ";
    }

    //more liability than asset line items

    if ((index == leftSideCount) && (index < rightSideCount)){
        std::stringstream filler;
        filler.width(streamWidth);

        while (index < rightSideCount) {
            ss << "                              ";
            ss << rightSide[index] << std::endl;
            index++;
        }

        ss <<
           "                              |-------------------------------"
           << std::endl;
        ss << "                              ";
    }

    //more asset than liability line items

    if ((index == rightSideCount) && (index < leftSideCount)){

        std::stringstream filler;
        filler.width(streamWidth);

        while (index < (leftSideCount-3)) {
            ss << leftSide[index];
            ss << "                              " << std::endl;
            index++;
        }

        if (rightSideCount == (leftSideCount-2)){

            ss << leftSide[index];
            ss << "|-------------------------------" << std::endl;
            ss << leftSide[index+1];


        }

        else {
            ss << leftSide[index];
            ss << "|-------------------------------" << std::endl;
            ss << "                               ";

        }
    }


    ss << getLineItem("| Total Liabilities: ",
                      streamWidth,
                      balanceSheet.getTotalLiabilities());

    ss << std::endl;
    ss <<
       "----------------------------------------------------------------"
       << std::endl;

    ss << getLineItem("Total Assets: ",
                      streamWidth,
                      balanceSheet.getTotalAssets());

    ss << getLineItem("| Ownership equity: ",
                      streamWidth,
                      balanceSheet.getTotalEquity());

    ss << std::endl;
    ss <<
       "----------------------------------------------------------------"
       << std::endl;

    return ss.str();
}
