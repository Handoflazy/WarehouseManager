#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include<ctime>
#include<iomanip>
#include<fstream>
#pragma warning(disable : 4996)
using namespace std;
string chuanHoa(string s);
struct Date
{
	int day;
	int month;
	int year;

	Date(int _day = 1, int _m = 1, int _y = 1900) {
		day = _day;
		month = _m;
		year = _y;
	}
};

//Tao cau truc Hang Hoa:
struct Goods
{
	long long maMatHang;
	string tenMatHang;
	int donGia;
	int soLuong;
	string donViTinh;
	//Date hanSuDung;
	Goods* next;
	Goods() {
		this->maMatHang = -1;
		this->tenMatHang = "";
		this->soLuong = 0;
		this->donGia = 0;
		this->donViTinh = " ";
		next = NULL;
	}
	//MatHang(long long maMatHang, const char* tenMatHang, int soLuong, const char* donViTinh, int donGia) {
	//	this->maMatHang = maMatHang;
	//	this->tenMatHang = tenMatHang;
	//	this->soLuong = soLuong;
	//	this->donGia = donGia;
	//	this->donViTinh = donViTinh;
	//	next = NULL;
	//}
	Goods(long maMatHang, string tenMatHang, int soLuong, string donViTinh, int donGia) {
		this->maMatHang = maMatHang;
		this->tenMatHang = tenMatHang;
		this->soLuong = soLuong;
		this->donGia = donGia;
		this->donViTinh = donViTinh;
		next = NULL;
	}

};
void swap_2MatHang(Goods* p, Goods* q);

struct GOGs
{
	string tenNhomHang;
	string maNhomHang;
	string ghiChu;
	int SLMH;


	GOGs* next;
	Goods* head;
	Goods* tail;
	GOGs() {
		tenNhomHang = "";
		maNhomHang = "'";
		next = NULL;
		SLMH = 0;
		ghiChu = "";
		head = NULL;
		tail = NULL;
	}
	GOGs(string _TenNH, string _maNH, string _GC) {
		tenNhomHang = _TenNH;
		maNhomHang = _maNH;
		next = NULL;
		SLMH = 0;
		ghiChu = _GC;
		head = NULL;
		tail = NULL;
	}
	void addGoods(Goods* MH) {

		if (!MH)
			return;
		if (head == NULL)
		{
			head = MH;
			tail = MH;
		}
		else
		{
			tail->next = MH;
			tail = MH;
		}
		SLMH++;
	}
	void xoaMatHang(long long maMatHang)
	{
		if (head->maMatHang == maMatHang) {
			head = head->next;
			return;
		}
		for (Goods* k = head; k != NULL; k = k->next)
		{
			if (k->maMatHang == maMatHang)
			{
				if (k == head)
				{
					xoaHead();
				}
				else if (k == tail)
				{
					xoaTail();
				}
				else
				{
					for (Goods* tmp = head; tmp != NULL; tmp = tmp->next)
					{
						if (tmp->next->maMatHang == maMatHang)
						{
							tmp->next = k->next;
							delete k;
						}
					}
				}
			}
		}
		SLMH--;
	}
	void xoaTail()
	{
		for (Goods* k = head; k != NULL; k = k->next)
		{
			if (k->next == tail)
			{
				Goods* tmp = tail;
				tail = k;
				delete tmp;
			}
		}
		SLMH--;
	}
	void xoaHead()
	{
		if (head == NULL)
			return;
		else if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			Goods* k = head;
			head = k->next;
			delete k;
		}
		SLMH--;
	}
	void sapXepMatHang() {
		for (Goods* k = head; k != tail; k = k->next)
		{
			for (Goods* p = k->next; p != NULL; p = p->next)
			{
				if (chuanHoa(k->tenMatHang).compare(chuanHoa(k->next->tenMatHang)) > 0)
				{
					swap_2MatHang(k, p);
				}
			}
		}
	}
	Goods* getGoodsByID(long long maMatHang)
	{
		for (Goods* k = head; k != NULL; k = k->next)
		{
			if (k->maMatHang == maMatHang)
				return k;
		}
		cout << "Mat hang khong ton tai!\n";
		return NULL;
	}


};

