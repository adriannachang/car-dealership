//*****************************************************************************************
//  Program Filename   :Auto Dealership Program
//  Version           :2.0
//  Author             :Adrianna Chang
//  Purpose            :Reads and writes database of vehicles to a binary file; user may add, delete, change, or read information
//  Date               :October 2nd, 2015
//  Input from         :Keyboard and binary file
//  Output to           :Monitor and binary file
//*****************************************************************************************
//Preprocessor Directives
#include <iostream>
#include <fstream> 
#include <stdlib.h> 
#include <string.h>
#include <vector>
#include <iomanip>
using namespace std;

//Name Constant Definitions
#define FILE_IN "carInventory.bin.dat" //Reading from and writing to the same file
#define FILE_OUT "carInventory.bin.dat"

//struct vehicle contains all the information about each vehicle
struct vehicle
{
	int inventoryNum;
	char autoVin[18], make[50], model[50], extColour[50], intColour[50], transmission[50];
	float price;
	
};

//*****************************************************************************************
// Function Name: menu
// Purpose: Provides user with options of what they would like to do, returns their choice to main
// Inputs to Function: None
// Outputs from Function: int choice
// External Inputs to Function: cin
// External Outputs from Function: cout
//*****************************************************************************************
int menu()
{
	//Variable Declarations
	int choice;
	
	//Function Body
	//User provided with options and prompted to make a selection
	cout<<endl<<"Would you like to...\n\t1)Enter new vehicle into inventory\n\t2)Display vehicle inventory\n\t3)Change vehicle information\n\t4)Delete vehicle from inventory\n\t5)Search for vehicle\n\t6)Exit Program\n\nSelection: ";
    cin>>choice;
    
   //If selection is invalid, user is notified of error and notified to reenter their choice
    while (choice < 1 || choice > 6)
    {
    	cout<<"Error: Invalid Entry."<<endl<<"Would you like to...\n\t1)Enter new vehicle into inventory\n\t2)Display vehicle inventory\n\t3)Change vehicle information\n\t4)Delete vehicle from inventory\n\t5)Search for vehicle\n\t6)Exit Program\n\nSelection: ";
		cin>>choice;
	}
    
    //choice returned to main
    return choice;
}

//*****************************************************************************************
// Function Name: getInfo
// Purpose: Takes in vehicle information from the user; error detection confirms valid information 
//and ascertains that information is not already in database; sorts vehicles based on inventory number
// Inputs to Function: None
// Outputs from Function: none
// External Inputs to Function: cin, getline, reads information from binary file (input.read)
// External Outputs from Function: cout, writes information to binary file (output.write)
//*****************************************************************************************

