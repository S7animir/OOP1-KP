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
(int GetiVldR();	int GetiVldC();		std::list<cell*> Gettable())

II.2.  установяване типа на данние по зададена колона и тип
(void ColumnToRorS(const int &n, const char &type))

II.3.  за добавяне на клетка в таблицата-колоните трябва да са с еднакъв тип данни

II.4.  за изчисление на сума(конкатенация) от данните
(void SumConc(const int &RowD, const int &ColumnD, 
	const int &RowOp1, const int &ColumnOp1, const int &RowOp2, const int &ColumnOp2))

II.5.  за изчисляване на средна стойност на числова колона-грешка ако не може да се изчисли;
(void AverageReal(const int &fromColumn, const int &Row, const int &Column))

II.6.  образува/връща обект CData, по зададен блок : ред/колона и ред/колона;
(CData CDataFromTo(const int &Row, const int &Column, const int &Row2, const int &Column2))

II.7.  запълва колона със случайни данни, генерирани по типа на колоната
(void RandData(const int &Column))

II.8.  преобразува/валидизира таблицата - колоните трябва да се с еднакъв тип данни;
II.9.  извлича /връща невалидните клетки;

II.10. установява от зададена колона и от ред до ред с подадена стойност
(void SetCfR1toR2(const long double &Real, const int &Column, const int &Row1, const int &Row2);
void SetCfR1toR2(const std::string &Str, const int &Column, const int &Row1, const int &Row2))

Главна функция:Да се зареди таблица и се тестват функциите
на таблицата.(без използване на оператор за цикъл)
*/


#include <iostream>
#include <string>
#include <list>
#include <random>
#include <limits>
#include <utility>
#include <vector>
#include <cstddef>

const long double NAN = std::numeric_limits<long double>::signaling_NaN();

void clearstream(std::istream& iss) {
	iss.clear();
	iss.sync();
}


class Cell {				//клас описател на клетка от таблица

	//скрити член променливи (в c++ в class по подразбиране членовете са private)
	long double ldReal_;			//реална стойност
	std::string strStr_;			//стрингова стойност
	unsigned int uintRow_;		//ред
	unsigned int uintColumn_;	//колона
	char chType_;					//тип на данните - символ

public:

	//конструктор по подразбиране
	Cell() : ldReal_(0), strStr_(""), uintRow_(0), uintColumn(0), chType_('E') {}
	
	//конструктор на празна клетка с посочени ред и колона
	Cell() : ldReal_(0), strStr_(""), chType_('E') 
		   (const unsigned int row, const unsigned int column) {
		
			   uintRow_ = row;
			   uintColumn_ = column;
	}

	//експлицитен конструктор за реална стойност на данните в клетката
	Cell() : strStr_(""), chType_('R') 
		(const long double real, const unsigned int row, const unsigned int column) {
			
			ldReal_ = real;
			uintRow_ = row;
			uintColumn_ = column;
	}

	//експлицитен конструктор за стрингова стойност на данните в клетката
	Cell() : ldReal_(NAN), chType_('S') 
		(const std::string& str, const unsigned int row, const unsigned int column) {
			
			//std::string::size_type sz;
			
			strStr_ = str;
			uintRow_ = row;
			uintColumn_ = column;

		//C++ 11	long double stold (const string&  str, size_t* idx = 0);
		/*try {
			ldReal = stold(Str, &sz);
			if(sz != Str.length())		//ако целият стринг не е число
				ldReal = NULL;			//реалната стойност се нулира
		}
		catch(const std::invalid_argument&) {
			ldReal = NULL;
		}
		catch(const std::out_of_range&) {
			ldReal = NULL;
		}*/
	}

	Cell(const long double real, const std::string& str, 
		const int row, const int column, const char type) {

			ldReal_ = real;
			strStr_ = str;
			uintRow_ = row;
			uintColumn_ = column;
			chType_ = type;
	}

	//copy assignment operator
	Cell& operator=( const Cell& ob) {

		ldReal_ = ob.ldReal_;
		strStr_ = ob.strStr_;
		uintRow_ = ob.uintRow_;
		uintColumn_ = ob.uintColumn_;
		chType_ = ob.chType_;
	}

	//copy constructor
	Cell(const cell& ob) {
		
		this = ob;
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
		chType_ = 'R';
		/*try {
			strStr = std::to_string(Real);
		}
		catch(const std::out_of_range&) {
			strStr = "";
		}
		catch(const std::length_error&) {
			strStr = "";
		}
		catch(std::bad_alloc&) {
			strStr = "";
		}*/
	}

	void SetStr(const std::string& str) {
		
		try {
			strStr_ = str;
			chType_ = 'S';
		}
		catch(const std::length_error&) {
			strStr_ = "";
			chType_ = 'S';
		}
		catch(std::bad_alloc&) {
			strStr_ = "";
			chType_ = 'S';
		}
	}

