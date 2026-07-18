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

void xemDanhSachTaiKhoan(List l) {
    system("cls");
    cout << "\t\t\t  <<>> XEM DANH SACH TAI KHOAN <<>> " << endl;
    Node* p = l._pHead;
    int dem = 1;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    while (p != NULL) {
        SetConsoleTextAttribute(h, 13);
        cout << "Khach hang thu " << dem << ":" << endl;
        cout << p->value;
        cout << "Trang thai tai khoan: \t\t\t";
        if (p->value.getKhoa() == true) {
            SetConsoleTextAttribute(h, 12);
            cout << "Bi khoa" << endl;
        }
        if (p->value.getKhoa() == false) {
            SetConsoleTextAttribute(h, 10);
            cout << "Dang hoat dong" << endl;
        }
        cout << endl;
        p = p->_pNext;
        dem++;
    }
    if (dem == 1) cout << "Hien tai van chua co khach hang." << endl;
    cout << endl;
    system("pause");
    return;
}

void themTaiKhoan(List& l) {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "\t\t\t  <<>> THEM TAI KHOAN <<>> " << endl;
    SetConsoleTextAttribute(h, 13);
    Node* p = l._pHead;
    string id, name, iso;
    unsigned long money;
    User tmp;
    cout << "Luu y, ID khong duoc trung (nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "Nhap ID (14 chu so): ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    while (p != NULL) {
        if (p->value.getID() == id) {
            do {
                cout << "ID nay da ton tai, vui long nhap ID moi!!" << endl;
                cout << p->value << endl;
                cout << "Hay lay ID khac." << endl;
                do {
                    SetConsoleTextAttribute(h, 2);
                    cout << "Nhap ID (14 chu so): ";
                    cin >> id;
                    SetConsoleTextAttribute(h, 13);
                    if (id == "exit" || id == "EXIT") {
                        cout << "Quay lai Menu" << endl;
                        system("pause");
                        return;
                    }
                    if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
                } while (id.size() != 14);
            } while (id == p->value.getID());
            break;
        }
        p = p->_pNext;
    }
    cout << "Ma PIN mac dinh cua ban: 123456" << endl;

    auto isValidName = [](const string& name) {
        for (char c : name) {
            if (!isalpha(c) && c != ' ') {
                return false;
            }
        }
        return !name.empty();
        };

    do {
        cout << "Ho va ten (chi nhap chu cai): ";
        cin.ignore();
        getline(cin, name);

        if (!isValidName(name)) {
            SetConsoleTextAttribute(h, 12);
            cout << "Ten khong hop le! Chi duoc nhap chu cai va khoang trang." << endl;
            SetConsoleTextAttribute(h, 13);
        }
    } while (!isValidName(name));

    cout << "So tien tao tai khoan: ";
    do {
        cin >> money;
        if (money < 0) cout << "Tien tao tai khoan khong the la so am!!!" << endl;
    } while (money < 0);

    cout << "Don vi tien te: ";
    do {
        cin >> iso;
        if (iso.size() != 3) cout << "Vui long nhap lai don vi tien te!!!" << endl;
    } while (iso.size() != 3);

    User tmp2(id, "123456", name, money, iso);
    addNode(l, getNode(tmp2));
    cout << "Tao tai khoan thanh cong! Xin chao " << name << endl;
    system("pause");
    return;
}

void delHead(List& l) {
    if (l._pHead != NULL) {
        Node* p = l._pHead;
        l._pHead = p->_pNext;
    }
}

void delTail(List& l) {
    Node* p = l._pHead;
    while (p->_pNext->_pNext != NULL) {
        p = p->_pNext;
    }
    p->_pNext = NULL;
}

void xoaTaiKhoan(List& l) {
    system("cls");
    cout << "\t\t\t  <<>> XOA TAI KHOAN <<>> " << endl;

    string id;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "Nhap ID tai khoan can xoa (Nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    SetConsoleTextAttribute(h, 13);
    Node* p = l._pHead;

    while (p->_pNext != NULL) {
        if (id == p->_pNext->value.getID()) {
            cout << "Xoa tai khoan thanh cong!" << endl;
            cout << "Da xoa " << p->_pNext->value.getName() << " ra khoi he thong." << endl;
            p->_pNext = p->_pNext->_pNext;
            system("pause");
            return;
        }
        p = p->_pNext;
    }

    SetConsoleTextAttribute(h, 12);
    cout << "Xoa tai khoan that bai, ID can xoa khong ton tai!" << endl;
    system("pause");
    return;
}

