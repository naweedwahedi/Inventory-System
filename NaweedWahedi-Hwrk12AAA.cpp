
// Farmer's Market Online Sales Software
#include <iostream> 
#include <string> 
#include <fstream> 
using namespace std; 

//Function Prototypes
void create_Empty_Inventory(); 
void edit_Inventory(); 
void display_Inventory(); 
void make_An_Order(); 
void create_Order_Report(); 
void create_Revenue_Report();
void save_Inventory(); 

const int MAX1 = 50; //maximum number of items 
const int MAX2 = 31; //maximum size of the array 

struct product //struct to store information about items
{ 
    char details[31]; 
    double price; 
    int quantityInStock; 
    int numberSold; 
}; 

int main() 
{
    int choice = 0; 
    do 
    //Menu do while
    {
        cout<< "\n\tNaweed Wahedi's Online Sales Software\n\n";
        cout<< "1. Create New Inventory\n";
        cout<< "2. Display Current Inventory\n";
        cout<< "3. Edit Inventory\n";
        cout<< "4. Create an Order\n";
        cout<< "5. Create Reorder Report\n";
        cout<< "6. Create Sales Report\n";
        cout<< "7. Save Current Report\n" ;
        cout<< "8. Quit Program\n\n";
        cout<< "Enter your choice:  " ;
        cin>> choice;
        
        switch(choice)
        {
            case 1: 
                create_Empty_Inventory(); 
                break;
            case 2:
                display_Inventory(); 
                break;
            case 3:
                edit_Inventory(); 
                break;
            case 4: 
                make_An_Order(); 
                break; 
            case 5: 
                create_Order_Report();
                break;
            case 6:
                create_Revenue_Report();
                break;
            case 7:
                save_Inventory();
                break;
            case 8:
            {
                cout << "Thank you ...\n";
                break;
            }
            default:
                cout << "Invalid response. Please try again.\n";
                break;
        } 
 
    } while (choice != 8); 
    cin.ignore();   
    cin.get(); 
    return (0); 
} 
void create_Empty_Inventory() 
{
    char ov = 0;
    product record = { '\0', 0.0, 0, 0};
    //ask user permission
    cout << "Creating a new inventory will erase any previous existing inventory file. Do you still want to continue (Y/N)?  ";
    cin >> ov;
    if (tolower(ov) != 'y' && tolower(ov) != 'n')
    {
        while (tolower(ov) != 'y' && tolower(ov) != 'n')
        {
            cout << "Invalid choice, please try again (Y or N): ";
            cin >> ov;
        }
    }
    if (tolower(ov) == 'n')
        return;
    fstream inventory("Inventory.dat", ios::out | ios::binary);
    for (int count = 0; count < MAX1; count++)
    {
        cout<< "Now creating record " << count + 1 << endl;
        inventory.write(reinterpret_cast<char *>(&record),sizeof(record));
    }
    inventory.close();
    cout <<"\n\n";
}

void edit_Inventory()
{
    product record; 
    long itemNum; 
    char array[MAX2]; 
    char ov = 0; 
    fstream inventory("Inventory.dat", ios::in | ios::out | ios::binary);
    display_Inventory();
    do
    {
    cout<<  "Which record do you want to edit?  "; 
    cin>>itemNum; 

    itemNum--; 
    inventory.seekg(itemNum * sizeof(record), ios::beg); 
    inventory.read(reinterpret_cast<char *>(&record), sizeof(record));
    cout<<endl << "Record's Current Information:\n" ;
    cout<<"Description: " ; 
    cout<<record.details << endl; 
    cout<<"Price "; 
    cout<<fixed<<setprecision(2) << record.price << endl; 
    cout<< "#Instock: ";
    cout<< record.quantityInStock << endl;
    cout<< "#Sold: ";
    cout<< record.numberSold << endl<<endl;
    cout<< "enter new data: \n"; 
    cout<< "Description: " ;  
    cin.ignore(); 

    cin.getline(record.details, MAX2);   
    cout<< "Price: ";  
    cin>>record.price; 
    cout<< "#Instock: ";  
    cin>>record.quantityInStock;  
    cout<< "#Sold: ";  
    cin>>record.numberSold;  
    inventory.seekp(itemNum * sizeof(record), ios::beg);  

    inventory.write(reinterpret_cast<char *>(&record), sizeof(record));  
    cout << "Do you want to edit another entry?  (Y/N) " ;  
    cin >> ov; 
    if (tolower(ov) != 'y' && tolower(ov) != 'n')  
    {

        while (tolower(ov) != 'y' && tolower(ov) != 'n')  
        {
            cout<< "Invalid choice, please try again (Y/N)";  
            cin>> ov; 
        }

    }

    } 
    while (tolower(ov) != 'n'); 
    inventory.close();

    cout <<"\n\n";   
}
void display_Inventory()
{
    product record; 
    int i = 1;  
    fstream inventory("Inventory.dat", ios::in | ios::binary); 
    inventory.read(reinterpret_cast<char *>(&record), sizeof(record)); 
    cout<<setw(6)<<"Item# " ;  
    cout<<setw(20)<<left << "Description "; 
    cout<<setw(10)<<fixed << setprecision(2) << left << "Price"; 
    cout<<setw(12)<<left << "#inStock"; 
    cout<<setw(10)<<left << "#sold" << endl;  
    while (!inventory.eof())
    {
       
        cout<<setw(6)<< i;   

        cout<<setw(20)<<left<<record.details;   

        cout<<setw(10)<<left<<record.price;  

        cout<<setw(12)<<left<<record.quantityInStock;  

        cout<<setw(10)<< record.numberSold <<endl;    

        inventory.read(reinterpret_cast<char *>(&record),sizeof(record));   
        i++; 
    } 
    inventory.close();
    cout << "\n\n";
}

