#include"Header.h"
#include"Object.h"

void saveGoods(Warehouse *w,GOGs* s) {
	Goods* temp = s->head;
	if (!temp)
		return;
	ofstream fout(w->maKho+"Warehouse/GroupofGoods/"+ s->maNhomHang);
	string Data;
	while (temp != NULL) {
		Data += temp->tenMatHang + "," + " " + to_string(temp->maMatHang) + " " + to_string(temp->soLuong) + temp->donViTinh + "," + to_string(temp->donGia)+'\n';
		temp = temp->next;
	}
	Data.pop_back();
	fout << Data;
	fout.close();
	return;
}
void saveGOGs(Warehouse* s) {
	GOGs* temp = s->head;
	if (!temp)
		return;
	string Data;
	ofstream fout(s->maKho + "Warehouse/DataGOGS");
	while (temp != NULL) {
		Data+= temp->tenNhomHang + "," + temp->maNhomHang + "," + temp->ghiChu + "," + " " + to_string(temp->SLMH) + '\n';
		saveGoods(s,temp);
		temp = temp->next;
	}
	Data.pop_back();
	fout << Data;
	fout.close();
}
void BackupMH(Warehouse* w,GOGs* s) {

	ifstream fin(w->maKho + "Warehouse/GroupofGoods/" + s->maNhomHang);
	if (!fin) {
		cout << "Kho mo dc file!\n";
		return;
	}
	Goods* temp = NULL;
	string ptemp;
	int ntemp;
	while (!fin.eof()) {
		temp = new Goods;
		getline(fin, ptemp, ',');
		temp->tenMatHang = ptemp;
		fin >> ntemp;
		temp->maMatHang = ntemp;
		fin >> ntemp;
		temp->soLuong = ntemp;
		getline(fin, ptemp, ',');
		temp->donViTinh = ptemp;

		fin >> ntemp;
		temp->donGia = ntemp;
		s->addGoods(temp);
		getline(fin,ptemp, '\n');
	}

}

void BackupGOGs(Warehouse* s) {
	ifstream fin(s->maKho + "Warehouse/DataGOGS");
	if (!fin) {
		cout << "Kho mo dc file!\n";
		return;
	}
	GOGs* temp = NULL;
	string ptemp;
	int ntemp;
	while (!fin.eof()) {
		temp = new GOGs;
		getline(fin, ptemp, ',');

		temp->tenNhomHang = ptemp;
		getline(fin, ptemp, ',');
		temp->maNhomHang = ptemp;
		getline(fin, ptemp, ',');
		temp->ghiChu = ptemp;
		fin >> ntemp;
		temp->SLMH = ntemp;
		BackupMH(s,temp);
		s->addGOGs(temp);
		getline(fin, ptemp, '\n');
	}


}
void Backup(string makho,Warehouse* s) {

	ifstream fin(makho + "WareHouse/DataWH");
	int ntemp = 0;
	string ptemp = "";
	getline(fin, ptemp, ',');
	s->tenKho = ptemp;
	getline(fin, ptemp, ',');
	s->maKho = ptemp;
	getline(fin, ptemp, ',');
	s->diaDiem = ptemp;
	fin >> ntemp;
	s->ranDomID = ntemp;
	BackupGOGs(s);

}