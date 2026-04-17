#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Object-oriented class for storing employee payroll data
class payroll {
private:

    int dm_emp_no;
    string dm_name;
    string dm_PAYE_status;
    float dm_hours;
    float dm_rate;
    float dm_gross;
    float dm_SRCOP;
    float dm_tax_credit;
    float dm_PAYE;
    float dm_USC;
    float dm_PRSI;
    float dm_net_pay;

public:
    // Constructor used to initialise employee details
    payroll(int id, string name, string status, float srcop, float credit) {
        dm_emp_no = id;
        dm_name = name;
        dm_PAYE_status = status;
        dm_SRCOP = srcop;
        dm_tax_credit = credit;
        dm_USC = 0;
    }

    // Function calculating gross pay based on hours and hourly rate
    void Get_gross_pay() {
        cout << "\nEnter details for " << dm_name << " (Emp No: " << dm_emp_no << ")" << endl;
        do {
            cout << "Enter hourly rate (Min €13.50): ";
            cin >> dm_rate;
        } while (dm_rate < 13.50);

        cout << "Enter weekly hours worked: ";
        cin >> dm_hours;

        dm_gross = dm_hours * dm_rate;
    }

    float Get_PAYE(char status) {

    if (status == 'S') {
        dm_SRCOP = 846.15;
        dm_tax_credit = 38.46;
    }
    else if (status == 'C') {
        dm_SRCOP = 1019.23;
        dm_tax_credit = 72.11;
    }

    float taxAt20 = 0, taxAt40 = 0;

    if (dm_gross <= dm_SRCOP) {
        taxAt20 = dm_gross * 0.20f;
    } else {
        taxAt20 = dm_SRCOP * 0.20f;
        taxAt40 = (dm_gross - dm_SRCOP) * 0.40f;
    }

    float totalGrossPAYE = taxAt20 + taxAt40;
    dm_PAYE = totalGrossPAYE - dm_tax_credit;

    if (dm_PAYE < 0) dm_PAYE = 0;

    return dm_PAYE;
}
   float Get_USC() {
    float gross = dm_gross;
    if (gross <= 231.00) {
        dm_USC = gross * 0.005f;
    } else if (gross <= 449.27) {
        dm_USC = (231.00 * 0.005f) + ((gross - 231.00) * 0.02f);
    } else {
        dm_USC = (231.00 * 0.005f) + (218.27 * 0.02f) + ((gross - 449.27) * 0.04f);
    }
    return dm_USC;
}

    void Get_PRSI() {
        dm_PRSI = dm_gross * 0.04f;
    }

    void Get_NetPay() {
        dm_net_pay = dm_gross - (dm_PAYE + dm_USC + dm_PRSI);
    }

    void Print_payslip(int emp_no, int week) {
    cout << "\n+------------------------------------------+" << endl;
    cout << "|           Rathmines IT Services          |" << endl;
    cout << "+------------------------------------------+" << endl;
    cout << "| Pay Week No: " << setw(2) << week << "                          |" << endl;
    cout << "| Employee No: " << setw(3) << dm_emp_no << "                         |" << endl;
    cout << "| Name: " << left << setw(18) << dm_name << "            |" << endl;
    cout << "+------------------------------------------+" << endl;
    cout << fixed << setprecision(2);
    cout << "| Gross Pay:                 €" << right << setw(12) << dm_gross << " |" << endl;
    cout << "|                                          |" << endl;
    cout << "| PAYE:                      €" << right << setw(12) << dm_PAYE << " |" << endl;
    cout << "| PRSI:                      €" << right << setw(12) << dm_PRSI << " |" << endl;
    cout << "| USC:                       €" << right << setw(12) << dm_USC << " |" << endl;
    cout << "+------------------------------------------+" << endl;
    cout << "| Net Pay:                   €" << right << setw(12) << dm_net_pay << " |" << endl;
    cout << "+------------------------------------------+" << endl;
}

};

// Loop used to process employee data and generate payslips
int main() {
    payroll Emp_101(101, "Kim Bloggs", "S", 846.15, 38.46);
    payroll Emp_102(102, "Joe Bloggs", "C", 1019.23, 72.11);

    Emp_101.Get_gross_pay();
    Emp_101.Get_PAYE('S');
    Emp_101.Get_USC();
    Emp_101.Get_PRSI();
    Emp_101.Get_NetPay();
    Emp_101.Print_payslip(101, 1);

    Emp_102.Get_gross_pay();
    Emp_102.Get_PAYE('C');
    Emp_102.Get_USC();
    Emp_102.Get_PRSI();
    Emp_102.Get_NetPay();
    Emp_102.Print_payslip(102, 1);

    return 0;
}
