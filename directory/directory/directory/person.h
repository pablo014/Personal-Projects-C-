//
//  person.h
//  directory
//
//  Created by Angelo Pablo on 10/17/19.
//  Copyright © 2019 Angelo Pablo. All rights reserved.
//

/*
 A person will have a first name, last name, apartment number, and information and that
 information will be sorted and displayed in different ways
 */
#include <iostream>
using namespace std;

#ifndef person_h
#define person_h
class Person{
private:
    string apt;
    string fname;
    string lname;
    string info;
    
public:
    //public data
    int num;
    //constructors
    Person();
    Person(const string num, const string name1, const string name2, const string information);
    Person(Person& person);
    //apt getters and setters
    string getApt(){ return apt; }
    void setApt(const string apt){ this->apt = apt; }
    
    //fname getters and setters
    string getFName(){return fname;}
    void setFName(const string fname){this->fname = fname;}
    
    //lname getters and setters
    string getLName(){return lname;}
    void setLName(const string lname){this->lname = lname;}
    
    //info getters and setters
    string getInfo(){return info;}
    void setInfo(const string info){this->info = info;}
    
    //overload the display operator
    friend ostream& operator<<(ostream& os, Person& person);
    
    //overload the assignment operator
    Person operator=(Person &rhs);
    bool operator==(Person &rhs);
};

/*
 Constructors
 */
Person::Person()
{
    apt = "Unassigned";
    fname = "";
    lname = "";
    info = "";
}
 
Person::Person(string num, string name1, string name2, string information)
{
    apt = num;
    fname = name1;
    lname = name2;
    info = information;
}
Person::Person(Person& person)
{
    apt = person.getApt();
    fname = person.getFName();
    lname = person.getLName();
    info = person.getInfo();
}

/*
 Overloaded Operators
 */
//overloaded <<
ostream& operator<<(ostream& os, Person& person)
{
    //always show if the student is assigned an apartment
    os << person.getApt() << endl;
    //if i dont have a first name show it as blank
    if (person.getLName() != "")
        os << person.getLName() << ", ";
    //if i dont have a last name show it as blank
    if (person.getFName() != "")
        os << person.getFName();
    //if i don't have any info on the person show it as blank
    if (person.getInfo() != "")
        os  << endl << endl << "Information:\n" << person.getInfo();
    //always end the display with an endline so I dont have to constantly end line
    os << endl;
    return os;
}
//overloaded assignment operator
Person Person::operator=(Person &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        apt = rhs.getApt();
        fname = rhs.getFName();
        lname = rhs.getLName();
        info = rhs.getInfo();
        return *this;
    }
}
//overloaded == this is mainly going to be checking for duplicates

bool Person::operator==(Person &rhs)
{
    string LFName = ""; //lowercase first name
    string OFName = ""; //lowercase original first name
    string LLName = ""; //lowercase last name
    string OLName = ""; //lowercase original last name
    
    //convert name to lower case
    for(int i=0; i<rhs.getFName().length();i++)
    {
        LFName += tolower(rhs.getFName()[i]);
        OLName += tolower(fname[i]);
    }
    for(int i=0; i<rhs.getLName().length();i++)
    {
        LFName += tolower(rhs.getLName()[i]);
        OFName += tolower(lname[i]);
    }
    
    //if any 2 conditions are the same return true
    if(rhs.getApt() == apt && LLName == lname)
        return true;
    else if (LFName == fname && LLName == lname)
        return true;
    else if (rhs.getApt() == apt && LFName == fname)
        return true;
    else
        return false;
}
 
#endif /* person_h */
