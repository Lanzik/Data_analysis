#include "User.hpp"

using namespace std;

User::User(int id_, string name_, string place_of_birth_, string member_since_,
vector<Author*> favorite_authors_, Genres favorite_genres_, vector<Book*> want_to_read_,
vector<Book*> currently_reading_, vector<Book*> read_)
{
  id = id_;
  name = name_;
  place_of_birth = place_of_birth_;
  member_since = member_since_;
  favorite_authors = favorite_authors_;
  favorite_genres = favorite_genres_;
  want_to_read = want_to_read_;
  currently_reading = currently_reading_;
  read = read_;
}

vector<Book> User::sort_by_genre(vector<Book> books, string genre)
{
  vector<Book> same_genre_books;
  for(int i = 0; i < books.size(); i++)
  {
    if(books[i].get_genre() == genre)
    {
      same_genre_books.push_back(books[i]);
      books.erase(books.begin() + i);
    }
  }
  sort(same_genre_books.begin(), same_genre_books.end(), sort_book_by_name);
  sort(books.begin(), books.end(), sort_book_by_name);
  same_genre_books.insert( same_genre_books.end(), books.begin(), books.end() );
  return same_genre_books;
}

void User::print_books(std::string shelf_type, std::string genre)
{
  vector<Book> books;
  if(shelf_type == "want_to_read")
    transform(begin(want_to_read), end(want_to_read), back_inserter(books),[](Book* book)
    {return *book;});
  else if(shelf_type == "currently_reading")
    transform(begin(currently_reading), end(currently_reading), back_inserter(books),[](Book* book)
    {return *book;});
  else
    transform(begin(read), end(read), back_inserter(books),[](Book* book)
    {return *book;});
  books = sort_by_genre(books, genre);
  for(int i = 0; i < books.size(); i++)
  {
    books[i].print();
    cout << "***" << endl;
  }
}

void User::print_credit()
{
  cout << fixed << setprecision(6) << credit << endl;
}

void User::add_review(Review* review)
{
  reviews.push_back(review);
}

int User::calculate_number_of_user_reviews_like()
{
  int sum_of_likes = 0;
  for(int i = 0; i < reviews.size(); i++)
  {
    sum_of_likes += reviews[i]->get_number_of_likes();
  }
  return sum_of_likes;
}

void User::print()
{
  cout << "id: " << id << endl
<< "Name: " << name << endl
<< "Place of Birth: " << place_of_birth << endl
<< "Member Since: " << member_since << endl
<< "Favorite Genres: ";
sort(favorite_authors.begin(), favorite_authors.end(), sort_author_by_name);
for(int i = 0; i < favorite_genres.size(); i++)
{
  cout << favorite_genres[i];
  if(i != favorite_genres.size() - 1)
  cout << ", ";
  else
  cout << endl;
}
cout << "Favorite Authors: ";
for(int i = 0; i < favorite_authors.size(); i++)
{
  cout << favorite_authors[i]->get_name();
  if(i != favorite_authors.size() - 1)
  cout << ", ";
  else
  cout << endl;
}
cout << "Number of Books in Read Shelf: " << read.size() << endl
<< "Number of Books in Want to Read Shelf: " << want_to_read.size() << endl
<< "Number of Books in Currently Reading Shelf: " << currently_reading.size() << endl
<< "Number of Likes: " << calculate_number_of_user_reviews_like() << endl;
}

void User::add_followings_followers(vector<User*> followings_, vector<User*> followers_)
{
  followings = followings_;
  followers = followers_;
}

void User::add_credit(float credit_)
{
  credit = credit_;
}

bool User::favorite_genre(string genre)
{
  for(int i = 0; i < favorite_genres.size(); i++)
  if(genre == favorite_genres[i])
  return true;
  return false;
}

vector<int> User::get_best_books()
{
  vector<Book> read_books;
  vector<Book> read_books_temp;
  vector<int> best_books;
  transform(begin(read), end(read), back_inserter(read_books),[](Book* book)
  {return *book;});
  read_books_temp = read_books;
  int rating = 0;
  int book_id;
  int number_book;

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < read_books_temp.size(); j++)
    {
      if (read_books_temp[j].calculate_reviews_rating_by_credit() > rating)
      {
        rating = read_books_temp[j].calculate_reviews_rating_by_credit();
        book_id = read_books_temp[j].get_id();
        number_book = j;
      }
    }
    best_books.push_back(book_id);
    read_books_temp.erase(read_books_temp.begin() + number_book);

  }
  return best_books;
}



vector<int> User::create_following_series(vector<int> &followings_series)
{
  for(int i = 0; i < followings.size(); i++)
  {
    auto it = find(followings_series.begin(), followings_series.end(), followings[i]->get_id());
    if(it == followings_series.end())
    {
      followings_series.push_back(followings[i]->get_id());
      followings[i]->create_following_series(followings_series);
    }
    return followings_series;
  }
}
