#ifndef BALANCESHEETFORMATTER_HPP
#define BALANCESHEETFORMATTER_HPP

#include <string>

#include "../Agents/BankBalanceSheet.hpp"

class BalanceSheetFormatter {
public:
    static std::string format(
            const BankBalanceSheet& balanceSheet);
private:
    static std::string getLineItem(std::string itemName,
                                   int itemWidth,
                                   double itemValue);
    static std::string makeBlank(int itemWidth);

};

#endif //BALANCESHEETFORMATTER_HPP