void getInfo()
{
	//Variable Declarations
	vehicle newVehicle, tempVehicle;
	//Vector of structs declared
	vector<vehicle> vehiclesEntered;
	
	//Objects of classes ifstream and ofstream declared, allowing file input and output respectively
	ifstream input;
	ofstream output;
	
	//Function Body			
	cout<<endl<<"**NEW VEHICLE INFORMATION**"<<endl;
	
	//Prompts user to enter vehicle inventory number 
	cout<<endl<<"Enter vehicle inventory number: ";
	cin>>newVehicle.inventoryNum;
	
	//If invalid entry is made, user notified of error and prompted to reenter value
	while (newVehicle.inventoryNum < 1000 || newVehicle.inventoryNum > 9999)
	{
		cout<<"Error: Invalid Entry."<<endl<<"Inventory number must be a four digit integer."<<endl<<endl<<"Enter vehicle inventory number: ";
		cin>>newVehicle.inventoryNum;
	}
	
    //Opens file for input; state flags ascertain that file is only being opened for reading and that the file is opened in binary mode
	input.open(FILE_IN, ios::in| ios::binary);  
    
	//Reads data from file, storing it in temp structure tempVehicle
    while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {
		//If inventory number written to file matches the current inventory number being entered, user is notified that the 
		//inventory number is already in the database; they are prompted to reenter inventory number
		if (tempVehicle.inventoryNum == newVehicle.inventoryNum)
		{
			cout<<"Error: Inventory number already in database."<<endl<<endl<<"Enter vehicle inventory number: ";
			cin>>newVehicle.inventoryNum;
		}
	}
	//Closes link to file
	input.close();
	
	//User prompted to enter auto VIN
	cout<<"Enter 17 digit auto VIN (vehicle identification number): ";
	//cin.ignore allows use of a getline after a cin statement
	cin.ignore(100, '\n');
	//Sets the size of the char array to be taken in to 18 (meaning that 17 characters + end character will be accepted)
	//and the newline character as a delimeter
	cin.getline(newVehicle.autoVin, 18,'\n');
	
	//Opens file for input again
	input.open(FILE_IN, ios::in| ios::binary);  
	
	//While data can still be read from the file into tempVehicle...
    while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {
		//If auto VIN written to file matches the current auto VIN being entered, user is notified that the 
		//auto VIN is already in the database; they are prompted to reenter auto VIN
		//NOTE: strcmp had to be used (function that compares 2 strings) because working directly with the char arrays
		//was causing problems
		if(strcmp(tempVehicle.autoVin,newVehicle.autoVin) == 0 )
		{
			cout<<"Error: Auto VIN already in database."<<endl<<endl<<"Enter 17 digit auto VIN (vehicle identification number): ";
			cin.getline(newVehicle.autoVin, 18,'\n');
			break;
		}
	}
	//Closes file for input
	input.close();
	
	//User prompted to enter rest on information about vehicle
	cout<<"Enter vehicle make: ";
	cin.getline(newVehicle.make, 50, '\n');
	cout<<"Enter vehicle model: ";
	cin.getline(newVehicle.model, 50, '\n');
	cout<<"Enter interior colour: ";
	cin>>newVehicle.intColour;
	cout<<"Enter exterior colour: ";
	cin>>newVehicle.extColour;	
	cout<<"Enter transmission type: ";
	cin>>newVehicle.transmission;
	cout<<"Enter retail price: $";
	cin>>newVehicle.price;
	
	//Opens file for output; state flags ascertain that file is only being opened for reading, that the file is opened
	//in binary mode, and that all information is being appended to the end of the file
    output.open(FILE_OUT, ios::out| ios::binary|ios::app);  
    
    //Writes struct newVehicle to the binary file
    output.write((char*) &newVehicle, sizeof(vehicle));
    //Closes file for output
	output.close();
    
    //Opens file for input
	input.open(FILE_IN, ios::in| ios::binary);  
    
    //While data can still be read from file into tempVehicle...
	while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {
		//Pushes tempVehicle into the vector <vehiclesEntered>
		vehiclesEntered.push_back(tempVehicle);
	}
	//Closes file for input
	input.close();
    
   //Sorts vehicles in the vector according to inventory number using insertion sort
   //For loop starts the counter off at 1, increasing by 1 every loop, stopping once it reaches the size of the vector
    for (int i=1; i<vehiclesEntered.size(); i++)	
	{
		//Int j set to value of int i
		int j= i;
		//While int j is greater than 0 and the inventory number of the item located at position j in the vector is less than 
		//the inventory number of the item located before it in the vector (item j-1)
		while (j> 0 && vehiclesEntered[j-1].inventoryNum > vehiclesEntered[j].inventoryNum)
		{
			//Temp variable of type vehicle (struct) is set to the item located at position j in the vector
			vehicle temp = vehiclesEntered[j];
			//Item at position j is now given value of item before it (item j-1 in vector)
			vehiclesEntered[j] = vehiclesEntered[j-1];
			//Item at position j-1 now takes on value of temp
			///Ultimately what happens here is that the values of the items at j and j-1 in the vector are switched
			vehiclesEntered[j-1] = temp;
			//J decremented by 1
			j--;
		}
	}
	//Opens file for output; state flags ascertain that file is opened for output only, that it's opened in binary mode, and that the contents will be truncated 
	//(essentially all the previous content of the file will be removed before file is written to)
	output.open(FILE_OUT, ios::out| ios::binary|ios::trunc);
	
	//For loop runs the number of times as there are items in the vector
	for(int i=0; i<vehiclesEntered.size();i++)
	{
		//Writes the elements in the vector to the file
		output.write((char*) &vehiclesEntered[i], sizeof(vehicle));
	}

	//Closes file for output
	output.close();
	//Notifies user that vehicle has been successfully entered to the inventory
	cout<<endl<<"**VEHICLE HAS BEEN ENTERED INTO INVENTORY**"<<endl<<endl;

}


//*****************************************************************************************
// Function Name: readInfo
// Purpose: Reads entire vehicle inventory from the binary file, printing it to the console
// Inputs to Function: None
// Outputs from Function: none
// External Inputs to Function: Reads information from binary file(input.read)
// External Outputs from Function: cout
//*****************************************************************************************

