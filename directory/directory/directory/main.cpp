//
//  main.cpp
//  directory
//
//  Created by Angelo Pablo on 10/15/19.
//  Copyright © 2019 Angelo Pablo. All rights reserved.
//
/*
 This project will keep a record of all the members in the 111th YSA ward that I know and
 will hold information that I know about them
 */

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "person.h"
using namespace std;

/*
 Load Function - This function will load the information at the very beginning and store into
 the container
 */
bool load(vector<Person*> &people)
{
    ifstream file;
    file.open("/Users/angelopablo/Desktop/projects/directory/directory/directory/list.txt");
    string test;
    int i = 0;
    int count;
    Person *person = new Person();
    if (file.is_open())
    {
        while(getline(file, test))
        {
            count = i % 4;
            switch (count) {
                case 0:
                    person->setApt(test);
                    break;
                case 1:
                    person->setFName(test);
                    break;
                case 2:
                    person->setLName(test);
                    break;
                case 3:
                    person->setInfo(test);
                    people.push_back(person);
                    person = new Person;
                    break;
            }
            test = "";
            i++;
        }
        file.close();
        return true;
    }
    else
    {
        cout << "error reading file\n";
        return false;
    }
}

/*
 Save Function
 */
void save(vector<Person*> people)
{
    ofstream file;
    file.open("/Users/angelopablo/Desktop/projects/directory/directory/directory/list.txt");
    int i = 0;
    while (i < people.size())
    {
        file << people[i]->getApt() << endl
        << people[i]->getFName() << endl
        << people[i]->getLName() << endl
        << people[i]->getInfo() << endl;
        i++;
    }
    file.close();
}

/*
 Search Function - this function will prompt the user for a name and it will bring up
 information on them
 */
vector<Person*> search(string fname, string lname, vector<Person*> people)
{
    //list of people with similar names as the one searched
    vector<Person*> searched;
    //convert the first and last name that is searched to lower case to make
    //searching more accurate
    string first = "";
    string last = "";
    string searchFirst;
    string searchLast;

    for (int i = 0; i < fname.length(); i++)
    {
        first += tolower(fname[i]);
    }
    for (int i = 0; i < lname.length(); i++)
    {
        last += tolower(lname[i]);
    }
    int i = 0;
    //search for all possible people with the same name
    do
    {
        searchFirst = "";
        searchLast = "";
        //convert first and last name to lower case to make search more accurate
        for (int j = 0; j < people[i]->getFName().size(); j++)
        {
            searchFirst += tolower(people[i]->getFName()[j]);
        }
        for (int j = 0; j < people[i]->getLName().size(); j++)
        {
            searchLast += tolower(people[i]->getLName()[j]);
        }
        //if first name is blank search for all with same last name
        if (fname == "")
        {
            //if the search is the same then push it over to the new vector
            if (last == searchLast)
            {
                people[i]->num = i;
                searched.push_back(people[i]);
            }
        }
        
        //if last name is blank search for all with same first name
        else if (lname == "")
        {
            //if the search is the same then push it over to the new vector
            if (first == searchFirst)
            {
                people[i]->num = i;
                searched.push_back(people[i]);
            }
        }
        
        //if both are searched search for all with both names
        else
        {
            if (first == searchFirst && last == searchLast)
                {
                    people[i]->num = i;
                    searched.push_back(people[i]);
                }
        }
        i++;
    }
    while(i < people.size());
    return searched;
}

/*
 Get Info Function - this function will be the
 */

/*
 Add Function - will add a new member to the ward
 */
