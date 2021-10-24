#include "Goodreads.hpp"

using namespace std;

Goodreads::Goodreads(string files_folder)
{
  read_author_file(files_folder);
  read_book_file(files_folder);
  read_user_file(files_folder);
  read_review_file(files_folder);
  add_users_credit();
  read_follow_edges_file(files_folder);
}

void Goodreads::read_author_file(string files_folder)
{
  string author_file_address = files_folder + AUTHORS_FILE;
  ifstream author_file(author_file_address);
  int id, year_of_birth;
  bool gender;
  string line, name, place_of_birth, member_since, genres_string;
  Genres genres;

  getline(author_file, line);
  while(getline(author_file, line))
  {
      id = stoi(separate_part(line, COMMA));
      name = separate_part(line, COMMA);
      if(separate_part(line, COMMA) == "male")
      gender == MALE;
      else
      gender == FEMALE;
      member_since = separate_part(line, COMMA);
      year_of_birth = stoi(separate_part(line, COMMA));
      place_of_birth = separate_part(line, COMMA);
      genres_string = line;
      genres = read_genres(genres_string);
      Author* author = new Author(id, name, gender, member_since, year_of_birth, place_of_birth, genres);
      authors.push_back(author);
  }
}

Genres Goodreads::read_genres(string genres_string)
{
  string genre;
  Genres genres;
  while(true)
  {
    genre = separate_part(genres_string, COMPONENT_SEPARATOR);
    if(genre == END)
    {
      genres.push_back(genres_string);
      break;
    }

    genres.push_back(genre);
  }
  return genres;
}


void Goodreads::read_review_file(string files_folder)
{
  string review_file_address = files_folder + REVIEWS_FILE;
  ifstream review_file(review_file_address);
  string line, date;
  int id, book_id, user_id, rating, number_of_likes;
  getline(review_file, line);
  while(getline(review_file, line))
  {
    id = stoi(separate_part(line, COMMA));
    book_id = stoi(separate_part(line, COMMA));
    user_id = stoi(separate_part(line, COMMA));
    rating = stoi(separate_part(line, COMMA));
    date = separate_part(line, COMMA);
    number_of_likes = stoi(line);
    Review* new_review = new Review(id, book_id, users[user_id], rating, date, number_of_likes);
    users[user_id]->add_review(new_review);
    books[book_id]->add_review(new_review);
    reviews.push_back(new_review);
  }
}

void Goodreads::read_follow_edges_file(string files_folder)
{
  string follow_edges_file_address = files_folder + FOLLOW_FILE;
  ifstream follow_edges_file(follow_edges_file_address);
  string line, followings_string, followers_string;
  vector<User*> followings;
  vector<User*> followers;
  int user_id;
  getline(follow_edges_file, line);
  while(getline(follow_edges_file, line))
  {
    user_id = stoi(separate_part(line, COMMA));
    followings_string = separate_part(line, COMMA);
    followings = read_users(followings_string);
    followers_string = separate_part(line, COMMA);
    followers = read_users(followings_string);
    users[user_id]->add_followings_followers(followings, followers);
  }

}

string Goodreads::separate_part(string &line, char sign)
{
    int position;
    position = line.find(sign);

    if(position == NOT_FOUND)
    return END;

    string first_string = line.substr(0, position);
    line = line.substr(position + 1);
    return first_string;
}

