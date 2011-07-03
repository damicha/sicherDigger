/* poly.cpp */
/* damicha of defect (2011) */

/* Test how to store objects of inherent classes of a virtual class in an array of type of
 * the virtual class.
 * -> Don't store the objects directly.
 * -> Store only pointer of the objects.
 * -> Create and destroy the objects by the class functions !!
 */


#include <stdio.h>
#include <string>
#include <sstream>
#include <deque>

using namespace std;

/* virtual base class */
class baseObj
{
public:
    string  name;
    int     val;

    baseObj() : val(0) {};

    string str() {
        stringstream ss;
        ss << "Name: " << name << "Val: " << val;
        return ss.str();
    }
    virtual int proceed() = 0;

};

/* class A */
class A : public baseObj
{
public:
    A() { name = "A"; }

    int proceed() {val++; return val;}
};

/* class B */
class B : public baseObj
{
public:
    B() { name = "B"; }
    
    int proceed() {val--; return val;}
};



/*
 * main
 */
int main(void)
{
    // create objects to work with
    A a;
    B b;

    // create list to store references to the objects a and b
    const int list_size = 5;
    baseObj * list[list_size];      // list of pointers

    // fill list
    list[0] = &a;
    list[1] = &b;
    list[2] = &b;
    list[3] = &b;
    list[4] = &a;
   
    // proceed object functions and print object values
    for (int i = 0; i < list_size; i++)
    {
        baseObj *o = list[i];
        o->proceed();
        printf("%s\n", o->str().c_str());
    }

}

