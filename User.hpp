#ifndef __USER_H__
#define __USER_H__


#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "definition.hpp"
#include "Author.hpp"
#include "Book.hpp"
#include "Review.hpp"

class User
{
public:
  User(int id_, std::string name_, std::string place_of_birth_, std::string member_since_,
  std::vector<Author*> favorite_authors_, Genres favorite_genres_, std::vector<Book*> want_to_read_,
  std::vector<Book*> currently_reading_, std::vector<Book*> read_);
  void print_books(std::string shelf_type, std::string genre);
  std::vector<Book> sort_by_genre(std::vector<Book> books, std::string genre);
  void print_credit();
  float calculate_user_credit();
  void add_review(Review* review);
  int calculate_number_of_user_reviews_like();
  void print();
  std::vector<int> get_best_books();
  void add_credit(float credit_);
  bool favorite_genre(std::string genre);
  void add_followings_followers(std::vector<User*> followings_, std::vector<User*> followers_);
  std::vector<int> create_following_series(std::vector<int> &followings_series);
  int get_most_repetitive_book(std::vector<int> best_books);
  float get_credit() { return credit; }
  int get_number_of_reviews(){ return reviews.size(); }
  int get_id(){ return id; }
  static bool sort_book_by_name(Book first_book, Book second_book) {
    if(first_book.get_name() == second_book.get_name())
    return (first_book.get_id() < second_book.get_id());
    else
    return (first_book.get_name() < second_book.get_name()); }
  static bool sort_author_by_name(Author* first_author, Author* second_author) {
    return (first_author->get_name() < second_author->get_name()); }
private:
  int id;
  std::string name;
  std::string place_of_birth;
  std::string member_since;
  float credit;
  std::vector<Author*> favorite_authors;
  Genres favorite_genres;
  std::vector<Book*> want_to_read;
  std::vector<Book*> currently_reading;
  std::vector<Book*> read;
  std::vector<Review*> reviews;
  std::vector<User*> followings;
  std::vector<User*> followers;
};

#endif
