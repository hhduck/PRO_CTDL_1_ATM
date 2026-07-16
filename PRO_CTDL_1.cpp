#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>
using namespace std;

class User
{
private:
    string ID;
    string PIN;

    string Name;
    unsigned long Money;
    string ISO;
    bool Khoa = false;
    bool firstLogin = true;

public:
    stack<string> lsTien;
    stack<string> lsLoaiGD;
    stack<string> lsTG;
    stack<string> lsTD;
    User()
    {
        ID = "00000000000000";
        PIN = "123456";
        Name = "Null";
        Money = 0;
        ISO = "VND";
    }
    User(string id, string pin, string name, unsigned long money, string iso)
    {
        ID = id;
        PIN = pin;
        Name = name;
        Money = money;
        ISO = iso;
    }

    string getID() { return ID; }
    string getPIN() { return PIN; }
    string getName() { return Name; }
    unsigned long getMoney() { return Money; }
    string getISO() { return ISO; }
    bool getKhoa() { return Khoa; }
    bool isFirstLogin() const { return firstLogin; }
    void setFirstLogin(bool status) { firstLogin = status; }

    void setID(string ID) { this->ID = ID; }
    void setPIN(string PIN) { this->PIN = PIN; }
    void setName(string Name) { this->Name = Name; }
    void setMoney(unsigned long Money) { this->Money = Money; }
    void setISO(string ISO) { this->ISO = ISO; }
    void setKhoa(bool Khoa) { this->Khoa = Khoa; }

    friend istream &operator>>(istream &is, User &n)
    {
        cout << "ID (14 chu so): ";
        do
        {
            is >> n.ID;
            if (n.ID.size() != 14)
                cout << "Do dai ID phai la 14 chu so!!!" << endl;
        } while (n.ID.size() != 14);

        cout << "Ma PIN mac dinh cua ban: 123456" << endl;
        n.setPIN("123456");

        cout << "Ho va ten: ";
        getline(is, n.Name);

        cout << "So tien tao tai khoan: ";
        do
        {
            is >> n.Money;
            if (n.Money < 0)
                cout << "Tien tao tai khoan khong the la so am!!!" << endl;
        } while (n.Money < 0);

        cout << "Don vi tien te: ";
        do
        {
            is >> n.ISO;
            if (n.ISO.size() != 3)
                cout << "Vui long nhap lai don vi tien te!!!" << endl;
        } while (n.ISO.size() != 3);

        return is;
    }

    friend ostream &operator<<(ostream &ou, User n)
    {
        ou << "ID:                   \t\t\t" << n.ID << endl;
        ou << "Ten chu tai khoan:    \t\t\t" << n.Name << endl;
        ou << "So du hien co:        \t\t\t" << n.Money << endl;
        ou << "Loai tien te:         \t\t\t" << n.ISO << endl;
        return ou;
    }
};

class Node
{
public:
    User value;
    Node *_pNext;
};

class List
{
private:
    string user[100];
    string pass[100];

public:
    Node *_pHead;
    Node *_pTail;

    List()
    {
        for (int i = 0; i < 6; i++)
        {
            user[i] = "Admin1";
            pass[i] = "123456";
        }
    }
    string getUseri(int i) { return user[i]; }
    string getPassi(int i) { return pass[i]; }

    void setUseri(string user, int i) { this->user[i] = user; }
    void setPassi(string pass, int i) { this->pass[i] = pass; }
};

void IntList(List &l)
{
    l._pHead = l._pTail = NULL;
}

Node *getNode(User c)
{
    Node *p = new Node();
    p->value = c;
    p->_pNext = NULL;
    return p;
}

void addCus(List &l, Node *p)
{
    if (l._pHead == NULL)
    {
        l._pHead = l._pTail = p;
    }
    else
    {
        p->_pNext = l._pHead;
        l._pHead = p;
    }
}

void addNode(List &l, Node *p)
{
    if (l._pHead == NULL)
    {
        l._pHead = l._pTail = p;
    }
    else
    {
        l._pTail->_pNext = p;
        l._pTail = p;
    }
}