void Goodreads::read_command(string command)
{
  stringstream ss_line;
  ss_line << command;
  ss_line >> last_command["type"];
  string type = last_command["type"];
  if(type == "show_author_info")
  {
    int author_id;
    ss_line >> author_id;
    authors[author_id]->print();
  }
  else if(type == "show_sorted_shelf")
  {
    int user_id;
    string shelf_type;
    string genre, continue_genre;
    ss_line >> user_id >> shelf_type >> genre >> continue_genre;
    if(continue_genre.size() != 0)
    genre = genre + " " + continue_genre;
    users[user_id]->print_books(shelf_type, genre);
  }
  else if(type == "credit")
  {
    int user_id;
    ss_line >> user_id;
    users[user_id]->print_credit();
  }

  else if(type == "best_book")
  {
    print_best_book();
  }
  else if(type == "best_reviewer")
  {
    print_best_reviewer();
  }
  else if(type == "recommend_first_approach")
  {
    int user_id;
    ss_line >> user_id;
    recommend_first_approach(user_id);
  }
  else if(type == "recommend_second_approach")
  {
    int user_id;
    ss_line >> user_id;
    recommend_second_approach(user_id);
  }
}

void Goodreads::add_users_credit()
{
  float user_credit;
  for(int i = 0; i < users.size(); i++)
  {
    user_credit = calculate_user_credit(i);
    users[i]->add_credit(user_credit);
  }
}

float Goodreads::calculate_user_credit(int user_id)
{
  float number_of_likes = calculate_number_of_likes();
  float number_of_user_reviews_like = users[user_id]->calculate_number_of_user_reviews_like();
  float number_of_user_reviews = users[user_id]->get_number_of_reviews();
  float number_of_reviews = reviews.size();

  return ((number_of_user_reviews_like / number_of_likes) +
  (number_of_user_reviews / number_of_reviews)) / 2;
}

void Goodreads::recommend_first_approach(int user_id)
{
  string genre;
  int favorite_genre = 0;
  float recommend_book_id = 0;
  float score = 0;
  for(int i = 0; i < books.size(); i++)
  {
    float rating = books[i]->calculate_reviews_rating_by_credit();
    genre = books[i]->get_genre();
    if(users[user_id]->favorite_genre(genre))
    favorite_genre = 5;
    if(calculate_score(rating, favorite_genre) > score)
    {
      score = calculate_score(rating, favorite_genre);
      recommend_book_id = i;
    }
    favorite_genre = 0;
  }
  books[recommend_book_id]->print();
  cout << "Reviews:" << endl;
  books[recommend_book_id]->print_reviews();

}

void Goodreads::recommend_second_approach(int user_id)
{
  vector<int> followings_series;
  vector<int> user_best_books;
  vector<int> best_books;
  followings_series.push_back(user_id);
  followings_series = users[user_id]->create_following_series(followings_series);
  for(int i = 0; i < followings_series.size(); i++)
  {
    user_best_books = users[followings_series[i]]->get_best_books();
    best_books.insert(best_books.end(), user_best_books.begin(), user_best_books.end());
  }
  int book_id;
  book_id = get_most_repetitive_book(best_books);
  books[book_id]->print();
  cout << "Reviews:" << endl;
  books[book_id]->print_reviews();

}

int Goodreads::get_most_repetitive_book(vector<int> best_books)
{
  int counter = 0;
  vector<int> number_of_repeative_books;
  int most_repetitive_book = 0;
  int best_book_id;
  for(int i = 0; i < best_books.size(); i++)
  {
    for(int j = 0; j < best_books.size(); j++)
    {
      if(best_books[i] == best_books[j])
      counter++;
    }
    if(counter >= most_repetitive_book)
    {
      most_repetitive_book = counter;
      best_book_id = best_books[i];
    }
    number_of_repeative_books.push_back(counter);
    counter = 0;
  }
  return best_book_id;
}

float Goodreads::calculate_score(float rating, int favorite_genre)
{
  return (rating + favorite_genre);
}

void Goodreads::print_best_book()
{
  int book_id = get_best_book_id();
  books[book_id]->print();
  cout << "Average Rating: " << fixed <<
  setprecision(2) << books[book_id]->get_average_rating() << endl;
}

void Goodreads::print_best_reviewer()
{
  int user_id = get_best_reviewer_id();
  users[user_id]->print();
}

