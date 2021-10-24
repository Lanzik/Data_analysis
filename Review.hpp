#ifndef __REVIEW_H__
#define __REVIEW_H__

#include <string>
#include <iostream>

class User;

class Review
{
public:
  Review(int id_, int book_id_, User* reviewer_, int rating_, std::string date_, int number_of_likes_);
  float get_rating_by_credit();
  void print();
  int get_number_of_likes(){ return number_of_likes; }
  int get_rating() { return rating; }
private:
  int id;
  int book_id;
  User* reviewer;
  int rating;
  std::string date;
  int number_of_likes;
};

#endif
