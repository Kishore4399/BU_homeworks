#include <stdio.h>
#include <windows.h>

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the bond price
double calculateZeroCouponBondPrice(double faceValue, double yield, int maturity) {
    return faceValue / pow(1 + yield, maturity);
}

double calculateAnnualCouponBondPrice(double faceValue, double yield, int maturity, float couponRate){
    double price = 0;
    for (size_t i = 1; i <= maturity; ++i){
        price += (faceValue * couponRate) / pow(1+yield, i);
    }
    price += faceValue / pow(1 + yield, maturity);

    return price;
}

double calculateZeroCouponBondDuration(double faceValue, double yield, int maturity, float deltaYield) {
    // Calculate bond price using the calculateZeroCouponBondPrice function
    double duration = (calculateZeroCouponBondPrice(faceValue, yield + deltaYield, maturity) - calculateZeroCouponBondPrice(faceValue, yield - deltaYield, maturity)) 
    / (2 * deltaYield * calculateZeroCouponBondPrice(faceValue, yield, maturity));
    return abs(duration);
}

double calculateAnnualCouponBondDuration(double faceValue, double yield, int maturity, float couponRate, float deltaYield) {
    // Calculate bond price using the calculateZeroCouponBondPrice function
    double duration = (calculateAnnualCouponBondPrice(faceValue, yield + deltaYield, maturity, couponRate) - calculateAnnualCouponBondPrice(faceValue, yield - deltaYield, maturity, couponRate))
     / (2 * deltaYield * calculateAnnualCouponBondPrice(faceValue, yield, maturity, couponRate));
    return abs(duration);
}

double calculateZeroCouponBondConvexity(double faceValue, double yield, int maturity, float deltaYield) {
    double convexity = (calculateZeroCouponBondPrice(faceValue, yield + deltaYield, maturity) + calculateZeroCouponBondPrice(faceValue, yield - deltaYield, maturity) 
    - 2 * calculateZeroCouponBondPrice(faceValue, yield, maturity)) 
    / (deltaYield * deltaYield * calculateZeroCouponBondPrice(faceValue, yield, maturity));
    return abs(convexity);
}

double calculateAnnualCouponBondConvexity(double faceValue, double yield, int maturity, float deltaYield, float couponRate ) {
    double convexity = (calculateAnnualCouponBondPrice(faceValue, yield + deltaYield, maturity, couponRate) + calculateAnnualCouponBondPrice(faceValue, yield - deltaYield, maturity, couponRate) 
    - 2 * calculateAnnualCouponBondPrice(faceValue, yield, maturity, couponRate)) 
    / (deltaYield * deltaYield * calculateAnnualCouponBondPrice(faceValue, yield, maturity, couponRate));
    return abs(convexity);
}

int calculateZeroCouponBondPrices(double faceValue, vector<double> yields, vector<int> maturities) {
    // Calculate and display the bond prices for each maturity-yield combination
    for (size_t i = 0; i < maturities.size(); ++i) {
        double maturity = static_cast<double>(maturities[i]);
        double yield = yields[i];

        // Calculate bond price using the calculateZeroCouponBondPrice function
        double price = calculateZeroCouponBondPrice(faceValue, yield, maturity);

        // Display the result
        cout << "Maturity: " << maturity << " years, Yield: " << (yield * 100) << "%" << ", Price: $" << price << endl;
    }

    return 0;
}

int calculateZeroCouponBondDurations(double faceValue, vector<double> yields, vector<int> maturities, float deltaYield) {

    for (size_t i = 0; i < maturities.size(); ++i) {
        double maturity = static_cast<double>(maturities[i]);
        double yield = yields[i];

        // Calculate bond price using the calculateZeroCouponBondPrice function
        double price = calculateZeroCouponBondPrice(faceValue, yield, maturity);
        double duration = calculateZeroCouponBondDuration(faceValue, yield, maturity, deltaYield);
        // Display the result
        cout << "Maturity: " << maturity << " years, Yield: " << (yield * 100) << "%" << ", Price: $" << price << ", Duration: "<< duration << endl;
    }

    // Calculate the duration using finite differences
    return 0;
}

