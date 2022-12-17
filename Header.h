#define _CRT_SECURE_NO_WARNINGS
#include"Object.h"
#include <windows.h>
#include <cwchar>
#include<fstream>
#include<iomanip>
#include<direct.h>

void ghiFileNhapBaoCao(PhieuNhapKho* l);
void ghiFileXuatBaoCao(GOGs* s, PhieuXuatKho* l);
void nhapThongTinChoKho(Warehouse*& kho);
void InvoiceMove(Warehouse* w, string oldID);
//Daclare Prototype:
void delGOGs(Warehouse* s);
void deleteWH(Warehouse* &s);
void delGood(Warehouse* s);
void DetailGOGS(Warehouse* s);

Warehouse* startUp();
void BackupGOGs(Warehouse* s);


Goods* matHangMoi();
void Backup(string makho,Warehouse* s);
void saveGoods(Warehouse* w,GOGs* s);
void saveGOGs(Warehouse* s);
PhieuNhapKho* createImportInvoice(Warehouse* s, GOGs* g);
Goods* matHangMoi();

void printImportInvoice(PhieuNhapKho* l);

//Kiem tra Nhom Hang
bool kiemTraNhomHang(Warehouse* p, string maNhomHang);


int demSoLuongCacLoaiMatHang(Warehouse* kho);

//in List hang xuat kho

void nhapThongTinChoKho(Warehouse*& kho);
void nhapThongTinChoNH(Warehouse*& s);
void detailWHouse(Warehouse* kho);

void importGoods(Warehouse* s);
void printImportInvoice(Warehouse* s,int options);
void printExportInvoice(Warehouse* s,int options);

void DetailGOG(GOGs* s);
GOGs* newGOGs(Warehouse* s);
void exportGoods(Warehouse* s);
void printExportInvoice(GOGs* s, PhieuXuatKho* l);

//void fileNhapHang(PhieuNhapKho* l);
PhieuXuatKho* createExportInvoice(Warehouse* s, GOGs* a);
bool exportRPValid(GOGs* g, PhieuXuatKho* l);