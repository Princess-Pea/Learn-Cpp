// #include <string>
// #include <iostream>
// using namespace std;

// class Date
// {
//     int year, month, day;

// public:
//     Date(int y, int m, int d) : year(y), month(m), day(d)
//     {
//         cout << "Date constructing with parameters" << endl;
//     }
//     void showdate()
//     {
//         cout << year << "-" << month << "-" << day << endl;
//     }
//     ~Date()
//     {
//         cout << "Date destructing" << endl;
//     }
// };

// class Person
// {
//     string name;
//     int age;

// public:
//     /*
//         Person()
//         {
//             cout << "Person Constructing" << endl;
//         }*/
//     Person(string n, int a)
//     {
//         name = n;
//         age = a;
//         cout << "Person Constructing with parameters" << endl;
//     }
//     void setPerson(string n, int a)
//     {
//         name = n;
//         age = a;
//     }
//     void showPerson()
//     {
//         cout << "name:" << name << endl;
//         cout << "age:" << age << endl;
//     }
//     ~Person()
//     {
//         cout << "Person destructing" << endl;
//     }
// };

// class Student : public Person
// {
//     int grade;
//     Date Entrydate;

// public:
//     /*Student() : Person("Jack", 150)
//     {
//         cout << "Student Constructing" << endl;
//     }*/
//     Student(string n, int a, int g, int y, int m, int d) : Person(n, a), Entrydate(y, m, d)
//     {
//         grade = g;
//         cout << "Student Constructing with parameters" << endl;
//     }
//     void setStudent(string n, int a, int g)
//     {
//         setPerson(n, a);
//         grade = g;
//     }
//     void showStudent()
//     {
//         showPerson();
//         cout << "grade:" << grade << endl;
//         Entrydate.showdate();
//     }
//     ~Student()
//     {
//         cout << "Student destructing" << endl;
//     }
// };
