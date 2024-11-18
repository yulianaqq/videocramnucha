#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct VideoShop {
    string name, genre, director;
    double popularity, price;
};

void addMovie(vector<VideoShop>& array) {
    VideoShop bit;
    cin.ignore();
    cout << "Enter the name of the film: ";
    getline(cin, bit.name);
    cout << "Enter the director: ";
    getline(cin, bit.director);
    cout << "Enter the genre: ";
    getline(cin, bit.genre);
    cout << "Enter the rating: ";
    cin >> bit.popularity;
    cout << "Enter the price: ";
    cin >> bit.price;
    array.push_back(bit);
    cout << "Movie added successfully!" << endl;
}

void saveMovies(const string& filename, const vector<VideoShop>& array) {
    ofstream f(filename, ios::out);
    if (!f.is_open()) {
        cout << "Error: File cannot be opened.\n";
        return;
    }
    for (const auto& movie : array) {
        f << movie.name << "\n"
          << movie.director << "\n"
          << movie.genre << "\n"
          << movie.popularity << "\n"
          << movie.price << "\n";
    }
    f.close();
    cout << "Movies saved successfully!" << endl;
}

void loadMovies(const string& filename, vector<VideoShop>& array) {
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "Error: File cannot be opened.\n";
        return;
    }
    VideoShop bit;
    while (getline(f, bit.name) && getline(f, bit.director) && getline(f, bit.genre)
           && (f >> bit.popularity) && (f >> bit.price)) {
        f.ignore();
        array.push_back(bit);
    }
    f.close();
}

void showMovies(const vector<VideoShop>& array) {
    if (array.empty()) {
        cout << "No movies available.\n";
        return;
    }
    cout << "\n\nName\t\tDirector\t\tGenre\t\tRating\t\tPrice\n";
    cout << "---------------------------------------------------------------------------------\n";
    for (const auto& movie : array) {
        cout << movie.name << "\t\t"
             << movie.director << "\t\t"
             << movie.genre << "\t\t"
             << movie.popularity << "\t\t"
             << movie.price << endl;
    }
}

void searchByName(const vector<VideoShop>& array, const string& name) {
    bool found = false;
    for (const auto& movie : array) {
        if (movie.name == name) {
            cout << "Found movie: " << movie.name << ", Director: " << movie.director
                 << ", Genre: " << movie.genre << ", Rating: " << movie.popularity
                 << ", Price: " << movie.price << endl;
            found = true;
        }
    }
    if (!found) cout << "No movie found with name: " << name << endl;
}

void searchByGenre(const vector<VideoShop>& array, const string& genre) {
    bool found = false;
    for (const auto& movie : array) {
        if (movie.genre == genre) {
            cout << "Found movie: " << movie.name << ", Director: " << movie.director
                 << ", Genre: " << movie.genre << ", Rating: " << movie.popularity
                 << ", Price: " << movie.price << endl;
            found = true;
        }
    }
    if (!found) cout << "No movie found in genre: " << genre << endl;
}

void searchByDirector(const vector<VideoShop>& array, const string& director) {
    bool found = false;
    for (const auto& movie : array) {
        if (movie.director == director) {
            cout << "Found movie: " << movie.name << ", Director: " << movie.director
                 << ", Genre: " << movie.genre << ", Rating: " << movie.popularity
                 << ", Price: " << movie.price << endl;
            found = true;
        }
    }
    if (!found) cout << "No movie found by director: " << director << endl;
}

void mostPopularInGenre(const vector<VideoShop>& array, const string& genre) {
    const VideoShop* mostPopular = nullptr;
    for (const auto& movie : array) {
        if (movie.genre == genre && (!mostPopular || movie.popularity > mostPopular->popularity)) {
            mostPopular = &movie;
        }
    }
    if (mostPopular) {
        cout << "Most popular movie in genre " << genre << " is " << mostPopular->name
             << " with a rating of " << mostPopular->popularity << endl;
    } else {
        cout << "No movies found in genre: " << genre << endl;
    }
}

int main() {
    vector<VideoShop> array;
    string filename = "film.txt";

    loadMovies(filename, array);

    cout << "Video store services:\n"
         << "1. Show all movies\n"
         << "2. Search by name\n"
         << "3. Search by genre\n"
         << "4. Search by director\n"
         << "5. Most popular film in genre\n"
         << "6. Add a movie\n"
         << "7. Save movies\n"
         << "0. Exit\n";
    
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 0) {
            char save;
            cout << "Do you want to save changes before exiting? (y/n): ";
            cin >> save;
            if (save == 'y' || save == 'Y') {
                saveMovies(filename, array);
            }
            break;
        }

        switch (choice) {
            case 1:
                showMovies(array);
                break;
            case 2: {
                string name;
                cout << "Enter movie name: ";
                cin.ignore();
                getline(cin, name);
                searchByName(array, name);
                break;
            }
            case 3: {
                string genre;
                cout << "Enter genre: ";
                cin.ignore();
                getline(cin, genre);
                searchByGenre(array, genre);
                break;
            }
            case 4: {
                string director;
                cout << "Enter director: ";
                cin.ignore();
                getline(cin, director);
                searchByDirector(array, director);
                break;
            }
            case 5: {
                string genre;
                cout << "Enter genre: ";
                cin.ignore();
                getline(cin, genre);
                mostPopularInGenre(array, genre);
                break;
            }
            case 6:
                addMovie(array);
                break;
            case 7:
                saveMovies(filename, array);
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }
    }
    return 0;
}
