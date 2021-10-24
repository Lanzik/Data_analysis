#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define COMMA ","
#define FIRST 0
#define AFTER 1
#define SPACE " "
#define DONT_EXIST -1
#define GENRES_SEPARATOR "$"
#define ONE 1

typedef vector<string> strings;
class Date
{
public:
	Date(string month, int day, int year)
	{
		month_ = month;
		day_ = day;
		year_ = year;
	}
	string get_month() { return month_; }
	int get_day() { return day_; }
	int get_year() { return year_; }

private:
	string month_;
	int day_;
	int year_;
};
class Author
{
public:
	Author(int id, string name, string gender, string month, int day, int year,
		int year_of_birth, string place_of_birth, vector<string> genres)
		: member_since_(month, day, year)
	{
		id_ = id;
		name_ = name;
		gender_ = gender;
		year_of_birth_ = year_of_birth;
		place_of_birth_ = place_of_birth;
		genres_ = genres;
	}
	int get_id() { return id_; }
	string get_name() { return name_; }
	string get_place_of_birth() { return place_of_birth_; }
	int get_year_of_birth() { return year_of_birth_; }
	Date get_member_since() { return member_since_; }
	strings get_genres() { return genres_; }
private:
	int id_;
	string name_;
	string gender_;
	Date member_since_;
	int year_of_birth_;
	string place_of_birth_;
	strings genres_;
};
class Book
{
public:
	Book(int id, string title, Author *author, string genre)
	{
		id_ = id;
		title_ = title;
		genre_ = genre;
		author_book_ = author;
	}
	int get_id() { return id_; }
	string get_title() { return title_; }
	Author* get_author_book() { return author_book_; }

private:
	int id_;
	string title_;
	string genre_;
	Author* author_book_;
};

typedef vector<Author> Authors;
typedef vector<Book> Books;

class Data
{
public:
	Data() {}
	Data(Authors authors)
	{
		authors_ = authors;
		books_ = read_books_info();
	}
	Authors read_authors_info();
	Books read_books_info();
	Author* find_author_by_id(int id);
	Books find_books_by_author_name(string author_name);
private:
	Authors authors_;
	Books books_;
};
Books Data::find_books_by_author_name(string author_name)
{
	Books author_books;
	for (int i = 0; i < books_.size(); i++)
	{
		if (author_name == books_[i].get_author_book()->get_name())
		{
			author_books.push_back(books_[i]);
		}
	}
	return author_books;
}
Authors Data::read_authors_info()
{
	int id;
	string name;
	string gender;
	string month;
	int day;
	int year;
	int year_of_birth;
	string place_of_birth;
	string genre;
	Authors temp_authors;
	string line;
	int sign_place;
	stringstream convert;
	ifstream authors_file("./Assets/authors.csv");
	getline(authors_file, line);
	while (getline(authors_file, line))
	{
		vector<string> genres;
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> id;
		convert.str("");
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		name = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		gender = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SPACE);
		month = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SPACE);
		convert << line.substr(FIRST, sign_place);
		convert >> day;
		convert.str("");
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> year;
		convert.str("");
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> year_of_birth;
		convert.str("");
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		place_of_birth = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		if ((sign_place = line.find(GENRES_SEPARATOR)) != DONT_EXIST)
		{
			while (sign_place != DONT_EXIST)
			{
				genre = line.substr(FIRST, sign_place);
				genres.push_back(genre);
				line = line.substr(sign_place + AFTER);
				sign_place = line.find(GENRES_SEPARATOR);
			}
			genres.push_back(line);
		}
		else
		{
			genre = line.substr(FIRST, sign_place);
			genres.push_back(genre);
		}
		temp_authors.push_back(Author(id, name, gender, month, day, year, year_of_birth,
			place_of_birth, genres));

	}
	return temp_authors;

}
Author* Data::find_author_by_id(int author_id)
{
	for (int i = 0; i < authors_.size(); i++)
	{
		if (authors_[i].get_id() == author_id)
		{
			return &authors_[i];
		}
	}
}
Books Data::read_books_info()
{
	int id;
	string title;
	int author_id;
	string genre;
	Books temp_books;
	string line;
	int sign_place;
	stringstream convert;
	ifstream authors_file("./Assets/books.csv");
	getline(authors_file, line);
	while (getline(authors_file, line))
	{
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> id;
		convert.str("");
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		title = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> author_id;
		convert.str("");
		convert.clear();
		line = line.substr(sign_place + AFTER);
		genre = line;
		temp_books.push_back(Book(id, title, find_author_by_id(author_id), genre));
	}
	return temp_books;
}

int main()
{
	Data main_data(Data().read_authors_info());
	string command;
	while (cin >> command)
	{
		if (command == "show_author_info")
		{
			int id;
			cin >> id;
			Author new__author();
			ostringstream oss;
			cout << "id: " << main_data.find_author_by_id(id)->get_id() << endl;
			string name = main_data.find_author_by_id(id)->get_name();
			cout << "Name: " << name << endl;
			cout << "Year of Birth: " << main_data.find_author_by_id(id)->get_year_of_birth() << endl;
			cout << "Place of Birth: " << main_data.find_author_by_id(id)->get_place_of_birth() << endl;
			cout << "Member Since: " << main_data.find_author_by_id(id)->get_member_since().get_month()
				<< " " << main_data.find_author_by_id(id)->get_member_since().get_day()
				<< " " << main_data.find_author_by_id(id)->get_member_since().get_year() << endl;
			cout << "Genres: ";
			for (int i = 0; i < main_data.find_author_by_id(id)->get_genres().size(); i++)
			{
				cout << main_data.find_author_by_id(id)->get_genres()[i];
				if (i == main_data.find_author_by_id(id)->get_genres().size() - ONE)
					cout << endl;
				else
					cout << ", ";
			}
			cout << "Books:" << endl;
			for (int j = 0; j < main_data.find_books_by_author_name(name).size(); j++)
			{
				cout << "id: " << main_data.find_books_by_author_name(name)[j].get_id() << " ";
				cout << "Title: " << main_data.find_books_by_author_name(name)[j].get_title() << endl;
			}





		}

	}
}
