// COMSC-210 | Lab 18 | Daniil Malakhov
// IDE used: Codeblocks
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct Node
{
    double rating;
    string comments;
    Node *next;
};

class Movie
{
private:
    string movie;
    Node* reviews;
public:
    // sets the title for the movie
    // arguments: string representing the movie title
    // returns: none
    void setMovie(string m) {movie = m;}
    // sets the the head of the review linked list
    // arguments: Node object that represents the head of the review linked list
    // returns: none
    void setReviews(Node* head) {reviews = head;}
    // returns the title of the movie
    // arguments: none
    // returns: returns the title of the movie
    string getMovie() {return movie;}
    // returns the head node of the review linked list
    // arguments: none
    // returns: the head node of the review linked list
    Node* getReviews() {return reviews;}
};

Node* addNodeHead(Node *, double, string);
Node* addNodeTail(Node *, double, string);
Node* addReview(Node*, int);
void output(Node*, string);

int main()
{
    vector<Movie> movies;

    // opens the file
    ifstream inputFile("reviews.txt");

    //checks if file is open
    if(!inputFile.is_open())
    {
        cout << "Error! Can't open File!";
        return 0;
    }

    string rev;
    int movieCount = 1;
    Movie temp;
    Node* head = nullptr;

    // reads from file line by line and puts it into string review
    while (getline(inputFile, rev))
    {
        // if three reviews are inputed into the head node then push back the movie class into the vector of movies and derefrence head node object
        if(movieCount > 3)
        {
           movies.push_back(temp);
           head = nullptr;
           movieCount = 1;
        }

        // generates a random double between 1.0 and 5.0 which represents rating
        double rating = ((double) rand()) / RAND_MAX;
        rating = 4 * rating + 1;
        rating = (int)(rating / 0.1) * 0.1;

        // adds node to head linked list
        head = addNodeHead(head, rating, rev);
        temp.setReviews(head);

        // creates title for movie and sets title for movie of movie object
        string title = "Movie x";
        temp.setMovie(title);

        movieCount++;
    }

    //pushes back the last movie object into vector array of movie objects
    movies.push_back(temp);

    //outputs all movies
    for(auto movie : movies)
        output(movie.getReviews(), movie.getMovie());

}

// adds a node to the head of the linked list and populates it with given rating and comment
// arguments: Node object representing the head, double variable representing the rating of movie, string variable representing comments on movie
// returns: A node object representing the head
Node* addNodeHead(Node *head, double rating, string comment)
{
    Node *newRating = new Node;
    if (!head)
    {
        head = newRating;
        newRating->next = nullptr;
        newRating->rating = rating;
        newRating->comments = comment;
    }
    else
    {
        newRating->next = head;
        newRating->rating = rating;
        newRating->comments = comment;
        head = newRating;
    }
    return head;
}

// adds a node to the tail of the linked list and populates it with given rating and comment
// arguments: Node object representing the head, double variable representing the rating of movie, string variable representing comments on movie
// returns: A node object representing the head
Node* addNodeTail(Node *head, double rating, string comment)
{
    Node *newRating = new Node;
    Node *temp = new Node;
    temp = head;
    if (!head)
    {
        head = newRating;
        newRating->next = nullptr;
        newRating->rating = rating;
        newRating->comments = comment;
    }
    else
    {
        while (temp->next != nullptr)
            temp = temp->next;
        newRating->next = nullptr;
        newRating->rating = rating;
        newRating->comments = comment;
        temp->next = newRating;
    }
    return head;
}

// adds a review to the list by calling the specified add node method, gathers data from user to populate node
// arguments: a node object representing the head, an integer variable representing the method to use when adding nodes to linked list
// returns: A node object representing the head
Node* addReview(Node *head, int entry)
{
    double rating;
    string comment;

    cout << "Enter review rating 0-5: ";
    cin >> rating;

    cin.ignore();

    cout << "Enter review comments: ";
    getline(cin, comment);

    if (entry == 1)
        head = addNodeHead(head, rating, comment);
    else
        head = addNodeTail(head, rating, comment);

    return head;
}

// outputs all the reviews and comments per rating in the linked list and prints average of all reviews
// arguments: a node object representing the head, a string representing title of movie
// returns: none
void output(Node* head, string title)
{
    cout << "Reviews for " << title << endl;

    if (!head) {
        cout << "No reviews in list" << endl;
        return;
    }

    int count = 1;
    double sum = 0;
    Node * current = head;

    while (current) {
        cout << "      > Review #" << count++ << ": " << current->rating << ": " << current->comments << endl;
        sum += current->rating;
        current = current->next;
    }

    cout << "      > Average: " << sum / (count - 1) << endl;
}
