#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

 
const int LENGTH = 12295;

struct anime
{
	string anime_id;
    string name;
    string genre;
    string type;
    string episodes;
    string ratings;
    string members;
};

anime hash_table_values[LENGTH]; // hash table which stores values
string hash_table_keys[LENGTH]; // hash table which stores keys

// hash index function
int get_index(string key){
    for (int get = 0; get < LENGTH; get++){
        if (hash_table_keys[get] == key) return get;
    }
    return -9999;
}

// hash value function
anime get_value(int ind){
    return hash_table_values[ind];
}
// Through these two functions (i.e., get_index and get_value), we can access each and every related element through anime_id


void parsar(){
    fstream csv;
    string temp1, temp2, temp3;
    anime Anime[LENGTH];
    int i = 0;
    csv.open("anime.tsv", ios :: in);
    if (!csv) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    while (!csv.eof()){
        // parsing every item in struct;

        getline(csv, Anime[i].anime_id, '\t');
		getline(csv,Anime[i].name, '\t');
	    getline(csv, Anime[i].genre, '\t');
        getline(csv, Anime[i].type, '\t');
        getline(csv, temp1, '\t');
        Anime[i].episodes = temp1;
        getline(csv, temp2, '\t');
        Anime[i].ratings = temp2;
        getline(csv, temp3, '\n');
        Anime[i].members = temp3;

        hash_table_keys[i] = Anime[i].anime_id;
        hash_table_values[i] = Anime[i];
        i++;
    }
}
//display by name
void display_anime(string name) {
    // Search for the anime with the given name
    bool found = false;
    for (int i = 0; i < LENGTH; i++) {
        if (hash_table_values[i].name == name) {
            // Anime found
            found = true;
            cout << "Anime ID: " << hash_table_values[i].anime_id << endl;
            cout << "Name: " << hash_table_values[i].name << endl;
            cout << "Genres: " << hash_table_values[i].genre << endl;
            cout << "Type: " << hash_table_values[i].type << endl;
            cout << "Episodes: " << hash_table_values[i].episodes << endl;
            cout << "Ratings: " << hash_table_values[i].ratings << endl;
            cout << "Members: " << hash_table_values[i].members << endl;
            cout << endl;
        }
    }
    if (!found) {
        cout << "Anime not found." << endl;
    }
}

//sort by anime id
void sortByanime_id()
{
	string temp; anime temp2;
	bool Swap; // To decrease best case complexity to O(n)
	for(int i = 0; i < LENGTH-1; i++)
	{
		Swap = false;
		for(int j = 0; j < LENGTH-i-1; j++)
		{
            istringstream iss(hash_table_keys[j]), iss2(hash_table_keys[j+1]);
            int num1, num2;
            iss >> num1; iss2 >> num2;
			if(num1 > num2)
			{
				temp = hash_table_keys[j];
				hash_table_keys[j] = hash_table_keys[j+1];
				hash_table_keys[j+1] = temp;
                temp2 = hash_table_values[j];
				hash_table_values[j] = hash_table_values[j+1];
				hash_table_values[j+1] = temp2;
				Swap = true;
			}
		}
		if(Swap == false)
		{
			return;
		}
    }
}

