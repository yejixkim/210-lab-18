// COMSC 210 | Lab 18 | Yeji Kim

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// create Movie class

class Movie {
    private:
        struct Review {
            double rating;
            string comment;
            Review *next;
        };

        string title;
        Review *head;

    public:
        // constructor
        Movie(string t) {
            title = t;
            head = nullptr;
        }

        // add review to head of the list
        void addReview(double rating, string comment) {
            Review *newReview = new Review;

            newReview->rating = rating;
            newReview->comment = comment;
            newReview->next = head;

            head = newReview;
        }

        // output movie titles, reviews, and avg
        void output() {
            cout << "Movie Title: " << title << endl;

            Review *current = head;
            int count = 1;
            double total = 0.0;

            while (current) {
                cout << " > Review " << count << ": " << fixed << setprecision(1) << current->rating <<
                ": " << current->comment << endl;

                total += current->rating;
                count++;
                current = current->next;
            }

            double average = total / (count - 1);

            cout << " > Average: " << fixed << setprecision(1) << average << endl;
            cout << endl;
        }

        // destructor
        ~Movie() {
            Review *current = head;

            while (current) {
                Review *next = current->next;
                delete current;
                current = next;
            }

            head = nullptr;
        }

        // copy constructor
        Movie(const Movie &other) {
            title = other.title;
            head = nullptr;

            // copy reviews
            Review *current = other.head;

            while (current) {
                addReview(current->rating, current->comment);
                current = current->next;
            }

            head = nullptr;

            
        }



};

int main () {
    cout << "Hello, World!" << endl;
    return 0;
}