void add(vector<Person*> &people)
{
    string fname;
    string lname;
    string apt;
    string info;
    Person* newPerson = new Person;
    bool isError = false;
    
    do {
        cout << "Please Enter the First Name: " << endl;
        getline(cin, fname);
        getline(cin, fname);
        cout << "Please Enter the Last Name: " << endl;
        getline(cin, lname);
        cout << "Please Enter the Apartment Number: " << endl;
        getline(cin, apt);
        cout << "Please Enter the Information: " << endl;
        getline(cin, info);
        
        //if the first name last name or apartment is blank loop through
        if (fname == "" || lname == "" || apt == "")
        {
            isError = true;
            cout << "You have left important information blank" << endl;
        }
        else
        {
            isError = false;
        }
    }
    while (isError);
    
    //set the new information
    newPerson->setFName(fname);
    newPerson->setLName(lname);
    newPerson->setApt(apt);
    newPerson->setInfo(info);
    
    //push it into the vector
    people.push_back(newPerson);
}
/*
 Remove Function - will take out a new member of the ward and delete their information
 */
void remove(vector<Person*> &people)
{
    string fname;
    string lname;
    vector<Person*> searched;
    int option = 0;
    bool isError = false;
    
    //search
    do
    {
        cout << "Whose information would you like to see?" << endl;
        cout << "First Name: "; cin >> fname;
        cout << "Last Name: "; cin >> lname;
        searched = search(fname, lname, people);
        cout << endl << endl;
        //if the first and last name are blank, meaning there is no input go through this again
        if (searched.empty())
        {
            isError = true;
            //send error message
            cout << "There is no " << fname << " " << lname << " on file. Please try again" << endl;
        }
        else
        {
            isError = false;
        }
    }
    while (isError);
    
    if (searched.size() > 1)
    {
        cout << "We have found " << searched.size() << " people with that name. Which record would you like to delete?\n";
        //loop through their options
        for (int i = 0; i < searched.size(); i++)
        {
            cout << i+1 << ". " << searched[i]->getApt() << " " << searched[i]->getLName() << ", " << searched[i]->getFName() << endl;
        }
        cin >> option; //we will use this information to get the number it is in the OG vector
        cout << endl;
        people.erase(people.begin()+searched[option - 1]->num);
    }
    else
    {
        people.erase(people.begin()+searched[0]->num);
    }
}
/*
 Edit Function - will pull the information from a user and allow the user to edit specific
 information
 */
