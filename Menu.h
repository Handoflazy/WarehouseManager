#pragma once
#include"Header.h"

int optionsReportType(Warehouse* s) {
	cout << "	  KHO " << s->tenKho;
	cout << "\n"
		"----------------------------\n"
		"         BAO CAO\n"
		"----------------------------\n"
		;
	cout << "\033[36m";
	string arr[] = { "1.TAT CA","2.THEO NGAY","3.THEO THANG ","4.THEO NAM","0.QUAY LAI" };
	int options;
	for (int i(0); i < 5; i++) {
		cout << setw(10) << left << "|" << setw(16) << left << arr[i] << setw(4) << " |" << endl;
	}

	cout << "\033[37m";
	cout << "----------------------------\n";
	cout << "Nhap lua chon cua ban: ";
	cin >> options;
	return options;
}
int optionsMainMenu(Warehouse* s) {
	cout << "	  KHO " << s->tenKho;
	cout << "\n"
		"----------------------------\n"
		"         Main Menu\n"
		"----------------------------\n"
		;
	cout << "\033[36m";
	string arr[] = { "1.NHAP KHO","2.XUAT KHO","3.CAP NHAT KHO","4.THONG KE","0.THOAT" };
	int options;
	for (int i(0); i < 5; i++) {
		cout << setw(8) << left << "|" << setw(18) << arr[i] << setw(6) << " |" << endl;
	}

	cout << "\033[37m";
	cout << "----------------------------\n";
	cout << "Nhap lua chon cua ban: ";
	cin >> options;
	return options;
};
int optionsEditWH(Warehouse* s) {
	cout << "	  KHO " << s->tenKho;
	cout << "\n"
		"----------------------------\n"
		"          SUA KHO         \n"
		"----------------------------\n"
		;
	cout << "\033[36m";
	string arr[] = { "1.SUA THONG TIN KHO","2.SUA NHOM HANG","0.QUAY LAI" };
	for (int i(0); i < 3; i++) {
		cout << setw(8) << " " << left << setw(20) << arr[i] << endl;
	}
	cout << "\033[37m";
	cout << "----------------------------\n";
	cout << "Nhap lua chon cua ban: ";

	int options;
	cin >> options;
	return options;
}
int optionsUpdateGOGs(Warehouse* s) {
	cout << "	  KHO " << s->tenKho;
	cout << "\n"
		"------------------------------\n"
		"      SUA NHOM HANG      \n"
		"------------------------------\n";
	string arr[] = { "1.THEM NHOM HANG","2.XOA NHOM HANG","3.SUA THONG TIN NHOM HANG","0.QUAY LAI" };
	cout << "\033[36m";
	for (int i(0); i < 4; i++) {
		cout << setw(5) << " " << arr[i] << endl;
	}
	cout << "\033[37m";
	cout << "Nhap lua chon cua ban: ";
	int options;
	cin >> options;
	return options;
	return 0;
}
int optionsUpdateWH(Warehouse* s) {
	cout << "	  KHO " << s->tenKho;
	cout << "\n"
		"----------------------------\n"
		"        CAP NHAT KHO     \n"
		"----------------------------\n"
		; cout << "\033[36m";
	string arr[] = { "1.TAO KHO MOI","2.XOA KHO","3.SUA KHO","0.QUAY LAI" };
	for (int i(0); i < 4; i++) {
		cout << setw(8) << " " << left << setw(20) << arr[i] << endl;
	}
	cout << "\033[37m";
	cout << "----------------------------\n";
	cout << "Nhap lua chon cua ban: ";
	int options;
	cin >> options;
	return options;
}
int optionsReport(Warehouse* s) {
	cout << "	  KHO " << s->tenKho;
	cout << "\n"
		"----------------------------\n"
		"          BAO CAO         \n"
		"----------------------------\n"
		; cout << "\033[36m";
	string arr[] = { "1.THONG KE NHAP KHO","2.THONG KE XUAT KHO","3.THONG KE HANG TON","0.QUAY LAI" };
	for (int i(0); i < 4; i++) {
		cout << setw(5) << " " << left << setw(20) << arr[i] << endl;
	}
	cout << "\033[37m";
	cout << "----------------------------\n";
	cout << "Nhap lua chon cua ban: ";
	int options;
	cin >> options;
	return options;
}


void MenuUpdateWH(Warehouse* &w) {
	string oldID;
	WhouseList list;
	list.makeList();
	char* cstr=NULL;
	int Option;
	do
	{
		system("cls");
		Option = optionsUpdateWH(w);
		switch (Option)
		{
		case 1:
			w = new Warehouse;
			nhapThongTinChoKho(w);
			list.append(w);
			list.updateList();
			break;
		case 2:
			deleteWH(w);
			break;
		case 3:
				do {
					system("cls");
					Option = optionsEditWH(w);
					switch (Option)
					{
					case 1:
						oldID = w->maKho;
						nhapThongTinChoKho(w);
						list.deleteKho(oldID);
						list.append(w);
						list.printList();
						list.updateList();
						InvoiceMove(w, oldID);
						break;
					case 2:
						do {
							system("cls");
							Option = optionsUpdateGOGs(w);
							switch (Option)
							{
							case 1:
								w->addGOGs(newGOGs(w));
								break;
							case 2:
								delGOGs(w);
								break;
							case 3:
								nhapThongTinChoNH(w);
								break;
							}
						} while (Option != 0);
						Option = -1;
					}
					
				} while (Option != 0);
				Option = -1;
		}
	} while (Option!=0);
}
void MenuReport(Warehouse*& w) {
	Date inputDate;
	string a;
	do
	{
		system("cls");
		int options3 = optionsReport(w);

		switch (options3)
		{
		case 1:
			do
			{
				system("cls");
				int options4 = optionsReportType(w);
				switch (options4)
				{
				case 1:
					printImportInvoice(w, 1);
					break;
				case 2:
					printImportInvoice(w, 2);
					break;
				case 3:
					printImportInvoice(w, 3);
					break;
				case 4:
					printImportInvoice(w, 4);
					break;
				default:
					break;
				}
				if (!options4)
					break;
			} while (true);
			break;
		case 2:
			do
			{
				system("cls");
				int options4 = optionsReportType(w);
				if (!options4)
					break;
				switch (options4)
				{
				case 1:
					
					printExportInvoice(w, 1);
					break;
				case 2:
					printExportInvoice(w, 2);;
					break;
				case 3:
					printExportInvoice(w, 3);
					break;
				case 4:
					printExportInvoice(w, 4);
					break;
				default:
					break;
				}
				if (!options4)
					break;
			} while (true);
			break;
		case 3:
			system("cls");
			detailWHouse(w);
			cin.ignore();
			cout << "Nhan Enter de quay lai !";
			cin.ignore();
			break;
		default:
			break;
		}
		if (options3 == 0)
			break;
	} while (1);

}
void MenuGeneral(Warehouse* &s) {
	int options(0);
	int options2(0);
	string a = "";
	
	do
	{
		system("cls");
		options = optionsMainMenu(s);
		Sleep(100);
		switch (options)
		{
		case 1:
			cout << "Tien hanh Nhap Kho!\n";
			Sleep(100);
			importGoods(s);
			break;
		case 2:
			cout << "Tien hanh Xuat Kho!\n";
			Sleep(100);
			exportGoods(s);
			break;
		case 3:
			MenuUpdateWH(s);
			break;

		case 4:
			MenuReport(s);
			break;
		default:
			break;
		}

		if (options == 0)
			break;
	} while (1);
}