int calculateAnnualCouponBondPrices(double faceValue, vector<double> yields, vector<int> maturities, float couponRate) {
    // Calculate and display the bond prices for each maturity-yield combination
    for (size_t i = 0; i < maturities.size(); ++i) {
        double maturity = static_cast<double>(maturities[i]);
        double yield = yields[i];

        // Calculate bond price using the calculateZeroCouponBondPrice function
        double price = calculateAnnualCouponBondPrice(faceValue, yield, maturity, couponRate);

        // Display the result
        cout << "Maturity: " << maturity << " years, Yield: " << (yield * 100) << "%" << ", Price: $" << price << endl;
    }

    return 0;
}

int calculateAnnualCouponBondDurations(double faceValue, vector<double> yields, vector<int> maturities, float couponRate, float deltaYield) {
    // Calculate and display the bond prices for each maturity-yield combination
    for (size_t i = 0; i < maturities.size(); ++i) {
        double maturity = static_cast<double>(maturities[i]);
        double yield = yields[i];

        // Calculate bond price using the calculateZeroCouponBondPrice function
        double price = calculateAnnualCouponBondPrice(faceValue, yield, maturity, couponRate);

        float duration = calculateAnnualCouponBondDuration(faceValue, yield, maturity, couponRate, deltaYield);


        // Display the result
        cout << "Maturity: " << maturity << " years, Yield: " << (yield * 100) << "%" << ", Price: $" << price << ", Duration: "<< duration << endl;
    }

    return 0;
}

int calculateZeroCouponBondconvexities(double faceValue, vector<double> yields, vector<int> maturities, float deltaYield){
    for (size_t i = 0; i < maturities.size(); ++i) {
        double maturity = static_cast<double>(maturities[i]);
        double yield = yields[i];

        // Calculate bond price using the calculateZeroCouponBondPrice function
        double price = calculateZeroCouponBondPrice(faceValue, yield, maturity);
        double convexity = calculateZeroCouponBondConvexity(faceValue, yield, maturity, deltaYield);

        // Display the result
        cout << "Maturity: " << maturity << " years, Yield: " << (yield * 100) << "%" << ", Price: $" << price << ", convexity: "<< convexity << endl;
    }

    return 0;
}

int calculateAnnualCouponBondconvexities(double faceValue, vector<double> yields, vector<int> maturities, float couponRate, float deltaYield){
    for (size_t i = 0; i < maturities.size(); ++i) {
        int maturity = static_cast<double>(maturities[i]);
        double yield = yields[i];

        // Calculate bond price using the calculateAnnualCouponBondPrice function
        double annualCouponPrice = calculateAnnualCouponBondPrice(faceValue, yield, maturity, couponRate);
        double annualCouponconvexity = calculateAnnualCouponBondConvexity(faceValue, yield, maturity, deltaYield, couponRate);

        double zeroCouponPrice = calculateZeroCouponBondPrice(faceValue, yield, maturity);
        double zeroCouponconvexity = calculateZeroCouponBondConvexity(faceValue, yield, maturity, deltaYield);

        // Display the result
        cout << "Maturity: " << maturity << " years, Yield: " << (yield * 100) << "%" << ", zero coupon bond convexity: " << zeroCouponconvexity << ", coupon bond convexity: "<< annualCouponconvexity << endl;
    }

    return 0;
}
// Function to calculate and print cash flows of an amortizing bond
void amortizingBondCashFlows(double faceValue, int maturity, double annualCouponRate, double annualPrincipalAmortizationRate) {
    // Calculate the principal amortization
    double principalAmortization = annualPrincipalAmortizationRate * faceValue;

    for (int year = 1; year <= maturity; ++year) {
        // Calculate the coupon payment
        double couponPayment = faceValue * annualCouponRate;
        
        // Total cash flow for the year
        double totalCashFlow = couponPayment + principalAmortization;

        // Print the cash flow for the year
        cout << "Year " << year << ": ";
        cout << "Coupon Payment = $" << couponPayment << ", ";
        cout << "Principal Amortization = $" << principalAmortization << ", ";
        cout << "Total Cash Flow = $" << totalCashFlow << endl;

        // Update the remaining principal for the next year
        faceValue -= principalAmortization;
    }
}