void MergeAnime(anime* array, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    anime tempArray[LENGTH];
    int index = leftFirst;
    int saveFirst = leftFirst;
    int num1, num2;
    istringstream ss1(array[leftFirst].anime_id), ss2(array[rightFirst].anime_id);
    ss1 >> num1;
    ss2 >> num2;
    while(leftFirst <= leftLast && rightFirst <= rightLast)
    {
        if(num1 < num2)
        {
            tempArray[index] = array[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[index] = array[rightFirst];
            rightFirst++;
        }
        index++;
    }
    while(leftFirst <= leftLast)
    {
        tempArray[index] = array[leftFirst];
        leftFirst++;
        index++;
    }
    while(rightFirst <= rightLast)
    {
        tempArray[index] = array[rightFirst];
        rightFirst++;
        index++;
    }
    for(index = saveFirst; index <= rightLast; index++)
    {
        array[index] = tempArray[index];
    }
}

void MergeSortAnime(anime* array, int first, int last)
{
    if(first < last)
    {
        int middle = (first+last)/2;
        MergeSortAnime(array, first, middle);
        MergeSortAnime(array, middle+1, last);
        MergeAnime(array, first, middle, middle+1, last);
    }
}

void MergeAnimeR(anime* array, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    anime tempArray[LENGTH];
    int index = leftFirst;
    int saveFirst = leftFirst;
    double num1, num2;
    istringstream ss1(array[leftFirst].ratings), ss2(array[rightFirst].ratings);
    ss1 >> num1;
    ss2 >> num2;
    while(leftFirst <= leftLast && rightFirst <= rightLast)
    {
        if(num1 < num2)
        {
            tempArray[index] = array[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[index] = array[rightFirst];
            rightFirst++;
        }
        index++;
    }
    while(leftFirst <= leftLast)
    {
        tempArray[index] = array[leftFirst];
        leftFirst++;
        index++;
    }
    while(rightFirst <= rightLast)
    {
        tempArray[index] = array[rightFirst];
        rightFirst++;
        index++;
    }
    for(index = saveFirst; index <= rightLast; index++)
    {
        array[index] = tempArray[index];
    }
}

void MergeSortAnimeR(anime* array, int first, int last)
{
    if(first < last)
    {
        int middle = (first+last)/2;
        MergeSortAnime(array, first, middle);
        MergeSortAnime(array, middle+1, last);
        MergeAnime(array, first, middle, middle+1, last);
    }
}

//sort by ratings
void sortByratings()
{
	string temp; anime temp2;
	bool Swap; // To decrease best case complexity to O(n)
	for(int i = 0; i < LENGTH-1; i++)
	{
		Swap = false;
		for(int j = 0; j < LENGTH-i-1; j++)
		{
            
            istringstream iss(hash_table_values[j].ratings), iss2(hash_table_values[j+1].ratings);
            double num1, num2;
            iss >> num1; iss2 >> num2;
			if(num1 > num2)
			{
				temp = hash_table_keys[j];
				hash_table_keys[j] = hash_table_keys[j+1];
				hash_table_keys[j+1] = temp;
                temp2 = hash_table_values[j];
				hash_table_values[j] = hash_table_values[j+1];
				hash_table_values[j+1] = temp2;
				Swap = true;
			}
		}
		if(Swap == false)
		{
			return;
		}
    }
}


//display animes with ratings
void display_animes_by_rating(string rating) {
    bool found = false;
    for (int i = 0; i < LENGTH; i++) {
        if (hash_table_values[i].ratings == rating) {
            found = true;
            cout << "Anime ID: " << hash_table_values[i].anime_id << endl;
            cout << "Name: " << hash_table_values[i].name << endl;
            cout << "Genres: " << hash_table_values[i].genre << endl;
            cout << "Type: " << hash_table_values[i].type << endl;
            cout << "Episodes: " << hash_table_values[i].episodes << endl;
            cout << "Ratings: " << hash_table_values[i].ratings << endl;
            cout << "Members: " << hash_table_values[i].members << endl;
            cout << endl;
        }
    }
    if (!found) {
        cout << "No animes found with that rating." << endl;
    }
}

//display animes with same members
void display_animes_by_members(string members) {
    bool found = false;
    for (int i = 0; i < LENGTH; i++) {
        if (hash_table_values[i].members == members) {
            found = true;
            cout << "Anime ID: " << hash_table_values[i].anime_id << endl;
            cout << "Name: " << hash_table_values[i].name << endl;
            cout << "Genres: " << hash_table_values[i].genre << endl;
            cout << "Type: " << hash_table_values[i].type << endl;
            cout << "Episodes: " << hash_table_values[i].episodes << endl;
            cout << "Ratings: " << hash_table_values[i].ratings << endl;
            cout << "Members: " << hash_table_values[i].members << endl;
            cout << endl;
        }
    }
    if (!found) {
        cout << "No animes found with that number of members." << endl;
    }
}

//displays animes with same type
void display_animes_by_type(string type) {
    bool found = false;
    for (int i = 0; i < LENGTH; i++) {
        if (hash_table_values[i].type == type) {
            found = true;
            cout << "Anime ID: " << hash_table_values[i].anime_id << endl;
            cout << "Name: " << hash_table_values[i].name << endl;
            cout << "Genres: " << hash_table_values[i].genre << endl;
            cout << "Type: " << hash_table_values[i].type << endl;
            cout << "Episodes: " << hash_table_values[i].episodes << endl;
            cout << "Ratings: " << hash_table_values[i].ratings << endl;
            cout << "Members: " << hash_table_values[i].members << endl;
            cout << endl;
        }
    }
    if (!found) {
        cout << "No animes found with that type." << endl;
    }
}

void split_genres(string genres, string genre_array[], int &size) {
    stringstream genre_string(genres);
    string genre;
    int i = 0;
    while( getline(genre_string, genres, ',')) {
            genre_array[i] = genres;
            i++;
    }
    size = i;
}

//display animes with same genres
void display_animes_by_genre(string genre) {
    bool found = false;
    for (int i = 0; i < LENGTH; i++) {
        string genre_array[100];
        int size;
        split_genres(hash_table_values[i].genre, genre_array, size);
        for (int j = 0; j < size; j++) {
            if (genre_array[j] == genre) {
                found = true;
                cout << "Anime ID: " << hash_table_values[i].anime_id << endl;
                cout << "Name: " << hash_table_values[i].name << endl;
                cout << "Genres: " << hash_table_values[i].genre << endl;
                cout << "Type: " << hash_table_values[i].type << endl;
                cout << "Episodes: " << hash_table_values[i].episodes << endl;
                cout << "Ratings: " << hash_table_values[i].ratings << endl;
                cout << "Members: " << hash_table_values[i].members << endl;
                cout << endl;
            }
        }
    }
    if (!found) {
        cout << "No animes found with that genre." << endl;
    }
}
// display all animes dets 
void print(int len)
{
    for(int i = 0; i < len; i++){
        cout << "Anime ID: " << hash_table_values[i].anime_id << endl;
        cout << "Name: " << hash_table_values[i].name << endl;
        cout << "Genres: " << hash_table_values[i].genre << endl;
        cout << "Type: " << hash_table_values[i].type << endl;
        cout << "Episodes: " << hash_table_values[i].episodes << endl;
        cout << "Ratings: " << hash_table_values[i].ratings << endl;
        cout << "Members: " << hash_table_values[i].members << endl;
        cout << endl;
    }
}
int main()
{
    parsar();
    int choice;
    string c;
    while (true){
        cout << "Enter your choices...: " << endl;
        cout << "1. search anime by its name" << endl;
        cout << "2. search anime by its genre" << endl;
        cout << "3. search anime by its ratings" << endl;
        cout << "4. search anime by its members" << endl;
        cout << "5. search anime by its type" << endl;
        cout << "6. sort by anime_id and print" << endl;
        cout << "7. sort by ratings and print" << endl;
        cout << "8. end" << endl;
        cin >> choice;
        if (choice == 1){
            cout << "ENTER: ";
            cin >> c;
            display_anime(c);
            continue;
        } 
        else if (choice == 2){
            cout << "ENTER: ";
            cin >> c;
            display_animes_by_genre(c);
            continue;
        }
        else if (choice == 3){
            cout << "ENTER: ";
            cin >> c;
            display_animes_by_rating(c);
            continue;
        }
        else if (choice == 4){
            cout << "ENTER: ";
            cin >> c;
            display_animes_by_members(c);
            continue;
        }
        else if (choice == 5){
            cout << "ENTER: ";
            cin >> c;
            display_animes_by_type(c);
            continue;
        }
        else if (choice == 6){
            int lenn;
            cout << "ENTER length u wanna print: ";
            cin >> lenn;
            MergeSortAnime(hash_table_values, 0, LENGTH-1);
            print(lenn);
            continue;
        }
        else if (choice == 7){
            int lenn;
            cout << "ENTER length u wanna print: ";
            cin >> lenn;
            MergeSortAnimeR(hash_table_values, 0, LENGTH-1);
            print(lenn);
            continue;
        }
        else if (choice == 8){
            break;
        }

    }
    
    return 0;
}