	void SetRow(const unsigned int row) {
		
		uintRow_ = row;
	}

	void SetColumn(const unsigned int column) {
		
		uintColumn_ = column;
	}

	void SetType(const char type) {

		if(type === 'R')
			chType_ = type;
		else if(type === 'E')
			chType_ = type;
		else
			chType_ = 'S';

		/*if(Type == 'R') {
			
			if(chType == 'S') {
				try {
					std::string::size_type sz;
					ldReal = stold(strStr, &sz);
					if(sz != strStr.length())		//ако целият стринг не е число
													//реалната стойност = NaN (Not a Number)
						ldReal = std::numeric_limits<long double>::signaling_NaN();
				}
				catch(const std::invalid_argument&) {
					ldReal = std::numeric_limits<long double>::signaling_NaN();
				}
				catch(const std::out_of_range&) {
					ldReal = std::numeric_limits<long double>::signaling_NaN();
				}
			}
			chType = 'R';
		}
		else if(Type == 'S') {

			if(chType == 'R') {
				try {
					strStr = std::to_string(ldReal);
				}
				catch(const std::out_of_range&) {
					strStr = "";
				}
				catch(const std::length_error&) {
					strStr = "";
				}
				catch(std::bad_alloc&) {
					strStr = "";
				}
			}
			chType = 'S';
		}
		else{
			chType = 'E';
			ldReal = 0;
			strStr = "";
		}*/


		/*chType = Type;
		if(chType == 'R') {
			strStr = "";
		}
		else if(chType == 'S')
			ldReal = NULL;
		else if(chType == 'E') {
			strStr = "";
			ldReal = NULL;
		}else {
			strStr = "ERROR";
			ldReal = NULL;
		}*/

		/*if(chType == 'R' && Type != 'R')
			chType = 'E';
		else if(chType == 'S' && Type != 'S')
			chType = 'E';
		else if(chType == 'V' && (Type == 'R' || Type == 'S'))
			chType = Type;
		else if(chType == 'E' && (Type == 'R' || Type == 'S' || Type == 'V'))
			Setcell(0, "", Type, iRow, iColumn);*/
	}

	/*void SetCell(const long double real, const std::string& str, const int row, 
		const int column, const char type) {
			
			ldReal_ = real;
			strStr = Str;
			chType = Type;
			iRow = Row;
			iColumn = Column;
	}*/

	//оператор + (събира при тип на данните реален, конкатинира при тип на данните стрингов)
	//при не съответствие на данните chType = 'G'  за грешка
	/*cell operator+ (const cell &ob) {
		cell temp;

		if(ob.chType == 'R' && chType == 'R')
			return (temp.Setcell(ldReal + ob.ldReal, "", 'R', 0, 0), temp);
		else if(ob.chType == 'S' && chType == 'S')
			return (temp.Setcell(std::numeric_limits<long double>::signaling_NaN(), 
			strStr + ob.strStr, 'S', 0, 0), temp);
		else if(ob.chType == 'E')
			return temp = *this;
		else if(chType == 'E')
			return ob;
		else if(chType == 'R' && ob.chType == 'S')
			return(temp.Setcell(ldReal + ob.ldReal, "", 'R', 0, 0), temp);
		
		return(temp.Setcell(ldReal + ob.ldReal, strStr + ob.strStr, 'S', 0, 0), temp);*/

		/*if(ob.chType == 'R' && chType == 'R')
			return (temp.Setcell(ldReal + ob.ldReal, "", 'R', 0, 0), temp);
		else if(ob.chType == 'S' && chType == 'S')
			return (temp.Setcell(std::numeric_limits<long double>::signaling_NaN(), 
			strStr + ob.strStr, 'S', 0, 0), temp);
		else if(ob.chType == 'E')
			return temp = *this;
		else if(chType == 'E')
			return ob;
		//else if(chType == 'R' && ob.chType == 'S')
			//return(temp.Setcell(ldReal + ob.ldReal, "", 'R', 0, 0), temp);
		
		temp.Setcell(NULL, "ERROR!!!", 'G', 0, 0);
		return temp;*/
	//}

	//cell operator= (const cell &ob) {

		//chType = ob.chType;
		//ldReal = ob.ldReal;
		//strStr = ob.strStr;

		/*if(chType == 'V') {
			chType = ob.chType;
			if(chType == 'R')
				ldReal = ob.ldReal;
			else if(chType == 'S')
				strStr = ob.strStr;
			else 
		}
		else if(ob.chType == 'R' && chType == 'R') {
			ldReal = ob.ldReal;
		}
		else if(ob.chType == 'S' && chType == 'S') {
			strStr = ob.strStr;
		}
		else Setcell(NULL, "", 'E', iRow, iColumn);*/

