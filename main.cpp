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
    void setMovie(string m) {movie = m;}
    void setReviews(Node* head) {reviews = head;}
    string getMovie() {return movie;}
    Node* getReviews() {return reviews;}
};

Node* addNodeHead(Node *, double, string);
Node* addNodeTail(Node *, double, string);
Node* addReview(Node*, int);
void output(Node*);

int main()
{
    vector<Movie> movies;

    ifstream inputFile("reviews.txt");

    if(!inputFile.is_open())
    {
        cout << "Error! Can't open File!";
        return 0;
    }

    string rev;
    int count = 1;

    while (getline(inputFile, rev))
    {
        Movie temp;
        Node* head = nullptr;
        double rating = rand() % 10;
        head = addNodeHead(head, rating, rev);
        temp.setReviews(head);
        string title = "Movie #" + count++;
        temp.setMovie(title);
    }

    for(auto movie : movies)
        output(movie.getReviews());

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
// arguments: a node object representing the head
// returns: none
void output(Node* head)
{
    cout << "Outputting All Reviews: " << endl;

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