float amortizingBondPrice(double faceValue, float yield, int maturity, double annualCouponRate, double annualPrincipalAmortizationRate) {
    double PV = 0;
    // Calculate the principal amortization
    double principalAmortization = annualPrincipalAmortizationRate * faceValue;

    for (int year = 1; year <= maturity; ++year) {
        // Calculate the coupon payment
        double couponPayment = faceValue * annualCouponRate;
        
        // Total cash flow for the year
        double totalCashFlow = couponPayment + principalAmortization;

        PV += totalCashFlow / pow(1+yield, year);

        // Update the remaining principal for the next year
        faceValue -= principalAmortization;
    }

    return PV;
}


int main() {
    // Define the face value and maturities of zero-coupon bonds
    const double faceValue = 100.0;
    vector<int> maturities = {1, 2, 3, 5, 10, 30}; // Maturities in years

    // Define the yields for each maturity
    vector<double> yields = {0.055, 0.052, 0.05, 0.047, 0.046, 0.048}; // Yields (interest rates) for each maturity

    /*a) Calculate prices of a zero coupon bond that pays $100 at maturity for each maturity & yield combination. 
    Which price is the highest? Is this reasonable?*/ 
    cout << "Zero Coupon Bond" << endl;
    calculateZeroCouponBondPrices(faceValue, yields, maturities);
    cout<<endl;
    /* The bond prices were calculated for various maturity-yield combinations, and the bond with a 1-year maturity yielded the 
    highest price of $94.7867. This result is reasonable due to the inverse relationship between bond prices and maturity periods, as well as 
    the direct relationship between bond prices and yields. A 1-year maturity bond demands a shorter waiting period for the 
    investor to receive the face value, making it more valuable in the present compared to longer-maturity bonds. Additionally, 
    the 1-year bond benefits from the highest yield, which further enhances its present value. As yields typically decrease with 
    increasing maturity, shorter-term bonds tend to have the highest prices under constant yield conditions. Therefore, 
    the higher price for the 1-year bond is reasonable, given its shorter maturity and higher yield.*/


    /*(b) Calculate the duration of each zero coupon bond, or sensitivity of the bond price to achange in bond yield, 
    using using finite differences. What is the relationship between bond prices and bond yields?*/
    calculateZeroCouponBondDurations(faceValue, yields, maturities, 0.0001);
    cout<<endl;
    /*The relationship between bond prices and bond yields is inversely proportional: When bond yields rise, 
    bond prices fall, and when bond yields fall, bond prices rise.*/


    /*(c) Calculate prices of coupon bonds that pay $100 at maturity and 5% annually until maturity. 
    Which prices are below $100? Which prices are above? Why?*/
    cout << "Annual Coupon Bond" << endl;
    calculateAnnualCouponBondPrices(faceValue, yields, maturities, 0.05);
    cout<<endl;
    /*The prices under $100 are $99.5261 and $99.6292 of maturity in 1 and 2 years respectively. The prices over $100 
    are $101.31, $103.15 and $103.146 of maturity in 5, 10 and 30 years respectively.
    The reason why some prices are below $100 and some are above $100 is due to the relationship between the coupon rate, 
    the yield, and the time to maturity. When the coupon rate is lower than the yield, the bond is priced below its face 
    value because investors require a higher yield to compensate for the lower coupon payments. Conversely, when the coupon 
    rate is higher than the yield, the bond is priced above its face value because investors are willing to accept lower 
    yields in exchange for the higher coupon payments.*/


    /*(d) Calculate the duration of each coupon bond using finite differences. Do zero-coupon bonds or coupon bonds 
    have higher duration? Why?*/
    calculateAnnualCouponBondDurations(faceValue, yields, maturities, 0.05, 0.0001);
    cout<<endl;
    /*Zero-coupon bonds have higher duration compared to coupon bonds. This is because zero-coupon bonds have no periodic 
    coupon payments, which means all their cash flows are concentrated at maturity. As a result, a larger portion of their 
    present value depends on the final payment at maturity. The absence of coupon payments causes the cash flows to be 
    received later in the bond's life, leading to a higher weighted average time until the bond's cash flows are received, 
    which is reflected in a higher duration.*/


    /*(e) Calculate the second derivative of each bond price with respect to yield (commonly known as convexity). 
    Are the second derivatives positive or negative?*/
    cout << "Coupon Bond Convexity: " << endl;
    calculateAnnualCouponBondconvexities(faceValue, yields, maturities, 0.05, 0.0001);
    cout<<endl;
    /* The second derivatives are positive*/


    /*(f) Consider a portfolio that is long one unit of the 1 year zero-coupon bond, long one unit of the 3 year 
    zero-coupon bond and short two units of the 2 year zero-coupon bond. Calculate the initial value of the portfolio.*/
    double initialValue = calculateZeroCouponBondPrice(100, 0.055, 1) + calculateZeroCouponBondPrice(100, 0.05, 3) - 2 * calculateZeroCouponBondPrice(100, 0.052, 2);
    cout<< "The initial value of the portfolio is: $ " << initialValue << endl;
    cout<<endl;

    /*(g) Calculate the duration of this portfolio. Calculate the convexity of the portfolio as well. Which quantity is bigger?*/
    double porfolioDuration = (calculateZeroCouponBondPrice(100, 0.055, 1) * calculateZeroCouponBondDuration(100, 0.055, 1, 0.0001)
    + calculateZeroCouponBondPrice(100, 0.05, 3) * calculateZeroCouponBondDuration(100, 0.05, 3, 0.0001)
    - (2 * calculateZeroCouponBondPrice(100, 0.052, 2) * calculateZeroCouponBondDuration(100, 0.052, 2, 0.0001))) / initialValue;
    cout << "The duration of this portfolio is: " << porfolioDuration << endl;

    double portfolioConvexity = (calculateZeroCouponBondPrice(100, 0.055, 1) * calculateZeroCouponBondConvexity(100, 0.055, 1, 0.0001)
    + calculateZeroCouponBondPrice(100, 0.05, 3) * calculateZeroCouponBondConvexity(100, 0.05, 3, 0.0001)
    - (2 * calculateZeroCouponBondPrice(100, 0.052, 2) * calculateZeroCouponBondConvexity(100, 0.052, 2, 0.0001))) / initialValue;
    cout << "The convexity of this portfolio is: " << portfolioConvexity << endl;
    cout<<endl;
    /* The convexity of the portfolio is bigger than the duration of the portfolio
    The duration of this portfolio is: -16.5212
    The convexity of this portfolio is: 288.294*/


    /*(h) Adjust the number of units of the short position in the two year zero-coupon bond
    so that the portfolio is duration neutral (leaving the units of the one and three year
    zero-coupon bonds unchnaged). How many units of the two year zero-coupon bond are
    required to do this?*/
    double unitOf2YearBond = (calculateZeroCouponBondPrice(100, 0.055, 1) * calculateZeroCouponBondDuration(100, 0.055, 1, 0.0001)
    + calculateZeroCouponBondPrice(100, 0.05, 3) * calculateZeroCouponBondDuration(100, 0.05, 3, 0.0001)) 
    / (calculateZeroCouponBondPrice(100, 0.052, 2) * calculateZeroCouponBondDuration(100, 0.052, 2, 0.0001));
    cout << "the number of units of the short position in the two year zero-coupon bond is " << unitOf2YearBond << endl;
    cout<<endl;


    /*(i) Suppose you own this adjusted portfolio and rates sell off by 100 basis points (each yield rises by 1%). 
    What happens to the value of your portfolio?*/
    double initialAdjValue = calculateZeroCouponBondPrice(100, 0.055, 1) + calculateZeroCouponBondPrice(100, 0.05, 3) - unitOf2YearBond * calculateZeroCouponBondPrice(100, 0.052, 2);
    double risedRateAdjValue = calculateZeroCouponBondPrice(100, 0.065, 1) + calculateZeroCouponBondPrice(100, 0.06, 3) - unitOf2YearBond * calculateZeroCouponBondPrice(100, 0.062, 2);
    cout << "The initial value of this adjusted portfolio is " << initialAdjValue << endl;
    cout << "The value of this adjusted portfolio after each yield rises by 1% is " << risedRateAdjValue << endl;
    cout<<endl;
    /*The value of this portfolio will increase from 4.08944 to 4.09675*/


    /*(j) Now suppose you own this adjusted portfolio and rates rally by 100 basis points (each yield decreases by 1%). 
    What happens to the value of your portfolio? Is this a portfolio you would want to own? What are the risks of owning this portfolio?*/
    double decreasedRateAdjValue = calculateZeroCouponBondPrice(100, 0.045, 1) + calculateZeroCouponBondPrice(100, 0.04, 3) - unitOf2YearBond * calculateZeroCouponBondPrice(100, 0.042, 2);
    cout << "The initial value of this adjusted portfolio is " << initialAdjValue << endl;
    cout << "The value of this adjusted portfolio after each yield decreases by 1% is " << decreasedRateAdjValue << endl;

    double risedRateValue = calculateZeroCouponBondPrice(100, 0.065, 1) + calculateZeroCouponBondPrice(100, 0.06, 3) - 2 * calculateZeroCouponBondPrice(100, 0.062, 2);
    double decreasedRateValue = calculateZeroCouponBondPrice(100, 0.045, 1) + calculateZeroCouponBondPrice(100, 0.04, 3) - 2 * calculateZeroCouponBondPrice(100, 0.042, 2);
    cout << "The initial value of portfolio in (f) is " << initialValue << endl;
    cout << "The value of portfolio in (f) after each yield rises by 1% is " << risedRateValue << endl;
    cout << "The value of portfolio in (f) after each yield decreases by 1% is " << decreasedRateValue << endl;

    cout<<endl;
    /*If interest rates decrease by 100 basis points (1%), your portfolio's value will increase, going from 4.0894 to 4.09719. 

    While this portfolio responded positively to falling rates, the magnitude of the change is relatively small for both rate increases and decreases. 
    This portfolio may be suitable if your primary goal is to preserve capital and minimize the impact of interest rate fluctuations. 
    It can provide stability in different rate environments, but it's not designed for aggressive returns. 

    The primary risk of owning this portfolio is its potential underperformance in a sustained rising rate environment. Additionally, 
    individual bonds within the portfolio may carry credit and liquidity risks, so it's important to consider those factors when making investment decisions.
 */


    /*(k) Print the cashflows of a 5-year amortizing bond that repays 20% of its principal annually and pays a 5% coupon (annually).*/
    amortizingBondCashFlows(100, 5, 0.05, 0.2);
    cout << endl;

    /*(l) Calculate the price and duration of the amortizing bond using finite differences.
    Comment on the difference between this bond and its zero coupon and coupon equivalents*/
    double amortizingBondP = amortizingBondPrice(100, 0.047, 5, 0.05, 0.2);
    cout << "The price of the amortizing bond is $ " << amortizingBondP << endl;
    double amortizingBondD = (amortizingBondPrice(100, 0.047 - 0.0001, 5, 0.05, 0.2) - amortizingBondPrice(100, 0.047 + 0.0001, 5, 0.05, 0.2))
    / (2 * 0.0001 * amortizingBondPrice(100, 0.047, 5, 0.05, 0.2));
    cout << "The duration of the amortizing bond is " << amortizingBondD << endl;
    /* 
    The price of the amortizing bond is $ 100.81
    The duration of the amortizing bond is 2.82185

    Difference:
        The price and duration characteristics of an amortizing bond differ significantly from its zero-coupon and 
        coupon-paying counterparts. An amortizing bond, with its gradual principal repayment, typically commands a 
        higher price compared to its zero-coupon equivalent of the same maturity. Furthermore, the amortizing bond 
        often exhibits a shorter duration than its maturity, indicating lower sensitivity to interest rate changes. 
        In contrast, zero-coupon bonds, sold at a discount, have durations closely aligned with their maturities, 
        making them highly responsive to interest rate fluctuations. Coupon-paying bonds, positioned between these extremes, 
        are influenced by both their coupon payments and principal repayment schedules. This renders amortizing bonds 
        an intriguing choice for investors seeking a balance between relatively higher prices, reduced interest rate risk, 
        and unique rate sensitivity dynamics.
    */

    return 0;
}