		//return *this;

	//}



	friend std::istream& operator>> (std::istream& is, Cell& ob);
	friend std::ostream& operator<< (std::ostream& os, const Cell& ob);

};

bool byrowcolumn(cell *ob1, cell *ob2) {
		
	if(ob1->GetiRow() < ob2->GetiRow())
		return true;
	else if(ob1->GetiRow() > ob2->GetiRow())
		return false;
	else return ob1->GetiColumn() < ob2->GetiColumn() ? true : false;
}

bool roworcolumnNULL(cell *theElement) {
	if(!theElement->GetiRow() || !theElement->GetiColumn() || 
		!(theElement->GetchType() == 'E' || theElement->GetchType() == 'R' || 
		theElement->GetchType() == 'S')) {
		delete theElement;
		return true;
	}
	return false;
}

bool deleteAll(cell *theElement) {
	delete theElement;
	return true;
}

class CData {

	std::list<cell*> table;
	unsigned int iVldR;
	unsigned int iVldC;

public:

	CData() {
		iVldR = NULL;
		iVldC = NULL;
	}

	CData(const int &VldR, const int &VldC) {
		
		iVldR = VldR;
		iVldC = VldC;

		for(int i=0; i<VldR; i++)
			for(int j=0; j<VldC; j++)
				table.push_back(new cell(0, "", i+1, j+1, 'E'));;

	}

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

	std::list<cell*> Gettable() {
		return table;
	}

	void ColumnToRorS(const unsigned int &n, const char &type) {
		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it)
			if((*it)->GetiColumn() == n)
				(*it)->SetchType(type);
	}

	void AddCell(const cell &ob) {

		if(ob.GetiColumn() > iVldC && ob.GetiRow())
			table.push_back(new cell(ob));
		else if(!ob.GetiColumn() || !ob.GetiRow())
			return;
		else {
			table.sort(byrowcolumn);
			for(std::list<cell*>::iterator it=table.begin(); (*it)->GetiRow() < 2; ++it)
				if(ob.GetiColumn() == (*it)->GetiColumn()) {
					if(iVldR < ob.GetiRow()) {
						table.push_back(new cell(ob));
						(table.back())->SetchType((*it)->GetchType());
						break;
					}
					else {
						char type = (*it)->GetchType();
						(*(*it)) = ob;
						(*it)->SetchType(type);
						break;
					}
				}
		}
	}

	std::pair<std::string, long double> SumConc() {

		long double result = 0;
		std::string conc = "";

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetchType() == 'R')
				result += (*it)->GetldReal();
			else if((*it)->GetchType() == 'S') {
				conc += (*it)->GetstrStr();
			}
		}
		std::pair<std::string, long double> retpair (conc, result);
		return retpair;
	}

	long double AverageReal() {

		long double result = 0;
		unsigned int num = 0;
		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetchType() == 'R') {
				result += (*it)->GetldReal();
				num++;
			}
		}

		return result/num;
	}

	/*void SumConc(const int &RowD, const int &ColumnD, 
		const int &RowOp1, const int &ColumnOp1, const int &RowOp2, const int &ColumnOp2) {

			std::list<cell*>::iterator itd;
			std::list<cell*>::iterator itop1;
			std::list<cell*>::iterator itop2;
			for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
				if((*it)->GetiRow() == RowD && (*it)->GetiColumn() == ColumnD)
					itd = it;
				if((*it)->GetiRow() == RowOp1 && (*it)->GetiColumn() == ColumnOp1)
					itop1 = it;
				if((*it)->GetiRow() == RowOp2 && (*it)->GetiColumn() == ColumnOp2)
					itop2 = it;
			}

			(*(*itd)) = (*(*itop1))+(*(*itop2));

	}*/

	/*long double AverageReal() {

		//std::list<cell*>::iterator itres;
		long double result = 0;
		int num = 0;

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetchType() == 'R') {
				result += (*it)->GetldReal();
				num++;
			}
			if((*it)->GetiRow() == Row && (*it)->GetiColumn() == Column)
				itres  = it;
		}

		if(!num) {
			std::cout<<"Can't calculate the average from column "<<fromColumn<<".";
			(*itres)->Setcell(0, "error", 'S', Row, Column);
		}
		else (*itres)->Setcell(result/num, "", 'R', Row, Column);
	}*/

	CData CDataFromTo(const unsigned int &Row, const unsigned int &Column, 
		const unsigned int &Row2, const unsigned int &Column2) {
		
		unsigned int row1 = Row;
		unsigned int column1 = Column;
		unsigned int row2 = Row2;
		unsigned int column2 = Column2;

		CData ob;
		std::list<cell*>::iterator it;

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
			if((*it)->GetiRow() >= row1 && (*it)->GetiRow() <= row2) {
				if((*it)->GetiColumn() >= column1 && (*it)->GetiColumn() <= column2) {
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
				(*it)->SetiRow(i+1);
				(*it)->SetiColumn(j+1);
				it++;
			};

		return ob;
	}

	void RandData(const int &Column) {

		std::random_device rd;

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetiColumn() == Column) {
				if((*it)->GetchType() == 'R') {
					std::uniform_real_distribution<long double> distribution(std::numeric_limits<long double>::min(),std::numeric_limits<long double>::max());
					(*it)->SetldReal(distribution(rd));
				}
				else if((*it)->GetchType() == 'S') {
					std::string str;
					std::uniform_int_distribution<int> distribution(0,10);
					std::uniform_int_distribution<int> dis(0,255);
					int j = distribution(rd);
					for(int i = 0; i<j; i++)
						str.push_back(dis(rd));

					(*it)->SetstrStr(str);
				}
			}
		}
	}

	void SetallColumn() {
		
		table.remove_if(roworcolumnNULL);
		
		std::vector<char> firstrowTypes(iVldC);
		table.sort(byrowcolumn);

		std::list<cell*>::iterator it;
		unsigned int i = 0;
		for(it=table.begin(); (*it)->GetiRow() < 2; ++it) {
			firstrowTypes[i] = (*it)->GetchType();
			i++;
		}

		for(; it!=table.end(); ++it) {
			(*it)->SetchType(firstrowTypes[(*it)->GetiColumn() - 1]);
		}

	}

	std::list<cell*> GetInvalidCells() {

		std::list<cell*> inv;

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if(!(*it)->GetiRow() || !(*it)->GetiColumn() || !((*it)->GetchType() == 'E' || 
				(*it)->GetchType() == 'R' || (*it)->GetchType() == 'S')) {
					inv.push_back((*it));
			}
			else if((*it)->GetchType() == 'E' && ((*it)->GetldReal() || (*it)->GetstrStr() != "")) {
				inv.push_back((*it));
			}
			else if((*it)->GetchType() == 'R' && ((*it)->GetldReal() - (*it)->GetldReal())) {
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

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetiColumn() == Column && (*it)->GetiRow() >= row1 && 
				(*it)->GetiRow() <= row2) {
					(*it)->SetldReal(Real);
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

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetiColumn() == Column && (*it)->GetiRow() >= row1 && 
				(*it)->GetiRow() <= row2) {
					(*it)->SetstrStr(Str);
					if(row1 == row2)
						break;
			}
		}
	}

	/*void SetallColumn() {

		table.sort(byrowcolumn);
		char *pType = new char;

		for(std::list<cell*>::iterator it=table.begin(); it!=table.end(); ++it) {
			if((*it)->GetiRow() == 1) {
				(*pType) = (*it)->GetchType();
				pType++;
			}
			else {
			}
		}
	}*/
};


