//
//  main.cpp
//  Running Times
//
//  Created by Angelo Pablo on 11/7/19.
//  Copyright © 2019 Angelo Pablo. All rights reserved.
//

#include <iostream>
using namespace std;

/*
 Add Time -
 */
void addTime()
{
    
}
/*
 Delete Time -
 */
void deleteTime()
{
    
}
/*
 Add Event -
 */
void addEvent()
{
    
}
/*
 Delete Event -
 */
void deleteEvent()
{
    
}
/*
 Display -
 */
void display()
{
    
}

int main() {
    //variables
    bool isOn = true; //this will determine if the task will be looped
    int option;
    //intro paragraph
    cout << "Welcome to the Running Times Application!" << endl
    << "What would you like to do?" << endl << endl;
    
    //Use a while loop to make a continuous main screen
    while (isOn)
    {
        //ask user what they want to do
        cout << "1. Add a Time" << endl
        << "2. Delete a Time" << endl
        << "3. Add an Event" << endl
        << "4. Delete an Event" << endl
        << "5. Display Times" << endl
        << "6. Exit" << endl;
        cin >> option;
        //options
        //user please dont put 6 or higher
        if (option < 7)
        {
            switch (option) {
                case 1:
                    addTime();
                    break;
                case 2:
                    deleteTime();
                    break;
                case 3:
                    addEvent();
                    break;
                case 4:
                    deleteEvent();
                    break;
                case 5:
                    display();
                    break;
                case 6:
                    isOn = false;
                    break;
            }
        }
        else
        {
            cout << "The option that you chose was invalid" << endl;
        }
    }
    
    return 0;
}
