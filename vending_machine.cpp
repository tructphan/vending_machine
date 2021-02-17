/* Name: Truc Phan
 * Description: Lab 4 - Vending Machine (cont.)
 * Date: 03/16/2020
 */

#include <iostream>
#include <string>

using namespace std;

//structure holding information of a drink
struct combination{
    int val[3] = {0,0,0}; //C truth values
    int bin[8]; //P truth values
    char letter;
    char number;
    string name;
    double price;
    int amount;
};

//function prototypes
void technicianMode(combination []);
double printMenu(combination []);
double calcPrice(combination p[], int, int, int);
double returnMoney(double);
void calcBin(char, int[]);

int main()
{
    double price, change; //drink's price and money to be returned (if any)
    bool check=true; //condition for menu
    char choice; //hold users' option
    //array holding list of drinks and their information, maximum 8 drinks
    combination p[8]; 
    //set everything in the array to 0 or null
    for (int i=0; i<8; i++) {
        p[i].letter='\0';
        p[i].number='\0';
        p[i].name="";
        p[i].price=0;
        p[i].amount=0;
    }
    
    //looping menu
    while(check) {
        cout << "To enter technician mode, press '0'\n" <<
                "To order, press any key\n" <<
                "To quit, press '#'\n";
            
        cin >> choice;
        if (choice=='0') {technicianMode(p);} //enter techinician mode
        if (choice=='#') {check=false;} //program quits
        else { //enter selling mode
            price = printMenu(p); //calculate drink's price
            
            //check if actual drink's price is returned, not when user enters wrong 
            //combination or drink has sold out
            if (price!=-1) { 
                change = returnMoney(price); //calculate change (if any)
                cout << "Amount of change to be returned: $" << change << endl <<
                        "Enjoy your drink!\n\n";
            }
            check=true; //return to print menu
        }   
    }
    
    return 0;
}

/* This function allows techinician to add drinks, remove drinks,
 * or change drinks' price. The function also checks for invalid
 * input 
 */
void technicianMode(combination p[8])
{
    string pin; //hold technician's password
    int choice; //hold technician's choice
    char a; //check if technician wants to continue
    bool check=true; //condition for printing menu
    bool truthTable[8][3] = {
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1},
    }; //the truth table presented by the array
     
    cout << "Technician Mode. Please enter pin:\n";
    cin >> pin;
    //assume that technician types in wrong pin
    while (pin!="0000#") { //password is 0000#, only technician knows
        cout << "Wrong pin. Please enter again:\n";
        getline(cin, pin);
    }
    
    //looping menu
    while(check) {
        //print out menu for technician to review
        cout << "Review menu:\n";
        //check if there is no drink in the menu
        if (p[0].letter=='\0')
            cout << "Menu is empty.\n";
            
        for (int j=0; j<8; j++) {
            if (p[j].letter!='\0') {
                cout << j << ". (" << p[j].letter << "," << p[j].number << 
                "): " << p[j].name << ". Price: $" << p[j].price << endl;
            }
        }
        
        cout << "\n1) Add new beverage\n" <<
                "2) Remove beverage\n" <<
                "3) Update beverage price\n" <<
                "4) Exit\n\n";
        cin >> choice;
    
        //test for wrong input
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Wrong input. Please enter again:\n";
            cin >> choice;
        }
        
        //adding new drinks option
        if (choice==1) {
            for (int i=0; i<8; i++) {
                //assigning truth values for each added drink
                for (int b=0; b<3; b++) {
                    p[i].val[b] = truthTable[i][b];
                }
                cout << "Combination for new drink: Enter letter (A-D)\n";
                cin >> p[i].letter;
                //test for invalid input (letters that are not A-D)
                while (p[i].letter!='A' && p[i].letter!='B' && p[i].letter!='C' && p[i].letter!='D') {
                    cout << "Wrong input. Please enter again (A-D):\n";
                    cin >> p[i].letter;
                }
                cout << "Input signals to the computer:\n";
                calcBin(p[i].letter, p[i].bin);
            
                cout << "Enter number (1-10)\n";
                cin >> p[i].number;
                //tets for invalid input (letters, symbols or numbers that are not 0-10)
                while (p[i].number!='0' && p[i].number!='1' && p[i].number!='2' && p[i].number!='3' && 
                p[i].number!='4' && p[i].number!='5' && p[i].number!='6' && p[i].number!='7' && 
                p[i].number!='8' && p[i].number!='9') {
                    cout << "Wrong input. Please enter again (1-10):\n";
                    cin >> p[i].number;
                }
                cout << "Input signals to the computer:\n";
                calcBin(p[i].number, p[i].bin);
            
                cout << "Enter drink's name:\n";
                cin >> p[i].name;
            
                cout << "Enter drink's price:\n";
                cin >> p[i].price;
                while (cin.fail() || p[i].price<=0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Wrong input. Please enter again:\n";
                    cin >> p[i].price;
                }
            
                cout << "Enter available amount of this drink:\n";
                cin >> p[i].amount;
                //test for invalid input (amount>0 only)
                while (cin.fail() || p[i].amount<=0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Wrong input. Please enter again:\n";
                    cin >> p[i].amount;
                }
            
                cout << "Press '#' to quit adding new drink. Press any key to continue.\n";
                cin >> a;
                if (a=='#') {break;} //stop adding new drinks
            }
        
        } //end choice 1
        
        //removing drinks option
        if (choice==2) {
            int rem;
            //print list of drinks
            cout << "Display menu. Enter option of the drink you want to remove:\n";
            for (int i=0; i<8; i++) {
                if (p[i].letter!='\0') {
                    cout << i << ". (" << p[i].letter << "," << p[i].number << "): " <<
                    p[i].name << endl;
                }
            }
            
            cin >> rem;
            //test for invalid input
            while (cin.fail() || rem<0 || rem>7) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Wrong input. Please enter again:\n";
                cin >> rem;
            }
            
            cout << "Updated menu:\n";
            //setting all the info of the chosen option to 0 or null (deleting)
            for (int j=0; j<8; j++) {
                if (rem==j) {
                    p[j].letter='\0';
                    p[j].number='\0';
                    p[j].name="";
                    p[j].price=0;
                    p[j].amount=0;
                }
            }
        } //end choice 2
        
        //changing drinks' price option
        if (choice==3) {
            int upd;
            //print list of drinks
            cout << "Display menu. Enter option of the drink you want to update price\n";
            for (int i=0; i<8; i++) {
                if (p[i].letter!='\0') {
                    cout << i << ". (" << p[i].letter << "," << p[i].number << "): " <<
                    p[i].name << ". Price is $" << p[i].price << endl;
                }
            }
            
            cin >> upd;
            //test for invalid input 
            while (cin.fail() || upd<0 || upd>7) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Wrong input. Please enter again:\n";
                cin >> upd;
            }
        
            //replacing the price by looping through the array and re-input
            //the chosen drink's price
            for (int j=0; j<8; j++) {
                if (upd==j) {
                    cout << "Enter drink's price:\n";
                    cin >> p[j].price; //replace price
                    //test for invalid input (price>0 only)
                    while (cin.fail() || p[j].price<=0) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Wrong input. Please enter again:\n";
                        cin >> p[j].price;
                    }
                }
            }
        } //end choice 3
        
        //quitting option
        if (choice==4) {
            check=false;
        }
    
    } //end while loop for printing menu
}

