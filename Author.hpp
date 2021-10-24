#ifndef __AUTHOR_H__
#define __AUTHOR_H__

#include <iostream>
#include <string>
#include <vector>
#include "Book.hpp"
#include "definition.hpp"

class Book;

class Author
{
public:
  Author(int id_, std::string name_, bool gender_, std::string member_since_, int year_of_birth_,
  std::string place_of_birth_, Genres genres_);
  void add_book(Book* book);
  void print();
  std::string get_name(){ return name; }
private:
  int id;
  std::string name;
  bool gender;
  std::string member_since;
  int year_of_birth;
  std::string place_of_birth;
  Genres genres;
  std::vector<Book*> books;
};

#endif