void readInfo()
{
	//Variable Declarations
	vehicle tempVehicle;
		
	//Function Body
	//Sets up stream for input
	ifstream input;
	//Opens file for input; state flags ascertain that file can only be read from, and opens it in binary mode
	input.open(FILE_IN, ios::in|ios::binary);
			
	//If there is an error opening the external file that the input stream is linked to, user is notified of error
	// and function exit is called, terminating the program
	if(!input)
	{
		cout<<"\nCannot locate input file.";
		cout<<"\nExiting the program.";
		exit(1);
	}
			
	cout<<setiosflags(ios::fixed);
	cout<<setprecision(2);
	
	cout<<endl<<"**CAR INVENTORY DISPLAY**"<<endl<<endl;
	//While data can still be read from the file into struct tempVehicle...
	while (input.read((char*) &tempVehicle, sizeof(vehicle)))
	{			
		//Outputs all vehicle information to the console
		cout<<"Vehicle Inventory Number: "<<tempVehicle.inventoryNum<<endl;
		cout<<"Auto VIN (vehicle identification number): "<<tempVehicle.autoVin<<endl;
		cout<<"Vehicle make: "<<tempVehicle.make<<endl;
		cout<<"Vehicle model: "<<tempVehicle.model<<endl;
		cout<<"Interior colour: "<<tempVehicle.intColour<<endl;
		cout<<"Exterior colour: "<<tempVehicle.extColour<<endl;	
		cout<<"Transmission type: "<<tempVehicle.transmission<<endl;
		cout<<"Retail price: $"<<tempVehicle.price<<endl<<endl;		
	}
			    
	//Closes file for input
	input.close();
}

//*****************************************************************************************
// Function Name: changeInfo
// Purpose: Allows user to change information of a vehicle
// Inputs to Function: None
// Outputs from Function: none
// External Inputs to Function: cin, reads information from binary file(input.read)
// External Outputs from Function: cout, writes information to binary file (temp.write)
//*****************************************************************************************

void changeInfo()
{
	//Variable Declarations
	int changeNum;
	vehicle tempVehicle, newVehicle;
	bool found=false;
	
	//Sets up stream for input
	ifstream input;
	//Opens input file
    input.open(FILE_IN, ios::in|ios::binary);
    
	//Sets up stream for output
   	ofstream temp;
   	//Creates text file called "temp.txt" and opens it for output
    temp.open("temp.txt", ios::out| ios::binary);
    
    //Prompts user to enter inventory num of car whose info they'd like to change
    cout<<endl<<"Enter inventory number of car whose information you would like to change: ";
    cin>>changeNum;
    
    //While data can be read from the file into tempVehicle...
    while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {
       //If the inventory number of the vehicle currently occupying tempVehicle variable DOES NOT match the inventory
       //number the user entered, tempVehicle is written to the "temp.txt" file
	    if (tempVehicle.inventoryNum != changeNum)
        {
			temp.write((char*) &tempVehicle, sizeof(vehicle));
        }
		
		//Otherwise (meaning the inventory number of the vehicle currently occupying tempVehicle DOES match the ivnentory
		//number the user entered), user is prompted to enter new information for vehicle
		//Information is taken into variable newVehicle	
		else
        {
			cout<<endl<<"**NEW INFORMATION FOR VEHICLE WITH INVENTORY NUMBER "<<changeNum<<"**"<<endl<<endl;
			newVehicle.inventoryNum = changeNum;
			cout<<"Enter 17 digit auto VIN (vehicle identification number): ";
			cin.ignore(100, '\n');
			cin.getline(newVehicle.autoVin, 18,'\n');
			cout<<"Enter vehicle make: ";
			cin.getline(newVehicle.make, 50, '\n');
			cout<<"Enter vehicle model: ";
			cin.getline(newVehicle.model, 50, '\n');
			cout<<"Enter interior colour: ";
			cin>>newVehicle.intColour;
			cout<<"Enter exterior colour: ";
			cin>>newVehicle.extColour;
			cout<<"Enter transmission type: ";
			cin>>newVehicle.transmission;
			cout<<"Enter retail price: $";
			cin>>newVehicle.price;
			
			//newVehicle is then written to the temporary file
			temp.write((char*) &newVehicle, sizeof(vehicle));
			//Boolean found is set to true
			found = true;
        }
    }
    //Closes the output and the input files
    temp.close();
    input.close();
    //Removes the old file that the vehicle inventory was stored in
    remove(FILE_IN);
    //Renames the temporary file to the name of the old file
    rename("temp.txt", FILE_IN);
    //If boolean was not set to true, user is notfied that the inventory number was not found in the database
    if (found == false)
    {
    	cout<<"Error: Inventory number not found in database."<<endl;
	}

	//Otherwise, ther user is notified that the information was successfully updated
	else
	{
		cout<<endl<<"**INFORMATION SUCCESSFULLY UDPATED**"<<endl;
	}	
	
}

