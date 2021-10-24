#include "Book.hpp"

using namespace std;

Book::Book(int id_, string title_, Author* author_, string genre_)
{

  id = id_;
  title = title_;
  author = author_;
  genre = genre_;

}

void Book::brief_print()
{
  cout << "id: " << id << " Title: " << title << endl;
}

void Book::print()
{
  cout << "id: " << id << endl
  << "Title: " << title << endl
  << "Genre: " << genre << endl
  << "Author: " << author->get_name() << endl;
}

void Book::print_reviews()
{
  for(int i = 0; i < reviews.size(); i++)
  reviews[i]->print();
}

void Book::add_review(Review* review)
{
  reviews.push_back(review);
}

float Book::get_average_rating()
{
  float sum_of_ratings = 0;
  for(int i = 0; i < reviews.size(); i++)
  {
    sum_of_ratings += reviews[i]->get_rating();
  }
  return sum_of_ratings / reviews.size();
}

float Book::calculate_reviews_rating_by_credit()
{
  float sum_of_reviews_rating_by_credit = 0;
  for(int i = 0; i < reviews.size(); i++)
  sum_of_reviews_rating_by_credit += reviews[i]->get_rating_by_credit();
  return (sum_of_reviews_rating_by_credit / reviews.size());
}
