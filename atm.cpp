#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Account{
  string username;
  int pin;
  double balance;
  int withdrawlLimit;
};

// TO-DO : 
// add so it can save more than one account


void loadAccount(Account& account){
  ifstream file("account.txt");
  if(file.is_open()){
    file >> account.username >> account.pin >> account.balance;
    file.close();
  }else{
    cout << "No existing accoutn found || Please Create an account!!\n";
  }
}


//save the accoutn to file
//using ofstream
void saveAccount(const Account& account){
  ofstream file("account.txt");
  if(file.is_open()){
    file << account.username << endl;
    file << account.pin << endl;
    file << account.balance << endl;
    file.close();
  }else{
    cout << "File not saveing account data\n";
  }
}

//login wiht username and pin;
bool login(Account& account) {
  string enteredUsername;
  int enteredPin;

  cout << "Username: ";
  cin >> enteredUsername;
  cout << "PIN: ";
  cin >> enteredPin;

  if(enteredUsername == account.username && enteredPin == account.pin){
    cout << "Login Successfull!\n";
    return true;
  }else {
    cout << "Invalid username or password!\n";
    return false;
  }
}

bool createAccount(Account& account) {
  cout << "Create new account:\n";
  cout << "Enter username: ";
  cin >> account.username;

  cout << "Enter 4-digit pin: ";
  cin >> account.pin;

  account.balance = 0.0;
  //reset withdrawl limit when new session
  account.withdrawlLimit = 3;

  //save teh account 
  saveAccount(account);
  cout << "Account created sucessfuly!\n";
  return true;
}

//once logged in display menu
void displayMenu(Account& account){
  cout << "\nATM Menu:\n";
  cout << "1. Check Balance\n";
  cout << "2. Deposit Money\n";
  cout << "3. Withdraw Money\n";
  cout << "4. Exit\n";
}

void checkBalance(const Account& account){
  cout << "Your current balance is: $" << account.balance << endl;
}

void deposit(Account& account){
  double amount;
  cout << "Enter the amount you want to deposit: €";
  cin >> amount;

  if(amount > 0){
    account.balance += amount;
    cout << "€" << amount << " has been deposited to your account!\n";
  }else{
    cout << "Invalid amount !! , Deposit Failed";
  }
}

void withdraw(Account& account){
  double amount;

  //teh withrawl limit per session is 3
  if(account.withdrawlLimit <=0){
    cout << "Withdrawl limit has been reached for this session";
    return;
  }
  cout << "Enter amount to Withdraw €";
  cin >> amount ;

  if(amount > 0 && amount <= account.balance){
    account.balance -= amount;
    //decrees the limit for session
    account.withdrawlLimit--;
    cout << "€" << amount << " has been withdrawn from your account !!\n";
    cout << "Remaining withdrawals for this session: " << account.withdrawlLimit << endl;
  }else if(amount > account.balance){
    cout << "Not enough funds!!\n";
  }else{
    cout << "invalid amount. Withdrawl failed !!!\n";
  }
}


int main(){
  //3 withdrawls per session
  //so noone can steel your money :)
  Account account = {"", 0, 0.0, 3}; 

  cout << "Welcome to the ATM!\n";
  cout << "1. Log in\n";
  cout << "2. Create a new account\n";
  cout << "Choose an option: ";

  int option;
  cin >> option;
  cin.ignore();

  bool loggedIn = false;
  if (option == 1) {
    loadAccount(account); // Load account data from file
    loggedIn = login(account);
  } else if (option == 2) {
    loggedIn = createAccount(account);
  } else {
    cout << "Invalid option. Exiting...\n";
    return 0;
  }

  if (!loggedIn) {
    cout << "Authentication failed. Exiting...\n";
    return 0;
  }

  int choice;
  do {
    displayMenu(account);
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        checkBalance(account);
        break;
      case 2:
        deposit(account);
        break;
      case 3:
        withdraw(account);
        break;
      case 4:
        saveAccount(account);
        cout << "Thank you for using the ATM. Goodbye!\n";
        break;
      default:
        cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 4);


  return 0;
}