//*****************************************************************************************
// Function Name: deleteInfo
// Purpose: Allows user to delete a vehicle from the inventory
// Inputs to Function: None
// Outputs from Function: none
// External Inputs to Function: cin, reads information from binary file(input.read)
// External Outputs from Function: cout, writes information to binary file (temp.write)
//*****************************************************************************************
void deleteInfo()

{
	//Variable Declarations
	int deleteNum;
	vehicle tempVehicle;
	bool found=false;
	
	//Sets up stream for input
	ifstream input;
	//Opens input file
    input.open(FILE_IN, ios::in|ios::binary);

	//Sets up stream for output
   	ofstream temp;
   	//Creates text file called "temp.txt" and opens it for output
    temp.open("temp.txt", ios::out| ios::binary);
    
    //Prompts user to enter inventory num of car they'd like to delete from inventory
    cout<<endl<<"Enter inventory number of car you would like to remove: ";
    cin>>deleteNum;
    
    //While data can be read from file into tempVehicle...
    while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {
        //If the inventory number of the vehicle currently occupying tempVehicle variable DOES NOT match the inventory
       //number the user entered, tempVehicle is written to the "temp.txt" file
       //This means that if the inventory num of the vehicle currently occupying tempVehicle DOES match the inventory
       //number the user entered, this vehicle will NOT be written to the "temp.txt" file
		if (tempVehicle.inventoryNum != deleteNum)
        {
			temp.write((char*) &tempVehicle, sizeof(vehicle));
        }
        
        //Sets the found boolean to true once match is found
        else
        {
        	found = true;
		}
    }
    //Closes the output and the input files
    temp.close();
    input.close();
    //Removes the old file that the vehicle inventory was stored in
    remove(FILE_IN);
    //Renames the temporary file to the name of the old file
    rename("temp.txt", FILE_IN);
    //If boolean was not set to true, user is notfied that the inventory number was not found in the database
   
    if (found == false)
    {
    	cout<<"Error: Inventory number not found in database."<<endl;
	}
    
    //Otherwise, user is notified that the vehicle was successfully deleted
	else
    {
    	cout<<endl<<"**VEHICLE REMOVED FROM DATABASE**"<<endl;
	}

}

//*****************************************************************************************
// Function Name: searchInventoryNum
// Purpose: Allows user to search for a vehicle by inventory number
// Inputs to Function: None
// Outputs from Function: none
// External Inputs to Function: cin, reads information from binary file(input.read)
// External Outputs from Function: cout
//*****************************************************************************************
void searchInventoryNum()
{
	//Variable Declarations
	int searchNum;
	vehicle tempVehicle;
	bool found=false;

	//Sets up stream for input
	ifstream input;
	//Opens file for input
    input.open(FILE_IN, ios::in|ios::binary);
    
    //Prompts user to enter inventory number of car they'd like to search
    cout<<endl<<"Enter inventory number of car you would like to search: ";
    cin>>searchNum;
    
    //While data can be read from the file into tempVehicle...
    while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {
       //If the inventory number of the vehicle currently occupying tempVehicle variable DOES match the inventory
       //number the user entered, user is notified that result was found
       //tempVehicle is then output to the console
		if (tempVehicle.inventoryNum == searchNum)
        {
			cout<<endl<<"**RESULT FOUND**"<<endl<<endl;
			cout<<"Vehicle Inventory Number: "<<tempVehicle.inventoryNum<<endl;
			cout<<"Auto VIN (vehicle identification number): "<<tempVehicle.autoVin<<endl;
			cout<<"Vehicle make: "<<tempVehicle.make<<endl;
			cout<<"Vehicle model: "<<tempVehicle.model<<endl;
			cout<<"Interior colour: "<<tempVehicle.intColour<<endl;
			cout<<"Exterior colour: "<<tempVehicle.extColour<<endl;	
			cout<<"Transmission type: "<<tempVehicle.transmission<<endl;
			cout<<"Retail price: $"<<tempVehicle.price<<endl<<endl;	
		    //Boolean found is set to true
			found = true;
       		//Break command exits the loop so that the while loop stops running once a match has been found
			break;
        }
    }
    //Closes file for input
    input.close();

	//If found is false, user is notified that the inventory number was not found in the database
    if (found == false)
    {
    	cout<<"Error: Inventory number not found in database."<<endl;
	}
}