//Tao cau truc Kho:
struct Warehouse
{
	string tenKho;
	string maKho;
	string diaDiem;
	Warehouse* next;
	long long ranDomID;
	//Tao ra hai con tro co kieu du lieu Nhom Hang de quan li cac nhom hang co trong kho:
	GOGs* head;
	GOGs* tail;
	Warehouse() {
		this->tenKho = " ";
		this->maKho = "";
		this->diaDiem = " ";
		next = NULL;
		tail = NULL;
		head = NULL;
		ranDomID = 1000;
	};
	Warehouse(string tenKho, string maKho, string diaDiem) {
		this->tenKho = tenKho;
		this->maKho = maKho;
		this->diaDiem = diaDiem;
		next = NULL;
		tail = NULL;
		head = NULL;
		ranDomID = 1000;
	}
	void update();
	void addGOGs(GOGs* x) {
		if (!x)
			return;

		if (head == NULL)
		{
			head = x;
			tail = x;
		}
		else
		{
			tail->next = x;
			tail = tail->next;
		}

	}
	GOGs* getGOGsFromWHouse(string maNH)
	{
		for (GOGs* k = head; k != NULL; k = k->next)
		{
			if (k->maNhomHang.compare(maNH) == 0)
				return k;
		}
		return NULL;
	}
	void xoaNhomHang(string ma) {
		if (!head)
			return;
		if (head->maNhomHang == ma) {
			head = head->next;
			return;
		}

		GOGs* temp = head;
		GOGs* prev = head;
		while (temp) {
			if (temp->maNhomHang == ma)
				break;
			prev = temp;
			temp = temp->next;
		}
		if (temp) {
			prev->next = temp->next;
			delete temp;
		}


	}

};
struct itemImport
{

	string itemName;
	int itemPrice;
	string Unit;
	int Quantity;
	itemImport* next = NULL;
	itemImport() {
		itemName = "";
		itemPrice = 0;
		Unit = "";
		Quantity = 0;
		next = NULL;
	}
	itemImport(string tenMH, string dVi, int dGia = 0, int sLN = 0) {
		itemName = tenMH;
		itemPrice = dGia;
		Unit = dVi;
		Quantity = sLN;
		next = NULL;
	}
};
struct PhieuNhapKho
{
	string maPhieuNhap;
	string maKho;
	Date ngayNhap;
	itemImport* head = NULL;
	itemImport* tail = NULL;
	PhieuNhapKho() {
		maPhieuNhap = "";
		maKho = "";
		ngayNhap = NULL;
	}
	PhieuNhapKho(string mPN, string mK, Date nN) {
		maPhieuNhap = mPN;
		maKho = mK;
		ngayNhap = nN;
	}
	void addItem(itemImport* item) {
		if (!head) {
			head = item;
			tail = item;
			return;
		}
		tail->next = item;
		tail = tail->next;
	}
	void append(string tenMH, string dVi, float dGia, int sLN = 0) {
		itemImport* temp = new itemImport(tenMH, dVi, dGia, sLN);
		if (!head)
		{
			head = temp;
			tail = temp;
			return;
		}
		tail->next = temp;
		tail = temp;

	}
	void print(Warehouse* s) {
		cout << "----------------------------------------------------------------------------------------------------------\n";

		cout << setw(62) << right << "   PHIEU NHAP KHO  " << endl << endl;
		cout << setw(45) << right << "Ngay " << ngayNhap.day << " thang " << ngayNhap.month << " nam " << ngayNhap.year << endl;

		cout << "Nhap tai kho : ";
		cout << setw(40) << left << s->tenKho;
		cout << setw(43) << right << "Ma kho: ";
		cout << maKho << endl;

		cout << "+--------------------------------------------------------------------------------------------------------+\n";
		cout << setw(5) << left << "| STT";
		cout << setw(30) << left << "| TEN MAT HANG";
		cout << setw(10) << left << "| DON VI";
		cout << setw(15) << left << "| SO LUONG";
		cout << setw(15) << left << "| GIA";
		cout << setw(15) << left << "| THANH TIEN";
		cout << "|" << endl;
		cout << "+--------------------------------------------------------------------------------------------------------+\n";
		int stt = 1;
		long tong = 0;
		for (itemImport* k = head; k != NULL; k = k->next)
		{
			int thanhTien = k->itemPrice * k->Quantity;
			cout << "  " << setw(5) << left << stt;
			cout << setw(30) << left << k->itemName;
			cout << setw(10) << left << k->Unit;
			cout << setw(15) << left << k->Quantity;
			cout << setw(15) << left << k->itemPrice;
			cout << setw(12) << left << thanhTien;
			cout << endl;
			stt++;
			tong = tong + thanhTien;
		}
		cout << "+--------------------------------------------------------------------------------------------------------+\n";
		cout << setw(98) << right << "TONG: " << tong << endl;
	}

};

