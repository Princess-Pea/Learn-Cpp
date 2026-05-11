#include <string>
#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;

public:
    Person(string name)
    {
        this->name = name;
    }
};

class Stu : virtual public Person
{
protected:
    string Id;

public:
    Stu(string name, string Id) : Person(name)
    {
        this->Id = Id;
    }
    void show()
    {
    }
};

class Epe : virtual public Person
{
protected:
    string job;

public:
    Epe(string name, string job) : Person(name)
    {
        this->job = job;
    }
    void show()
    {
    }
};

class StuhasJob : public Stu, public Epe
{
public:
    StuhasJob(string name, string job, string Id) : Stu(name, Id), Epe(name, job), Person(name)
    {
    }
    void show()
    {
        Stu::show();
        Epe::show();
    }
};
