#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<map>
#include<windows.h>
using namespace std;
class NHANVIEN
{
private:
    string ten;
    string ngaytruc;
    static int siso;
public:
    string getTen() {return ten;}
    string getNgaytruc() {return ngaytruc;}
    void setTen(string ten) {this->ten = ten;}
    void setNgaytruc(string ngaytruc) {this->ngaytruc = ngaytruc;}
    static int getSiso() {return siso;}
};
int NHANVIEN::siso = 5;
class SANPHAM
{
private:
    string ten;
    int giavon, giaban;
    int slton;
    int msp;
    int km;
    static int tongvon, tongban;
public:
    string getTen() {return ten;}
    void setTen(string ten) {this->ten = ten;}
    int getGiavon() {return giavon;}
    void setGiavon(float giavon) {this->giavon = giavon;}
    int getGiaban() {return giaban;}
    void setGiaban(float giaban) {this->giaban = giaban;}
    int getSlton() {return slton;}
    void setSlton(int slton) {this->slton = slton;}
    int getMsp() {return msp;}
    void setMsp(int msp) {this->msp = msp;}
    int getKm() {return km;}
    void setKm(int km) {this->km = km;}
    static void addTongvon(int x) {tongvon += x;}
    static void addTongban(int y) {tongban += y;}
    static int getTongvon() {return tongvon;}
    static int getTongban() {return tongban;}
};
int SANPHAM::tongvon = 0;
int SANPHAM::tongban = 0;
void quanly(vector<SANPHAM> &, map<int,int> &, vector<NHANVIEN> &, map<int,int> &, string &);
void nhanvien(vector<SANPHAM> &, map<int,int> &, vector<NHANVIEN> &, map<int,int> &, string &);
void sudung(vector<SANPHAM> &, map<int,int> &, vector<NHANVIEN> &, map<int,int> &, string &);
void filedata(vector<SANPHAM> &sp, map<int,int> &ktsp)
{
    fstream fin;
    fin.open("danhmucsanpham.txt",ios::in);
    SANPHAM tmp;
    string ten;
    int msp;
    int giavon, giaban;
    int slton;
    float km;
    //if(!fin.is_open()) cout << -1;
    for(int i = 1; i <= 5; i ++)
        getline(fin,ten,',');
    getline(fin,ten);
    int t = 0;
    while(fin.peek()!=EOF)
    {
        fin >> msp; fin.ignore();
        getline(fin,ten,',');
        fin >> giavon; fin.ignore();
        fin >> giaban; fin.ignore();
        fin >> slton; fin.ignore();
        fin >> km;
        tmp.setMsp(msp);
        tmp.setTen(ten);
        tmp.setGiavon(giavon);
        tmp.setGiaban(giaban);
        tmp.setSlton(slton);
        tmp.setKm(km); fin.ignore();
        sp.push_back(tmp);
        ktsp.insert(make_pair(msp,t));
        t++;
    }
    fin.close();
}
void filedata1(vector<NHANVIEN> &nv)
{
    fstream fin;
    fin.open("nhanvien.txt",ios::in);
    NHANVIEN tmp;
    string ten, ngaytruc;
    getline(fin,ten,',');
    getline(fin,ngaytruc);
    while(fin.peek()!= EOF)
    {
        getline(fin,ten,',');
        getline(fin,ngaytruc);
        tmp.setTen(ten);
        tmp.setNgaytruc(ngaytruc);
        nv.push_back(tmp);
    }
    fin.close();
}
void filedata2(string &pw)
{
    fstream fin;
    fin.open("thongtinchung.txt",ios::in);
    fin >> pw;
    int tv, tb;
    fin >> tv >> tb;
    SANPHAM::addTongvon(tv);
    SANPHAM::addTongban(tb);
    fin.close();
}
void update(vector<SANPHAM> &sp, map<int,int> ktsp)
{
    map<int,int>::iterator it;
    fstream fout;
    fout.open("tmp_danhmucsanpham.txt",ios::out);
    fout << "Ma san pham,Ten san pham,Gia von,Gia ban,So luong,Khuyen mai";
    for(it = ktsp.begin(); it != ktsp.end(); it ++)
    {
        fout << endl;
        int index = it->second;
        fout << sp[index].getMsp() << "," << sp[index].getTen() << "," << sp[index].getGiavon()
             << "," << sp[index].getGiaban() << "," << sp[index].getSlton() << "," << sp[index].getKm() << "%";
    }
    fout.close();
    remove("danhmucsanpham.txt");
    rename("tmp_danhmucsanpham.txt", "danhmucsanpham.txt");
    sp.clear();
}
void update1(vector<NHANVIEN> &nv)
{
    fstream fout;
    fout.open("tmp_nhanvien.txt",ios::out);
    fout << "Ho va ten,Ngay truc";
    for(int i = 0; i < NHANVIEN::getSiso(); i ++)
    {
            fout << endl;
            fout << nv[i].getTen() << "," << nv[i].getNgaytruc();
    }
    fout.close();
    remove("nhanvien.txt");
    rename("tmp_nhanvien.txt","nhanvien.txt");
    nv.clear();
}
void update2(vector<SANPHAM> sp, map<int,int> ktsp, map<int,int> &bh)
{
    fstream fout;
    fout.open("tmp_hoadon.txt",ios::out);
    fout << left;
    fout << "______________________________________________________________________" << endl;
    fout << "|" << setw(30) << "Ten san pham";
    fout << "|" << setw(10) << "So luong";
    fout << "|" << setw(10) << "Don gia";
    fout << "|" << setw(15) << "Thanh tien";
    fout << "|" << endl;
    fout << "______________________________________________________________________" << endl;
    map<int,int>::iterator it;
    int tongtien = 0;
    for(it = bh.begin(); it != bh.end(); it ++)
    {
    int pos = ktsp[it->first];
    int gb = sp[pos].getGiaban();
    gb = gb - gb * sp[pos].getKm() / 100;
    fout << "|" << setw(30) << sp[pos].getTen();
    fout << "|" << setw(10) << it->second;
    fout << "|" << setw(10) << gb;
    fout << "|" << setw(15) << gb * it->second;
    fout << "|" << endl;
    tongtien += gb * it->second;
    }
    fout << "|" << setw(30) << "";
    fout << "|" << setw(10) << "";
    fout << "|" << setw(10) << "";
    fout << "|";
    fout << "Tong : " << setw(8) << tongtien;
    fout << "|" << endl;
    fout << "______________________________________________________________________";
    fout.close();
    remove("hoadon.txt");
    rename("tmp_hoadon.txt","hoadon.txt");
    bh.clear();
}
void update3(string pw)
{
    fstream fout;
    fout.open("tmp_thongtinchung.txt",ios::out);
    fout << pw << endl;
    fout << SANPHAM::getTongvon() << endl;
    fout << SANPHAM::getTongban();
    fout.close();
    remove("thongtinchung.txt");
    rename("tmp_thongtinchung.txt","thongtinchung.txt");
}
void xuatSanpham(vector<SANPHAM> sp)
{
    cout << "_______________________________________________________________________________" << endl;
    cout << left;
    cout << "|";
    cout << setw(3) << "MSP";
    cout << "|";
    cout << setw(30) << "Ten san pham";
    cout << "|";
    cout << setw(10) << "Gia von";
    cout << "|";
    cout << setw(10) << "Gia ban";
    cout << "|";
    cout << setw(9) << "So luong";
    cout << "|";
    cout << setw(10) << "Khuyen mai";
    cout << "|"<< endl;
    cout << "_______________________________________________________________________________" << endl;
    for(int i = 0; i < sp.size(); i ++)
    {
    cout << left;
    cout << "|" << setw(3) << sp[i].getMsp();
    cout << "|" << setw(30) << sp[i].getTen();
    cout << "|" << setw(10) << sp[i].getGiavon();
    cout << "|" << setw(10) << sp[i].getGiaban();
    cout << "|" << setw(9) << sp[i].getSlton();
    cout << "|" << setw(10) << sp[i].getKm();
    cout << "|" << endl;
    }
    cout << "_______________________________________________________________________________" << endl;
}
void xuatNhanvien(vector<NHANVIEN> nv)
{
    cout << "_________________________________" << endl;
    cout << left;
    cout << "|" << setw(20) << "Ho va ten";
    cout << "|" << setw(10) << "Ngay truc";
    cout << "|" << endl;
    cout << "_________________________________" << endl;
    for(int i = 0; i < NHANVIEN::getSiso(); i++)
    {
    cout << left;
    cout << "|" << setw(20) << nv[i].getTen();
    cout << "|" << setw(10) << nv[i].getNgaytruc();
    cout << "|" << endl;
    }
    cout << "_________________________________" << endl;
}
int findSanpham(vector<SANPHAM> sp, string ten)
{
    for(int i = 0; i < sp.size(); i ++)
    {
        if(sp[i].getTen() == ten) return i;
    }
    return -1;
}
int findNhanvien(vector<NHANVIEN> nv, string ten)
{
    for(int i = 0; i < NHANVIEN::getSiso(); i ++)
    {
        if(nv[i].getTen() == ten) return i;
    }
    return -1;
}
void addSanpham(vector<SANPHAM> &sp, map<int,int> &ktsp)
{
    cout << "Nhap so luong cac san pham muon them : ";
    int num;
    cin >> num;
    for(int i = 1; i <= num; i ++)
    {
        cin.ignore();
        string ten;
        float giavon, giaban;
        int sl;
        float km;
        SANPHAM tmp;
        cout << "Them san pham thu " << i << ":" << endl;
        cout << "Nhap ten san pham muon them : ";
        getline(cin,ten);
        tmp.setTen(ten);
        cout << "Nhap gia von : ";
        cin >> giavon;
        tmp.setGiavon(giavon);
        cout << "Nhap gia ban : ";
        cin >> giaban;
        tmp.setGiaban(giaban);
        cout << "Nhap so luong them : ";
        cin >> sl;
        tmp.setSlton(sl);
        cout << "Nhap khuyen mai : ";
        cin >> km;
        tmp.setKm(km);
        int kt = findSanpham(sp, ten);
        if(kt != -1)
        {
            tmp.setMsp(sp[kt].getMsp());
            tmp.setSlton(sp[kt].getSlton() + tmp.getSlton());
            sp[kt] = tmp;
        }
        else
        {
            map<int,int>::iterator it;
            it = ktsp.end();
            it --;
            tmp.setMsp(it->first + 1);
            sp.push_back(tmp);
            ktsp.insert(make_pair(it->first + 1,sp.size() - 1));
        }
    }
    cout << "-->Them thanh cong!" << endl;
    update(sp, ktsp);
    filedata(sp, ktsp);
}
void eraseSanpham(vector<SANPHAM> &sp, map<int,int> &ktsp)
{
    cout << "Nhap so luong cac san pham muon xoa bo : ";
    int num;
    cin >> num;
    for(int i = 1; i <= num; i ++)
    {
        cout << "Xoa san pham thu " << i << ":" << endl;
        cout << "Nhap ma san cua san pham muon xoa : ";
        int msp;
        cin >> msp;
        ktsp.erase(msp);
    }
    cout << "-->Xoa thanh cong!" << endl;
    update(sp, ktsp);
    filedata(sp, ktsp);
}
void dienNgaytruc(vector<NHANVIEN> &nv)
{
    cout << "Nhap so luong nhan vien muon thiet lap ngay truc : ";
    int num;
    cin >> num;
    for(int i = 1; i <= num; i ++)
    {
        cin.ignore();
        string ten, ngaytruc;
        while(1){
        cout << "Nhap ten nhan vien muon thiet lap : ";
        getline(cin,ten);
        int pos;
        pos = findNhanvien(nv,ten);
        if(pos != -1)
        {
            cout << "Nhap ngay truc : ";
            cin >> ngaytruc;
            nv[pos].setNgaytruc(ngaytruc);
            break;
        }
        else cout << "-->Ten nhan vien khong ton tai, vui long nhap lai." << endl;
        }
    }
    cout << "-->Thiet lap thanh cong!" << endl;
    update1(nv);
    filedata1(nv);
}
void banhang(map<int,int> &bh)
{
    cout << "Nhap so luong san pham muon mua : ";
    int num;
    cin >> num;
    cout << "Nhap cac ma san pham : ";
    int msp;
    map<int,int>::iterator it;
    for(int i = 1; i <= num; i ++)
    {
        cin >> msp;
        it = bh.find(msp);
        if(it != bh.end())
        {
            bh[msp] ++;
        }
        else
            bh.insert(make_pair(msp,1));
    }
}
void hienthiHoadon(vector<SANPHAM> sp, map<int,int> ktsp, map<int,int> bh)
{
    cout << left;
    cout << "______________________________________________________________________" << endl;
    cout << "|" << setw(30) << "Ten san pham";
    cout << "|" << setw(10) << "So luong";
    cout << "|" << setw(10) << "Don gia";
    cout << "|" << setw(15) << "Thanh tien";
    cout << "|" << endl;
    cout << "______________________________________________________________________" << endl;
    map<int,int>::iterator it;
    int tongtien = 0;
    for(it = bh.begin(); it != bh.end(); it ++)
    {
    int pos = ktsp[it->first];
    int gb = sp[pos].getGiaban();
    gb = gb - gb * sp[pos].getKm() / 100;
    cout << "|" << setw(30) << sp[pos].getTen();
    cout << "|" << setw(10) << it->second;
    cout << "|" << setw(10) << gb;
    cout << "|" << setw(15) << gb * it->second;
    cout << "|" << endl;
    tongtien += gb * it->second;
    SANPHAM::addTongvon(sp[pos].getGiavon() * it->second);
    }
    SANPHAM::addTongban(tongtien);
    cout << "|" << setw(30) << "";
    cout << "|" << setw(10) << "";
    cout << "|" << setw(10) << "";
    cout << "|";
    cout << "Tong : " << setw(8) << tongtien;
    cout << "|" << endl;
    cout << "______________________________________________________________________" << endl;
    cout << "Ban co muon in hoa don : " << endl;
    int tmp;
    cout << "1.Co" << endl;
    cout << "2.Khong" << endl;
    cout << "Nhap lua chon : ";
    cin >> tmp;
    if(tmp == 1) cout << "-->In thanh cong!" << endl;
}
void xuatNgaytruc(vector<NHANVIEN> nv)
{
    string ten;
    cout << "Nhap ten nhan vien can tra cuu ngay truc : ";
    getline(cin,ten);
    int pos;
    pos = findNhanvien(nv,ten);
    if(pos != -1)
    {
         cout << "-->Thanh cong!" << endl;
         cout << ten << " truc ngay " << nv[pos].getNgaytruc() << endl;
    }
    else
    {
        cout << "-->Ten nhan vien khong ton tai, vui long nhap lai" << endl;
        xuatNgaytruc(nv);
    }
}
void changePassword(string &pw)
{
    cout << "Nhap mat khau cu : ";
    string tmp;
    cin >> tmp;
    if(tmp == pw)
    {
        while(1)
        {
            cout << "Nhap mat khau moi : ";
            string tmp1, tmp2;
            cin >> tmp1;
            cout << "Nhap lai mat khau moi : ";
            cin >> tmp2;
            if(tmp1 == tmp2)
            {
                pw = tmp1;
                cout << "-->Doi mat khau thanh cong!" << endl;
                break;
            }
            else
            {
                cout << "-->Mat khau khong trung khop, vui long nhap lai" << endl;
            }
        }
    }
    else
    {
        cout << "-->Mat khau khong chinh xac, vui long nhap lai." << endl;
        changePassword(pw);
    }
}
void quanly(vector<SANPHAM> &sp, map<int,int> &ktsp, vector<NHANVIEN> &nv, map<int,int> &bh, string &pw)
{
    system("cls");
    cout << "__________________________________________" << endl;
    cout << "Ban dang thuc hien voi tu cach quan ly." << endl;
    cout << "1.In cac san pham" << endl;
    cout << "2.Them/xoa san pham" << endl;
    cout << "3.In thong tin nhan vien" << endl;
    cout << "4.Dien thong tin ngay truc" << endl;
    cout << "5.In tong doanh so" << endl;
    cout << "6.Doi mat khau" << endl;
    cout << "7.Tro lai" << endl;
    cout << "8.Ket thuc chuong trinh" << endl;
    cout << "__________________________________________" << endl;
    cout << "Nhap lua chon : ";
    int lc;
    cin >> lc;
    switch(lc)
    {
    int lenh;
    case 1:
        system("cls");
        cout << "-->1.In cac san pham" << endl;
        xuatSanpham(sp);
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
        else exit(0);
        break;
    case 2:
        system("cls");
        cout << "-->2.Them/xoa san pham" << endl;
        cout << "__________________________" << endl;
        cout << "1.Xoa san pham" << endl;
        cout << "2.Them san pham" << endl;
        cout << "3.Tro lai"<< endl;
        cout << "__________________________" << endl;
        cout << "Nhap lua chon : ";
        cin >> lenh;
        if(lenh == 1){
            cout << "-->Xoa san pham" << endl;
            eraseSanpham(sp, ktsp);
            cout << "1.Tro lai" << endl;
            cout << "2.Ket thuc" << endl;
            cout << "Nhap lua chon : " << endl;
            cin >> lenh;
            if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
            else exit(0);
        }
        if(lenh == 2){
            cout << "-->Them san pham" << endl;
            addSanpham(sp, ktsp);
            cout << "___________________________" << endl;
            cout << "1.Tro lai" << endl;
            cout << "2.Ket thuc" << endl;
            cout << "___________________________" << endl;
            cout << "Nhap lua chon : " << endl;
            cin >> lenh;
            if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
            else exit(0);
            }
        if(lenh == 3) quanly(sp, ktsp, nv, bh, pw);
        break;
    case 3:
        system("cls");
        cout << "-->3.In thong tin nhan vien"<< endl;
        xuatNhanvien(nv);
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
        else exit(0);
        break;
    case 4:
        system("cls");
        cout << "-->4.Dien thong tin ngay truc" << endl;
        dienNgaytruc(nv);
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
        else exit(0);
        break;
    case 5:
        system("cls");
        cout << "-->5.In tong doanh so" << endl;
        cout << "Tong doanh so : "<< SANPHAM::getTongban() << endl;
        cout << "Lai : " << SANPHAM::getTongban() - SANPHAM::getTongvon() << endl;
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
        else exit(0);
        break;
    case 6:
        system("cls");
        cout << "-->6.Doi mat khau" << endl;
        changePassword(pw);
        update3(pw);
        filedata2(pw);
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) quanly(sp, ktsp, nv, bh, pw);
        else exit(0);
    case 7:
        system("cls");
        sudung(sp, ktsp, nv, bh, pw);
        break;
    case 8:
        exit(0);
        break;
    }
}
void nhanvien(vector<SANPHAM>&sp, map<int,int> &ktsp, vector<NHANVIEN> &nv, map<int,int> &bh, string &pw)
{
    system("cls");
    cout << "__________________________________________" << endl;
    cout << "Ban dang thuc hien voi tu cach nhan vien" << endl;
    cout << "1.Ban hang" << endl;
    cout << "2.Tra ngay truc" << endl;
    cout << "3.Tro lai" << endl;
    cout << "4.Ket thuc chuong trinh" << endl;
    cout << "__________________________________________" << endl;
    cout << "Nhap lua chon : ";
    int lc;
    cin >> lc;
    int lenh;
    cin.ignore();
    switch(lc)
    {
    case 1:
        system("cls");
        cout << "-->1.Ban hang" << endl;
        banhang(bh);
        hienthiHoadon(sp, ktsp, bh);
        update2(sp,ktsp,bh);
        update3(pw);
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) nhanvien(sp, ktsp, nv, bh, pw);
        else exit(0);
        break;
    case 2:
        system("cls");
        cout << "-->2.Tra ngay truc" << endl;
        xuatNgaytruc(nv);
        cout << "Nhap lua chon : " << endl;
        cout << "1.Tro lai" << endl;
        cout << "2.Ket thuc" << endl;
        cin >> lenh;
        if(lenh == 1) nhanvien(sp, ktsp, nv, bh, pw);
        else exit(0);
        break;
    case 3:
        system("cls");
        sudung(sp, ktsp, nv, bh, pw);
        break;
    case 4:
        exit(0);
        break;
    }
}
void sudung(vector<SANPHAM> &sp, map<int,int> &ktsp, vector<NHANVIEN> &nv, map<int,int> &bh, string &pw)
{
    cout << "______________________________" << endl;
    cout << "Vui long chon che do : " << endl;
    cout << "1.Quan ly" << endl;
    cout << "2.Nhan vien" << endl;
    cout << "______________________________" << endl;
    int cd;
    cin >> cd;
    if(cd == 1)
    {
        system("cls");
        cout << "-->1.Quan ly" << endl;
        string tmp;
        while(1)
        {
            cout << "-->Vui long nhap mat khau de vao che do quan ly : ";
            cin >> tmp;
            if(tmp == pw)
            {
                quanly(sp, ktsp, nv, bh, pw);
                break;
            }
            else cout << "-->Mat khau khong dung, vui long nhap lai." << endl;
        }
    }
    else
    {
        system("cls");
        cout << "-->2.Nhan vien" << endl;
        nhanvien(sp, ktsp, nv, bh, pw);
    }
}
int main()
{
    vector<SANPHAM> sp;
    vector<NHANVIEN> nv;
    map<int,int> ktsp;
    map<int,int> bh;
    string pw;
    filedata(sp,ktsp);
    filedata1(nv);
    filedata2(pw);
    sudung(sp, ktsp, nv, bh, pw);
}
