# car-dealership
This was my first assignment for ICS4U (my grade 12 computer science class). It was coded in dev C++

This is a program for an auto dealership. It keeps track of an auto inventory using structures and writes them to a binary file called carInventory.bin. 

The program has several cars already stored in its database; upon initializing the program, the user may choose what they would like to do from a selection menu. They can enter a car into the database, display all the cars in the database (data read from the carInventory.bin file), search for a specific car, change information pertaining to a specific car, or delete a car from the database.

When a new car is pushed into the database, the program will automatically sort it according to the inventory #.

Accepted values:
Inventory # must be a 4-digit integer
Auto VIN must be a char array of 17 digits - either letters or numbers
The make, model, colours, and transmission of the car must be char arrays
The price of the car must be a float