struct ExportItem {
	long long maHang;
	int soLuongXuat;
	ExportItem* next;
	ExportItem(long long MH=0, int SL=0) {
		maHang = MH;
		soLuongXuat = SL;
		next = NULL;
	}
};

struct PhieuXuatKho {
	string  maPhieu;
	string maKho;
	string GOGsID;
	Date ngayXuat;
	ExportItem* head;
	ExportItem* tail;
	PhieuXuatKho(string a ="", string c="", Date d=NULL) {
		maPhieu = a;

		maKho = c;
		ngayXuat = d;

		head = NULL;
		tail = NULL;
	}
	void addItem(ExportItem* item) {
		if (!head)
		{
			head = item;
			tail = item;
			return;
		}
		tail->next = item;
		tail = tail->next;
		
	}
	void append(long itemID, int sLN = 0) {
		ExportItem* temp = new  ExportItem(itemID, sLN);
		if (!head)
		{
			head = temp;
			tail = temp;
			return;
		}
		tail->next = temp;
		tail = temp;

	}

};

class WhouseList {
public:
	Warehouse* List;
	Warehouse* Tail;
	WhouseList() {
		List = NULL;
		Tail = NULL;
	}
	void append(Warehouse* s) {
		if (!List) {
			List = s;
			Tail = s;
			return;
		}
		Tail->next = s;
		Tail = s;
	}
	void makeList() {
		ifstream fin("Warehouse List");
		if (!fin) {
			cout << "Khong tim thay kho cu!\n";
			return;
		}
		string ptemp;
		getline(fin, ptemp, '\n');
		while (!fin.eof()) {
			Warehouse* temp = new Warehouse;
			getline(fin, ptemp, ',');
			temp->tenKho = ptemp;
			getline(fin, ptemp, ',');
			temp->maKho = ptemp;
			getline(fin, ptemp, '\n');
			temp->diaDiem = ptemp;
			append(temp);
		}
	}
	void updateList() {
		ofstream fout("Warehouse List");
		if (!fout) {
			cout << "Sao luu list that bai!\n";
			return;
		}
		Warehouse* temp = List;
		while (temp) {
			fout << "\n" << temp->tenKho << ","
				<< temp->maKho << ","
				<< temp->diaDiem;
			temp = temp->next;
		}
	}
	void deleteKho(string makho) {
		Warehouse* temp = List;
		if (temp->maKho == makho) {
			List = List->next;
			return;
		}
		while (temp->next&&temp->next->maKho != makho) {
			temp = temp->next;
		}
		temp->next = temp->next->next;
	}
	void printList() {
		Warehouse* temp = List;
		while (temp) {
			cout << temp->tenKho << " " << temp->maKho << " " << temp->diaDiem << endl;
			temp = temp->next;
		}
	}
	Warehouse* getWH(string maKho) {
		Warehouse* temp = List;
		while (temp&&temp->maKho != maKho) {
			temp = temp->next;
		}
		if (!temp)
			cout << "Kho khong ton tai!\n";
		return temp;
	}
};
