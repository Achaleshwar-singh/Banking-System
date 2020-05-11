#include <iostream>
#include <map>
#include <fstream>
using namespace std;
class Account
{
private:
    long accountno;
    string firstname;
    string lastname;
    double amount;
    static long nextaccountno;
public:
    Account() {}
    Account(string fname, string lname, double money)
    {
        nextaccountno++;
        this->accountno=nextaccountno;
        this->firstname=fname;
        this->lastname=lname;
        this->amount=money;
    }
    long getaccountno()
    {
        return this->accountno;
    }
    string getfirstname()
    {
        return this->firstname;
    }
    string getlastname()
    {
        return this->lastname;
    }
    double getamount()
    {
        return this->amount;
    }
    void cashdeposit(double money);
    void cashwithdraw(double money);
    void cashtransfer(Account acc, double money);
    static void setlastaccountno(long accountno);
    long getlastaccountno()
    {
        return this->nextaccountno;
    }
    friend ofstream & operator<<(ofstream &ofs,Account &acc);
    friend ifstream & operator>>(ifstream &ifs,Account &acc);
    friend ostream & operator<<(ostream &os, Account &acc);
};
void Account::cashdeposit(double money)
{
    this->amount=this->amount+money;
}
void Account::cashwithdraw(double money)
{
    if(money>this->amount)
    {
        cout<<"SORRY YOU DONT HAVE ENOUGH BALANCE IN YOUR ACCOUNT"<<endl;
    }
    else
    {
        this->amount=this->amount-money;
    }
}
ofstream & operator<<(ofstream &ofs,Account &acc)
{
    ofs<<acc.accountno<<endl;
    ofs<<acc.firstname<<endl;
    ofs<<acc.lastname<<endl;
    ofs<<acc.amount<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs,Account &acc)
{
    ifs>>acc.accountno;
    ifs>>acc.firstname;
    ifs>>acc.lastname;
    ifs>>acc.amount;
    return ifs;
}
ostream & operator<<(ostream &os, Account &acc)
{
    cout<<"YOUR ACCOUNT NO IS:-"<<acc.accountno<<endl;
    cout<<"YOUR FIRST NAME IS:-"<<acc.firstname<<endl;
    cout<<"YOUR LAST NAME IS:-"<<acc.lastname<<endl;
    cout<<"YOUR CURRENT ACCOUNT BALANCE IS:-"<<acc.amount<<endl;
}
void Account::setlastaccountno(long accountno)
{
    nextaccountno=accountno;
}
long Account::nextaccountno=0;
class Bank
{
private:
    map<long,Account>accounts;
public:
    Bank();
    Account openaccount(string fname, string lname, double money);
    Account checkbalance(long accountno);
    Account deposit(long accountno, double money);
    Account withdraw(long accountno, double money);
    Account transfer(long accountno, long raccountno, double money);
    Account showdetails(long accountno);
    void closeaccount(long acountno);
    Account showallaccounts();
    ~Bank();

};
Account Bank::showdetails(long accountno)
{
    map<long,Account>::iterator itr=accounts.find(accountno);
    return itr->second;
}
Account Bank::showallaccounts()
{
    map<long,Account>::iterator itr;
    for(itr=accounts.begin(); itr!=accounts.end(); itr++)
    {
        return itr->second;
    }
}
Account Bank::transfer(long accountno, long raccountno, double money)
{
    map<long,Account>::iterator itr1=accounts.find(accountno);
    map<long,Account>::iterator itr2=accounts.find(raccountno);
    if(money>itr1->second.getamount())
    {
        cout<<"YOU DO NOT HAVE ENOUGH BALANCE IN YOUR ACCOUNT TRY AGAIN"<<endl;
    }
    else
    {
        itr1->second.cashwithdraw(money);
        itr2->second.cashdeposit(money);
    }
    return itr1->second;
}
Account Bank::checkbalance(long accountno)
{
    map<long,Account>:: iterator itr;
    itr=accounts.find(accountno);
    return itr->second;
}
Bank::Bank()
{
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile)
    {
        //cout<<"ERROR OPENING FILE"<<endl;
    }
    else
    {
        while(!infile.eof())
        {
            infile>>account;
            accounts.insert(pair<long,Account>(account.getaccountno(),account));
        }
        Account::setlastaccountno(account.getaccountno());
        infile.close();
    }
}
Bank::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data",ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=accounts.begin(); itr!=accounts.end(); itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
}
Account Bank:: openaccount(string fname, string lname, double money)
{
    ofstream outfile;
    Account account(fname, lname, money);
    accounts.insert(pair<long,Account>(account.getaccountno(),account));
    outfile.open("Bank.data",ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=accounts.begin(); itr!=accounts.end(); itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
    return account;

}
Account Bank::deposit(long accountno,double money)
{
    map<long,Account>::iterator itr;
    itr=accounts.find(accountno);
    itr->second.cashdeposit(money);
    return itr->second;
}
Account Bank::withdraw(long accountno,double money)
{
    map<long,Account>::iterator itr;
    itr=accounts.find(accountno);
    itr->second.cashwithdraw(money);
    return itr->second;
}
void Bank::closeaccount(long accountno)
{
    if(accounts.erase(accountno))
    {
        cout<<"YOUR ACCOUNT HAS BEEN CLOSED"<<endl;
    }
    else
    {
        cout<<"CHECK YOUR ACCOUNT NUMBER AND TRY AGAIN"<<endl;;
    }

}
int main()
{
    Bank b;
    Account acc;
    string fname;
    string lname;
    double money;
    long accountno;
    int n;
    cout<<"******************************************************BANKING SYSTEM***************************************************"<<endl<<endl<<endl;
    do
    {
        cout<<"**********ENTER YOUR CHOICE**********"<<endl;
        cout<<"PRESS 1 FOR CREATE ACCOUNT"<<endl;
        cout<<"PRESS 2 FOR CHECK BALANCE"<<endl;
        cout<<"PRESS 3 FOR DEPOSIT CASH"<<endl;
        cout<<"PRESS 4 FOR WITHDRAW CASH"<<endl;
        cout<<"PRESS 5 FOR TRANSFER CASH"<<endl;
        cout<<"PRESS 6 FOR CLOSE ACCOUNT"<<endl;
        cout<<"PRESS 7 FOR SHOW ACCOUNT DETAILS"<<endl;
        cout<<"PRESS 8 FOR SHOW ALL ACCOUNTS"<<endl;
        cout<<"PRESS 9 TO CLOSE PROGRAM"<<endl;
        cin>>n;
        try
        {
            switch(n)
            {
            case 1:
                cout<<"ENTER YOUR FIRST NAME"<<endl;
                cin>>fname;
                cout<<"ENTER YOUR LAST NAME"<<endl;
                cin>>lname;
                cout<<"ENTER INITIAL MONEY YOU WANT TO DEPOSIT";
                cin>>money;
                acc=b.openaccount(fname,lname,money);
                cout<<"CONGRATULATIONS YOUR ACCOUNT HAS BEEN CREATED"<<endl;
                cout<<"YOUR ACCOUNT NO IS :-"<<acc.getaccountno()<<endl;
                cout<<"YOUR NAME IS :-"<<acc.getfirstname()<<" "<<acc.getlastname();
                cout<<"YOUR ACCOUNT BALANCE IS :-"<<acc.getamount()<<endl;
                cout<<"*************************THANK YOU*************************"<<endl<<endl;
                break;
            case 2:
                cout<<"ENTER YOUR ACCOUNT NO"<<endl;
                cin>>accountno;
                acc=b.checkbalance(accountno);
                cout<<"YOUR ACCOUNT BALANCE IS:-  "<<acc.getamount()<<endl;
                cout<<"*************************THANK YOU*************************"<<endl<<endl;
                break;
            case 3:
                cout<<"ENTER YOUR ACCOUNT NUMBER"<<endl;
                cin>>accountno;
                cout<<"ENTER MONEY YOU WANT TO DEPOSIT"<<endl;
                cin>>money;
                acc=b.deposit(accountno,money);
                cout<<"YOUR ACCOUNT BALANCE AFTER DEPOSIT IS:-  "<<acc.getamount()<<endl;
                cout<<"*************************THANK YOU*************************"<<endl<<endl;
                break;
            case 4:
                cout<<"ENTER YOUR ACCOUNT NUMBER"<<endl;
                cin>>accountno;
                cout<<"ENTER AMOUNT TO WITHDRAW"<<endl;
                cin>>money;
                acc=b.withdraw(accountno,money);
                cout<<"YOUR ACCOUNT BALANCE AFTER WITHDRAW IS:-  "<<acc.getamount()<<endl;
                cout<<"*************************THANK YOU*************************"<<endl<<endl;
                break;
            case 5:
                long raccountnumber;
                cout<<"ENTER YOUR ACCOUNT NUMBER"<<endl;
                cin>>accountno;
                cout<<"ENTER RECEIPTANT ACCOUNT NUMBER"<<endl;
                cin>>raccountnumber;
                cout<<"ENTER AMOUNT TO TRANSFER"<<endl;
                cin>>money;
                acc=b.transfer(accountno,raccountnumber,money);
                cout<<"YOUR ACCOUNT BALANCE IS:-  "<<acc.getamount()<<endl;
                cout<<"*************************THANK YOU*************************"<<endl<<endl;
                break;
            case 6:
                cout<<"ENTER YOUR ACCOUNT NUMBER"<<endl;
                cin>>accountno;
                b.closeaccount(accountno);
                break;
            case 7:
                cout<<"ENTER YOUR ACCOUNT NO"<<endl;
                cin>>accountno;
                acc=b.showdetails(accountno);
                cout<<"YOUR ACCOUNT DETAILS ARE AS:-"<<endl;
                cout<<acc;
                break;
            case 8:
                acc=b.showallaccounts();
                cout<<acc;
                cout<<"**********************************"<<endl;
                break;
            case 9:
                n=9;
                break;
            default:
                cout<<"ENTER CORRECT CHOICE"<<endl;
                n=0;
                break;
            }
        }
        catch(...)
        {
            cout<<"PLEASE CHECK YOUR DETAILS SOME PROBLEM OCCUR"<<endl;
        }
    }
    while(n<9);
    return 0;
}
