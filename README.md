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

CHALLENGES FACED: 
Figuring out how to sort the cars according to their inventory number was definitely a challenge for me - I was initally unsure of how to do it, but ended up pushing all of the inventory vehicles into a vector, sorting the vector, and then rewriting the data in the vector back to the binary file. Furthermore, I was challenged with how to allow the user to delete a vehicle from the inventory... I solved this by using a temporary text file, in which all the vehicle data EXCEPT for the vehicle the user wanted to delete was written to the temp file, and then the temp file was renamed to replace the old binary file.

MOST PROUD OF:
I was pretty proud of this entire project as a whole... I worked extremely hard on it, and I wanted the program to be able to do as much for the user as possible. Being able to search and delete vehicles from the inventory was a feature I worked hard on and thought was very cool.
