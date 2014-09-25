/* Project 102: 61160427 (difficult version) written by Nikolov

I. Да се състави клас - описател на клетка от таблица

Скрити член променливи:
реална стойност
стрингова стойност
ред
колона
тип на данните - символ

Конструктори:
-експлицитен
-копиращ

Функции за четене/запис на член променливите, необходимите оператори,
включващи оператор за четене и извеждане от/към поток

II. Да се състави клас ( CData ), описващ редовете от таблица,
съставена от клетки, съдържащ в себе си частни член променливи:
съдържание на таблицата (списък от указатели към обекти клетка)
брой на валидните колони в таблицата
брой на валидните редове в таблицата

Конструктор:
по броя на валидните колони и редове

Деструктор

Функции:

II.1.  за четене на членовете

II.2.  установяване типа на данние по зададена колона и тип

II.3.  за добавяне на клетка в таблицата-колоните трябва да са с еднакъв тип данни

II.4.  за изчисление на сума(конкатенация) от данните (за всички)

II.5.  за изчисляване на средна стойност на числова колона-грешка ако не може да се изчисли (за всички)

II.6.  образува/връща обект CData, по зададен блок : ред/колона и ред/колона

II.7.  запълва колона със случайни данни, генерирани по типа на колоната

II.8.  преобразува/валидизира таблицата - колоните трябва да се с еднакъв тип данни;
II.9.  извлича /връща невалидните клетки;

II.10. установява от зададена колона и от ред до ред с подадена стойност

Главна функция:Да се зареди таблица и се тестват функциите
на таблицата.(без използване на оператор за цикъл)
*/


#include <iostream>
#include <string>
#include <list>
#include <random>
#include <limits>
#include <utility>
#include <cstddef>

#include <fstream>

const long double NAN = std::numeric_limits<long double>::signaling_NaN();

void ClearStream(std::istream& iss) {
	iss.clear();
	iss.sync();
}

void ClearStream(std::ostream& oss) {
	oss.clear();
	oss.flush();
}

class Cell {				//клас описател на клетка от таблица

	//скрити член променливи (в c++ в class по подразбиране членовете са private)
	long double ldReal_;			//реална стойност
	std::string strStr_;			//стрингова стойност
	unsigned int uintRow_;		//ред
	unsigned int uintColumn_;	//колона
	char chType_;					//тип на данните - символ

	Cell(Cell&&);
	Cell& operator=(Cell&&);

public:

	//конструктор по подразбиране
	Cell() : ldReal_(0), uintRow_(0), uintColumn_(0), chType_('E') {
		strStr_.clear();
	}
	
	//конструктор на празна клетка с посочени ред и колона
	/*Cell(const unsigned int row, const unsigned int column) : ldReal_(0), chType_('E') {
		
		strStr_.clear();
		uintRow_ = row;
		uintColumn_ = column;
	}*/

	//експлицитен конструктор за реална стойност на данните в клетката
	Cell(const long double real, const unsigned int row, const unsigned int column) : chType_('R') {
		
		ldReal_ = real;
		strStr_.clear();
		uintRow_ = row;
		uintColumn_ = column;
	}

	//експлицитен конструктор за стрингова стойност на данните в клетката
	Cell(const std::string& str, const unsigned int row, const unsigned int column) : ldReal_(NAN), chType_('S') {
		
		strStr_ = str;
		uintRow_ = row;
		uintColumn_ = column;
	}

	/*Cell(const long double real, const std::string& str, 
		const int row, const int column, const char type) {

			ldReal_ = real;
			strStr_ = str;
			uintRow_ = row;
			uintColumn_ = column;
			chType_ = type;
	}*/

	//copy constructor
	Cell(const Cell& ob) {
		
		ldReal_ = ob.ldReal_;
		strStr_ = ob.strStr_;
		uintRow_ = ob.uintRow_;
		uintColumn_ = ob.uintColumn_;
		chType_ = ob.chType_;
	}