int Goodreads::get_best_reviewer_id()
{
  int user_id = 0;
  for(int i = 1; i < users.size(); i++)
  {
    if(users[i]->calculate_number_of_user_reviews_like() >
     users[user_id]->calculate_number_of_user_reviews_like())
    user_id = i;
  }
  return user_id;
}


int Goodreads::get_best_book_id()
{
  int book_id = 0;
  for(int i = 1; i < books.size(); i++)
  {
    if(books[i]->get_average_rating() > books[book_id]->get_average_rating())
    book_id = i;
  }
  return book_id;
}

int Goodreads::calculate_number_of_likes()
{
  int sum_of_likes = 0;
  for(int i = 0; i < reviews.size(); i++)
  {
    sum_of_likes += reviews[i]->get_number_of_likes();
  }
  return sum_of_likes;
}



void Goodreads::read_book_file(string files_folder)
{
  string book_file_address = files_folder + BOOKS_FILE;
  ifstream book_file(book_file_address);
  int id, author_id;
  string title, genre, line;
  getline(book_file, line);

  while(getline(book_file, line))
  {
    id = stoi(separate_part(line, COMMA));
    title = separate_part(line, COMMA);
    author_id = stoi(separate_part(line, COMMA));
    genre = line;
    Book* book = new Book(id, title, authors[author_id], genre);

    books.push_back(book);
    authors[author_id]->add_book(book);
  }
}

void Goodreads::read_user_file(string files_folder)
{
  string user_file_address = files_folder + USERS_FILE;
  ifstream user_file(user_file_address);
  int id;
  string name, place_of_birth, member_since, line, authors_string, genres_string,
  want_to_read_string, currently_reading_string, read_string;
  vector<Author*> favorite_authors;
  Genres favorite_genres;
  vector<Book*> want_to_read, currently_reading, read;
  getline(user_file, line);
  while(getline(user_file, line))
  {
    id = stoi(separate_part(line, COMMA));
    name = separate_part(line, COMMA);
    place_of_birth = separate_part(line, COMMA);
    member_since = separate_part(line, COMMA);
    authors_string = separate_part(line, COMMA);
    favorite_authors = read_authors(authors_string);
    genres_string = separate_part(line, COMMA);
    favorite_genres = read_genres(genres_string);
    want_to_read_string = separate_part(line, COMMA);
    want_to_read = read_books(want_to_read_string);
    currently_reading_string = separate_part(line, COMMA);
    currently_reading = read_books(currently_reading_string);
    read_string = line;
    read = read_books(read_string);
    User* new_user = new User(id, name, place_of_birth, member_since, favorite_authors,
    favorite_genres, want_to_read, currently_reading, read);
    users.push_back(new_user);
  }

}

vector<Book*> Goodreads::read_books(string books_string)
{
  string book_id;
  vector<Book*> favorite_books;
  while(true)
  {
    book_id = separate_part(books_string, COMPONENT_SEPARATOR);
    if(book_id == END)
    {
      favorite_books.push_back(books[stoi(books_string)]);
      break;
    }
    favorite_books.push_back(books[stoi(book_id)]);
  }
  return favorite_books;
}

vector<Author*> Goodreads::read_authors(string authors_string)
{
  string author_id;
  vector<Author*> favorite_authors;
  while(true)
  {
    author_id = separate_part(authors_string, COMPONENT_SEPARATOR);
    if(author_id == END)
    {
      favorite_authors.push_back(authors[stoi(authors_string)]);
      break;
    }
    favorite_authors.push_back(authors[stoi(author_id)]);
  }
  return favorite_authors;
}

vector<User*> Goodreads::read_users(string users_string)
{
  string user_id;
  vector<User*> follow_users;
  while(true)
  {
    user_id = separate_part(users_string, COMPONENT_SEPARATOR);
    if(user_id == END)
    {
      follow_users.push_back(users[stoi(users_string)]);
      break;
    }
    follow_users.push_back(users[stoi(user_id)]);
  }
  return follow_users;
}
