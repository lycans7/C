/*
 * callBackExample.cpp
 *
 *  Created on: 26-Dec-2018
 *      Author: Parth shah
 */


//warning:  Mind compiled code, intended to illustrate the mechanism
#include <iostream>
#include <map>

typedef void (*Callback)();
std::map<int, Callback>  callback_map;

void RegisterCallback(int event, Callback function)
{
    callback_map[event] = function;
}

bool finished = false;

int GetNextEvent()
{
    static int i = 0;
    ++i;
    if (i == 5) finished = false;
}

void EventProcessor()
{
    int event;
    while (!finished)
    {
        event = GetNextEvent();
        std::map<int, Callback>::const_iterator it = callback_map.find(event);
        if (it != callback_map.end())    // if a callback is registered for event
        {
            Callback function = *it;
            if (function)
            {
                (*function)();
            }
            else
            {
               std::cout << "No callback found\n";
            }
        }
    }
}

void Cat()
{
   std::cout << "Cat\n";
}

void Dog()
{
    std::cout << "Dog\n";
}

void Bird()
{
    std::cout << "Bird\n";
}

int main()
{
    RegisterCallback(1, Cat);
    RegisterCallback(2, Dog);
    RegisterCallback(3, Cat);
    RegisterCallback(4, Bird);
    RegisterCallback(5, Cat);

    EventProcessor();
    return 0;
}

