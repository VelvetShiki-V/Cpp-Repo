#include"func.h"

void test1()
{
    Date d1(2022, 8, 6);
    Date d2(d1);
    //d1.DateShow();
    //d2.DateShow();

    //Date d3 = d1 + 10;
    //Date d4 = d2.operator+(50);
    //d3.DateShow();
    //d4.DateShow();

    //(d1 += 500).DateShow();
    //(d2 += 5000).DateShow();
    
    //Date d3;
    //Date d4(2020, 12, 24);
    //cout << (d1==d2) << endl;
    //cout << d1.operator==(d3) << endl;
    //cout << (d3!=d4) << endl;
    //cout << (d2!=d2) << endl;
    
    //Date d3 = d1 - 5;
    //Date d4 = d2.operator-(50);
    //d3.DateShow();
    //d4.DateShow();

    //(d1 -= 500).DateShow();
    //(d2.operator-=(5000)).DateShow();
    
    //Date d3;
    //Date d4(1998, 11, 17);
    //Date d5(1931, 9, 18);
    //cout << (d1 - d2) << endl;
    //cout << d1.operator-(d3) << endl;
    //cout << d5.operator-(d4) << endl;
    //cout << (d4 - d3) << endl;
    //cout << d2.operator-(d5) << endl;
    
    //Date d3 = d1++;
    //Date d4 = d2.operator++(0);
    //d3.DateShow();
    //d4.DateShow();

    //(++d1).DateShow();
    //(d2.operator++()).DateShow();
}

void test2()
{
    Date d1(2022, 2, 38);
    d1.DateShow();
    Date d2(1900, 15, 5);
    d2.DateShow();
    Date d3(980, -5, -8);
    d3.DateShow();
    Date d4(-5, 2, 28);
    d4.DateShow();
    Date d5(2022, 2, 29);
    d5.DateShow();
    Date d6(2024, 2, 29);
    d6.DateShow();
}

void test3()
{
    Date d1(2022, 13, 32);
    //cout << d1;
    //Date d2;
    //cin >> d2;
    //cout << d2;
    Date d2;
    Date d3;
    cin >> d1 >> d2 >> d3;
    cout << d1 << d2 << d3;
}

int main()
{
    //test1();
    //test2();
    test3();
}