void edit(vector<Person*> &people)
{
    string fname;
    string lname;
    int option = 0;
    int close;
    int eChoice;
    cout << "Whose information would you like to edit?" << endl;
    cout << "First Name: "; cin >> fname;
    cout << "Last Name: "; cin >> lname;
    //search for the name
    vector<Person*> searched = search(fname, lname, people);
    //tell the user number of peoples names we found if there are more than 1 and ask them
    //to choose one
    if (searched.size() > 1)
    {
        cout << "We have found " << searched.size() << " people with that name. Which record would you like to edit?\n";
        //loop through their options
        for (int i = 0; i < searched.size(); i++)
        {
            cout << i+1 << ". " << searched[i]->getApt() << " " << searched[i]->getLName() << ", " << searched[i]->getFName() << endl;
        }
        cin >> option; //we will use this information to get the number it is in the OG vector
        cout << endl;
    }
    
    //loop through until the user is done editing all information on this member
    bool stillWorking = true;
    while (stillWorking)
    {
        //ask the user what information they want to edit
        cout << "What would you like to edit?" << endl
        << "1. Apartment Number" << endl
        << "2. First Name" << endl
        << "3. Last Name" << endl
        << "4. Information" << endl;
        cin >> eChoice;
        string info;
        //edit the information on that user
        switch (eChoice) {
            case 1:
                cout << "What would you like the new apartment number to be?" << endl;
                cin >> info;
                if(option > 0)
                {
                    people[searched[option - 1]->num]->setApt(info);
                    cout << people[searched[option - 1]->num]->getLName() << ", "
                    << people[searched[option - 1]->num]->getFName() << " apartment has been changed to " << people[searched[option - 1]->num]->getApt();
                }
                else
                {
                    people[searched[0]->num]->setApt(info);
                    cout << people[searched[0]->num]->getLName() << ", "
                    << people[searched[0]->num]->getFName() << " apartment has been changed to " << people[searched[0]->num]->getApt();
                }
                break;
                
            case 2:
                cout << "What would you like the new first name to be?" << endl;
                cin >> info;
                if(option > 0)
                {
                    cout << people[searched[option - 1]->num]->getLName() << ", "
                    << people[searched[option - 1]->num]->getFName() << " from apartment " << people[searched[option - 1]->num]->getApt() << "'s first name has changed to ";
                    
                    people[searched[option - 1]->num]->setFName(info);
                    
                    cout << people[searched[option - 1]->num]->getFName();
                }
                else
                {
                    cout << people[searched[0]->num]->getLName() << ", "
                    << people[searched[0]->num]->getFName() << " from apartment " << people[searched[0]->num]->getApt() << "'s first name has changed to ";
                    
                    people[searched[0]->num]->setFName(info);
                    
                    cout << people[searched[0]->num]->getFName();
                }
                break;
                
            case 3:
                cout << "What would you like the new last name to be?" << endl;
                cin >> info;
                if(option > 0)
                {
                    cout << people[searched[option - 1]->num]->getLName() << ", "
                    << people[searched[option - 1]->num]->getFName() << " from apartment " << people[searched[option - 1]->num]->getApt() << "'s last name has changed to ";
                
                    people[searched[option - 1]->num]->setLName(info);
                    
                    cout << people[searched[option - 1]->num]->getLName();
                }
                else
                {
                    cout << people[searched[0]->num]->getLName() << ", "
                    << people[searched[0]->num]->getFName() << " from apartment " << people[searched[0]->num]->getApt() << "'s last name has changed to ";
                    
                    people[searched[0]->num]->setLName(info);
                    
                    cout << people[searched[0]->num]->getLName();
                }
                break;
                
            case 4:
                cout << "What would you like the new information to be?\n";
                getline(cin, info);
                getline(cin, info);
                cout << "This is the info: " << info << endl;
                if(option > 0)
                {
                    people[searched[option - 1]->num]->setInfo(info);
                    
                    cout << people[searched[option - 1]->num]->getLName() << ", "
                    << people[searched[option - 1]->num]->getFName() << " from apartment " << people[searched[option - 1]->num]->getApt() << "'s information has changed to ";
                    
                    cout << people[searched[option - 1]->num]->getInfo();
                }
                else
                {
                    people[searched[0]->num]->setInfo(info);
                    
                    cout << people[searched[0]->num]->getLName() << ", "
                    << people[searched[0]->num]->getFName() << " from apartment " << people[searched[0]->num]->getApt() << "'s information has changed to ";
                    
                    cout << people[searched[0]->num]->getInfo();
                }
                break;
        }
        cout << endl;
        //ask user if they want to change anything else on this user
        if (option != 0)
            cout << "Would you like to change anything else in " << people[searched[option - 1]->num]->getFName() << "\'s file?" << endl;
        else
            cout << "Would you like to change anything else in " << people[searched[0]->num]->getFName() << "\'s file?" << endl;
            cout << "1. Yes" << endl
            << "2. No" << endl;
        cin >> close;
        if (close == 2)
        {
            stillWorking = false;
        }
    }
}

/*
 Edit Function Hub - this function will ask the user if they would like to add, remove, or
 edit an existing member
 */
void editH(vector<Person*> &people)
{
    bool end = false;
    int option;
    while (end == false) {
        cout << "Would you like to:" << endl
        << "1. Add a member" << endl
        << "2. Remove a member" << endl
        << "3. Edit the Information of a member" << endl
        << "4. Go Back" << endl;
        cin >> option;
        switch(option)
        {
            case 1:
                add(people);
                break;
            case 2:
                remove(people);
                break;
            case 3:
                edit(people);
                break;
            case 4:
                end = true;
                break;
        }
    }
}

/*
 Display Function - used in all three sorts
 */
void display(list<Person*> sorted)
{
    list<Person*>::iterator it;
    for (it = sorted.begin(); it != sorted.end(); it++)
    {
        cout << **it << endl;
    }
}
/*
 The sorts will use a list to sort
 */
/*
 SortF Function - sorts the information alphabetically by first name
 */
