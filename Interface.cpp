#include"Header.h"
#include"Object.h"
WhouseList list;

using namespace std;
Warehouse* startUp() 
{
	//string s = "+Dang khoi dong chuong trinh+\n";
	//for (int i(0); i < s[i]; i++) {
	//	cout << s[i];
	//	Sleep(70);
	//}
	//cout << endl;
	//s = "+Khoi dong hoan tat^^\n";
	//for (int i(0); i <= s[i]; i++) {
	//	cout << s[i];
	//	Sleep(20);
	//}
	cout << "\n<\033[34mCHAO MUNG DEN VOI CHUONG TRINH QUAN LY KHO\033[37m>\n";

	;
	cout <<
		"\n"
		"------------------------------\n"
		"     1.NHAP MA KHO HIEN CO\n"
		"------------------------------\n"
		;
	cout <<
		"\n"
		"------------------------------\n"
		"          0.NEW KHO     \n"
		"------------------------------\n"
		;
	bool options;
	string maKho;
	Warehouse* temp = new Warehouse;
	Warehouse* check;
	list.makeList();
	cout << "Lua chon: ";
	cin >> options;
	if (options)
	{
		if (!list.List) {
			cout << "Khong ton tai kho nao truoc day!\nVui long tao kho moi!\n";
			cout << "Tien hanh khoi tao thong tin cho kho!\n";
			nhapThongTinChoKho(temp);
			list.append(temp);
		}
		else
		{
			do
			{
				system("cls");
				list.printList();
				cout << "Nhap ma Kh0: ";
				cin.ignore();
				cin >> maKho;
				cout << maKho;
				check = list.getWH(maKho);
				if (!check) {
					cout << "Sai ma Kho!\n";
					cout << "Nhap lai!\n";
					system("pause");
				}
				else
					break;
			} while (1);
			Backup(maKho, temp);
		}
		
	}
	else {
		cout << "Tien hanh khoi tao thong tin cho kho!\n";
		temp = new Warehouse;
		nhapThongTinChoKho(temp);
		list.append(temp);
		
	}
	list.updateList();
	return temp;

}
void deleteWH(Warehouse* &s) {
	detailWHouse(s);
	if (s->head) {
		cout << "Kho con luu tru thong tin!\n";
		cout << "Xac nhan xoa[1]/[0]\n";
		bool options;
		cin >> options;
		if (!options)
			return;
	}
	cout << s->maKho;
	list.deleteKho(s->maKho);
	list.updateList();
	delete s;
	s = new Warehouse;
}
void delGood(Warehouse* s) {

	if (!s->head) {
		cout << "Khong co mat hang nao de xoa!\n";
		return;
	}
	GOGs* temp = NULL;
	do
	{
		system("cls");
		DetailGOGS(s);
		cout << "Nhap ma Nhom hang cua nhom hang muon xoa: ";
		cin.ignore();
		string maNH;
		cin >> maNH;
		temp = s->getGOGsFromWHouse(maNH);
		if (!temp) {
			cout << "Sai ma Nhom hang!\n";
			cout << "Tiep tuc xoa/Thoat[1][0]";
			cout << "Lua chon:";
			bool options;
			cin >> options;
			if (!options)
				break;
		}
	} while (!temp);
	if (!temp)
		return;
	DetailGOG(temp);
	Goods* temp2;
	long long maMH;
	do {
		cout << "Nhap ma Mat Hang muon xoa:";

		cin >> maMH;
		temp2 = temp->getGoodsByID(maMH);
		if (!temp2) {
			cout << "Mat hang khong ton tai trong Nhom Hang!";
			cout << "Tiep tuc xoa mat Hang trong Nhom Hang/Thoat[1]/[0]\n";
			cout << "Lua chon:";
			bool options;
			cin >> options;
			if (!options)
				break;
		}

	} while (!temp2);
	if (!temp2)
		return;
	cout << "<Xac nhan xoa Mat Hang" << temp2->tenMatHang << "Khoi Nhom hang>";
	cout << "Xoa/Thoat[1][0]:";
	bool options;
	cin >> options;
	if (!options)
		return;
	temp->xoaMatHang(maMH);
}
void delGOGs(Warehouse* s) {
	if (!s->head) {
		cout << "Khong co nhom hang nao de xoa!";
		return;
	}
	detailWHouse(s);
	cout << "<Nhap ma Nhom Hang muon xoa:";
	string ma;
	cin >> ma;
	GOGs* temp = s->getGOGsFromWHouse(ma);
	if (!temp) {
		cout << "Kho khong co nhom hang nay!\n";
		return;
	}
	if (temp->head)
	{
		cout << "Nhom Hang con luu tru thong tin!\n";
		cout << "Xac nhan xoa[1]/[0]\n";
		bool options;
		cin >> options;
		if (!options)
			return;

	}
	s->xoaNhomHang(ma);
	return;
}
void Warehouse::update() {
	ofstream fileOut;
	fileOut.open(maKho+"WareHouse/DataWH");
	if (!fileOut) {
		cout << "Sao luu khong thanh cong\n";
	}
	fileOut << tenKho << "," << maKho << "," << diaDiem << "," << ranDomID;
	if (fileOut)
		cout << "Sao luu Kho thanh cong!\n";
	fileOut.close();

	saveGOGs((this));
}
//Nhap thong tin cho Nhom hang:
GOGs* newGOGs(Warehouse* s)
{
	system("cls");
	cout << "<TIEN HANH THEM NHOM HANG MOI VAO KHO!>\n";
	string maNhomHang;
	string tenNH;
	string ghiChu;
	do
	{
		cout << "Nhap ma Nhom Hang:";
		cin.ignore();
		getline(cin, maNhomHang);
		if (!kiemTraNhomHang(s, maNhomHang)) {
			cout << "Ma Nhom Hang da ton tai!\n";
			cout << "Tiep tuc/Thoat[1][0]:";
			bool options;
			cin >> options;
			if (!options)
				return NULL;
		}
	} while (!kiemTraNhomHang(s, maNhomHang));
	cout << "Nhap ten nhom hang:";
	getline(cin, tenNH);
	cout << "Nhap ghi chu ban muon co trong Nhom Hang!(neu khong co xin vui long nhan Enter)\n";
	cout << "\033[35m";
	getline(cin, ghiChu);
	cout << "\033[37m";

	GOGs* temp = new GOGs(tenNH, maNhomHang, ghiChu);
	cout << "Khoi tao nhom Hang moi thanh cong!\n";
	cout << "\033[31m";
	cout << "Da cap nhat lai kho hang\n";
	cout << "\033[37m";
	Sleep(1000);
	return temp;

}
void nhapThongTinChoNH(Warehouse*& s)
{
	if (!s->head) {
		cout << "Kho ko co nhom hang nao!\n";
		Sleep(600);
		return;
	}
	
	system("cls");
	DetailGOGS(s);
	string maNhomHang;
	GOGs* temp;
	do
	{
		cout << "Nhap ma NH ban muon chinh sua: ";
		cin.ignore();
		getline(cin, maNhomHang);
		temp = s->getGOGsFromWHouse(maNhomHang);
		if (!temp) {
			cout << "Ma Nhom Hang khong ton tai trong kho!\n";
			cout << "Nhap Lai/Thoat[1]/[0]: ";
			bool options;
			cin >> options;
			if (!options)
				return;
		}
	} while (!temp);
	do
	{
		cout << "Nhap ma Nhom Hang moi: ";
		getline(cin, maNhomHang);
		if (maNhomHang == temp->maNhomHang) {
			break;
		}
		if (!kiemTraNhomHang(s, maNhomHang)) {
			cout << "Ma Nhom Hang da ton tai!\n";
			cout << "Tiep tuc/Thoat[1][0]: ";
			bool options;
			cin >> options;
			if (!options)
				return;
		}
	} while (!kiemTraNhomHang(s, maNhomHang));
	temp->maNhomHang = maNhomHang;
	cout << "Nhap ten nhom hang:";
	getline(cin, temp->tenNhomHang);
	cout << "Nhap ghi chu ban muon co trong Nhom Hang!(neu khong co xin vui long nhan Enter)\n";

	getline(cin, temp->ghiChu);

	cout << "Cap nhat Hang thanh cong!\n";
	return;



}


