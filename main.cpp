// COMSC 210 | Lab 18 | Yeji Kim

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// create Movie class

class Movie {
    private: struct Review {
        double rating;
        string comment;
        Review * next;
    };

    string title;
    Review * head;

    public:
        // constructor
        Movie(string t) {
            title = t;
            head = nullptr;
        }

    // add review to head of the list
    void addReview(double rating, string comment) {
        Review * newReview = new Review;

        newReview -> rating = rating;
        newReview -> comment = comment;
        newReview -> next = head;

        head = newReview;
    }

    // output movie titles, reviews, and avg
    void output() {
        cout << "Movie Title: " << title << endl;

        Review * current = head;
        int count = 1;
        double total = 0.0;

        while (current) {
            cout << " > Review # " << count << ": " << fixed << setprecision(1) << current -> rating <<
                ": " << current -> comment << endl;

            total += current -> rating;
            count++;
            current = current -> next;
        }

        double average = total / (count - 1);

        cout << " > Average: " << fixed << setprecision(1) << average << endl;
        cout << endl;
    }

    // destructor
    ~Movie() {
        Review * current = head;

        while (current) {
            Review * next = current -> next;
            delete current;
            current = next;
        }

        head = nullptr;
    }

    // copy constructor
    Movie(const Movie & other) {
        title = other.title;
        head = nullptr;

        // copy reviews
        Review * current = other.head;

        while (current) {
            addReview(current -> rating, current -> comment);
            current = current -> next;
        }
    }

    // copy assignment operator
    Movie & operator = (const Movie & other) {
        if (this != & other) {
            // delete current reviews
            Review * current = head;

            while (current) {
                Review * next = current -> next;
                delete current;
                current = next;
            }

            head = nullptr;

            title = other.title;

            // copy reviews
            current = other.head;

            while (current) {
                addReview(current -> rating, current -> comment);
                current = current -> next;
            }
        }

        return * this;
    }
};

int main() {
    srand(time(0));

    //open input file
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cout << "Error: Could not open input.txt" << endl;
        return 1;
    }

    // Read 12 review comments
    vector < string > comments;
    string comment;

    while (getline(inputFile, comment)) {
        comments.push_back(comment);
    }

    inputFile.close();

    // Create movies
    vector < Movie > movies;

    movies.push_back(Movie("Lord of the Rings"));
    movies.push_back(Movie("The Godfather"));
    movies.push_back(Movie("Star Wars"));
    movies.push_back(Movie("Jurassic Park"));

    // Add 3 reviews to each movie
    int commentIndex = 0;

    for (int i = 0; i < movies.size(); i++) {
        for (int j = 0; j < 3; j++) {
            // Generate random rating from 1.0 to 5.0
            double rating = 1.0 + (rand() % 41) / 10.0;

            movies[i].addReview(rating, comments[commentIndex]);

            commentIndex++;
        }
    }

    // Output all movies
    for (int i = 0; i < movies.size(); i++) {
        movies[i].output();
    }

    return 0;
}