#include<stdio.h>
#include<stdlib.h>
#include<string.h>
class Cstudent
{
    public:
    Cstudent(char i_name[10],short i_age,char i_cla[20]);
    char c_name[10];
    short c_age;
    char c_cla[20];
}
Cstudent::Cstudent(char i_name[10],short i_age,char i_cla[20])
{
    strcpy(c_name,i_name);
    c_age=i_age;
    strcpy(c_cla,i_cla);
}