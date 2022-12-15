#include"Header.h"
#include"Object.h"


void InvoiceMove(Warehouse* w,string oldID) {
	ifstream fin(oldID + "Warehouse/Nhap",ios::beg);
	ofstream fout(w->maKho + "Warehouse/Nhap");
	string line;
	if (!fin || !fout) {
		return;
	}
	while (getline(fin, line)) {
		fout << line<<endl;
	}
	fin.close();
	fout.close();
	fin.open(oldID + "Warehouse/Xuat",ios::beg);
	fout.open(w->maKho + "Warehouse/Xuat");
	while (getline(fin, line)) {
		fout << line<<endl;
	}

}

void printImportInvoice(Warehouse* s,int options) {
	system("cls");
	Date d;
	if (options == 2) {
		cout << "Nhap ngay:";
		cin >> d.day;
		cout << "Nhap thang:";
		cin >> d.month;
		cout << "Nhap nam:";
		cin >> d.year;
	}
	else if (options == 3) {
		cout << "Nhap thang:";
		cin >> d.month;
		cout << "Nhap nam:";
		cin >> d.year;
	}
	else if (options == 4) {
		cout << "Nhap nam:";
		cin >> d.year;
	}
	ifstream fin(s->maKho+"Warehouse/Nhap");
	if (!fin)
		return;

	int ntemp;
	string stemp;
	while (!fin.eof()) {
		PhieuNhapKho* l = new PhieuNhapKho;
		fin >> ntemp; l->ngayNhap.day = ntemp;
		fin >> ntemp; l->ngayNhap.month = ntemp;
		fin >> ntemp; l->ngayNhap.year = ntemp;
		getline(fin, stemp, '\n');
		getline(fin, stemp, ','); l->maPhieuNhap = stemp;
		getline(fin, stemp, '\n'); l->maKho = stemp;
		string temp;
		while (stemp != "/") {
			itemImport* goods = new itemImport;
			getline(fin, stemp, ','); goods->itemName = stemp;
			getline(fin, stemp, ','); goods->Unit = stemp;
			fin >> ntemp; goods->Quantity = ntemp;
			fin >> ntemp; goods->itemPrice = ntemp;
			getline(fin, stemp, '\n');
			l->addItem(goods);
		}
		if (options==1) {
			l->print(s);
		}
		else if(options==2) {
			if (l->ngayNhap.day == d.day && l->ngayNhap.month == d.month && l->ngayNhap.year == d.year) {
				l->print(s);
			}
		}
		else if (options == 3) {
			if (l->ngayNhap.month == d.month && l->ngayNhap.year == d.year) {
				l->print(s);
			}
		}
		else {
			if (l->ngayNhap.year == d.year) {
				l->print(s);
			}
		}
		
	}
	cin.ignore();
	cout << "Enter de quay lai Menu\n";
	cin.ignore();
}
void printExportInvoice(Warehouse* s,int options) {

	system("cls");
	Date d;
	if (options == 2) {
		cout << "Nhap ngay:";
		cin >> d.day;
		cout << "Nhap thang:";
		cin >> d.month;
		cout << "Nhap nam:";
		cin >> d.year;
	}
	else if (options == 3) {
		cout << "Nhap thang:";
		cin >> d.month;
		cout << "Nhap nam:";
		cin >> d.year;
	}
	else if (options == 4) {
		cout << "Nhap nam:";
		cin >> d.year;
	}
	ifstream fin(s->maKho + "Warehouse/Xuat");
	if (!fin)
		return;

	long long ntemp;
	string stemp;
	while (!fin.eof()) {
		PhieuXuatKho* l = new PhieuXuatKho;
		fin >> ntemp; l->ngayXuat.day = ntemp;
		fin >> ntemp; l->ngayXuat.month = ntemp;
		fin >> ntemp; l->ngayXuat.year = ntemp;
		getline(fin, stemp, '\n');
		getline(fin, stemp, ','); l->maPhieu = stemp;
		getline(fin, stemp, ','); l->maKho = stemp;
		getline(fin, stemp, '\n'); l->GOGsID = stemp;
	
		while (stemp != "/") {
			ExportItem* goods = new ExportItem;
			fin >> ntemp; goods->maHang = ntemp;
			fin >> ntemp; goods->soLuongXuat = ntemp;
			getline(fin, stemp, '\n');
			l->addItem(goods);
		}
		if (options == 1) {
			printExportInvoice(s->getGOGsFromWHouse(l->GOGsID), l);
		}
		else if (options == 2) {
			if (l->ngayXuat.day == d.day && l->ngayXuat.month == d.month && l->ngayXuat.year == d.year) {
				printExportInvoice(s->getGOGsFromWHouse(l->GOGsID), l);
			}
		}
		else if (options == 3) {
			if (l->ngayXuat.month == d.month && l->ngayXuat.year == d.year) {
				printExportInvoice(s->getGOGsFromWHouse(l->GOGsID), l);
			}
		}
		else {
			if (l->ngayXuat.year == d.year) {
				printExportInvoice(s->getGOGsFromWHouse(l->GOGsID), l);
			}
		}

	}
	cin.ignore();
	cout << "Enter de quay lai Menu\n";
	cin.ignore();
}
void ghiFileNhapBaoCao(PhieuNhapKho* l) {char* cstr = new char[l->maKho.length()+1];
	ofstream fout(l->maKho + "Warehouse/Nhap", ios::app);
	string data;
	data += "\n"+ to_string(l->ngayNhap.day) + " " + to_string(l->ngayNhap.month) + " " + to_string(l->ngayNhap.year)+"\n";
	data += l->maPhieuNhap+ "," + l->maKho + "\n";
	for (itemImport* k = l->head; k != NULL; k = k->next)
	{
		data += k->itemName+',';
		data += k->Unit + ',';
		data += to_string(k->Quantity) + " ";
		data += to_string(k->itemPrice)+"\n";
		
	}
	data.pop_back();
	data += "/";
	fout << data;
	
}
void ghiFileXuatBaoCao(GOGs* s, PhieuXuatKho* l) {

	ofstream fout(l->maKho + "Warehouse/Xuat",ios::app);
	string data;
	data += "\n" + to_string(l->ngayXuat.day) + " " + to_string(l->ngayXuat.month) + " " + to_string(l->ngayXuat.year) + "\n";
	data += l->maPhieu+ "," + l->maKho +"," + s->maNhomHang + "\n";;
	
	for (ExportItem * k = l->head; k != NULL; k = k->next)
	{
		data += to_string(k->maHang)+" ";
		data += to_string(k->soLuongXuat) + '\n';
	}
	data.pop_back();
	data += "/";
	fout << data;

}
