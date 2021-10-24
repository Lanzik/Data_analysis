#include "Review.hpp"
#include "User.hpp"

using namespace std;

Review::Review(int id_, int book_id_, User* reviewer_, int rating_, std::string date_, int number_of_likes_)
  {
    id = id_;
    book_id = book_id_;
    rating = rating_;
    reviewer = reviewer_;
    date = date_;
    number_of_likes = number_of_likes_;
  }
void Review::print()
{
  cout << "id: " << id << " Rating: " << rating << " Likes: " << number_of_likes
  << " Date: " << date << endl;

}

float Review::get_rating_by_credit()
{
  return (reviewer->get_credit() * rating);
}