//Cac ham nhap cac thong tin can thiet cho Kho:
void nhapThongTinChoKho(Warehouse*& kho)
{
	
	string tenKho;
	string maKho;
	string diaDiem;

	cout << "Nhap ten Kho    : ";
	cin.ignore();

	getline(cin, tenKho);

	cout << "Nhap ma  Kho    : ";
	getline(cin, maKho);

	cout << "Nhap dia diem   : ";
	getline(cin, diaDiem);
	kho->tenKho = tenKho;
	kho->maKho = maKho;
	kho->diaDiem = diaDiem;
	char* cstr = new char[maKho.length() + 1];
	strcpy(cstr, maKho.c_str());
	strcat(cstr, "Warehouse");
	_mkdir(cstr);
	strcat(cstr, "/GroupofGoods");
	_mkdir(cstr);


}

void detailWHouse(Warehouse* kho)
{

	system("cls");
	if (kho->maKho == "") {
		cout << "\033[31mKho chua dc Khoi tao, vui long TAO KHO MOI o phan CAP NHAT \033[37m\n";
		return;
	}
	cout << setw(15) << "|" << "THONG TIN KHO " << setw(20) << kho->tenKho << setw(15) << "|" << endl;
	cout << setw(49) << left << "|" << "|" << endl;
	cout << "|Ma so kho: " << setw(37) << kho->maKho << "|" << endl;
	cout << "|Dia chi  : " << setw(37) << kho->diaDiem << "|" << endl;
	cout << "|	   Danh Sach nhom hang hien co:" << setw(11) << right << "|" << endl;
	if (!kho->head) {
		cout << "|               kHO RONG	                 |\n" << endl;
		return;
	}
	GOGs* tmp = kho->head;
	//tmp->sapXepMatHang();
	int dem = 1;
	while (tmp != NULL)
	{
		cout << setw(50) << setfill('*');
		cout << setw(18) << left << "|" << "Nhom hang thu " << dem << setw(18) << right << "| " << endl;
		cout << left;
		cout << setfill(' ');
		cout << "|Ten Nhom Hang: " << setw(33) << tmp->tenNhomHang << "|" << endl;
		cout << "|Ma  Nhom Hang: " << setw(33) << tmp->maNhomHang << "|" << endl;
		//tmp->inChiTietNhomHang();

		cout << "|Ghi chu : " << setw(38) << tmp->ghiChu << "|" << endl;
		tmp = tmp->next;
		dem++;
	}
	cout << "In chi tiet hon~[1]/[0] bo qua:";

	string options;
	cin >> options;
	cout << endl;
	if (options == "1")
	{
		system("cls");
		GOGs* tmp = kho->head;
		//tmp->sapXepMatHang();
		int dem = 1;
		while (tmp != NULL)
		{

			DetailGOG(tmp);

			tmp = tmp->next;
		}

	}

}
void DetailGOG(GOGs* s) {
	cout << "DETAIL GROUP OF GOOD  " << "\033[34m" << s->tenNhomHang << "\033[37m " << s->maNhomHang << endl;
	cout << "===========================================================================================\n";
	cout << setw(5) << left << "| STT";
	cout << setw(30) << left << "| TEN MAT HANG";
	cout << setw(15) << left << "| MA SAN PHAM";
	cout << setw(10) << left << "| DON VI";
	cout << setw(15) << left << "| SO LUONG";
	cout << setw(15) << left << "| GIA";
	cout << "|" << endl;
	int stt = 0;
	for (Goods* k = s->head; k != NULL; k = k->next)
	{

		cout << "| " << setw(3) << left << stt;
		cout << "| " << setw(28) << left << k->tenMatHang;
		cout << "| " << setw(13) << left << k->maMatHang;
		cout << "| " << setw(8) << left << k->donViTinh;
		cout << "| " << setw(13) << left << k->soLuong;
		cout << "| " << setw(13) << left << k->donGia;
		cout << left << "|";
		cout << endl;
		stt++;
	}
	cout << "===========================================================================================\n";
	cout << endl;
}
string chuanHoa(string s)
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - 32;
	}
	return s;
}
void DetailGOGS(Warehouse* s) {
	system("cls");
	GOGs* tmp = s->head;
	//tmp->sapXepMatHang();
	int dem = 1;
	while (tmp != NULL)
	{

		DetailGOG(tmp);

		tmp = tmp->next;
	}
}
void exportGoods(Warehouse* s) {
	if (s->maKho == "") {
		cout << "\033[31mKho chua dc Khoi tao, vui long NHAP THONG TIN CHO KHO o phan CAP NHAT \033[37m\n";
		Sleep(1000);
		return;
	}
	if (!s->head) {
		cout << "\033[31mKho Khong co hang nao,vui long nhap them hang \033[37m\n";
		Sleep(1000);
		return;
	}
	GOGs* curGroup = NULL;
	string Option;

	do
	{
		DetailGOGS(s);
		cout << "<Nhap ma nhom Hang ma ban muon xuat!>\n";
		cout << "Lua chon cua ban:";
		cin >> Option;
		curGroup = s->getGOGsFromWHouse(Option);
		if (!curGroup) {
			cout << "Nhom hang ko ton tai trong kho!\n";
			cout << "<Nhap lai!>";
			Sleep(600);
			system("cls");
		}
		else
		{
			if (!curGroup->head) {

				cout << "Nhom Hang nay Khon ton tai mat hang nao,vui long nhap them!\n";
				cout << "<Nhom hang khac/Quay lai Menu[1][0]>\n";
				cout << "Lua chon cua ban:";
				cin >> Option;
				if (Option == "1") {
					curGroup = NULL;
				}
				else if (Option == "0") {
					return;
				}
			}
		}

	} while (!curGroup);

	PhieuXuatKho* l = createExportInvoice(s, curGroup);
	if (!l) {
		cout << "Xuat hang ko thanh cong!\n";
		return;
	}
	ExportItem* temp = l->head;
	while (temp) {
		Goods* item = curGroup->getGoodsByID(temp->maHang);
		if (temp->soLuongXuat > item->soLuong) {
			cout << "<So luong " << item->tenMatHang << " Trong kho khong du!>\n";
			cout << "<Don hang nay xuat that bai!>\n";
			Sleep(700);
			delete s;
			s = new Warehouse;
			Backup(s->maKho,s);
			return;
		}
		item->soLuong = item->soLuong - temp->soLuongXuat;
		temp = temp->next;

	}

	cout << "Tien hanh xuat hang\n";
	cout << "\n2000 YEAR LATER~~\n";
	Sleep(2000);
	ghiFileXuatBaoCao(curGroup, l);
	s->update();
	cout << "<Nhap hang hoan tat!>\n";
	cin.ignore();
	cout << "<Nhan Enter de Ve Menu chinh!>";
	cin.ignore();



}
PhieuXuatKho* createExportInvoice(Warehouse* s, GOGs* a) {
	Sleep(500);
	system("cls");
	DetailGOG(a);

	time_t t = time(0);
	PhieuXuatKho* l;
	string maPhieu;
	long itemID;
	string DV;
	int soLuong;
	Date temp;
	struct tm* Now = localtime(&t);
	cout << "<Tien hanh khoi tao phieu xuat kho!>\n";
	
	cout << "Nhap ma Phieu: ";
	cin.ignore();
	getline(cin, maPhieu);
	cout << "Nhap ngay xuat: ";
	cin >> temp.day;
	cout << "Nhap thang xuat: ";
	cin >> temp.month;
	cout << "Nhap nam xuat: ";
	cin >> temp.year;
	l = new PhieuXuatKho(maPhieu, s->maKho, temp);
	do {
		Goods* temp = NULL;
		cout << "_______________________________________________\n";
		do
		{
			cout << "Nhap ma mat hang       :";
			cin >> itemID;
			temp = a->getGoodsByID(itemID);
			if (!temp) {
				cout << "Sai ma mat Hang!\n";
				cout << "Nhap lai/Ngung xuat hang![1]/[0]:";
				bool options;
				cin >> options;
				if (!options)
					return NULL;
			}
		} while (!temp);
		do {
			do
			{
			cout << "Nhap so luong mat hang  :";
			cin >> soLuong;
			if (soLuong < 0) {
				cout << "So luong ko hop le\nNhap lai!\n";
			}
			} while (soLuong<0);
			if (soLuong > temp->soLuong) {
				cout << "So luong vuot qua so luong trong kho!\n";
				cout << "Vui lap nhap lai hoac nhap them mat hang!\n";
				cout << "Nhap lai/Khong xuat mat hang nay![1]/[0]:";
				bool options;
				cin >> options;
				if (!options)
					break;
			}
		} while (soLuong > temp->soLuong);
		if (soLuong <= temp->soLuong) {
			l->append(itemID, soLuong);
			cout << "==========================================\n";
			cout << temp->tenMatHang << " So luong Xuat: " << soLuong << endl;
		}
	
		cout << "<Tiep Tuc Xuat/Dung-[1]/[0]>\n";
		cout << "Lua chon:";
		bool options;
		cin >> options;
		cin.ignore();
		if (!options)
			break;
	} while (1);
	if (!exportRPValid(a, l)) {
		cout << "Phieu ko hop le!\n";
		cout << "Tao Phieu moi[1][0] :";
		bool options;
		cin >> options;
		if (options) {
			system("cls");
			return createExportInvoice(s, a);
		}
		else
			return NULL;
	}
	printExportInvoice(a, l);
	cout << "Xac nhan nhap kho voi phieu nay?[1][0]: ";
	bool options;
	cin >> options;
	if (!options)
	{
		cout << "Ban co muon tao phieu moi?[1][0]: ";
		cin >> options;
		if (options)
			return createExportInvoice(s, a);
		else
		{
			cout << "Tao phieu nhap kho ko thanh cong!\n";
			cout << "Quay lai menu chinh!\n";
			Sleep(300);
			return NULL;
		}
	}
	cout << "Da khoi tao phieu Nhap kho thanh cong!\n";
	Sleep(1000);
	return l;

}