// Studs For Homework12B

void make_An_Order()
{
    product order;
    char again;
    int amount = 0;
    double price = 0.0;
    long itemNum;

    fstream inventory("inventory.dat", ios::in |ios::out| ios::binary);

    cout << "Which Item # do you want to order? ";
    cin >> itemNum;
    cin.ignore();
    do
    {

        itemNum = itemNum - 1;

        inventory.seekg(itemNum* sizeof(order), ios::beg);
        inventory.read(reinterpret_cast<char *>(&order), sizeof(order));

        cout << "Description: " << order.details << endl;
        cout << "Price: " << order.price << endl;
        cout << "Quantity In Stock: " << order.quantityInStock << endl;
        cout << "How many?: ";
        cin >> amount;
        if ((order.quantityInStock - amount)>=0)
        {
            order.numberSold += amount;
            order.quantityInStock -=amount;
            price = order.price * amount;
            cout << "Amount due: "<< fixed << setprecision(2) << price <<endl;
        }
        else
            cout << "Sorry, your order exceeds number in stock!" <<endl;
        inventory.seekp(itemNum* sizeof(order), ios::beg);
        // Write the new record over the current record.
        inventory.write(reinterpret_cast<char *>(&order), sizeof(order));
        cout << "Which Item # do you want to order(-1 to quit)? ";
        cin >> itemNum;
    }while(itemNum != -1);

    // Close the file.
    inventory.close();
}
void create_Order_Report()
{
    product reorder;
    cout << "REORDER REPORT" << endl;
    // Open the file for binary input.
    fstream inventory ("inventory.dat", ios::in | ios::binary);

    // Now read and display the records.
    inventory.read(reinterpret_cast<char *>(&reorder), sizeof(reorder));
    cout << "ITEM# " << right <<setw(12) << "STOCK" <<endl;
    while (!inventory.eof())
    {
        if (reorder.quantityInStock <= 5)
        {
            cout << reorder.details;
            cout << "\t\t" <<fixed << setprecision(2) << reorder.quantityInStock;
        }
        inventory.read(reinterpret_cast<char *>(&reorder),sizeof(reorder));
    }
    cout<<endl;
    // Close the file.
    inventory.close();
}
void create_Revenue_Report()
{
    product revenue;
    int count = 0;
    double revenue$;
    // Open the file for binary input.
    fstream inventory ("inventory.dat", ios::in | ios::binary);

    // Now read and display the records.
    inventory.read(reinterpret_cast<char *>(&revenue), sizeof(revenue));
    cout << "ITEM# " << "DESCRIPTION" << right <<setw(12) << "PRICE";
    cout << right << setw(10) << "#INSTOCK" << right << setw(10) << "#SOLD";
    cout << right << setw(10) << "REVENUE" << endl;
    int recnum = 0;
    while (!inventory.eof())
    {
        cout << ++count <<"     " <<revenue.details;
        if (recnum==5)
            cout << "\t" <<fixed << setprecision(2) <<revenue.price;
        else
            cout << "\t\t" <<fixed << setprecision(2) <<revenue.price;
        cout <<setw(10)<< revenue.quantityInStock;
        cout << right << setw(10) << setfill(' ') << revenue.numberSold;
        revenue$ = revenue.price * revenue.numberSold;
        cout << right << setw(11) << setfill(' ') << fixed << setprecision(2)
            << revenue$ <<endl;
        recnum++;
        inventory.read(reinterpret_cast<char *>(&revenue),sizeof(revenue));
    }
    cout<<endl;
    // Close the file.
    inventory.close();
}
void save_Inventory()
{
    cout << "Inventory saved. " << endl;
}
