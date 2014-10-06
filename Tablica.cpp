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
#include <string>		// std::string
#include <list>
#include <limits>
#include <algorithm>
#include <vector>
#include <utility>		// std::move

//#include <random>
//#include <cstddef>


//#include <fstream>


const long double NAN = std::numeric_limits<long double>::quiet_NaN();

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

public:

	//конструктор по подразбиране
	Cell() : ldReal_(NAN), strStr_(""), uintRow_(0), uintColumn_(0), chType_('S') {}
	
	//конструктор на празна клетка с посочени ред и колона
	Cell(const unsigned int row, const unsigned int column) 
		: ldReal_(NAN), strStr_(""), uintRow_(row), uintColumn_(column), chType_('S') {}

	//експлицитен конструктор за реална стойност на данните в клетката
	Cell(const long double real, const unsigned int row, const unsigned int column) 
		: ldReal_(real), strStr_(""), uintRow_(row), uintColumn_(column), chType_('R') {}

	//експлицитен конструктор за стрингова стойност на данните в клетката
	Cell(const std::string& str, const unsigned int row, const unsigned int column) 
		: ldReal_(NAN), strStr_(str), uintRow_(row), uintColumn_(column), chType_('S') {}

	/*Cell(const long double real, const std::string& str, 
		const int row, const int column, const char type) {

			ldReal_ = real;
			strStr_ = str;
			uintRow_ = row;
			uintColumn_ = column;
			chType_ = type;
	}*/

	//копиращ конструктор
	Cell (const Cell& ob) : ldReal_(ob.ldReal_), strStr_(ob.strStr_), uintRow_(0), uintColumn_(0), chType_(ob.chType_) {}

	//move constructor
	Cell(Cell &&ob) : ldReal_(std::move(ob.ldReal_)), strStr_(std::move(ob.strStr_)), uintRow_(std::move(ob.uintRow_)), 
		uintColumn_(std::move(ob.uintColumn_)), chType_(std::move(ob.chType_)) {}

	//copy assignment operator
	Cell& operator= (const Cell &ob) {

		ldReal_ = ob.ldReal_;
		strStr_ = ob.strStr_;
		uintRow_ = ob.uintRow_;
		uintColumn_ = ob.uintColumn_;
		chType_ = ob.chType_;
		
		return *this;
	}

	//move assignment operator
	Cell& operator= (Cell &&ob) {

		ldReal_ = std::move(ob.ldReal_);
		strStr_ = std::move(ob.strStr_);
		//uintRow_ = std::move(ob.uintRow_);
		//uintColumn_ = std::move(ob.uintColumn_);
		//chType_ = std::move(ob.chType_);
		
		return *this;
	}

	//оператор за събиране (събира или конкатинира стойността на данните в клетката)
	Cell operator+ (const Cell& ob) {
		
		Cell temp;
		if(chType_ == 'R') {
			temp.ldReal_ = ldReal_ + ob.ldReal_;
		}
		else {
			temp.strStr_ = strStr_ + ob.strStr_;
		}
		return temp;
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
			ldReal_ = NAN;
			chType_ = 'S';
		}
		catch(const std::length_error&) {
			strStr_.clear();
			ldReal_ = NAN;
			chType_ = 'S';
		}
		catch(std::bad_alloc&) {
			strStr_.clear();
			ldReal_ = NAN;
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

		if(type == 'R') {
			if(chType_ == 'S') {
				std::string::size_type sz = 0;
				try {
					ldReal_ = std::stold(strStr_, &sz);
					ldReal_ = sz == strStr_.length() ? ldReal_ : NAN;
				}
				catch(...) {
					ldReal_ = NAN;
				}
			}

			chType_ = type;
		}
		else if(type == 'S') {
			if(chType_ == 'R') {
				try {
					strStr_ = std::to_string(ldReal_);
				}
				catch(...) {
					strStr_.clear();
				}
			}
			chType_ = type;
		}

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

class ComputeError {

	std::string strWhat_;

public:

	ComputeError() : strWhat_("Compute error!") {}

	ComputeError(const std::string &msg) : strWhat_(msg) {}

	std::string what() { return strWhat_;}

};

class DeleteIfIs {

public:
	bool operator() (Cell *ob) {
		if(ob != nullptr) {
			delete ob;
			return true;
		}
		return false;
	}
};

class GetColumnType {
	
	unsigned int column_;

public:

	GetColumnType () : column_(0) {}

	GetColumnType (const unsigned int column) : column_(column) {}

	bool operator() (Cell *ob) {
		if(ob->GetRow() == 1 && ob->GetColumn() == column_)
			return true;
		return false;
	}
};

class CData {

	std::list<Cell*> table_;
	unsigned int uintRows_;
	unsigned int uintColumns_;
	
	CData (const CData& ob);
	CData(CData&&);
	CData& operator= (CData&&);
	CData& operator= (const CData &ob);

public:

	//конструктор по подразбиране
	CData() : table_(), uintRows_(0), uintColumns_(0) {}

	CData(const unsigned int rows, const unsigned int columns) : uintRows_(rows), uintColumns_(columns) {
		
		for(unsigned int i = 0; i < uintRows_; ++i)
			for(unsigned int j = 0; j < uintColumns_; ++j)
				table_.push_back( new Cell(i+1, j+1) );
	}

	~CData() {
		table_.remove_if(DeleteIfIs());
		uintRows_ = 0;
		uintColumns_ = 0;
	}

	unsigned int GetRows() {
		return uintRows_;
	}

	unsigned int GetColumns() {
		return uintColumns_;
	}

	std::list<Cell*> GetTable() {
		
		std::list<Cell*> temp;
		
		for(std::list<Cell*>::iterator it=table_.begin(); it!=table_.end(); ++it) {
			
			temp.push_back( new Cell(*(*it)) );
		}

		return temp;
	}

	void SetColumnType(const unsigned int column, const char type) {
		
		for(std::list<Cell* >::iterator it=table_.begin(); it!=table_.end(); ++it) {
			
			if((*it)->GetColumn() == column)
				(*it)->SetType(type);
		}
	}

	void AddCell(const Cell &ob) {

		if(!ob.GetColumn() || !ob.GetRow())
			return;
		else if(ob.GetColumn() > uintColumns_) {
			
			table_.push_back(new Cell(ob));
			++uintColumns_;
			if(ob.GetRow() > uintRows_)
				++uintRows_;
		}
		else if(ob.GetRow() > uintRows_) {
			
			GetColumnType columnType(ob.GetColumn());

			std::list<Cell* >::iterator it = std::find_if(table_.begin(), table_.end(), columnType );

			if((*it)->GetType() == ob.GetType()) {
				table_.push_back(new Cell(ob));
				++uintRows_;
			}
		}
	}

	long double TableSum() {
		
		long double result = 0.0;
		for(std::list<Cell* >::iterator it=table_.begin(); it!=table_.end(); ++it) {

			if( (*it)->GetType() == 'R' )
				result = result + (*it)->GetReal();
		}

		return result;
	}

	std::string TableConcat() {

		std::string str = "";
		for(std::list<Cell* >::iterator it=table_.begin(); it!=table_.end(); ++it) {

			if( (*it)->GetType() == 'S' )
				str = str + (*it)->GetStr();
		}

		return str;
	}

	long double ColumnsAverage() {

		std::vector<unsigned int> columns;
		long double result = 0;
		unsigned int count = 0;

		for(std::list<Cell* >::iterator it=table_.begin(); it!=table_.end(); ++it) {

			if( (*it)->GetRow() == 1 && (*it)->GetType() == 'R' )
				columns.push_back((*it)->GetColumn());
		}

		for(std::list<Cell* >::iterator it=table_.begin(); it!=table_.end(); ++it) {

			for(unsigned int i = 0; i < columns.size(); ++i) {
				if((*it)->GetColumn() == columns[i]) {
					result = result + (*it)->GetReal();
					++count;
				}
			}
		}

		if(count)
			result = result/count;
		else {
			result = NAN;
			throw ComputeError("The table (CData) do not have columns with real(number) data!");
		}

		if(result - result != 0)
			throw ComputeError("Result is not a number");

		return result;
	}

	CData CDataFromTo(unsigned int row1, unsigned int column1, unsigned int row2, unsigned int column2) {
		
		CData ob;
		std::list<Cell*>::iterator it;
		
		if(row1 > row2) {
			unsigned int temp = row1;
			row1 = row2;
			row2 = temp;
		}

		if(column1 > column2) {
			unsigned int temp = column1;
			column1 = column2;
			column2 = temp;
		}

		/*if(!row1 || !column1 || !row2 || !column2 || 
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

		return ob;*/
	}
};

std::istream &operator>> (std::istream &is, Cell &ob) {
	
	Cell temp;
	is>>temp.chType_;

	if(temp.chType_ == 'R' || temp.chType_ == 'S') {
		
		if(temp.chType_ == 'R') {
			is>>temp.ldReal_;
			temp.strStr_.clear();
		}
		else {
			temp.ldReal_ = NAN;
			is>>temp.strStr_;
		}
		
		long long int i = 0;
		is>>i;
		if(i < 0 || i > static_cast <long long int> (std::numeric_limits<unsigned int>::max())) {
			is.setstate(std::ios_base::failbit);
		}
		else {
			temp.uintRow_ = static_cast <unsigned int> (i);
			is>>i;
			if(i < 0 || i > (long int)std::numeric_limits<unsigned int>::max()) {
				is.setstate(std::ios_base::failbit);
			}
			else temp.uintColumn_ = static_cast <unsigned int> (i);
		}
		
		if(is.good())
			ob = temp;
		else {
			ClearStream(is);
			//throw std::ios_base::failure("Invalid input!");
		}
	}

	return is;
}

std::ostream &operator<< (std::ostream &os, const Cell &ob) {
	
	if(os.good()) {
		os<<ob.chType_<<" ";
	
		if(ob.chType_ == 'R')
			os<<ob.ldReal_;
		else
			os<<ob.strStr_;
	
		os<<" "<<ob.uintRow_<<" "<<ob.uintColumn_<<" ";
	}
	else ClearStream(os);
	
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
	ob4 = (ob5 + ob2);
	//std::cin>>ob4;
	//std::cin>>ob2;

	//std::cin>>ob88;

	

	std::cout<<ob4;
	std::cout<<ob4;
	//CData ob6(3, 5);
	//ob6.ColumnToRorS(1, 'S');
	CData ob7(3,5);
	ob7.SetColumnType(3, 'R');
	std::list<Cell* > rety;
	rety = ob7.GetTable();
	unsigned int ttt;
	ttt = ob7.GetRows();
	Cell tt(5.5, 88, 90);
	ob7.AddCell(tt);
	//ob6.SumConc();
	//ob6.RandData(2);
	long double ddd = 0;
	try {
	ddd = ob7.ColumnsAverage();
	}
	catch(...){
		ddd=12.12;
	}
	Cell io;
}