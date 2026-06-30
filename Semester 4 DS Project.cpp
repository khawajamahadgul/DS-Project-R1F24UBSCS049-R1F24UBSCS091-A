#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Song{
	public:
		string title;
		string artist;
		int duration;
		Song* next;
		Song* prev;
		
	Song (string t, string a, int d = 0){
		title = t;
		artist = a;
		duration = d;
		next = nullptr;
		prev = nullptr;
	}
};

class Playlist{
	private:
		Song* head;
		Song* tail;
		Song* current;
		int songCount;
		bool repeatAll;
		bool repeatOne;
	public:
		Playlist(){
			head = nullptr;
			tail = nullptr;
			current = nullptr;
			songCount = 0;
			repeatAll = false;
			repeatOne = false;
		}
		~Playlist(){
			Song* temp = head;
			Song* chop = nullptr;
			while (temp != nullptr){
				chop = temp->next;
				delete temp;
				temp = chop;
			}
		}
		void addSong(string title, string artist, int duration = 0){
			Song* create = new Song(title, artist, duration);
			if (head == nullptr){
				head = tail = current = create;
			} else {
				tail->next = create;
				create->prev = tail;
				tail = create;
			}
			songCount++;
        	cout<<"Added: \""<<title<< "\" by "<<artist<<"\n\n";
			system("pause");
		}
		void addAftercurrent(string title, string artist, int duration = 0){
			if (head == nullptr || current == nullptr || current == tail) {
            	addSong(title, artist, duration);
            	return;
			}
			Song* create = new Song(title, artist, duration);
			create->next = current->next;
			current->next->prev = create;
			current->next = create;
			create->prev= current;
			songCount++;
			cout<<"Added: \""<<title<< "\" by "<<artist<<"\n\n";
			system("pause");
		}
		void removeSong(string title){
        	if (head == nullptr) {
            	cout << "Playlist is empty!\n\n";
            	system("pause");
            	return;
        }
        	Song* temp = head;

        	while (temp != nullptr && temp->title != title){
            	temp = temp->next;
        }

        	if (temp == nullptr){
            	cout << "Song \"" << title << "\" not found!\n\n";
            	system("pause");
            	return;
        }
        	if (temp == current){
            	if (current->next != nullptr)
                	current = current->next;
            	else if (current->prev != nullptr)
                	current = current->prev;
            	else
                	current = nullptr;
        }
            if (temp == head && temp == tail){
            	head = tail = nullptr;
        	} else if (temp == head){
            	head = head->next;
            	head->prev = nullptr;
        	} else if (temp == tail){
            	tail = tail->prev;
            	tail->next = nullptr;
        	} else{
            	temp->prev->next = temp->next;
            	temp->next->prev = temp->prev;
        	}

        cout << "Removed: \"" << temp->title << "\"\n\n";
        delete temp;
        songCount--;
        system("pause");
    }
        void playNext(){
        if (head == nullptr) {
            cout << "Playlist is empty!\n\n";
            system("pause");
            return;
        }

        if (repeatOne && current != nullptr) {
            cout << "Now Playing: " << current->title << " - " << current->artist<<"\n\n";
            system("pause");
            return;
        }
        if (current == nullptr || current->next == nullptr) {
            if (repeatAll) {
                current = head;
                cout << "Wrapping to start!\n";
            } else {
                cout << "End of playlist!\n\n";
                system("pause");
                return;
            }
        } else {
            current = current->next;
        }

        cout << "Now Playing: " << current->title << " - " << current->artist <<"\n\n"; 
		system("pause");   
    }
        void playPrevious() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n\n";
            system("pause");
            return;
        }

        if (repeatOne && current != nullptr) {
            cout << "Now Playing: " << current->title << " - " << current->artist<<"\n\n";
            system("pause");
            return;
        }

        if (current == nullptr || current->prev == nullptr) {
            if (repeatAll) {
                current = tail;
                cout << "Wrapping to end!\n";
            } else {
                cout << "Start of playlist!\n\n";
                system("pause");
                return;
            }
        } else {
            current = current->prev;
        }

        cout << "Now Playing: " << current->title << " - " << current->artist <<"\n\n";
        system("pause");
    }
    	void playSong(string title) {
    		if (head == nullptr) {
        	cout << "Playlist is empty!" << endl << endl;
        	system("pause");
        	return;
    	}

    	Song* temp = head;
    	while (temp != nullptr && temp->title != title) {
        	temp = temp->next;
    	}

    	if (temp == nullptr) {
        	cout << "Song \"" << title << "\" not found!" <<"\n\n";
        	system("pause");
        	return;
    	}

    	current = temp;
    	cout << "Now Playing: " << current->title << " - " << current->artist <<"\n\n";
    	system("pause");
	}
		void stop() {
    	if (current == nullptr) {
        	cout << "Nothing is playing!" <<"\n\n";
        	system("pause");
    	} else {
        	cout << "Stopped: " << current->title <<"\n\n";
        	current = nullptr;
        	system("pause");
    	}
	}
        void searchSong(string title) {
        if (head == nullptr) {
            cout << "Playlist is empty!" <<"\n\n";
            system("pause");
            return;
        }

        Song* temp = head;
        int index = 1;

        while (temp != nullptr) {
            if (temp->title == title) {
                cout << "Found \"" << title << "\" at position " << index << endl;
                cout << "artist: " << temp->artist << endl;
                cout << "duration: " << temp->duration << " seconds" <<"\n\n";
                system("pause");
                return;
            }
            temp = temp->next;
            index++;
        }

        cout << "Song \"" << title << "\" not found!" <<"\n\n";
        system("pause");
    }
        void displayPlaylist() {
        	system("cls");
        if (head == nullptr) {
            cout << endl;
            cout << "============================================" << endl;
            cout << "         PLAYLIST IS EMPTY!" << endl;
            cout << "============================================" <<"\n\n";
            system("pause");
            return;
        }

        cout << endl;
        cout << "============================================" << endl;
        cout << "            MY PLAYLIST" << endl;
        cout << "============================================" << endl;

        Song* temp = head;
        int index = 1;

        while (temp != nullptr) {
            if (temp == current) {
                cout << " >> " << index << ". " << temp->title << " - " << temp->artist << " <<" << endl;
            } else {
                cout << "    " << index << ". " << temp->title << " - " << temp->artist << endl;
            }
            temp = temp->next;
            index++;
        }

        cout << "============================================" << endl;
        cout << "Total Songs: " << songCount << "  |  ";

        if (repeatOne)
            cout << "Repeat: ONE";
        else if (repeatAll)
            cout << "Repeat: ALL";
        else
            cout << "Repeat: OFF";

        cout << endl;
        cout << "============================================" <<"\n\n";
        system("pause");
    }
        void showcurrent() {
        	system("cls");
        if (current == nullptr) {
            cout << "No song is currently playing!" <<"\n\n";
            system("pause");
        } else {
            cout << "Now Playing: " << current->title << " - " << current->artist <<"\n\n";
            system("pause");
        }
    }
        void reversePlaylist() {
        if (songCount < 2) {
            cout << "Not enough songs!" <<"\n\n";
            system("pause");
            return;
        }

        Song* temp = nullptr;
        Song* swapper = head;

        while (swapper != nullptr) {
            temp = swapper->prev;
            swapper->prev = swapper->next;
            swapper->next = temp;
            swapper = swapper->prev;
        }

        temp = head;
        head = tail;
        tail = temp;

        current = head;
        cout << "Playlist reversed!" << "\n\n";
        system("pause");
    }

    void togglerepeatAll() {
        repeatAll = !repeatAll;
        if (repeatAll) repeatOne = false;
        cout << (repeatAll ? "Repeat ALL: ON" : "Repeat ALL: OFF") <<"\n\n";
        system("pause");
    }

    void togglerepeatOne() {
        repeatOne = !repeatOne;
        if (repeatOne) repeatAll = false;
        cout << (repeatOne ? "Repeat ONE: ON" : "Repeat ONE: OFF") <<"\n\n";
        system("pause");
    }
};