Goods* goodsCheckByName(GOGs* p, string tenMatHang)
{
	//Neu khong co nhom hang nay se tra ve true
	if (!p)
		return NULL;

	for (Goods* q = p->head; q != NULL; q = q->next) {
		if (q->tenMatHang == tenMatHang)
			return q;
	}
	return NULL;
}

bool kiemTraNhomHang(Warehouse* p, string maNhomHang)
{
	//Neu kho rong tra ve true
	if (p->head == NULL)
		return true;
	for (GOGs* k = p->head; k != NULL; k = k->next)
	{
		if (chuanHoa(k->maNhomHang).compare(chuanHoa(maNhomHang)) == 0)
		{
			return false;// da co nhom hang nay trong kho
		}
	}
	return true; // chua co nhom hang nay
}
//
void importGoods(Warehouse* s) {

	if (s->maKho == "") {
		cout << "\033[31mKho chua dc Khoi tao, vui long NHAP THONG TIN CHO KHO o phan CAP NHAT \033[37m\n";
		Sleep(1000);
		return;
	}
	system("cls");
	if (!s->head) {
		detailWHouse(s);
		cout << "Trong kho hien tai khong co nhom hang nao!\n";
		cout << "Ban co muon tao nhom hang moi de luu tru mat hang moi nay![Yes[1]/No[0]]!\n";
		cout << "Lua chon: ";
		bool options;
		cin >> options;
		if (options) {
			s->addGOGs(newGOGs(s));
		}
		else {
			cout << "\033[31m" << "<Nhap hang khong thanh cong!!>\n" << "\033[37m";
			cout << "Quay ve Menu chinh~~";
			Sleep(1000);
		}
		return;
	}
	GOGs* curGroup = NULL;
	string options;
	do
	{
		detailWHouse(s);
		cout << "<\033[32mNhap ma nhom hang ban muon nhap hang vao!\033[37m>\n";
		cout << "<Nhap 0 de tao nhom hang moi cho mat hang nhap vao!>\n";
		cout << "Lua chon: ";
		cin >> options;
		if (options == "0" || s->getGOGsFromWHouse(options)) {

			if (options == "0")
				break;
			cin.ignore();
			cout << "<Nhan Enter de tiep tuc quy trinh nhap hang!>";
			cin.ignore();
			curGroup = s->getGOGsFromWHouse(options);
			break;
		}
		cout << "\033[31m" << "<Khong ton tai ma NH!>\n";
		cout << "\033[31m" << "<Tien hanh nhap lai^^!\033[37m>";
		Sleep(1000);



	} while (1);
	if (options == "0") {
		curGroup = newGOGs(s);
		s->addGOGs(curGroup);
		Sleep(500);

		detailWHouse(s);

		cout << "<Nhan Enter de tiep tuc quy trinh nhap hang!>";
	}

	PhieuNhapKho* l;
	l = createImportInvoice(s,curGroup);
	if (!l)
		return;
	Sleep(500);
	cout << "<Bat dau nhap hang!>";
	Sleep(500);
	itemImport* temp = l->head;
	Goods* newMH;
	while (temp) {
		newMH = goodsCheckByName(curGroup, temp->itemName);
		if (newMH) {
			cout << "<Mat hang" << temp->itemName << "<Da ton tai trong kho!>\n";
			cout << "<Ban co muon cap nhat lai gia mat hang?[1][0]>\n";
			cout << "Gia cu:" << newMH->donGia << endl;
			cout << "Lua chon: ";
			bool options;
			cin >> options;
			if (options)
				newMH->donGia = temp->itemPrice;
			newMH->soLuong += temp->Quantity;
		}
		else {
			newMH = new Goods(s->ranDomID++, temp->itemName, temp->Quantity, temp->Unit, temp->itemPrice);
			curGroup->addGoods(newMH);
		}
		temp = temp->next;
	}

	cout << "\n2000 YEAR LATER~~\n";
	Sleep(2000);
	s->update();
	cout << "<Nhap hang hoan tat!>\n";
	cin.ignore();
	cout << "<Nhan Enter de Ve Menu chinh!>";
	cin.ignore();





}