	//copy assignment operator
	Cell& operator= (const Cell &ob) {

		ldReal_ = ob.ldReal_;
		strStr_ = ob.strStr_;
		uintRow_ = ob.uintRow_;
		uintColumn_ = ob.uintColumn_;
		chType_ = ob.chType_;
		
		return *this;
	}

	//чете реална стойност
	long double GetReal() const{
		
		return ldReal_;
	}

	std::string GetStr() const{
		
		return strStr_;
	}

	unsigned int GetRow() const{
		
		return uintRow_;
	}

	unsigned int GetColumn() const{
		
		return uintColumn_;
	}

	char GetType() const{
		
		return chType_;
	}

	//запис на реална стойност
	void SetReal(const long double real) {
		
		ldReal_ = real;
		strStr_.clear();
		chType_ = 'R';
	}

	void SetStr(const std::string& str) {
		
		try {
			strStr_ = str;
			chType_ = 'S';
			ldReal_ = NAN;
		}
		catch(const std::length_error&) {
			strStr_.clear();
			chType_ = 'S';
			ldReal_ = NAN;
		}
		catch(std::bad_alloc&) {
			strStr_.clear();
			chType_ = 'S';
			ldReal_ = NAN;
		}
	}

	void SetRow(const unsigned int row) {
		
		uintRow_ = row;
	}

	void SetColumn(const unsigned int column) {
		
		uintColumn_ = column;
	}

	void SetType(const char type) {

		if(type == 'R')
			chType_ = type;
		else if(type == 'E')
			chType_ = type;
		else
			chType_ = 'S';
	}

	Cell operator+ (const Cell& ob) {
		
		Cell temp;
		temp.chType_ = chType_;
		temp.ldReal_ = ldReal_ + ob.ldReal_;
		temp.strStr_ = strStr_ + ob.strStr_;

		return temp;
	}
	
	friend std::istream& operator>> (std::istream& is, Cell& ob);
	friend std::ostream& operator<< (std::ostream& os, const Cell& ob);

};

bool byrowcolumn(Cell *ob1, Cell *ob2) {
		
	if(ob1->GetRow() < ob2->GetRow())
		return true;
	else if(ob1->GetRow() > ob2->GetRow())
		return false;
	else return ob1->GetColumn() < ob2->GetColumn() ? true : false;
}

bool roworcolumnNULL(Cell *theElement) {
	if(!theElement->GetRow() || !theElement->GetColumn() || 
		!(theElement->GetType() == 'E' || theElement->GetType() == 'R' || 
		theElement->GetType() == 'S')) {
		delete theElement;
		return true;
	}
	return false;
}

bool deleteAll(Cell *theElement) {
	delete theElement;
	return true;
}

class CData {

	std::list<Cell*> table;
	unsigned int iVldR;
	unsigned int iVldC;

public:

	CData() {
		iVldR = NULL;
		iVldC = NULL;
	}

	/*CData(const int &VldR, const int &VldC) {
		
		iVldR = VldR;
		iVldC = VldC;

		for(int i=0; i<VldR; i++)
			for(int j=0; j<VldC; j++)
				table.push_back(new Cell(0, "", i+1, j+1, 'E'));;

	}*/

	~CData() {
		table.remove_if(deleteAll);
		iVldR = NULL;
		iVldC = NULL;
	}

	int GetiVldR() {
		return iVldR;
	}

	int GetiVldC() {
		return iVldC;
	}

	std::list<Cell*> Gettable() {
		return table;
	}

