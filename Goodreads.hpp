#ifndef __GOODREADS_H__
#define __GOODREADS_H__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include "Author.hpp"
#include "Book.hpp"
#include "User.hpp"
#include "Review.hpp"
#include "definition.hpp"

class Goodreads
{
public:
  Goodreads(std::string files_folder);
  void read_author_file(std::string files_folder);
  Genres read_genres(std::string genres_string);
  void read_book_file(std::string files_folder);
  void read_user_file(std::string files_folder);
  void read_review_file(std::string files_folder);
  void read_follow_edges_file(std::string files_folder);
  std::string separate_part(std::string &line, char sign);
  void read_command(std::string command);
  int find_Last_Index(std::string line, char sign);
  std::vector<Author*> read_authors(std::string authors_string);
  std::vector<Book*> read_books(std::string books_string);
  std::vector<User*> read_users(std::string users_string);
  float calculate_user_credit(int user_id);
  void add_users_credit();
  int calculate_number_of_likes();
  void print_best_book();
  int get_best_book_id();
  void print_best_reviewer();
  int get_best_reviewer_id();
  float calculate_score(float rating, int favorite_genre);
  void recommend_first_approach(int user_id);
  void recommend_second_approach(int user_id);
  int get_most_repetitive_book(std::vector<int> best_books);


private:
  std::vector<Author*> authors;
  std::vector<Book*> books;
  std::vector<User*> users;
  std::vector<Review*> reviews;
  std::map<std::string, std::string> last_command;
};

#endif
