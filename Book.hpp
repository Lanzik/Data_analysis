#ifndef __BOOK_H__
#define __BOOK_H__

#include <iostream>
#include <string>
#include <vector>
#include "Review.hpp"
#include "Author.hpp"

class Author;

class Book
{
public:
  Book(int id_, std::string title_, Author* author_, std::string genre_);
  void brief_print();
  void print();
  void print_reviews();
  void add_review(Review* review);
  float get_average_rating();
  float calculate_reviews_rating_by_credit();
  int get_id(){ return id;}
  std::string get_genre(){ return genre; }
  std::string get_name(){ return title; }
private:
  int id;
  std::string title;
  Author* author;
  std::string genre;
  std::vector<Review*> reviews;
};

#endif
