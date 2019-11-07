//
//  time.h
//  Running Times
//
//  Created by Angelo Pablo on 11/7/19.
//  Copyright © 2019 Angelo Pablo. All rights reserved.
//

/*
 A time will have an event, an hour, a minute, a second, a millisecond, and a total
 */

#include <iostream>
using namespace std;

#ifndef TIME_H
#define TIME_H

class Time
{
private:
    string event;
    int hour;
    int minute;
    int second;
    int milli;
    string total;
public:
    Time();
    Time(const string event, const string total, const int hour, const int minute, const int second, const int milli);
    string getEvent(){
        return event;
    }
    string getTotal(){
        return total;
    }
    int getHour(){
        return hour;
    }
    int getMinute(){
        return minute;
    }
    int getSecond(){
        return second;
    }
    int getMilli(){
        return milli;
    }
    void setEvent(string event){
        this->event = event;
    }
    void setTotal(string total){
        this->total = total;
    }
    void setHour(int hour){
        this->hour = hour;
    }
    void setMinute(int minute){
        this->minute = minute;
    }
    void setSecond(int second){
        this->second = second;
    }
    void setMilli(int milli){
        this->milli = milli;
    }
}

#endif /* time_h */