	void ColumnToRorS(const unsigned int &n, const char &type) {
		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it)
			if((*it)->GetColumn() == n)
				(*it)->SetType(type);
	}

	/*void AddCell(const Cell &ob) {

		if(ob.GetColumn() > iVldC && ob.GetRow())
			table.push_back(new Cell(ob));
		else if(!ob.GetColumn() || !ob.GetRow())
			return;
		else {
			table.sort(byrowcolumn);
			for(std::list<Cell*>::iterator it=table.begin(); (*it)->GetRow() < 2; ++it)
				if(ob.GetColumn() == (*it)->GetColumn()) {
					if(iVldR < ob.GetRow()) {
						table.push_back(new Cell(ob));
						(table.back())->SetType((*it)->GetType());
						break;
					}
					else {
						char type = (*it)->GetType();
						//(*(*it)) = ob;
						(*it)->SetType(type);
						break;
					}
				}
		}
	}*/

	std::pair<std::string, long double> SumConc() {

		long double result = 0;
		std::string conc;

		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetType() == 'R')
				result += (*it)->GetReal();
			else if((*it)->GetType() == 'S') {
				conc += (*it)->GetStr();
			}
		}
		std::pair<std::string, long double> retpair (conc, result);
		return retpair;
	}

	long double AverageReal() {

		long double result = 0;
		unsigned int num = 0;
		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetType() == 'R') {
				result += (*it)->GetReal();
				num++;
			}
		}

		return result/num;
	}

	CData CDataFromTo(const unsigned int &Row, const unsigned int &Column, 
		const unsigned int &Row2, const unsigned int &Column2) {
		
		unsigned int row1 = Row;
		unsigned int column1 = Column;
		unsigned int row2 = Row2;
		unsigned int column2 = Column2;

		CData ob;
		std::list<Cell*>::iterator it;

		if(row1 > row2) {
			int Rowt;
			Rowt = row1;
			row1 = row2;
			row2 = Rowt;
		}
		if(column1 > column2) {
			int Columnt;
			Columnt = column1;
			column1 = column2;
			column2 = Columnt;
		}

		if(!row1 || !column1 || !row2 || !column2 || 
			row1 < 1 || row2 > iVldR || column1 < 1 || column2 > iVldC) {
			ob.iVldR = 0;
			ob.iVldC = 0;
			return ob;
		}

		ob.iVldR = row2 - row1 + 1;
		ob.iVldC = column2 - column1 + 1;
		
		for(it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetRow() >= row1 && (*it)->GetRow() <= row2) {
				if((*it)->GetColumn() >= column1 && (*it)->GetColumn() <= column2) {
					ob.table.push_back((*it));
					if(row1 == row2 && column1 == column2)
						break;
				}
			}
		}

		ob.table.sort(byrowcolumn);

		it=table.begin();
		for(unsigned int i = 0; i < ob.iVldR; i++)
			for(unsigned int j = 0; j < ob.iVldC; j++) {
				(*it)->SetRow(i+1);
				(*it)->SetColumn(j+1);
				it++;
			};

		return ob;
	}

	void RandData(const unsigned int column) {

		std::random_device rd;

		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetColumn() == column) {
				if((*it)->GetType() == 'R') {
					std::uniform_real_distribution<long double> distribution(std::numeric_limits<long double>::min(),std::numeric_limits<long double>::max());
					(*it)->SetReal(distribution(rd));
				}
				else if((*it)->GetType() == 'S') {
					std::string str;
					std::uniform_int_distribution<int> distribution(0,10);
					std::uniform_int_distribution<int> dis(0,255);
					int j = distribution(rd);
					for(int i = 0; i<j; i++)
						//str.push_back(dis(rd));

					(*it)->SetStr(str);
				}
			}
		}
	}

	void SetallColumn() {
		
		table.remove_if(roworcolumnNULL);
		
		std::vector<char> firstrowTypes(iVldC);
		table.sort(byrowcolumn);

		std::list<Cell*>::iterator it;
		unsigned int i = 0;
		for(it=table.begin(); (*it)->GetRow() < 2; ++it) {
			firstrowTypes[i] = (*it)->GetType();
			i++;
		}

		for(; it!=table.end(); ++it) {
			(*it)->SetType(firstrowTypes[(*it)->GetColumn() - 1]);
		}

	}

	std::list<Cell*> GetInvalidCells() {

		std::list<Cell*> inv;

		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if(!(*it)->GetRow() || !(*it)->GetColumn() || !((*it)->GetType() == 'E' || 
				(*it)->GetType() == 'R' || (*it)->GetType() == 'S')) {
					inv.push_back((*it));
			}
			else if((*it)->GetType() == 'E' && ((*it)->GetReal() || (*it)->GetStr() != "")) {
				inv.push_back((*it));
			}
			else if((*it)->GetType() == 'R' && ((*it)->GetReal() - (*it)->GetReal())) {
				inv.push_back((*it));
			}
		}

		return inv;
	}

	void SetCfR1toR2(const long double &Real, const unsigned int &Column, 
		const unsigned int &Row1, const unsigned int &Row2) {

		unsigned int row1 = Row1;
		unsigned int row2 = Row2;

		if(row1 > row2) {
			int Row;
			Row = row1;
			row1 = row2;
			row2 = Row;
		}

		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetColumn() == Column && (*it)->GetRow() >= row1 && 
				(*it)->GetRow() <= row2) {
					(*it)->SetReal(Real);
					if(row1 == row2)
						break;
			}
		}
	}

	void SetCfR1toR2(const std::string &Str, const unsigned int &Column, 
		const unsigned int &Row1, unsigned const int &Row2) {

		unsigned int row1 = Row1;
		unsigned int row2 = Row2;

		if(row1 > row2) {
			int Row;
			Row = row1;
			row1 = row2;
			row2 = Row;
		}

		for(std::list<Cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetColumn() == Column && (*it)->GetRow() >= row1 && 
				(*it)->GetRow() <= row2) {
					(*it)->SetStr(Str);
					if(row1 == row2)
						break;
			}
		}
	}
};

