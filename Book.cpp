//Onyinyechi Okafor 011
#include "Book.hpp"

#include <iostream>
#include <string>
using namespace std;


Book::Book(string t, string auth, int yr, string pub, long long isbn, float rate) {
	title = t;
	author = auth;
	year = yr;
	publisher = pub;
	isbn13 = isbn;
	rating = rate;
	checked_out = false;
}

Book::Book() {
	title = "";
	author = "";
	year = 0;
	publisher = "";
	isbn13 = 0;
	rating = 0;
	checked_out = false;
}

float Book::getRating() {
	return rating;
}


void Book::printBook() {
	cout << "---------------------" << endl;
	cout << title << "\nAuthor: " << author << "\t\tYear: " << year << endl;
	cout << "Publisher: " << publisher << "\tISBN-13: " << isbn13 << "\tRating: " << rating << endl;
	cout << "Currently Available: " << (checked_out ? "No" : "Yes") << endl;
}

bool Book::operator<(Book b2) {
    //if authors are different, compare lexicographically
    if (author != b2.author){
       return author < b2.author;
    }
    //if authors are same, compare lexicographically
    return title < b2.title;
}

bool Book::operator>(Book b2) {
    //using *this to refer to current object (book)
    //use < operator to see if book is less than current book
	return b2 < *this;
}

bool Book::operator==(Book b2) {
    //books are equal if their authors and titles are the same
	return (author == b2.author) && (title == b2.title);
}

bool Book::operator!=(Book b2) {
    //using *this to refer to current object (book)
    //use == operator to check if books are equal, then negates the result to see if they aren't equal
	return !(*this == b2);
}

bool Book::operator<=(Book b2) {
    //a book is <= to another if it's < the other book or = to it
	return (operator < (b2) || operator == (b2));
}

bool Book::operator>=(Book b2) {
    //a book is >= to another if it's > the other book or = to it
    return (operator > (b2) || operator == (b2));
}