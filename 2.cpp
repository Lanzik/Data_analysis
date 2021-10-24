#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#define COMMA ","
#define FIRST 0
#define AFTER 1
#define SPACE " "
#define DONT_EXIST -1
#define SEPARATOR "$"
#define ONE 1
#define BLANK ""

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
	Book(){}
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
	string get_genre() { return genre_; }
	string get_author_name() { return author_book_->get_name(); }
private:
	int id_;
	string title_;
	string genre_;
	Author* author_book_;
};
typedef vector<Author> Authors;
typedef vector<Book> Books;


class User
{
public:
	User(int id, string name, string place_of_birth, string month, int day, int year, Authors favorite_authors,
		strings favorite_genres, Books want_to_read, Books currently_reading, Books read)
		: member_since_(month, day, year)
	{
		id_ = id;
		name_ = name;
		place_of_birth_ = place_of_birth;
		favorite_authors_ = favorite_authors;
		favorite_genres_ = favorite_genres;
		want_to_read_ = want_to_read;
		currently_reading_ = currently_reading;
		read_ = read;
	}
	int get_id() { return id_; }
	Books get_shelf(string type)
	{
		if (type == "want_to_read")
			return want_to_read_;
		else if (type == "read")
			return read_;
		else
			return currently_reading_;
	}
private:
	int id_;
	string name_;
	string place_of_birth_;
	Date member_since_;
	Authors favorite_authors_;
	strings favorite_genres_;
	Books want_to_read_;
	Books currently_reading_;
	Books read_;
};
typedef vector<User> Users;
class Data
{
public:
	Data() {}
	Data(Authors authors)
	{
		authors_ = authors;
		books_ = read_books_info();
		users_ = read_user_info();
	}
	Authors read_authors_info();
	Books read_books_info();
	Users read_user_info();
	User* find_user_by_id(int id);
	Author* find_author_by_id(int id);
	Book* find_book_by_id(int id);
	Books find_books_by_author_name(string author_name);
private:
	Authors authors_;
	Books books_;
	Users users_;
};
Users Data::read_user_info()
{
	int id, sign_place, day, year, author_id, book_id;
	string name, place_of_birth, line, month, genre;
	Users temp_users;
	stringstream convert;
	ifstream user_file("./Assets/users.csv");
	getline(user_file, line);
	while (getline(user_file, line))
	{
		Books want_to_read, currently_reading, read;
		Authors favorite_authors;
		strings favorite_genres;
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> id;
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		name = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		place_of_birth = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SPACE);
		month = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SPACE);
		convert << line.substr(FIRST, sign_place);
		convert >> day;
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> year;
		convert.str(BLANK);
		convert.clear();

		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SEPARATOR);
		while (sign_place != DONT_EXIST && sign_place < line.find(COMMA))
		{
			convert << line.substr(FIRST, sign_place);
			convert >> author_id;
			favorite_authors.push_back(*find_author_by_id(author_id));
			convert.str(BLANK);
			convert.clear();
			line = line.substr(sign_place + AFTER);
			sign_place = line.find(SEPARATOR);
		}
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> author_id;
		favorite_authors.push_back(*find_author_by_id(author_id));
		convert.str(BLANK);
		convert.clear();

		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SEPARATOR);
		while (sign_place != DONT_EXIST && sign_place < line.find(COMMA))
		{
			genre = line.substr(FIRST, sign_place);
			favorite_genres.push_back(genre);
			line = line.substr(sign_place + AFTER);
			sign_place = line.find(SEPARATOR);
		}
		sign_place = line.find(COMMA);
		genre = line.substr(FIRST, sign_place);
		favorite_genres.push_back(genre);

		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SEPARATOR);
		while (sign_place != DONT_EXIST && sign_place < line.find(COMMA))
		{
			convert << line.substr(FIRST, sign_place);
			convert >> book_id;
			want_to_read.push_back(*find_book_by_id(book_id));
			convert.str(BLANK);
			convert.clear();
			line = line.substr(sign_place + AFTER);
			sign_place = line.find(SEPARATOR);
		}
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> book_id;
		want_to_read.push_back(*find_book_by_id(book_id));
		convert.str(BLANK);
		convert.clear();

		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SEPARATOR);
		while (sign_place != DONT_EXIST && sign_place < line.find(COMMA))
		{
			convert << line.substr(FIRST, sign_place);
			convert >> book_id;
			currently_reading.push_back(*find_book_by_id(book_id));
			convert.str(BLANK);
			convert.clear();
			line = line.substr(sign_place + AFTER);
			sign_place = line.find(SEPARATOR);
		}
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> book_id;
		currently_reading.push_back(*find_book_by_id(book_id));
		convert.str(BLANK);
		convert.clear();

		line = line.substr(sign_place + AFTER);
		sign_place = line.find(SEPARATOR);
		while (sign_place != DONT_EXIST && sign_place < line.find(COMMA))
		{
			convert << line.substr(FIRST, sign_place);
			convert >> book_id;
			read.push_back(*find_book_by_id(book_id));
			convert.str(BLANK);
			convert.clear();
			line = line.substr(sign_place + AFTER);
			sign_place = line.find(SEPARATOR);
		}
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> book_id;
		read.push_back(*find_book_by_id(book_id));
		convert.str(BLANK);
		convert.clear();
		temp_users.push_back(User(id, name, place_of_birth, month, day, year, favorite_authors,
			favorite_genres, want_to_read, currently_reading, read));
	}
	return temp_users;

}
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
		strings genres;
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> id;
		convert.str(BLANK);
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
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> year;
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> year_of_birth;
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		place_of_birth = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		if ((sign_place = line.find(SEPARATOR)) != DONT_EXIST)
		{
			while (sign_place != DONT_EXIST)
			{
				genre = line.substr(FIRST, sign_place);
				genres.push_back(genre);
				line = line.substr(sign_place + AFTER);
				sign_place = line.find(SEPARATOR);
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
Book* Data::find_book_by_id(int book_id)
{
	for (int i = 0; i < books_.size(); i++)
	{
		if (books_[i].get_id() == book_id)
		{
			return &books_[i];
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
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		title = line.substr(FIRST, sign_place);
		line = line.substr(sign_place + AFTER);
		sign_place = line.find(COMMA);
		convert << line.substr(FIRST, sign_place);
		convert >> author_id;
		convert.str(BLANK);
		convert.clear();
		line = line.substr(sign_place + AFTER);
		genre = line;
		temp_books.push_back(Book(id, title, find_author_by_id(author_id), genre));
	}
	return temp_books;
}
User* Data::find_user_by_id(int user_id)
{
	for (int i = 0; i < users_.size(); i++)
	{
		if (users_[i].get_id() == user_id)
		{
			return &users_[i];
		}
	}
}
void print_books_info(Books books,int number)
{
	
}
void print_books(Books books, string genre)
{

	Books sorted_books;
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].get_genre() == genre)
		{
			sorted_books.push_back(books[i]);
			books.erase(books.begin() + i);
		}
	}
	Book temp_book;
	for (int j = 0; j < sorted_books.size() - 1; j++)
	{
		for (int k = 0; k < sorted_books.size(); k++)
		{
			if (sorted_books[j].get_title() > sorted_books[k].get_title())
			{
				temp_book = sorted_books[j];
				sorted_books[j] = sorted_books[k];
				sorted_books[k] = temp_book;

			}
		}
	}
	for (int i = 0; i < sorted_books.size(); i++)
	{
		cout << "id: " << sorted_books[i].get_id() << endl;
		cout << "Title: " << sorted_books[i].get_title() << endl;
		cout << "Genre: " << sorted_books[i].get_genre() << endl;
		cout << "Author: " << sorted_books[i].get_author_name() << endl << "***" << endl;
	}
	sorted_books.erase(sorted_books.begin() , sorted_books.end());

	for (int k = 0; k < books.size(); k++)
	{
		sorted_books.push_back(books[k]);
	}

	for (int j = 0; j < sorted_books.size() - 1; j++)
	{
		for (int k = j; k < sorted_books.size(); k++)
		{
			if (sorted_books[j].get_title() > sorted_books[k].get_title())
			{
				temp_book = sorted_books[j];
				sorted_books[j] = sorted_books[k];
				sorted_books[k] = temp_book;

			}
		}
	}
	for (int i = 0; i < sorted_books.size(); i++)
	{
		cout << "id: " << sorted_books[i].get_id() << endl;
		cout << "Title: " << sorted_books[i].get_title() << endl;
		cout << "Genre: " << sorted_books[i].get_genre() << endl;
		cout << "Author: " << sorted_books[i].get_author_name() << endl << "***" << endl;
	}

}

