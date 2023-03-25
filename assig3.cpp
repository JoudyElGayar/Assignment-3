/* 
------------------------------------------------------------------
* Author: Joudy El Gayar
* Class: CSCE 1101/Assignement 3 
* ID: 900222142
* Date: 25/02/2023
* Description: This program should implement a car workshop appointment system, where customers can book appointments. The program should be able to take a customer’s information and the appointment that they’d like to book and assigns them to a mechanic according to their availability. *
------------------------------------------------------------------
*/


#include <iostream>
#include <string>
#include<queue>
#include <fstream>

using namespace std;

//Person class
class Person{      

private:

string Name;
int ID;
int Age;

public:
//default constructor
Person()   
{     
 Name="";   
 ID=0;       
 Age=0;    
 } 
 //setters
void setName(string n){  
    Name=n;}

void setId(int id){
ID = id;}

void setAge(int a){
Age = a;
}
 //getters
string getName(){   

return Name;

}

int getId(){

return ID;

}

int getAge(){

return Age;

}
 //print function 
virtual void printInfo(){    // we should use virtualization to be able to use this fucntion in other classes.
cout<<"Name : "<<Name<<endl;
cout<<"ID: "<<ID<<endl;
cout<<"Age="<<Age<<endl;     } 
};

struct Appointment { 
int hours;    
int mins; };

// customer class
class Customer :public Person {   
private: 
int MechanicalID;    
 Appointment app;     

 public:   
 //default constructor 
Customer()
{
    MechanicalID= 0;
    app.hours=0;
    app.mins=0;
}
//setters 
 void setMechanicalID(int m){         
    MechanicalID=m;     
    }         
void setAppointment(int h,int m){
app.hours=h;     
app.mins=m;     
}
//getters
int getMechanicalID(){
    return MechanicalID;
}
int getAppointhour()
{
    return app.hours;
}
int getAppointmins()
{
    return app.mins;
}
//overloaded comparison operators
bool operator <(Customer& other) {         
    if(app.hours<other.getAppointhour()||app.mins<other.getAppointmins())
    {             
    return true; 
    }     
   else      
        return false;
        }


 bool operator ==( Customer& other){        
    if(app.hours==other.getAppointhour() || app.mins==other.getAppointmins()) {            
         return true;  }
         else
     return false; }


 bool operator >(Customer& other){         
    if(app.hours>other.getAppointhour() || app.mins>other.getAppointhour()){         
     return true ;}
    else                   
         return false;       
            }  
};

 class Mechanic:public Person { 
private:     
    int counter; 
    Appointment bookedapps[10];

public:     
bool isAvailable(int hour, int min ) {
    int x=1;
        for (int i = 0; i < counter; i++) {
        if (bookedapps[i].hours == hour && bookedapps[i].mins == min) {
          x=0;
        }
        else  continue;
      }
      return x;
    }
   
   void setCounter() {
        counter++;
    }
    void setAppointment(int x, int y) {
        bookedapps[counter].hours = x;
        bookedapps[counter].mins = y;
        counter++;
    }

   int getCounter(){

return counter;

}
int gethours(int x)
{
    return bookedapps[x].hours;
}
int getmins(int x)
{
    return bookedapps[x].mins;
}


};

//queue class
template <class T>
class Queue {
    private: 
     int front;
    int rear;
    int counter;
    int maxSize;
    T *values;
public:
    Queue()
    {
        int size = 10;
        values= new T [size];
        maxSize=size;
        front= 0;
        rear= -1;
        counter= 0;

    }
    ~Queue() { delete [] values; }    
    bool IsEmpty(void)
    {
        if (counter!=0)
            return false;
        else
            return true;
    }
    bool IsFull(void)
    {
        if (counter < maxSize)
            return false;
        else
            return true;
    }
    bool Enqueue(T &x)
    {
        if (IsFull()) {
            cout << "Error: the queue is full." << endl;
            return false;
        }
        else {
            rear= (rear + 1) % maxSize;
            
            values[rear] = x;
            counter++;
            return true;
        }
    }
    T Dequeue()
    {
        if (IsEmpty()) {
            exit(EXIT_FAILURE);
            }
            else {
                T y;
                y=values[front];
                front= (front + 1) % maxSize;
                counter--;
                return y;
            }

    }
    
    
};
int main()
{
   Mechanic m1[3];
    string Name;
    int Age;
    int ID;
    ifstream file;
    file.open("mechanic.txt");
    while(!file.eof())
    {
        for(int i=0;i<3;i++)
        {
            file >> Name;
            file >> Age;
            file >> ID;
            m1[i].setName(Name);
            m1[i].setAge(Age);
            m1[i].setId(ID);
            
        }
    }
    file.close();
    Customer e[5];
    string name2;
    int ages;
    int hour;
    int min;
    ifstream file2;
    file2.open("customer.txt");
    while(!file2.eof())
    {
        for(int r=0;r<5;r++)
        {
            file2 >> name2;
            file2 >> ages;
            file2 >> hour;
            file2 >> min;
            e[r].setName(name2);
            e[r].setAge(ages);
            e[r].setAppointment(hour,min);
        }
    }
    file2.close();
    int z=0;
    for(int j=0;j<5;j++)
    {
        
        if(j>=3)
        {
            
               if(m1[z].isAvailable(e[j].getAppointhour(),e[j].getAppointmins())== 1)
               {
                   m1[z].setAppointment(e[j].getAppointhour(),e[j].getAppointmins());
                   e[j].setMechanicalID(z);
                   z++;
               }
                else
                {
                    if(m1[z+1].isAvailable(e[j].getAppointhour(),e[j].getAppointmins())== 1)
                    {
                        m1[z].setAppointment(e[j].getAppointhour(),e[j].getAppointmins());
                        e[j].setMechanicalID(z+1);
                        z++;
                    }
                }
               
            }
        else
        {
            if(m1[j].isAvailable(e[j].getAppointhour(),e[j].getAppointmins())==1)
            {
                m1[j].setAppointment(e[j].getAppointhour(),e[j].getAppointmins());
                e[j].setMechanicalID(j);
                
            }
            
            else{
                    cout << "There is no mechanic available for " << e[j].getName() << endl;
                
                }
        }
    }
    
 Queue <Customer> s;
    for(int k=0;k<5;k++)
    {
        Customer temp;
        for(int u=0;u<5;u++)
        {
            if(e[k] < e[u])
            {
                temp=e[k];
                e[k]=e[u];
                e[u]=temp;
            }
        }
           
    }
    for(int i=0;i<5;i++)
    {
        s.Enqueue(e[i]);
    }
    
    for(int a=0;a<5;a++)
    {
        Customer m[5];
        m[a]= s.Dequeue();
        cout << "MR." << m[a].getName() << " at the appointment " << m[a].getAppointhour() << ":" << m[a].getAppointmins() << " to the mechanic " << m1[m[a].getMechanicalID()].getName() << endl;
    }
return 0;

}