PhieuNhapKho* createImportInvoice(Warehouse* w,GOGs *g) {

	system("cls");
	time_t t = time(0);
	PhieuNhapKho* l;
	string maPhieu;
	string itemID;
	string tenMH;
	string DV;
	int soLuong;
	int gia;
	struct tm* Now = localtime(&t);
	cout << "<Tien hanh tao Phieu Nhap Kho!>\n";
	cout << "Kho " << "\033[35m" << w->tenKho << "\033[37m" << " ngay " << right << "Ngay " << Now->tm_mday << " thang " << 1 + Now->tm_mon << " nam " << 1900 + Now->tm_year << endl;
	cout << "Nhap ma Phieu           :";
	cin.ignore();
	getline(cin, maPhieu);
	Date temp;
	cout << "Nhap ngay nhap: ";
	cin >> temp.day;
	cout << "Nhap thang nhap: ";
	cin >> temp.month;
	cout << "Nhap nam nhap: ";
	cin >> temp.year;
	l = new PhieuNhapKho(maPhieu, w->maKho, temp);
	cin.ignore();
	do {
		cout << "_______________________________________________\n";
		cout << "Nhap ten mat hang       :";
		getline(cin, tenMH);

		cout << "Nhap don vi cua mat hang:";
		getline(cin, DV);
		do
		{
		cout << "Nhap so luong mat hang  :";
		cin >> soLuong;
		if (soLuong < 0)
			cout << "So khong hop le!\nVui long nhap lai!\n";

		} while (soLuong<0);
		do
		{
		cout << "Nhap don gia cua mat hang :";
		cin >> gia;
		if (gia < 0) {
			cout << "So khong hop le!\nVui long nhap lai!\n";
		}
		} while (gia<0);
		l->append(tenMH, DV, gia, soLuong);
		cout << "<Tiep tuc/Dung-[1]/[0]>\n";
		cout << "Lua chon:";
		bool options;
		cin >> options;
		cin.ignore();
		if (!options)
			break;
	} while (1);
	string options;
	do
	{
		printImportInvoice(l);
		cout << "<\033[31m" << "Xac nhan nhap kho voi phieu nay!OK[1]/NO[0]\033[37m:";
		cin >> options;
		if (options == "0") {
			cout << "Ban co muon tao phieu moi![1][0]: ";
			cin >> options;
			if (options == "1")
				return createImportInvoice(w,g);
			else
			{
				cout << "Nhap hang khong thanh cong!";
				return NULL;
			}
		}

	} while (options != "1");
	ghiFileNhapBaoCao(l);
	cout << "Da khoi tao phieu xuat kho thanh cong!\n";	Sleep(700);
	return l;


}
bool exportRPValid(GOGs* g, PhieuXuatKho* l) {
	ExportItem* temp = l->head;
	while (temp) {
		int sll = g->getGoodsByID(temp->maHang)->soLuong;
		ExportItem* temp2 = temp;
		while (temp2) {
			if (temp->maHang == temp2->maHang) {
				sll -= temp2->soLuongXuat;
				if (sll < 0) {
					return false;
				}
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return true;
}

void swap_2MatHang(Goods* p, Goods* q)
{
	//Doi du lieu ten Mathang 
	string tmp = p->tenMatHang;
	p->tenMatHang = q->tenMatHang;
	q->tenMatHang = tmp;

	//Doi du lieu ma Mat Hang
	long long  tmp2 = p->maMatHang;
	p->maMatHang = q->maMatHang;
	q->maMatHang = tmp2;

	//Doi du lieu don gia
	int tmp3 = p->donGia;
	p->donGia = q->donGia;
	q->donGia = tmp3;

	//Doi du lieu don vi tinh
	string tmp4 = p->donViTinh;
	p->donViTinh = q->donViTinh;
	q->donViTinh = tmp4;

	//Doi du lieu so luong
	int tmp5 = p->soLuong;
	p->soLuong = q->soLuong;
	q->soLuong = tmp5;
}

int demSoLuongCacLoaiMatHang(Warehouse* kho)
{
	int dem = 0;
	for (GOGs* k = kho->head; k != NULL; k = k->next)
	{
		for (Goods* l = k->head; l != NULL; l = l->next)
		{
			dem++;
		}
	}
	return dem;
}


void printImportInvoice(PhieuNhapKho* l) {
	system("cls");
	cout << "----------------------------------------------------------------------------------------------------------\n";

	cout << setw(62) << right << "   PHIEU NHAP KHO  " << endl << endl;
	cout << setw(45) << right << "Ngay " << l->ngayNhap.day << " thang " << l->ngayNhap.month << " nam " << l->ngayNhap.year << endl;
	cout << "MA KHO NHAP:" << l->maKho << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+\n";
	cout << setw(5) << left << "| STT";
	cout << setw(30) << left << "| TEN MAT HANG";
	cout << setw(10) << left << "| DON VI";
	cout << setw(15) << left << "| SO LUONG";
	cout << setw(15) << left << "| GIA";
	cout << setw(15) << left << "| THANH TIEN";
	cout << "|" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+\n";
	int stt = 1; long long tong = 0;
	long long thanhTien = 0;
	for (itemImport* k = l->head; k != NULL; k = k->next)
	{
		thanhTien = k->itemPrice * k->Quantity;
		cout << "  " << setw(5) << left << stt;
		cout << setw(30) << left << k->itemName;
		cout << setw(10) << left << k->Unit;
		cout << setw(15) << left << k->Quantity;
		cout << setw(15) << left << k->itemPrice;
		cout << setw(15) << left << thanhTien;
		tong += thanhTien;
		cout << endl;
		stt++;
	}
	cout << setw(98) << right << "TONG: " << tong << endl;
}
void printExportInvoice(GOGs* s, PhieuXuatKho* l) {
	system("cls");
	cout << "----------------------------------------------------------------------------------------------------------\n";

	cout << setw(62) << right << "   PHIEU XUAT KHO  " << endl << endl;
	cout << setw(45) << right << "Ngay " << l->ngayXuat.day << " thang " << l->ngayXuat.month << " nam " << l->ngayXuat.year << endl;
	cout << "MA KHO XUAT:" << l->maKho << endl;
	cout << "NHOM HANG XUAT:" << s->tenNhomHang << endl;
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
	long long tong = 0;
	long long thanhTien = 0;
	for (ExportItem* k = l->head; k != NULL; k = k->next)
	{
		thanhTien = k->soLuongXuat * s->getGoodsByID(k->maHang)->donGia;
		cout << "  " << setw(5) << left << stt;
		cout << setw(30) << left << s->getGoodsByID(k->maHang)->tenMatHang;
		cout << setw(10) << left << s->getGoodsByID(k->maHang)->donViTinh;
		cout << setw(15) << left << k->soLuongXuat;
		cout << setw(15) << left << s->getGoodsByID(k->maHang)->donGia;
		cout << setw(15) << left << thanhTien;
		tong = tong + thanhTien;
		cout << endl;
		stt++;
	}
	cout << setw(98) << right << "TONG: " << tong << endl;
}