bool sortF(Person* first, Person* second)
{
    int i = 0;
    string fname = first->getFName();
    string sname = second->getFName();
    //convert both persons first names to lower case and compare
    while ( (i<fname.length()) && (i<sname.length()) )
    {
      if (tolower(fname[i])<tolower(sname[i])) return true;
      else if (tolower(fname[i])>tolower(sname[i])) return false;
      ++i;
    }
    //if the first name is longer return true ex. Anna vs Annabelle, Anna > Annabelle
    return ( fname.length() < sname.length() );
    return true;
}

/*
 SortL Function - sorts the information alphabetically by last name
 */
bool sortL(Person* first, Person* second)
{
    int i = 0;
    string fname = first->getLName();
    string sname = second->getLName();
    //convert both persons first names to lower case and compare
    while ( (i<fname.length()) && (i<sname.length()) )
    {
      if (tolower(fname[i])<tolower(sname[i])) return true;
      else if (tolower(fname[i])>tolower(sname[i])) return false;
      ++i;
    }
    //if the first name is longer return true ex. Anna vs Annabelle, Anna > Annabelle
    return ( fname.length() < sname.length() );
    return true;
}

/*
 SortA Function - sorts the information alphabetically by apt number
 */
bool sortA(Person* first, Person* second)
{
    int apt1 = stoi(first->getApt());
    int apt2 = stoi(second->getApt());
    return apt1 < apt2;
}

/*
 Display Hub Function - This will ask the user how they want the list sorted. By
 Apartment, Last Name Alphabetical, or First Name Alphabetical.
 */
void displayH(vector<Person*> people)
{
    bool isOn = true;
    int input;
    
    //convert people to a list
    //it is easier to sort in a list than in a vector
    list<Person*> peopleList;
    
    //loop through every person and push it over to a list
    for (int i = 0; i < people.size(); i++)
    {
        peopleList.push_back(people[i]);
    }
    
    //prompt user for a type of sort to display
    while(isOn)
    {
        cout << "How would you like your student list sorted by?\n"
        << "1. First Name Alphabetical\n"
        << "2. Last Name Alphabetical\n"
        << "3. Apartment Number\n"
        << "4. Go Back\n";
        cin >> input;
        switch (input) {
            case 1:
                peopleList.sort(sortF);
                display(peopleList);
                break;
                
            case 2:
                peopleList.sort(sortL);
                display(peopleList);
                break;
                
            case 3:
                //this list will sort by apartment, then within it will each apartment
                //it will be sorted last name alphabetical
                peopleList.sort(sortL);
                peopleList.sort(sortA);
                display(peopleList);
                break;
                
            case 4:
                isOn = false;
                break;
        }
    }
}

/*
 This will be the main hub for the code where the user will go back to after completing
 an action
 */
int main() {
    bool end = false;
    int option;
    string fname;
    string lname;
    vector<Person*> people;
    vector<Person*> searched;
    //at the beginning of the program always load people
    if(load(people))
    {
        //main menu - this will keep going until you quit
    while (end == false)
    {
        cout << "Welcome to the YSA directory" << endl
        << "What operation would you like to conduct?" << endl
        << "1. Search" << endl
        << "2. Edit" << endl
        << "3. Display" << endl
        << "4. End" << endl;
        cin >> option;
        switch(option)
        {
            case 1:
                //prompt user who they would like to see
                cout << "Whose information would you like to see?" << endl;
                cout << "First Name: "; cin >> fname;
                cout << "Last Name: "; cin >> lname;
                searched = search(fname, lname, people);
                cout << endl << endl;
                if (!searched.empty())
                {
                    for (int i = 0; i < searched.size(); i++)
                    {
                        cout << *searched[i] << endl << endl;
                    }
                }
                else
                {
                    cout << "Sorry " << fname << " " << lname << " is not on file." << endl << endl;
                }
                break;
            case 2:
                editH(people);
                break;
            case 3:
                displayH(people);
                break;
            case 4:
                save(people);
                cout << "Thank you for using this ward directory service\n";
                end = true;
                break;
        }
    }
    }
    return 0;
}
