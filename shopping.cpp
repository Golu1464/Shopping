#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct SelectedProduct {
    string productName;
    string brandName;
    int quantity;
    double price;

    SelectedProduct(const string& product, const string& brand, int qty, double cost)
        : productName(product), brandName(brand), quantity(qty), price(cost) {}
};

void displayProducts(const map<int, string>& products) {
    cout << "Available Products:" << endl;
    for (const auto& product : products) {
        cout << product.first << ". " << product.second << endl;
    }
}

void displayBrands(const map<int, pair<string, double>>& brands, const string& productName) {
    cout << "Available brands for " << productName << ":" << endl;
    for (const auto& brand : brands) {
        cout << brand.first << ". " << brand.second.first << " " << brand.second.second << "/-" << endl;
    }
}

void printCenteredText(const string& text) {
    int termWidth = 80; // You can adjust this based on your terminal width.
    int padding = (termWidth - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
}

int getValidInput(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if(cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } else {
            break;
        }
    }
    return choice;
}

double formatCurrency(double amount) {
    cout << fixed << setprecision(2) << amount;
    return amount;
}

int main() {
    string customerName;
    map<int, string> products;
    char shopAgain;

    printCenteredText("🙏 Welcome To Our Shop 🙏");

    cout << "Enter customer name: ";
    cin >> customerName;

    // Define available products and brands
    products[1] = "Mobile";
    products[2] = "Laptop";
    products[3] = "TV";
    products[4] = "Earphone";

    double totalBill = 0.0;  // Variable to track the total current bill
    vector<SelectedProduct> selectedProductsList; // List to store selected products

    do {
        displayProducts(products);

        int productChoice;
        string productName;
        int brandChoice;
        double brandPrice;
        int quantity;

        cout << "Select a product by entering its number: ";
        productChoice = getValidInput(1, 4);  // Allow valid product choices between 1 and 4

        if (products.find(productChoice) != products.end()) {
            productName = products[productChoice];
            map<int, pair<string, double>> brands;

            // Define brand choices
            if (productChoice == 1) {
                brands[1] = make_pair("Samsung", 40000.0);
                brands[2] = make_pair("Xiomi", 25000.0);
                brands[3] = make_pair("Apple", 100000.0);
                brands[4] = make_pair("OnePlus", 30000.0);
                brands[5] = make_pair("Realme", 25000.0);
            } else if (productChoice == 2) {
                brands[1] = make_pair("Hp", 70000.0);
                brands[2] = make_pair("Dell", 60000.0);
                brands[3] = make_pair("Apple", 120000.0);
            } else if (productChoice == 3) {
                brands[1] = make_pair("LG", 20000.0);
                brands[2] = make_pair("Lloyd", 25000.0);
                brands[3] = make_pair("Samsung", 26000.0);
                brands[4] = make_pair("MI", 24000.0);
                brands[5] = make_pair("Sony", 50000.0);
            } else if (productChoice == 4) {
                brands[1] = make_pair("Boat", 2000.0);
                brands[2] = make_pair("Realme", 2500.0);
                brands[3] = make_pair("JBL", 3500.0);
            }

            do {
                displayBrands(brands, productName);

                cout << "Select a brand for " << productName << " by entering its number: ";
                brandChoice = getValidInput(1, brands.size());  // Allow valid brand choices based on size

                if (brands.find(brandChoice) != brands.end()) {
                    brandPrice = brands[brandChoice].second;

                    cout << "Enter the desired quantity: ";
                    while (true) {
                        cin >> quantity;
                        if (cin.fail() || quantity <= 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid quantity. Please enter a valid quantity: ";
                        } else {
                            break;
                        }
                    }

                    // Add the price of the selected product to the total current bill
                    totalBill += quantity * brandPrice;

                    // Add the selected product to the list
                    selectedProductsList.emplace_back(productName, brands[brandChoice].first, quantity, quantity * brandPrice);

                    cout << "Current total bill: ";
                    formatCurrency(totalBill);
                    cout << "/-" << endl;

                    cout << "Continue shopping (Y/y) or proceed to billing (N/n): ";
                    cin >> shopAgain;
                } else {
                    cout << "Invalid brand choice. Please try again." << endl;
                }
            } while (shopAgain == 'y' || shopAgain == 'Y');
        } else {
            cout << "Invalid product choice. Please try again." << endl;
        }

        cout << "Continue shopping (Y/y) or proceed to billing (N/n): ";
        cin >> shopAgain;
    } while (shopAgain == 'y' || shopAgain == 'Y');

    cout << "Billing for " << customerName << ":" << endl;

    for (const auto& product : selectedProductsList) {
        cout << "Product: " << product.productName << " | Brand: " << product.brandName << " | Quantity: " << product.quantity << " | Price: ";
        formatCurrency(product.price);
        cout << "/-" << endl;
    }

    cout << "Total bill: ";
    formatCurrency(totalBill);
    cout << "/-" << endl;
    cout << "Thank you for shopping with us!" << endl;

    return 0;
}
