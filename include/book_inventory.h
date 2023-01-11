#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace book {
struct Book {
  string title;         // title of the book
  string author;        // author of the book
  float cost;           // cost of the book
  string isbn;          // a unique string assigned to each book
  string language_code; // language of the book
  int num_pages;        // number of pages
  string publisher;     // publisher of the book
  int count;            // how many books left in the inventory
};

using Books = vector<Book>;
Books read_database(std::string filepath);
std::string search(Books inventory, std::string title);
bool order(Books &inventory, Books &shopinglist, std::string isbn);
double get_receipt(Books &shopinglist);

inline Books read_database(std::string filepath) {
  string line, word;
  ifstream myfile(filepath);
  vector<Book> books;
  // cout << myfile.good() << endl;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      stringstream str(line);
      Book tmpBook;
      vector<string> row;
      while (getline(str, word, ',')) {
        row.push_back(word);
      }
      // cout << row.size() << endl;
      tmpBook.title = row[1];
      tmpBook.author = row[2];
      tmpBook.cost = stof(row[3]);
      tmpBook.isbn = row[4];
      tmpBook.language_code = row[5];
      tmpBook.num_pages = atoi(row[6].c_str());
      tmpBook.publisher = row[7];
      tmpBook.count = atoi(row[8].c_str());
      books.push_back(tmpBook);
    }
    myfile.close();
  } else {
    throw std::runtime_error("Unable to open");
  }
  return books;
}

inline string search(Books inventory, string title) {

  for (auto s : inventory) {
    if (s.title == title.c_str()) {
      return s.isbn;
    }
  }
  return "none";
};
inline bool order(Books &inventory, Books &shopinglist, string isbn) {
  for (int i = 0; i < inventory.size(); i++) {
    if (inventory[i].isbn == isbn.c_str()) {
      shopinglist.push_back(inventory[i]);
      inventory[i].count--;
      return true;
    }
  }
  return false;
};
inline double get_receipt(Books &shopinglist) {
  float total_price;
  cout << "*************************************************" << endl;
  cout << "| title     |    isbn       |          pirce    |" << endl;
  cout << "|-----------------------------------------------|" << endl;
  for (auto s : shopinglist) {
    cout << "|   " << s.title << "   |   " << s.isbn << "    |   " << s.cost
         << "$"
         << "    |" << endl;
    total_price += s.cost;
  };
  cout << "|-----------------------------------------------|" << endl;
  cout << "|                      Total Price  |   " << total_price << "$"
       << "    |" << endl;
  cout << "*************************************************" << endl;
  return total_price;
}
} // namespace book