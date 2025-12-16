#include<bits/stdc++.h>
using namespace std;

class Bank{
    public:
        virtual void addAC(Account* acc)=0;
        virtual void Tnsc(Account* from,Account* to,int amount)=0;
};
class Account{
    protected:
        int balance;
        string acNum="";
        Bank* bank;
    public:
        Account(string num,int inibalance,Bank* b){
            string acNum=num;
            int balance=inibalance;
            bank=b;
        }
        string getNumber(){
            return acNum;
        }
        int getbalance(){
            return balance;
        }
        virtual void deposit(int amount){
            if(amount>0){
                balance +=amount;
                cout<<"Deposited $:" <<amount<<" to "<<acNum<<endl;
            }else{
                cout<<"Enter amount greater than 0";
            }
            transactionLog("Deposit");
        }
        virtual bool withdraw(int amount){
            if(amount>0&&amount<=balance)
            {
                balance-=amount;
                cout<<"Withdrew $"<<amount<<" from "<<acNum<<endl;
                transactionLog("Withdraw");
                return true;
            }
            cout<<"Withdrawal failed: Insufficient funds."<<endl;
            return false;
        }
        virtual void transactionLog(const string& type){
            cout<<"Log"<<type<<" on "<<acNum<<endl;
        }
        bool transferto(Account* to,int amount){
            if(withdraw(amount)){
                to->deposit(amount);
                return true;
            }
            return false;
        }
};
class SavingsAc:public Account{
    private:
        int interestrate;
    public:
        SavingsAc(string num,int inibalance,int rate,Bank* b):Account(num,inibalance,b),interestrate(rate){};
        bool withdraw(int amount) override{
            return Account::withdraw(amount);
        }
        void applyInterest(){
            int interest=balance*interestrate;
            deposit(interest);
            cout<<"Interest is :"<<interest<<endl;
        }
        void transactionLog(const string& type)override{
            cout<<"Savings log:" <<type<<" on "<<acNum<<"Balance : $"<<fixed<<balance<<")"<<endl;;
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
        void Tnsc(Account* from,Account* to,int amount)override{
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
        bool withdraw(int amount)override{
            if(amount>balance){
                balance-=overdraftFee;
                cout<<"Overdraft fee applied: $"<<overdraftFee<<endl;
            }
        return Account::withdraw(amount);
    }
    void transactionLog(const string &type) override{
        cout<<"Checking log:"<<type<<" on "<< acNum<<" (Fee applicable if overdrawn)"<< endl;
    }
};