std::istream &operator>> (std::istream &is, cell &ob)
{


	/*do {
		std::cout<<"\nEnter type of data, R - for number, S - for string :";
		clearstream(is);
		is >> ob.chType;
	}while(ob.chType != 'R' && ob.chType != 'S');

	if(ob.chType == 'R') {
		do {
			clearstream(is);
			std::cout<<"Enter data of type number (Example : 12345.01): ";
			is >> ob.ldReal;
		}while(!is.good());
	}
	else {
		do {
			std::cout<<"Enter data of type string (Example : data): ";
			clearstream(is);
			is >> ob.strStr;
		}while(!is.good());
	}
	
	do{
		clearstream(is);
		std::cout<<"Enter number of the row :";
		is >> ob.iRow;
	}while(!is.good());

	do{
		clearstream(is);
		std::cout<<"Enter number of the column :";
		is >> ob.iColumn;
	}while(!is.good());

    return (clearstream(is), is);*/
}

std::ostream &operator<< (std::ostream &os, const cell &ob) {

	/*if(os.good())
		os<<"\nRow: "<<ob.iRow<<" : Column: "<<ob.iColumn<<"\n"<<"Contens, ";

	if(ob.chType == 'R')
		os<<"real :"<<ob.ldReal;
	else if(ob.chType == 'S')
		os<<"string :"<<ob.strStr;
	else if(ob.chType == 'E')
		os<<"empty cell.";
	else
		os<<"error.";
	
	os<<"\n";

	return os;*/
}


void main() {
	cell ob1("1leva1", 13, 14);
	cell ob5("123456", 10, 9);
	cell ob2(3.21845215553, 99, 100);
	cell ob3 = ob1;
	cell ob4 = ob2;
	std::cin>>ob4;
	std::cout<<ob4;
	std::cin>>ob4;
	std::cout<<ob4;
	CData ob6(3, 5);
	ob6.ColumnToRorS(1, 'S');
	CData ob7;
	ob6.SumConc();
	ob6.RandData(2);
}