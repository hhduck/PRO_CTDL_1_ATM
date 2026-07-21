#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <filesystem>
using namespace std;

bool nhapSoKhongDauAnToan(unsigned long &ketQua)
{
    string raw;
    cin >> raw;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    if (raw.empty())
        return false;

    for (char c : raw)
    {
        if (!isdigit((unsigned char)c))
            return false;
    }

    try
    {
        ketQua = stoul(raw);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

struct GiaoDich
{
    string tien;
    string loai;
    string thoiGian;
    string thongDiep;
};

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
    stack<GiaoDich> lichSu;

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
public:
    Node *_pHead;
    Node *_pTail;

    List()
    {
        _pHead = NULL;
        _pTail = NULL;
    }
};

struct Admin
{
    string user;
    string pass;
};

class AdminNode
{
public:
    Admin value;
    AdminNode *_pNext;
};

class AdminList
{
public:
    AdminNode *_pHead;
    AdminNode *_pTail;

    AdminList()
    {
        _pHead = NULL;
        _pTail = NULL;
    }
};

AdminNode *getAdminNode(Admin a)
{
    AdminNode *p = new AdminNode();
    p->value = a;
    p->_pNext = NULL;
    return p;
}

void addAdminNode(AdminList &l, AdminNode *p)
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

Node *getNode(User c)
{
    Node *p = new Node();
    p->value = c;
    p->_pNext = NULL;
    return p;
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

void xemDanhSachTaiKhoan(List &l)
{
    system("cls");
    cout << "\t\t\t  <<>> XEM DANH SACH TAI KHOAN <<>> " << endl;
    Node *p = l._pHead;
    int dem = 1;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    while (p != NULL)
    {
        SetConsoleTextAttribute(h, 13);
        cout << "Khach hang thu " << dem << ":" << endl;
        cout << p->value;
        cout << "Trang thai tai khoan: \t\t\t";
        if (p->value.getKhoa() == true)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "Bi khoa" << endl;
        }
        if (p->value.getKhoa() == false)
        {
            SetConsoleTextAttribute(h, 10);
            cout << "Dang hoat dong" << endl;
        }
        cout << endl;
        p = p->_pNext;
        dem++;
    }
    if (dem == 1)
        cout << "Hien tai van chua co khach hang." << endl;
    cout << endl;
    system("pause");
    return;
}

void themTaiKhoan(List &l)
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "\t\t\t  <<>> THEM TAI KHOAN <<>> " << endl;
    SetConsoleTextAttribute(h, 13);
    Node *p = l._pHead;
    string id, name, iso;
    unsigned long money;
    cout << "Luu y, ID khong duoc trung (nhap exit de quay lai Menu)." << endl;

    auto isValidIDStr = [](const string &s)
    {
        if (s.size() != 14)
            return false;
        for (char c : s)
        {
            if (!isdigit((unsigned char)c))
                return false;
        }
        return true;
    };

    bool trung;
    do
    {
        trung = false;

        do
        {
            SetConsoleTextAttribute(h, 2);
            cout << "Nhap ID (14 chu so): ";
            cin >> id;
            SetConsoleTextAttribute(h, 13);
            if (id == "exit" || id == "EXIT")
            {
                cout << "Quay lai Menu" << endl;
                system("pause");
                return;
            }
            if (!isValidIDStr(id))
            {
                SetConsoleTextAttribute(h, 12);
                cout << "ID khong hop le! ID phai gom dung 14 chu so." << endl;
                SetConsoleTextAttribute(h, 13);
            }
        } while (!isValidIDStr(id));

        Node *p2 = l._pHead;
        while (p2 != NULL)
        {
            if (p2->value.getID() == id)
            {
                trung = true;
                SetConsoleTextAttribute(h, 12);
                cout << "ID nay da ton tai, thuoc ve tai khoan: " << p2->value.getName() << endl;
                SetConsoleTextAttribute(h, 13);
                cout << "Vui long nhap ID khac." << endl;
                break;
            }
            p2 = p2->_pNext;
        }
    } while (trung);
    cout << "Ma PIN mac dinh cua ban: 123456" << endl;

    auto isValidName = [](const string &name)
    {
        for (char c : name)
        {
            if (!isalpha((unsigned char)c) && c != ' ')
            {
                return false;
            }
        }
        return !name.empty();
    };

    do
    {
        cout << "Ho va ten (chi nhap chu cai): ";
        cin.ignore();
        getline(cin, name);

        if (!isValidName(name))
        {
            SetConsoleTextAttribute(h, 12);
            cout << "Ten khong hop le! Chi duoc nhap chu cai va khoang trang." << endl;
            SetConsoleTextAttribute(h, 13);
        }
    } while (!isValidName(name));

    cout << "So tien tao tai khoan: ";
    bool hopLeMoney;
    do
    {
        hopLeMoney = nhapSoKhongDauAnToan(money);
        if (!hopLeMoney)
            cout << "Vui long nhap so hop le!!!" << endl;
    } while (!hopLeMoney);

    cout << "Don vi tien te: ";
    do
    {
        cin >> iso;
        if (iso.size() != 3)
            cout << "Vui long nhap lai don vi tien te!!!" << endl;
    } while (iso.size() != 3);

    User tmp2(id, "123456", name, money, iso);
    addNode(l, getNode(tmp2));
    cout << "Tao tai khoan thanh cong! Xin chao " << name << endl;
    system("pause");
    return;
}

