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