void showMenu() {
	system("cls");
    cout << endl;
    cout << "============================================" << endl;
    cout << "      MUSIC PLAYLIST MANAGER" << endl;
    cout << "============================================" << endl;
    cout << "  [1] Add Song at End" << endl;
    cout << "  [2] Add Song After current" << endl;
    cout << "  [3] Remove Song by Name" << endl;
    cout << "  [4] Play Next" << endl;
    cout << "  [5] Play Previous" << endl;
    cout << "  [6] Search Song" << endl;
    cout << "  [7] Display Full Playlist" << endl;
    cout << "  [8] Reverse Playlist" << endl;
    cout << "  [9] Toggle Repeat All" << endl;
    cout << "  [10] Toggle Repeat One" << endl;
    cout << "  [11] Show current Song" << endl;
    cout << "  [12] Play Specific Song" << endl;
	cout << "  [13] Stop Playing" << endl;
    cout << "  [0] Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter your choice: ";
	}

int main() {
    Playlist playlist;
    int choice;
    
    playlist.addSong("Blinding Lights", "The Weeknd", 200);
    playlist.addSong("Shape of You", "Ed Sheeran", 234);
    playlist.addSong("Bohemian Rhapsody", "Queen", 354);
    playlist.addSong("Hotel California", "Eagles", 391);

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, artist;
                int duration;
                cin.ignore();
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter duration (seconds): ";
                cin >> duration;
                playlist.addSong(title, artist, duration);
                break;
            }
            case 2: {
                string title, artist;
                int duration;
                cin.ignore();
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter duration (seconds): ";
                cin >> duration;
                playlist.addAftercurrent(title, artist, duration);
                break;
            }
            case 3: {
                string title;
                cin.ignore();
                cout << "Enter song title to remove: ";
                getline(cin, title);
                playlist.removeSong(title);
                break;
            }
            case 4:
                playlist.playNext();
                break;
            case 5:
                playlist.playPrevious();
                break;
            case 6: {
                string title;
                cin.ignore();
                cout << "Enter song title to search: ";
                getline(cin, title);
                playlist.searchSong(title);
                break;
            }
            case 7:
                playlist.displayPlaylist();
                break;
            case 8:
                playlist.reversePlaylist();
                break;
            case 9:
                playlist.togglerepeatAll();
                break;
            case 10:
                playlist.togglerepeatOne();
                break;
            case 11:
                playlist.showcurrent();
                break;
            case 12: {
    			string title;
    			cin.ignore();
    			cout << "Enter song title to play: ";
    			getline(cin, title);
    			playlist.playSong(title);
    			break;
			}
			case 13:
    			playlist.stop();
    			break;
            case 0:
                cout << endl << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Try again." <<"\n\n";
        }
    } while (choice != 0);

    return 0;
}