void xoaTaiKhoan(List &l)
{
    system("cls");
    cout << "\t\t\t  <<>> XOA TAI KHOAN <<>> " << endl;

    string id;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "Nhap ID tai khoan can xoa (Nhap exit de quay lai Menu)." << endl;
    do
    {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT")
        {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14)
            cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    SetConsoleTextAttribute(h, 13);
    Node *p = l._pHead;

    if (p != NULL && id == p->value.getID())
    {
        cout << "Xoa tai khoan thanh cong!" << endl;
        cout << "Da xoa " << p->value.getName() << " ra khoi he thong." << endl;
        remove(("data/" + p->value.getID() + ".txt").c_str());
        remove(("data/LichSu" + p->value.getID() + ".txt").c_str());
        l._pHead = p->_pNext;
        if (l._pHead == NULL)
            l._pTail = NULL;
        delete p;
        system("pause");
        return;
    }

    while (p != NULL && p->_pNext != NULL)
    {
        if (id == p->_pNext->value.getID())
        {
            cout << "Xoa tai khoan thanh cong!" << endl;
            cout << "Da xoa " << p->_pNext->value.getName() << " ra khoi he thong." << endl;
            remove(("data/" + p->_pNext->value.getID() + ".txt").c_str());
            remove(("data/LichSu" + p->_pNext->value.getID() + ".txt").c_str());
            Node *tmp = p->_pNext;
            p->_pNext = p->_pNext->_pNext;
            if (p->_pNext == NULL)
                l._pTail = p;
            delete tmp;
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

void moKhoaTaiKhoan(List &l)
{
    system("cls");
    cout << "\t\t\t  <<>> MO KHOA TAI KHOAN <<>> " << endl;
    string id;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    Node *p = l._pHead;
    SetConsoleTextAttribute(h, 10);
    cout << "Nhap ID tai khoan can mo khoa (nhap exit de quay lai Menu)." << endl;
    do
    {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT")
        {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14)
            cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);
    SetConsoleTextAttribute(h, 10);

    while (p != NULL)
    {
        if (id == p->value.getID())
        {
            if (p->value.getKhoa() == false)
            {
                SetConsoleTextAttribute(h, 10);
                cout << "Tai khoan van dang duoc hoat dong binh thuong." << endl;
                system("pause");
                return;
            }
            else
            {
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

bool dangNhapAdmin(AdminList &l)
{
    string user, pass;
    char ast = ' ';
    int aste = 0;
    int dem = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "\t\t\tDANG NHAP ADMIN" << endl;
    SetConsoleTextAttribute(h, 2);
    cout << "User: ";
    cin >> user;
    AdminNode *pAdmin = l._pHead;
    while (pAdmin != NULL)
    {
        if (pAdmin->value.user == user)
        {
            do
            {
                if (dem == 3)
                {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Ban da nhap sai qua qua nhieu lan, vui long thu lai trong giay lat." << endl;
                    system("pause");
                    return false;
                }
                pass = "";

                SetConsoleTextAttribute(h, 2);
                cout << "Pass: ";
                do
                {
                    ast = _getch();
                    if (ast == 13)
                    {
                        break;
                    }
                    if (ast == 8 || ast == 127)
                    {
                        if (pass.size() != 0)
                        {
                            cout << "\b \b";
                            pass.erase(pass.size() - 1);
                            aste--;
                        }
                    }
                    else
                    {
                        pass += ast;
                        cout << "*";
                        aste++;
                    }
                } while (ast != 13);
                cout << endl;

                if (pAdmin->value.pass == pass)
                {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Dang nhap Admin thanh cong, xin chao " << user << "." << endl;
                    system("pause");
                    return true;
                }

                if (pAdmin->value.pass != pass)
                {
                    SetConsoleTextAttribute(h, 13);
                    cout << "Mat khau nhap sai, vui long nhap lai." << endl;
                    dem++;
                }

            } while (pAdmin->value.pass != pass);
        }
        pAdmin = pAdmin->_pNext;
    }
    SetConsoleTextAttribute(h, 13);
    cout << "Dang nhap that bai, tai khoan hoac mat khau cua ban nhap sai." << endl;
    system("pause");
    return false;
}

void MenuAdmin()
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 3);
    cout << "******************MENU***************" << endl;
    cout << "\t1. Xem danh sach tai khoan\t\t" << endl;
    cout << "\t2. Them tai khoan         \t\t" << endl;
    cout << "\t3. Xoa tai khoan          \t\t" << endl;
    cout << "\t4. Mo khoa tai khoan      \t\t" << endl;
    cout << "\t5. Thoat                  \t\t" << endl;
    cout << "**************************************" << endl;
}
void xemThongTin(User &A)
{
    system("cls");
    cout << "\t\t\t  <<>> THONG TIN TAI KHOAN <<>> " << endl;
    cout << A;
    system("pause");
    return;
}

void maPinSao(string &pin)
{
    char ast = ' ';
    int aste = 0;
    pin = "";
    do
    {
        ast = _getch();
        if (ast == 13)
        {
            break;
        }
        if (ast == 8 || ast == 127)
        {
            if (pin.size() != 0)
            {
                cout << "\b \b";
                pin.erase(pin.size() - 1);
                aste--;
            }
        }
        else
        {
            pin += ast;
            cout << "*";
            aste++;
        }
    } while (ast != 13);
}

void doiMaPin(User &A)
{
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
    do
    {
        cout << "PIN: ";
        maPinSao(pin);
        if (pin == "0")
        {
            cout << "\nQuay lai Menu." << endl;
            system("pause");
            return;
        }
        cout << endl;
        SetConsoleTextAttribute(h, 13);
        if (pin != A.getPIN())
            cout << "Ma PIN nhap sai, vui long nhap lai." << endl;
    } while (pin != A.getPIN());

    if (pin == A.getPIN())
    {
        do
        {
            SetConsoleTextAttribute(h, 2);
            cout << "Nhap Ma PIN moi: ";
            do
            {
                maPinSao(pinnew1);
                cout << endl;
                if (pinnew1.size() != 6)
                    cout << "Ma PIN phai co 6 chu so, vui long nhap lai: " << endl;
            } while (pinnew1.size() != 6);
            cout << "Xac nhan lai ma PIN moi: ";
            do
            {
                maPinSao(pinnew2);
                cout << endl;
                if (pinnew2.size() != 6)
                    cout << "Ma PIN phai co 6 chu so, vui long nhap lai: " << endl;
            } while (pinnew2.size() != 6);

            if (pinnew1 != pinnew2)
                cout << "Ma PIN moi khong khop nhau, vui long nhap lai ma PIN moi." << endl;
        } while (pinnew1 != pinnew2);

        if (pinnew1 == pinnew2)
        {
            A.setPIN(pinnew2);
            SetConsoleTextAttribute(h, 13);
            cout << "Doi ma PIN thanh cong!" << endl;
            system("pause");
            return;
        }
    }
}

Node *dangNhapUser(List &l)
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, 10);
    cout << "\n\t\t\tDANG NHAP USER\n"
         << endl;

    string id, pin;
    SetConsoleTextAttribute(h, 2);
    cout << "ID: ";
    cin >> id;

    Node *p = l._pHead;
    while (p != NULL)
    {
        if (p->value.getID() == id)
        {
            if (p->value.getKhoa())
            {
                cout << "Tai khoan bi khoa. Lien he Admin.\n";
                cout << "Bam Enter de quay lai menu...";
                cin.ignore();
                cin.get();
                return NULL;
            }

            int soLanSai = 0;
            const int MAX_LAN_SAI = 3;

            while (soLanSai < MAX_LAN_SAI)
            {
                cout << "Nhap ma PIN: ";
                maPinSao(pin);
                cout << endl;

                if (pin == p->value.getPIN())
                {
                    if (p->value.isFirstLogin() && pin == "123456")
                    {
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
                else
                {
                    soLanSai++;
                    if (soLanSai < MAX_LAN_SAI)
                    {
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
    system("pause");
    return NULL;
}

void MenuUser(User A)
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << "***************MENU***************" << endl;
    cout << "\t1. Xem thong tin tai khoan  \t\t" << endl;
    cout << "\t2. Rut tien                 \t\t" << endl;
    cout << "\t3. Chuyen tien              \t\t" << endl;
    cout << "\t4. Xem noi dung giao dich   \t\t" << endl;
    cout << "\t5. Doi ma Pin               \t\t" << endl;
    cout << "\t6. Thoat                    \t\t" << endl;
    cout << "**********************************" << endl;
}

void MenuSanh()
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    cout << "********WELCOME TO BANK**********" << endl;
    cout << "-------- Admin or User -----------" << endl;
    cout << "\t 1. Admin\t\t\t" << endl;
    cout << "\t 2. User\t\t\t" << endl;
    cout << "\t 3. Exit\t\t\t  " << endl;
    cout << "**********************************" << endl;
}

void giaoDich(User &A, char ct, unsigned long tien, string loai, string thongdiep = "")
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string nam = to_string(1900 + ltm->tm_year);
    string thang = to_string(1 + ltm->tm_mon);
    string ngay = to_string(ltm->tm_mday);
    string gio = to_string(ltm->tm_hour);
    string phut = to_string(ltm->tm_min);
    string giay = to_string(ltm->tm_sec);

    GiaoDich gd;
    gd.tien = ct + to_string(tien);
    gd.loai = loai;
    gd.thoiGian = ngay + "/" + thang + "/" + nam + " " + gio + ":" + phut + ":" + giay;
    gd.thongDiep = thongdiep;

    A.lichSu.push(gd);
}

void rutTien(User &A)
{
    system("cls");
    cout << "\t\t\t  <<>> RUT TIEN <<>> " << endl;
    char tmp;
    unsigned long rut, tong = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    cout << "So du hien co trong tai khoan cua ban: " << A.getMoney() << " VND." << endl;
    do
    {
        if (A.getMoney() < 50000)
        {
            cout << "Ban khong du tien de thuc hien, vui long nap them.";
            system("pause");
            return;
        }
        SetConsoleTextAttribute(h, 2);
        cout << "Vui long chon so tien de rut (>= 50.000 va phai la boi so cua 50.000)."
             << endl
             << "(hoac nhap 0 de quay lai Menu va huy tat ca giao dich) VND: ";
        bool hopLeRut;
        do
        {
            hopLeRut = nhapSoKhongDauAnToan(rut);
            if (!hopLeRut)
            {
                cout << "So tien rut phai lon hon hoac bang 50.000 va la boi so cua 50.000 de rut, vui long nhap lai.";
                continue;
            }
            if (rut == 0)
            {
                cout << "Quay lai Menu" << endl;
                system("pause");
                return;
            }
            if (rut < 50000 || rut % 50000 != 0)
            {
                cout << "So tien rut phai lon hon hoac bang 50.000 va la boi so cua 50.000 de rut, vui long nhap lai.";
                hopLeRut = false;
            }
        } while (!hopLeRut);
        if (A.getMoney() - 50000 < tong + rut)
        {
            SetConsoleTextAttribute(h, 13);
            cout << "So du hien tai khong du, vui long nap them." << endl;
            system("pause");
            return;
        }
        SetConsoleTextAttribute(h, 2);
        tong = tong + rut;
        cout << "Ban co muon rut them? [Y/N]: ";
        cin >> tmp;
    } while (tmp == 'y' || tmp == 'Y');

    if (tmp == 'n' || tmp == 'N')
    {

        char xacNhan;
        cout << "Xac nhan giao dich? (Y/N): ";
        cin >> xacNhan;

        if (xacNhan == 'Y' || xacNhan == 'y')
        {
            A.setMoney(A.getMoney() - tong);
            giaoDich(A, '-', tong, "Rut Tien");

            SetConsoleTextAttribute(h, 13);
            cout << "Rut tien thanh cong! Ban vua moi rut: " << tong << " VND." << endl;
            cout << "So du con lai trong tai khoan: " << A.getMoney() << " VND." << endl;
        }
        else if (xacNhan == 'N' || xacNhan == 'n')
        {
            cout << "Da huy giao dich." << endl;
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "Lua chon khong hop le, da huy toan bo giao dich." << endl;
        }

        system("pause");
        return;
    }
    else
    {
        SetConsoleTextAttribute(h, 12);
        cout << "Lua chon khong hop le, da huy toan bo giao dich." << endl;
        system("pause");
        return;
    }
}

void xemLichSugiaoDich(User A)
{
    system("cls");
    cout << "\t\t\t  <<>> LICH SU GIAO DICH <<>> " << endl;
    stack<GiaoDich> lichSu = A.lichSu;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 13);
    if (lichSu.empty())
    {
        cout << "Tai khoan cua ban chua co thuc hien cuoc giao dich nao trong hom nay." << endl;
        system("pause");
        return;
    }
    while (!lichSu.empty())
    {
        GiaoDich gd = lichSu.top();
        lichSu.pop();

        cout << left << setw(25) << "So ID:" << A.getID() << endl;
        cout << left << setw(25) << "Ngay giao dich:" << gd.thoiGian << endl;
        cout << left << setw(25) << "Loai giao dich:" << gd.loai << endl;
        cout << left << setw(25) << "So tien giao dich:" << gd.tien << endl;
        cout << left << setw(25) << "So du hien tai:" << A.getMoney() << endl;

        if (gd.thongDiep != "")
            cout << left << setw(25) << "Thong diep:" << gd.thongDiep << endl;

        cout << endl;
    }
    system("pause");
    return;
}

void chuyenTien(User &A, List &l)
{
    system("cls");
    cout << "\t\t\t  <<>> CHUYEN TIEN <<>> " << endl;
    string id;
    unsigned long chuyen;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);

    cout << "Nhap ID tai khoan can chuyen den (nhap exit de quay lai Menu)." << endl;
    do
    {
        SetConsoleTextAttribute(h, 2);
        cout << "ID: ";
        cin >> id;
        SetConsoleTextAttribute(h, 13);
        if (id == "exit" || id == "EXIT")
        {
            cout << "Quay lai Menu" << endl;
            system("pause");
            return;
        }
        if (id.size() != 14)
            cout << "ID can phai co du 14 chu so, vui long nhap lai" << endl;
    } while (id.size() != 14);

    Node *p = l._pHead;
    while (p != NULL)
    {
        if (id == p->value.getID())
        {
            SetConsoleTextAttribute(h, 13);

            if (p->value.getID() == A.getID())
            {
                cout << "Chuyen khoan that bai, ID chuyen tien khong the trung voi ID chuyen toi!" << endl;
                system("pause");
                return;
            }

            if (p->value.getKhoa() == true)
            {
                cout << "Tai khoan dich dang bi khoa, khong the chuyen tien!" << endl;
                system("pause");
                return;
            }

            cout << "Da tim thay ID!" << endl;
            cout << "Ten nguoi nhan: " << p->value.getName() << endl;
            cout << "So du hien co trong tai khoan cua ban: " << A.getMoney() << "VND." << endl;

            if (A.getMoney() < 50000)
            {
                cout << "Ban khong du tien de thuc hien, vui long nap them." << endl;
                system("pause");
                return;
            }

            SetConsoleTextAttribute(h, 2);
            cout << "Vui long cho so tien de chuyen(>= 50.000 va phai la boi so cua 50.000)"
                 << endl
                 << "(hoac nhap 0 de quay lai Menu va huy tat ca giao dich) VND: ";

            bool hopLeChuyen;
            do
            {
                hopLeChuyen = nhapSoKhongDauAnToan(chuyen);
                if (!hopLeChuyen)
                {
                    cout << "So tien phai lon hon hoac bang 50.000 va la boi so cua 50.000, vui long nhap lai: ";
                    continue;
                }
                if (chuyen == 0)
                {
                    cout << "Quay lai Menu" << endl;
                    system("pause");
                    return;
                }
                if (chuyen < 50000 || chuyen % 50000 != 0)
                {
                    cout << "So tien phai lon hon hoac bang 50.000 va la boi so cua 50.000, vui long nhap lai: ";
                    hopLeChuyen = false;
                }
            } while (!hopLeChuyen);

            if (A.getMoney() - 50000 < chuyen)
            {
                cout << "So du hien tai khong du, vui long nap them.";
                system("pause");
                return;
            }
            char xacNhan;
            cout << "Xac nhan giao dich? (Y/N): ";
            cin >> xacNhan;

            if (xacNhan != 'Y' && xacNhan != 'y')
            {
                cout << "Da huy giao dich." << endl;
                system("pause");
                return;
            }
            A.setMoney(A.getMoney() - chuyen);
            p->value.setMoney(p->value.getMoney() + chuyen);

            string thongdiep;
            SetConsoleTextAttribute(h, 2);
            cout << "Thong diep muon gui: ";
            cin.ignore();
            getline(cin, thongdiep);

            giaoDich(A, '-', chuyen, "Chuyen Tien toi ID " + p->value.getID() + " (" + p->value.getName() + ")", thongdiep);
            giaoDich(p->value, '+', chuyen, "Nhan tien tu ID " + A.getID() + " (" + A.getName() + ")", thongdiep);

            SetConsoleTextAttribute(h, 13);
            cout << "Chuyen tien thanh cong! Ban vua moi chuyen: " << chuyen << "VND cho " << p->value.getName() << endl;
            cout << "So du con lai trong tai khoan: " << A.getMoney() << endl;
            system("pause");
            return;
        }
        p = p->_pNext;
    }

    SetConsoleTextAttribute(h, 13);
    cout << "Chuyen khoan that bai, ID can chuyen khong ton tai!" << endl;
    system("pause");
    return;
}

void capNhatFileTheTu(List &l)
{
    ofstream out1("TheTu.txt");
    Node *p = l._pHead;
    while (p != NULL)
    {
        out1 << p->value.getID() << endl;
        out1 << p->value.getPIN() << endl;
        if (p->value.getKhoa() == false)
            out1 << "0" << endl;
        if (p->value.getKhoa() == true)
            out1 << "1" << endl;
        p = p->_pNext;
    }
}

void capNhatFileID(List &l)
{
    Node *p = l._pHead;
    while (p != NULL)
    {
        ofstream out3("data/" + p->value.getID() + ".txt");
        out3 << p->value.getID() << endl;
        out3 << p->value.getName() << endl;
        out3 << p->value.getMoney() << endl;
        out3 << p->value.getISO() << endl;
        out3.close();
        p = p->_pNext;
    }
}

void capNhatFileLichSu(List &l)
{
    Node *p = l._pHead;
    while (p != NULL)
    {
        ofstream out2("data/LichSu" + p->value.getID() + ".txt");
        stack<GiaoDich> lichSu = p->value.lichSu;
        stack<GiaoDich> temp;
        while (!lichSu.empty())
        {
            temp.push(lichSu.top());
            lichSu.pop();
        }
        while (!temp.empty())
        {
            GiaoDich gd = temp.top();
            temp.pop();

            out2 << p->value.getID() << endl;
            out2 << gd.thoiGian << endl;
            out2 << gd.loai;
            if (gd.thongDiep != "")
                out2 << " voi thong diep: " << gd.thongDiep;
            out2 << endl;
            out2 << gd.tien << endl;
        }
        out2.close();
        p = p->_pNext;
    }
}

int main()
{
    AdminList DSAdmin;
    List DSKhachHang;

    std::filesystem::create_directory("data");
    ifstream in1("Admin.txt");
    string user, pass;
    while (in1 >> user && in1 >> pass)
    {
        Admin a;
        a.user = user;
        a.pass = pass;
        addAdminNode(DSAdmin, getAdminNode(a));
    }
    in1.close();

    ifstream in3("TheTu.txt");
    string id, pin, khoa;
    while (in3 >> id)
    {
        in3 >> pin;
        in3 >> khoa;
        if (pin == "")
            pin = "123456";

        string name = "Null";
        unsigned long money = 0;
        string iso = "VND";

        ifstream in2("data/" + id + ".txt");
        if (in2.is_open())
        {
            string dummyID;
            getline(in2, dummyID);
            getline(in2, name);
            in2 >> money;
            in2 >> iso;
            in2.close();
        }
        else
        {
            cout << "[CANH BAO] Khong tim thay file " << id << ".txt, du lieu tai khoan nay se duoc khoi tao mac dinh." << endl;
        }

        User tmp(id, pin, name, money, iso);
        if (khoa == "1")
            tmp.setKhoa(true);
        if (khoa == "0")
            tmp.setKhoa(false);
        addNode(DSKhachHang, getNode(tmp));

        ifstream in4("data/LichSu" + id + ".txt");
        string lsid;
        while (in4 >> lsid)
        {
            string tg, loai, tien, thongdiep = "";
            in4.ignore();
            getline(in4, tg);
            getline(in4, loai);
            in4 >> tien;

            const string marker = " voi thong diep: ";
            size_t pos = loai.find(marker);
            if (pos != string::npos)
            {
                thongdiep = loai.substr(pos + marker.length());
                loai.erase(pos);
            }
            GiaoDich gd;
            gd.thoiGian = tg;
            gd.loai = loai;
            gd.tien = tien;
            gd.thongDiep = thongdiep;

            Node *p = DSKhachHang._pHead;
            while (p != NULL)
            {
                if (p->value.getID() == lsid)
                {
                    p->value.lichSu.push(gd);
                }
                p = p->_pNext;
            }
        }
        in4.close();
    }
    in3.close();

    capNhatFileID(DSKhachHang);
    capNhatFileTheTu(DSKhachHang);
    capNhatFileLichSu(DSKhachHang);

    while (true)
    {
        MenuSanh();
        int tmp;
        string chon;
        bool MenuA = true;
        bool MenuU = true;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 2);
        do
        {
            cout << "Vui long chon: ";
            if (!(cin >> chon))
                exit(0);
            if (chon != "1" && chon != "2" && chon != "3")
                cout << "Ban da chon sai, vui long chon lai." << endl;
        } while (chon != "1" && chon != "2" && chon != "3");
        tmp = stoi(chon);
        switch (tmp)
        {
        case 1:
        {
            if (dangNhapAdmin(DSAdmin) == true)
            {
                do
                {
                    MenuAdmin();
                    int tmp1;
                    do
                    {
                        cout << "Vui long chon: ";
                        if (!(cin >> chon))
                            exit(0);
                        if (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5")
                            cout << "Ban da chon sai, vui long chon lai." << endl;
                    } while (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5");
                    tmp1 = stoi(chon);
                    switch (tmp1)
                    {
                    case 1:
                    {
                        xemDanhSachTaiKhoan(DSKhachHang);
                        break;
                    }
                    case 2:
                    {
                        themTaiKhoan(DSKhachHang);
                        capNhatFileID(DSKhachHang);
                        capNhatFileTheTu(DSKhachHang);
                        capNhatFileLichSu(DSKhachHang);
                        break;
                    }
                    case 3:
                    {
                        xoaTaiKhoan(DSKhachHang);
                        capNhatFileID(DSKhachHang);
                        capNhatFileTheTu(DSKhachHang);
                        break;
                    }
                    case 4:
                    {
                        moKhoaTaiKhoan(DSKhachHang);
                        capNhatFileID(DSKhachHang);
                        capNhatFileTheTu(DSKhachHang);

                        break;
                    }
                    case 5:
                    {
                        MenuA = false;
                        break;
                    }
                    }
                } while (MenuA == true);
            }
            break;
        }
        case 2:
        {
            Node *p = dangNhapUser(DSKhachHang);
            capNhatFileTheTu(DSKhachHang);
            capNhatFileID(DSKhachHang);
            if (p != NULL)
            {
                do
                {
                    MenuUser(p->value);
                    int tmp2;
                    do
                    {
                        cout << "Vui long chon: ";
                        if (!(cin >> chon))
                            exit(0);
                        if (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5" && chon != "6")
                            cout << "Ban da chon sai, vui long chon lai." << endl;
                    } while (chon != "1" && chon != "2" && chon != "3" && chon != "4" && chon != "5" && chon != "6");
                    tmp2 = stoi(chon);
                    switch (tmp2)
                    {
                    case 1:
                    {
                        xemThongTin(p->value);
                        break;
                    }
                    case 2:
                    {
                        rutTien(p->value);
                        capNhatFileID(DSKhachHang);
                        capNhatFileTheTu(DSKhachHang);
                        capNhatFileLichSu(DSKhachHang);
                        break;
                    }
                    case 3:
                    {
                        chuyenTien(p->value, DSKhachHang);
                        capNhatFileID(DSKhachHang);
                        capNhatFileTheTu(DSKhachHang);
                        capNhatFileLichSu(DSKhachHang);
                        break;
                    }
                    case 4:
                    {
                        xemLichSugiaoDich(p->value);
                        break;
                    }
                    case 5:
                    {
                        doiMaPin(p->value);
                        capNhatFileID(DSKhachHang);
                        capNhatFileTheTu(DSKhachHang);
                        break;
                    }
                    case 6:
                    {
                        MenuU = false;
                        break;
                    }
                    }
                } while (MenuU == true);
            }
            break;
        }
        case 3:
        {
            return 0;
        }
        }
    }

    return 0;
}