void moKhoaTaiKhoan(List& l) {
    system("cls");
    cout << "\t\t\t  <<>> MO KHOA TAI KHOAN <<>> " << endl;
    string id;
    int dem = 1;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    Node* p = l._pHead;
    SetConsoleTextAttribute(h, 10);
    cout << "Nhap ID tai khoan can mo khoa (nhap exit de quay lai Menu)." << endl;
    do {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT") {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14) cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    SetConsoleTextAttribute(h, 10);

    while (p != NULL) {
        if (id == p->value.getID()) {
            if (p->value.getKhoa() == false) {
                SetConsoleTextAttribute(h, 10);
                cout << "Tai khoan van dang duoc hoat dong binh thuong." << endl;
                system("pause");
                return;
            }
            else {
                p->value.setKhoa(false);
                cout << "Mo khoa tai khoan thanh cong!" << endl;
                system("pause");
                return;
            }
        }
        p = p->_pNext;
    }
    SetConsoleTextAttribute(h, 12);
    cout << "Mo tai khoan that bai, ID can mo khoa khong ton tai!" << endl;
    system("pause");
    return;
}

bool dangNhapAdmin(List l) {
    string user, pass;
    char ast = ' ';
    int aste = 0;
    int dem = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "\t\t\tDANG NHAP ADMIN" << endl;
    SetConsoleTextAttribute(h, 2);
    cout << "User: "; cin >> user;
    for (int i = 0; i < 6; i++) {
        if (l.getUseri(i) == user) {
            do {
                if (dem == 3) {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Ban da nhap sai qua qua nhieu lan, vui long thu lai trong giay lat." << endl;
                    system("pause");
                    return false;
                }
                pass = "";

                SetConsoleTextAttribute(h, 2);
                cout << "Pass: ";
                do {
                    ast = _getch();
                    if (ast == 13 || ast == ' ') {
                        break;
                    }
                    if (ast == 8 || ast == 127) {
                        if (pass.size() != 0) {
                            cout << "\b \b";
                            pass.erase(pass.size() - 1);
                            aste--;
                        }
                    }
                    else {
                        pass += ast;
                        cout << "*";
                        aste++;
                    }
                } while (ast != 13 || ast != ' ');
                cout << endl;

                if (l.getPassi(i) == pass) {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Dang nhap Admin thanh cong, xin chao " << user << "." << endl;
                    system("pause");
                    return true;
                }

                if (l.getPassi(i) != pass) {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Mat khau nhap sai, vui long nhap lai." << endl;
                    dem++;
                }

            } while (l.getPassi(i) != pass);
        }
    }
    SetConsoleTextAttribute(h, 13);
    cout << "Dang nhap that bai, tai khoan hoac mat khau cua ban nhap sai." << endl;
    system("pause");
    return false;
}

void MenuAdmin() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 3);
    cout << "************* <<>> WELCOME TO AAAAA BANK <<>> ************" << endl;
    cout << "|\t\t       [MENU ADMIN]                      |" << endl;
    cout << "|------------- Vui long chon loai chuc nang -------------|" << endl;
    cout << "|        \t1. Xem danh sach tai khoan\t\t |" << endl;
    cout << "|        \t2. Them tai khoan         \t\t |" << endl;
    cout << "|        \t3. Xoa tai khoan          \t\t |" << endl;
    cout << "|        \t4. Mo khoa tai khoan      \t\t |" << endl;
    cout << "|        \t5. Quay lai sanh          \t\t |" << endl;
    cout << "**********************************************************" << endl;
}
void xemThongTin(User& A) {
    system("cls");
    cout << "\t\t\t  <<>> THONG TIN TAI KHOAN <<>> " << endl;
    cout << A;
    system("pause");
    return;
}

void maPinSao(string& pin) {
    char ast = ' ';
    int aste = 0;
    pin = "";
    do {
        ast = _getch();
        if (ast == 13 || ast == ' ') {
            break;
        }
        if (ast == 8 || ast == 127) {
            if (pin.size() != 0) {
                cout << "\b \b";
                pin.erase(pin.size() - 1);
                aste--;
            }
        }
        else {
            pin += ast;
            cout << "*";
            aste++;
        }
    } while (ast != 13 || ast != ' ');
}