/* This fucntion prints the menu of beverages along with their prices,
 * then allows users to input the combination for each drink. Then 
 * it records the truth values of chosen drink to calculate the price
 */
double printMenu(combination p[8]) 
{
    //list of drinks and their prices
    cout << "Favorite beverages:\n";
    for (int i=0; i<8; i++) {
        if (p[i].letter!='\0') {
            cout << "(" << p[i].letter << "," << p[i].number << "): " <<
            p[i].name << ". Price is $" << p[i].price << endl;
        }
    }
            
    char choice1; //for letter input
    char choice2; //for digit input
    int c1,c2,c3; //truth values
    
    cout << "Enter combination:\n";
    cin >> choice1 >> choice2;
    //test for invalid input
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Wrong input. Please enter again:\n";
        cin >> choice1 >> choice2;
    }
    for (int j=0; j<8; j++) {
        if (choice1==p[j].letter && choice2==p[j].number) {
            //assign c1, c2, c3 to the drink's truth values
            c1=p[j].val[0];
            c2=p[j].val[1];
            c3=p[j].val[2];
            cout << "Input signals to the computer:\n";
            calcBin(choice1, p[j].bin);
            calcBin(choice2, p[j].bin);
            cout << endl;
        }
    }
    calcPrice(p,c1,c2,c3); //call function to calculate drink's price
}

/* This funtion selects out the chosen drink by checking
 * their truth values, and return the drink's price. The 
 * function also checks for invalid input and sold out drinks
 */
double calcPrice(combination p[8], int a, int b, int c)
{
    for (int i=0; i<8; i++) {
        if (p[i].val[0]==a && p[i].val[1]==b && p[i].val[2]==c) {
            if (p[i].amount>0) { //check if the drink is still available
                cout << "Output to LED screen:\n";
                cout << p[i].name << " $" << p[i].price << endl << endl;
                
                cout << "Input signals to the computer:\n";
                for (int b=0; b<p[i].name.size(); b++) {
                    calcBin(p[i].name[b], p[i].bin);
                }
                calcBin(' ', p[i].bin);
                calcBin('$', p[i].bin);
                
                //convert price to a string to change into binary signals
                string price = to_string(p[i].price); 
                for (int b=0; b<price.size(); b++) {
                    calcBin(price[b], p[i].bin);
                }
                
                p[i].amount--; //decrement amount of drink in the machine
                return p[i].price;
            }
            else { //if the drink is sold out
                cout << "The drink you choose has sold out.\n\n";
                return -1;
            }
        }
    }
    //assume that users input wrong combination
    cout << "Wrong combination.\n\n";
    return -1;
}

/* This fucntion asks users to input the amount of money into 
 * the machine. It either informs users do not input enough,
 * or calculates the change to return to users
 */
double returnMoney(double price) 
{
    double inputMoney, change;
    double total=0; //store total money put in the machine
    
    cout << "Input the amount of money:\n";
    cin >> inputMoney;
    //test for invalid input 
    while (cin.fail() || inputMoney<=0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Wrong input. Please enter again:\n";
        cin >> inputMoney;
    }
    total = inputMoney; //set total to input money
    
    //if input money is smaller than drink's price
    while (total<price) {
        cout << "$" << inputMoney << " received. $" << price-total << " left.\n";
        cin >> inputMoney;
        //tets for invalid input
        while (cin.fail() || inputMoney<=0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Wrong input. Please enter again:\n";
            cin >> inputMoney;
        }
        total += inputMoney; //add up input money to total
    }
    change = total-price; //calculate change to return to users
    return change;
} 

/*
 * This function calculates the binary value of a character
 */
void calcBin(char a, int s[])
{
    for(int i=7;i>=0;i--) {     
       s[i]=a%2;     
       a=a/2;  
    }
    
    for(int i=0;i<8;i++) {
       cout << s[i];
    }
    cout << endl;
}







