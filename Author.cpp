#include "Author.hpp"

using namespace std;

Author::Author(int id_, std::string name_, bool gender_, std::string member_since_, int year_of_birth_,
std::string place_of_birth_, Genres genres_)
{
  id = id_;
  name = name_;
  gender = gender_;
  member_since = member_since_;
  year_of_birth = year_of_birth_;
  place_of_birth = place_of_birth_;
  genres = genres_;
}

void Author::add_book(Book* book)
{
  books.push_back(book);
}

void Author::print()
{
  cout  << "id: " << id << endl;
  cout  << "Name: " << name << endl;
  cout << "Year of Birth: " << year_of_birth << endl;
  cout << "Place of Birth: " << place_of_birth << endl;
  cout << "Member Since: " << member_since << endl;
  cout << "Genres: ";
  for(int i = 0; i < genres.size(); i++)
  {
    cout << genres[i];
    if(i != genres.size() - 1)
    cout << ", ";
  }
  cout << endl << "Books:" << endl;
  for(int i = 0; i < books.size(); i++)
  books[i]->brief_print();
}