int main()
{
	Data main_data(Data().read_authors_info());
	string command;
	while (cin >> command)
	{
		if (command == "show_author_info")
		{
			int author_id;
			cin >> author_id;
			ostringstream oss;
			cout << "id: " << main_data.find_author_by_id(author_id)->get_id() << endl;
			string name = main_data.find_author_by_id(author_id)->get_name();
			cout << "Name: " << name << endl;
			cout << "Year of Birth: " << main_data.find_author_by_id(author_id)->get_year_of_birth() << endl;
			cout << "Place of Birth: " << main_data.find_author_by_id(author_id)->get_place_of_birth() << endl;
			cout << "Member Since: " << main_data.find_author_by_id(author_id)->get_member_since().get_month()
				<< " " << main_data.find_author_by_id(author_id)->get_member_since().get_day()
				<< " " << main_data.find_author_by_id(author_id)->get_member_since().get_year() << endl;
			cout << "Genres: ";
			for (int i = 0; i < main_data.find_author_by_id(author_id)->get_genres().size(); i++)
			{
				cout << main_data.find_author_by_id(author_id)->get_genres()[i];
				if (i == main_data.find_author_by_id(author_id)->get_genres().size() - ONE)
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
		else if (command == "show_sorted_shelf")
		{
			int user_id;
			string shelf_type;
			string genre;
			cin >> user_id >> shelf_type >> genre;
			print_books(main_data.find_user_by_id(user_id)->get_shelf(shelf_type), genre);
		}

	}
}
