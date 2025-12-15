// 01-invoice-srp-ocp.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

struct LineItem
{
    string sku;
    int quantity{0};
    double unitPrice{0.0};
};

struct process{

    string processHandler(const vector<LineItem> &items,
                          const map<string, double> &discounts,
                          const string &email)
    {
        // pricing
        double subtotal = 0.0;
        for (auto &it : items)
            subtotal += it.unitPrice * it.quantity;

        // discounts (tightly coupled)
        double discount_total = 0.0;
        for (auto &kv : discounts)
        {
            const string &k = kv.first;
            double v = kv.second;
            if (k == "percent_off")
            {
                discount_total += subtotal * (v / 100.0);
            }
            else if (k == "flat_off")
            {
                discount_total += v;
            }
            else
            {
                // unknown ignored
            }
        }

        // tax inline
        double tax = (subtotal - discount_total) * 0.18;
        double grand = subtotal - discount_total + tax;

        // rendering inline (pretend PDF)
        ostringstream pdf;
        pdf << "INVOICE\n";
        for (auto &it : items)
        {
            pdf << it.sku << " x" << it.quantity << " @ " << it.unitPrice << "\n";
        }
        pdf << "Subtotal: " << subtotal << "\n"
            << "Discounts: " << discount_total << "\n"
            << "Tax: " << tax << "\n"
            << "Total: " << grand << "\n";

        // email I/O inline (tight coupling)
        if (!email.empty())
        {
            cout << "[SMTP] Sending invoice to " << email << "...\n";
        }

        // logging inline
        cout << "[LOG] Invoice processed for " << email << " total=" << grand << "\n";

        return pdf.str();
    }

};

class compute{
public:
process invoiceMaker;
    double computeTotal(const vector<LineItem> &items,
                        const map<string, double> &discounts, const string &email)
    {
        string dummyEmail = "noreply@example.com";
        auto rendered = invoiceMaker.processHandler(items, discounts, email);
        cout << rendered ;
        auto pos = rendered.rfind("Total:");
        if (pos == string::npos)
            throw runtime_error("No total");
        auto line = rendered.substr(pos + 6);
        return stod(line);
    }
};

class InvoiceService{
    public:
    compute invoicer;
        void invoiceProcess(const vector<LineItem> &items,
                            const map<string, double> &discounts,
                            const string &email)
        {
         cout<<   invoicer.computeTotal(items, discounts, email) << endl;


        }
};





int main()
{
    InvoiceService svc;
    // Create items
    vector<LineItem> items = {{"ITEM-001", 3, 100.0}, {"ITEM-002", 1, 250.0}};
    map<string, double> discounts = {{"percent_off", 10.0}};
     svc.invoiceProcess(items, discounts, "customer@example.com");
    return 0;
    return 0;
}