void searchAutoVin()
{
	//Variable Declarations
	char searchNum[18];
	vehicle tempVehicle;
	bool found=false;

	//Sets up stream for input
	ifstream input;
	//Opens file for input
    input.open(FILE_IN, ios::in|ios::binary);
    
	//Prompts user to enter auto VIN of car they'd like to search
    cout<<endl<<"Enter auto VIN of car you would like to search: ";
    cin.ignore(100, '\n');
	cin.getline(searchNum, 18,'\n');
	
	//While data can be read from the file into tempVehicle...
    while (input.read((char*) &tempVehicle, sizeof(vehicle)))
    {     
		//If auto VIN of the vehicle currently occupying tempVehicle matches the auto VIN entered by the user, 
		//user is notified that a result was found
		//NOTE: Once again, strcmp had to be used (function that compares 2 strings) because working directly with the char arrays
		//was causing problems
		if( strcmp(searchNum,tempVehicle.autoVin) == 0 )
        {
			//All information about tempVehicle output to the screen
			cout<<endl<<"**RESULT FOUND**"<<endl<<endl;
			cout<<"Vehicle Inventory Number: "<<tempVehicle.inventoryNum<<endl;
			cout<<"Auto VIN (vehicle identification number): "<<tempVehicle.autoVin<<endl;
			cout<<"Vehicle make: "<<tempVehicle.make<<endl;
			cout<<"Vehicle model: "<<tempVehicle.model<<endl;
			cout<<"Interior colour: "<<tempVehicle.intColour<<endl;
			cout<<"Exterior colour: "<<tempVehicle.extColour<<endl;	
			cout<<"Transmission type: "<<tempVehicle.transmission<<endl;
			cout<<"Retail price: $"<<tempVehicle.price<<endl<<endl;	
			//Boolean found is set to true
			found = true;
       		//Break command exits the loop so that the while loop stops running once a match has been found		
			break;
        }
    }
    input.close();
    //Closes file for input

	//If found is false, user is notified that the inventory number was not found in the database
    if (found == false)
    {
    	cout<<"Error: Auto VIN not found in database."<<endl;
	}

}

int main()
{
     //Variable Declarations:
     int choice, selection;

    //Function Body
    //Welcomes user to the program
    cout<<"Welcome to the Dealership Car Inventory Program!"<<endl;
    //Calls function menu; variable choice is set to returned value from function 
	choice=menu();
	
	//While choice is not 6 (choice 6 being to exit the program)
	while (choice != 6)
	{		
		//If choice is 1, calls function getInfo to take in vehicle info from user and write it to a binary file
		if (choice == 1)
    	{
			getInfo();
		}
		
		//If choice is 2, calls function readInfo to read vehicle info from binary file
		else if (choice == 2)
		
		{
			readInfo();
		}
		
		//If choice is 3, calls function changeInfo to allow user to change vehicle information
		else if (choice == 3)
		{
			changeInfo();
		}
		
		//If choice is 4, calls function deleteInfo to allow user to delete a vehicle from the inventory
		else if (choice == 4)
		{
			deleteInfo();
		}
		
		//If choice is 5
		else if (choice == 5)
		{
			//Prompts user to select whether they'd like to search for a vehicle by inventory num or by VIN
			cout<<endl<<"Would you like to.....\n\t1)Search for vehicle by inventory number\n\t2)Search for vehicle by auto VIN\n\nSelection: ";
			cin>>selection;
			
			//If invalid entry made, user is notified of error and prompted to reenter selection
			while (selection != 1 && selection != 2)
			{
				cout<<"Error: Invalid Entry."<<endl<<"Would you like to.....\n\t1)Search for vehicle by inventory number\n\t2)Search for vehicle by auto VIN\n\nSelection: ";
				cin>>selection;
			}
			
			//If selection is 1, calls on function searchInventoryNum 
			if (selection == 1)
			{
				searchInventoryNum();
			}
			
			//Otherwise, calls on function searchAutoVin
			else
			{
				searchAutoVin();
			}
		}
		//Calls on function menu, allowing user to select what they'd like to do next
		choice=menu();  
	}
		
		//Says goodbye to the user
		cout<<endl<<"Thanks for using the program! Goodbye. "<<endl<<endl;
	

      system("PAUSE");
      return 0;
}
//end function main