std::istream &operator>> (std::istream &is, Cell &ob) {

	is.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	std::streampos pos = is.tellg();

	try {
		Cell temp;
		is>>temp.chType_;

		if(temp.chType_ == 'R') {
			is>>temp.ldReal_;
			temp.strStr_.clear();
		}
		else if(temp.chType_ == 'S') {
			temp.ldReal_ = NAN;
			is>>temp.strStr_;
		}
		else {
			temp.chType_ = 'E';
			temp.ldReal_ = 0;
			temp.strStr_.clear();
		}
		
		is>>temp.uintRow_;
		is>>temp.uintColumn_;

		ob = temp;
	}
	catch(const std::ios_base::failure) {
		ClearStream(is);
		is.ignore('R'||'S'||'E');
	}

	return is;
}

std::ostream &operator<< (std::ostream &os, const Cell &ob) {
	
	//std::streampos pos = os.tellp();
	os.exceptions(std::ios_base::failbit | std::ios_base::badbit);

	try {
		os<<ob.chType_<<" ";
		
		if(ob.chType_ == 'R')
			os<<ob.ldReal_;
		else if(ob.chType_ == 'S')
			os<<ob.strStr_;
		else os<<"";
		
		os<<" "<<ob.uintRow_<<" "<<ob.uintColumn_<<" ";
	}
	catch(std::ios_base::failure) {
		ClearStream(os);
		//os.seekp(os.tellp()-pos);

	}
	
	return os;
}



//В main ВСИЧКО Е ЗА ТЕСТВАНЕ, А НЕ В ГОТОВ ВАРИАНТ!!!
void main() {
	Cell ob88;
	Cell ob1("1leva1", 13, 14);
	Cell ob5("123456", 10, 9);
	Cell ob2(3.21845215553, 99, 100);
	Cell ob3 = ob1;
	Cell ob4 = ob2;
	
	//std::cin>>ob4;
	//std::cin>>ob2;

	//std::cin>>ob88;

	std::fstream outfile;
	outfile.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	try {
		//outfile.open ("test.txt");
		
		//outfile<<ob1;
		//outfile.close();
		
		//ако се чудиш защо тук не влиза - нямаш файл test.txt
		outfile.open ("test.txt");
		outfile>>ob2;
		outfile.close();
	}
	catch(std::ios_base::failure){}

	std::cout<<ob4;
	std::cout<<ob4;
	//CData ob6(3, 5);
	//ob6.ColumnToRorS(1, 'S');
	CData ob7;
	//ob6.SumConc();
	//ob6.RandData(2);
}