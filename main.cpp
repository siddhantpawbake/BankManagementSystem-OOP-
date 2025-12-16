#include<bits/stdc++.h>
using namespace std;

class Account;

class Bank{
    public:
        virtual void addAC(Account* acc)=0;
        virtual void Tnsc(Account* from,Account* to,double amount)=0;
};

class Account{
    protected:
        double balance;
        string acNum="";
        Bank* bank;
    public:
        Account(const string& num,double inibalance,Bank* b){
            acNum = num;
            balance = inibalance;
            bank = b;
        }
        string getNumber(){
            return acNum;
        }
        double getbalance(){
            return balance;
        }
        virtual void deposit(double amount){
            if(amount>0){
                balance += amount;
                cout<<"Deposited $:" <<amount<<" to "<<acNum<<endl;
            }else{
                cout<<"Enter amount greater than 0"<<endl;
                return;
            }
            transactionLog("Deposit");
        }
        virtual bool withdraw(double amount){
            if(amount>0 && amount<=balance)
            {
                balance -= amount;
                cout<<"Withdrew $"<<amount<<" from "<<acNum<<endl;
                transactionLog("Withdraw");
                return true;
            }
            cout<<"Withdrawal failed: Insufficient funds."<<endl;
            return false;
        }
        virtual void transactionLog(const string& type){
            cout<<"Log "<<type<<" on "<<acNum<<endl;
        }
        bool transferto(Account* to,double amount){
            if(withdraw(amount)){
                to->deposit(amount);
                return true;
            }
            return false;
        }
};
class SavingsAc:public Account{
    private:
        double interestrate;
    public:
        SavingsAc(const string& num,double inibalance,double rate,Bank* b):Account(num,inibalance,b),interestrate(rate){}
        bool withdraw(double amount) override{
            return Account::withdraw(amount);
        }
        void applyInterest(){
            double interest = balance * interestrate;
            deposit(interest);
            cout<<"Interest is :"<<fixed<<setprecision(2)<<interest<<endl;
        }
        void transactionLog(const string& type)override{
            cout<<"Savings log: "<<type<<" on "<<acNum<<" Balance: $"<<fixed<<setprecision(2)<<balance<<endl;
        }
};
class SimpleBank:public Bank{
    private:
        vector<Account*>accounts;
    public:
        void addAC(Account *acc)override{
            accounts.push_back(acc);
            cout<<"Added account: "<<acc->getNumber()<<endl;
        }
        void Tnsc(Account* from,Account* to,double amount)override{
            if(from->transferto(to,amount)){
                cout<<"Transfer Successful from ac "<<from->getNumber()<<" to "<<to->getNumber()<<endl;
            }
            else{
                cout<<"Transfer Failed"<<endl;
            }
        }
        void displaybalances(){
            cout<<"<----Bank Summary---->"<<endl;
            for(auto i:accounts){
                cout<< i->getNumber()<<":$"<<fixed<<setprecision(2)<<i->getbalance()<<endl;
            }
        }
};
class CheckingAccount : public Account
{
private:
    double overdraftFee;

public:
    CheckingAccount(string num,double initialBalance,double fee,Bank *b):Account(num,initialBalance,b),overdraftFee(fee){}
        bool withdraw(double amount)override{
            if(amount>balance){
                balance -= overdraftFee;
                cout<<"Overdraft fee applied: $"<<overdraftFee<<endl;
            }
            return Account::withdraw(amount);
        }
    void transactionLog(const string &type) override{
        cout<<"Checking log:"<<type<<" on "<< acNum<<" (Fee applicable if overdrawn)"<< endl;
    }
};
int main()
{
    SimpleBank bank;

    vector<Account *> localAccounts;
    int choice;

    do
    {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Money\n";
        cout << "6. Apply Interest (Savings)\n";
        cout << "7. Display All Balances\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string accNum;
            double balance, rate;

            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Interest Rate (e.g., 0.05): ";
            cin >> rate;

            Account *acc = new SavingsAc(accNum, balance, rate, &bank);
            bank.addAC(acc);
            localAccounts.push_back(acc);
        }

        else if (choice == 2)
        {
            string accNum;
            double balance, fee;

            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Overdraft Fee: ";
            cin >> fee;

            Account *acc = new CheckingAccount(accNum, balance, fee, &bank);
            bank.addAC(acc);
            localAccounts.push_back(acc);
        }

        else if (choice == 3)
        {
            string accNum;
            double amount;

            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            for (auto acc : localAccounts)
            {
                if (acc->getNumber() == accNum)
                {
                    acc->deposit(amount);
                    break;
                }
            }
        }

        else if (choice == 4)
        {
            string accNum;
            double amount;

            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            for (auto acc : localAccounts)
            {
                if (acc->getNumber() == accNum)
                {
                    acc->withdraw(amount);
                    break;
                }
            }
        }

        else if (choice == 5)
        {
            string fromNum, toNum;
            double amount;
            Account *from = nullptr, *to = nullptr;

            cout << "From Account: ";
            cin >> fromNum;
            cout << "To Account: ";
            cin >> toNum;
            cout << "Amount: ";
            cin >> amount;

            for (auto acc : localAccounts)
            {
                if (acc->getNumber() == fromNum)
                    from = acc;
                if (acc->getNumber() == toNum)
                    to = acc;
            }

            if (from && to)
            {
                bank.Tnsc(from, to, amount);
            }
            else
            {
                cout << "Invalid account number(s)." << endl;
            }
        }

        else if (choice == 6)
        {
            string accNum;
            cout << "Enter Savings Account Number: ";
            cin >> accNum;

            for (auto acc : localAccounts)
            {
                if (acc->getNumber() == accNum)
                {
                    SavingsAc *sav = dynamic_cast<SavingsAc *>(acc);
                    if (sav)
                    {
                        sav->applyInterest();
                    }
                    else
                    {
                        cout << "Not a savings account." << endl;
                    }
                    break;
                }
            }
        }

        else if (choice == 7)
        {
            bank.displaybalances();
        }

        else if (choice == 0)
        {
            cout << "Exiting system..." << endl;
        }

        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