void doiMaPin(User& A) {
    system("cls");
    cout << "\t\t\t  <<>> DOI MA PIN <<>> " << endl;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << "Ma PIN gom 6 chu so (Nhap 0 de quay lai Menu)." << endl;
    SetConsoleTextAttribute(h, 2);
    cout << "Nhap ma PIN hien tai: ";
    char ast = ' ';
    int aste = 0;
    string pin, pinnew1, pinnew2;
    do {
        cout << "PIN: ";
        maPinSao(pin);
        if (pin == "0") {
            cout << "\nQuay lai Menu." << endl;
            system("pause");
            return;
        }
        cout << endl;
        SetConsoleTextAttribute(h, 13);
        if (pin != A.getPIN()) cout << "Ma PIN nhap sai, vui long nhap lai." << endl;
    } while (pin != A.getPIN());

    if (pin == A.getPIN()) {
        do {
            SetConsoleTextAttribute(h, 2);
            cout << "Nhap Ma PIN moi: ";
            do {
                maPinSao(pinnew1);
                cout << endl;
                if (pinnew1.size() != 6) cout << "Ma PIN phai co 6 chu so, vui long nhap lai: " << endl;
            } while (pinnew1.size() != 6);
            cout << "Xac nhan lai ma PIN moi: ";
            do {
                maPinSao(pinnew2);
                cout << endl;
                if (pinnew2.size() != 6) cout << "Ma PIN phai co 6 chu so, vui long nhap lai: " << endl;
            } while (pinnew2.size() != 6);

            if (pinnew1 != pinnew2) cout << "Ma PIN moi khong khop nhau, vui long nhap lai ma PIN moi." << endl;
        } while (pinnew1 != pinnew2);

        if (pinnew1 == pinnew2) {
            A.setPIN(pinnew2);
            SetConsoleTextAttribute(h, 13);
            cout << "Doi ma PIN thanh cong!" << endl;
            system("pause");
            return;
        }
    }
}

Node* dangNhapUser(List& l) {
    string id, pin;
    cout << "Nhap ID: ";
    cin >> id;

    Node* p = l._pHead;
    while (p != NULL) {
        if (p->value.getID() == id) {
            if (p->value.getKhoa()) {
                cout << "Tai khoan bi khoa. Lien he Admin.\n";
                cout << "Bam Enter de quay lai menu...";
                cin.ignore();
                cin.get();
                return NULL;
            }

            int soLanSai = 0;
            const int MAX_LAN_SAI = 3;

            while (soLanSai < MAX_LAN_SAI) {
                cout << "Nhap ma PIN: ";
                maPinSao(pin);
                cout << endl;

                if (pin == p->value.getPIN()) {
                    if (p->value.isFirstLogin() && pin == "123456") {
                        cout << "\nDAY LA LAN DAU DANG NHAP. VUI LONG DOI MA PIN.\n";
                        cout << "Bam Enter de tiep tuc doi mat khau...";
                        cin.ignore();
                        cin.get();
                        doiMaPin(p->value);
                        p->value.setFirstLogin(false);
                    }
                    cout << "Dang nhap thanh cong!\n";
                    return p;
                }
                else {
                    soLanSai++;
                    if (soLanSai < MAX_LAN_SAI) {
                        cout << "Sai ma PIN. Con " << (MAX_LAN_SAI - soLanSai)
                            << " lan thu. Vui long thu lai.\n";
                    }
                }
            }

            cout << "Ban da nhap sai ma PIN " << MAX_LAN_SAI
                << " lan. Tai khoan se bi khoa.\n";
            cin.ignore();
            cin.get();
            p->value.setKhoa(true);
            return NULL;
        }
        p = p->_pNext;
    }

    cout << "ID khong ton tai.\n";
    return NULL;
}

void MenuUser(User A) {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << "*************** <<>> AAAAA  BANK <<>> ***************" << endl;
    cout << "|                     MENU USER                     |" << endl;
    cout << "|---------- Vui long chon loai giao dich -----------|" << endl;
    cout << "| \t1. Xem thong tin tai khoan  \t\t\    |" << endl;
    cout << "| \t2. Nap tien                 \t\t\    |" << endl;
    cout << "| \t3. Rut tien                 \t\t\    |" << endl;
    cout << "| \t4. Chuyen tien              \t\t\    |" << endl;
    cout << "| \t5. Xem lich su giao dich    \t\t\    |" << endl;
    cout << "| \t6. Doi ma pin               \t\t\    |" << endl;
    cout << "| \t7. Quay lai sanh            \t\t\    |" << endl;
    cout << "*****************************************************" << endl;
}

void MenuSanh() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    cout << "******** <<>> WELCOME TO AAAAA BANK <<>> **********" << endl;
    cout << "|\t       [ AAAAA BANK LOBBY ]               |" << endl;
    cout << "|---------------- Admin or User ------------------|" << endl;
    cout << "| \t 1. Admin       \t\t\t  |" << endl;
    cout << "| \t 2. User        \t\t\t  |" << endl;
    cout << "| \t 3. Exit                      \t\t\  |" << endl;
    cout << "***************************************************" << endl;
}
