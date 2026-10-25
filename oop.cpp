#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
using namespace std;

class Book {
  string bookid;
  string title;
  string author;
  string category;
  int stock;
  string library_id;

public:
  Book() {
    bookid = "";
    title = " ";
    author = " ";
    category = " ";
    stock = 0;
    library_id = " ";
  }

  void add_book(string lib_id) {
    ofstream file;
    file.open("book.txt", ios::app);
    library_id = lib_id;
    cout << "\nEnter the Book ID : ";
    getline(cin >> ws, bookid);
    cout << "\nEnter the Title : ";
    getline(cin >> ws, title);
    cout << "\nEnter the Author : ";
    getline(cin >> ws, author);
    cout << "\nEnter the category : ";
    getline(cin >> ws, category);
    cout << "\nEnter the Stock : ";
    cin >> stock;
    while (stock < 0) {
      cout << "Stock cannot be negative. Enter again: ";
      cin >> stock;
    }
    file << library_id << "|" << bookid << "|" << title << "|" << author << "|"
         << category << "|" << stock << endl;
    file.close();
  }

  string get_library_id() { return library_id; }

  void display_book() {
    cout << "\nLibrary ID : " << library_id << endl;
    cout << "Book ID : " << bookid << endl;
    cout << "Title : " << title << endl;
    cout << "Author : " << author << endl;
    cout << "Catogory : " << category << endl;
    cout << "Stock : " << stock << endl;
    cout << endl;
  }
  bool search_book(string id, string t) { return bookid == id || title == t; }
  string get_book_id() { return bookid; }

  void set_library_id(string id) { library_id = id; }
  bool issue_book() {
    if (stock > 0) {
      stock--;
      return true;
    }
    return false;
  }
  void save_record(ofstream &file) {
    file << library_id << "|" << bookid << "|" << title << "|" << author << "|"
         << category << "|" << stock << endl;
  }
  void return_book() { stock++; }
  friend class restore;
};

bool remove_issue(string user_id, string book_id) {
  ifstream in("issue.txt");
  ofstream out("issue_temp.txt");

  string a, b;
  bool found = false;

  while (getline(in, a, '|') && getline(in, b)) {
    if (a == user_id && b == book_id && !found) {
      found = true;
    } else {
      out << a << "|" << b << endl;
    }
  }

  in.close();
  out.close();

  if (found) {
    remove("issue.txt");
    rename("issue_temp.txt", "issue.txt");
  } else {
    remove("issue_temp.txt");
  }

  return found;
}

struct node {
  Book data;
  node *next;
};
node *head = NULL;

void save_books() {
  ofstream file("book.txt", ios::trunc);

  node *temp = head;

  while (temp != NULL) {
    temp->data.save_record(file);
    temp = temp->next;
  }

  file.close();
}

void record_issue(string user_id, string book_id) {
  ofstream file("issue.txt", ios::app);
  file << user_id << "|" << book_id << endl;
  file.close();
}

class restore {
public:
  restore() {
    ifstream file;
    file.open("book.txt");
    string a, b, c, d, e, f;
    int l;
    while (getline(file, a, '|') && getline(file, b, '|') &&
           getline(file, c, '|') && getline(file, d, '|') &&
           getline(file, e, '|') && getline(file, f)) {
      l = stoi(f);
      node *newnode = new node;
      newnode->data.library_id = a;
      newnode->data.bookid = b;
      newnode->data.title = c;
      newnode->data.author = d;
      newnode->data.category = e;
      newnode->data.stock = l;
      newnode->next = head;
      head = newnode;
    }
    file.close();
  }
};

class user {
  string userid;
  string name;
  string pass;
  string libra_id;
  int a;

public:
  void register_user(string n, string c) {
    random_device b;
    a = b() % 9000 + 1000;
    userid = "USID" + to_string(a);
    ofstream file1;
    file1.open("user.txt", ios::app);
    libra_id = n;
    cout << "\nEnter The Name : ";
    getline(cin >> ws, name);
    cout << "\nEnter the Password : ";
    getline(cin >> ws, pass);
    file1 << userid << "|" << name << "|" << pass << "|" << libra_id << endl;
    file1.close();
    cout << "\nUser Information" << endl;
    cout << "\nLibrary Name : " << c << endl;
    cout << "Libraery ID : " << libra_id << endl;
    cout << "Name : " << name << endl;
    cout << "User ID : " << userid << endl;
  }

  void display_lib_id() {
    ifstream file;
    file.open("admin.txt");
    string a, b, c, d, e;
    cout << "\nCreate account in Library " << endl;
    while (getline(file, a, '|') && getline(file, b, '|') &&
           getline(file, c, '|') && getline(file, d, '|') && getline(file, e)) {
      cout << "\nLibrary Name : " << d << endl;
      cout << "Library ID : " << e << endl;
    }
    file.close();
  }
  string get_id(string lib) {
    ifstream file;
    file.open("admin.txt");
    string a, b, c, d, e;
    while (getline(file, a, '|') && getline(file, b, '|') &&
           getline(file, c, '|') && getline(file, d, '|') && getline(file, e)) {
      if (lib == e) {
        file.close();
        return d;
      }
    }
    file.close();
    return "Invalid ID";
  }
  string login_user() {
    string id, pass;
    cout << "\nEnter The User ID : ";
    getline(cin >> ws, id);
    cout << "\nEnter The Password : ";
    getline(cin >> ws, pass);
    ifstream file;
    file.open("user.txt", ios::in);
    string a, b, c, d;
    while (getline(file, a, '|') && getline(file, b, '|') &&
           getline(file, c, '|') && getline(file, d)) {
      if (id == a && pass == c) {
        userid = a;
        file.close();
        return d;
      }
    }
    file.close();
    return "Invalid User or Password";
  }

  string get_user_id() { return userid; }
};

class admin {
  string id;
  string pass;
  string name;
  string library_name;
  string code;
  string logged_library_id;
  string logged_admin_id;
  int a, b;

public:
  void register_admin() {
    ofstream file;
    file.open("admin.txt", ios::app);
    random_device r;
    cout << "\nEnter Library Name: ";
    getline(cin >> ws, library_name);
    cout << "\nEnter The Name : ";
    getline(cin >> ws, name);
    cout << "\nEnter the Password : ";
    getline(cin >> ws, pass);
    a = r() % 9000 + 1000;
    b = r() % 9000 + 1000;
    id = "ID" + to_string(a);
    code = "ID" + to_string(b);
    cout << "Admin ID : " << id << endl;
    cout << "Library ID : " << code << endl;
    file << name << "|" << pass << "|" << id << "|" << library_name << "|"
         << code << endl;
    file.close();
  }
  bool login_admin() {
    cout << "\nEnter the Admin ID : ";
    getline(cin >> ws, id);
    cout << "\nEnter the password : ";
    getline(cin >> ws, pass);
    ifstream file;
    file.open("admin.txt");
    string a, b, c, d, e;
    while (getline(file, a, '|') && getline(file, b, '|') &&
           getline(file, c, '|') && getline(file, d, '|') && getline(file, e)) {
      if (b == pass && c == id) {
        cout << "\n===Login Successfull===" << endl;
        cout << "Login Details" << endl;
        cout << "Library Name : " << d << endl;
        cout << "Library ID : " << e << endl;
        logged_library_id = e;
        logged_admin_id = c;
        file.close();
        return true;
      }
    }
    cout << "Invalid ID or Password" << endl;
    file.close();
    return false;
  }
  string get_library_id() { return logged_library_id; }

  string get_admin_id() { return logged_admin_id; }
};

int main() {
  restore book;
  int c, a, d;
  string l_id, a_id, id, s;
  string s_ti, s_id, p, q;
  do {
    cout << "1.Admin " << endl;
    cout << "2.User " << endl;
    cout << "3.Back" << endl;
    cout << "\nEnter the choice : ";
    cin >> c;
    switch (c) {
    case 1:
      do {
        cout << "\n1.New Admin (registration)";
        cout << "\n2.Login Admin ";
        cout << "\n3.Back ";
        cout << "\nEnter the choice : ";
        cin >> a;
        admin r;
        switch (a) {
        case 1: {
          r.register_admin();
        } break;
        case 2: {
          if (r.login_admin()) {
            l_id = r.get_library_id();
            a_id = r.get_admin_id();
            do {
              cout << "1.Add Book " << endl;
              cout << "2.Display Book " << endl;
              cout << "3.Log Out " << endl;
              cout << "Enter the choice : ";
              cin >> d;
              switch (d) {
              case 1: {
                node *newnode = new node;
                newnode->data.add_book(l_id);
                newnode->next = head;
                head = newnode;
              } break;
              case 2: {
                node *temp = head;
                if (temp == NULL) {
                  cout << "\nNo books available." << endl;
                }
                while (temp != NULL) {
                  if (temp->data.get_library_id() == l_id) {
                    temp->data.display_book();
                  }
                  temp = temp->next;
                }
              } break;
              case 3:
                break;
              default:
                cout << "\nInvalid Choice";
                break;
              }
            } while (d != 3);
          }
        } break;
        case 3:
          break;
        default:
          cout << "\nInvalid Choice" << endl;
        }
      } while (a != 3);
      break;
    case 2: {
      user r;
      do {
        cout << "\n1.New user (registration)";
        cout << "\n2.Login User";
        cout << "\n3.Search Book";
        cout << "\n4.Issue Book";
        cout << "\n5.Return Book";
        cout << "\n6.Log Out";
        cout << "\nEnter the choice : ";
        cin >> a;
        switch (a) {
        case 1: {
          r.display_lib_id();
          cout << "\nEnter the Library ID : ";
          getline(cin >> ws, id);
          a_id = r.get_id(id);
          if (a_id == "Invalid ID") {
            cout << "Invalid User ID or Password." << endl;
          } else {
            r.register_user(id, a_id);
          }
        } break;
        case 2:
          s = r.login_user();
          if (s == "Invalid User or Password") {
            cout << "Invalid User ID or Password." << endl;
          } else {
            cout << "\nLogin Successful!" << endl;

            node *temp = head;
            bool found = false;

            while (temp != NULL) {
              if (temp->data.get_library_id() == s) {
                temp->data.display_book();
                found = true;
              }
              temp = temp->next;
            }

            if (!found) {
              cout << "No books available in your library." << endl;
            }
          }
          break;
        case 3: {
          if (s == "" || s == "Invalid User or Password") {
            cout << "Please login first." << endl;
            break;
          }

          cout << "\nEnter Book ID (or -): ";
          getline(cin >> ws, s_id);

          cout << "Enter Book Title (or -): ";
          getline(cin >> ws, s_ti);

          node *temp = head;
          bool found = false;

          while (temp != NULL) {
            if (temp->data.get_library_id() == s &&
                temp->data.search_book(s_id == "-" ? "" : s_id,
                                       s_ti == "-" ? "" : s_ti)) {
              temp->data.display_book();
              found = true;
            }
            temp = temp->next;
          }

          if (!found)
            cout << "Book not found." << endl;

          break;
        }
        case 4: {
          if (s == "" || s == "Invalid User or Password") {
            cout << "Please login first." << endl;
            break;
          }
          cout << "\nEnter Book ID to issue: ";
          getline(cin >> ws, s_id);
          node *temp = head;
          bool found = false;
          while (temp != NULL) {
            if (temp->data.get_library_id() == s &&
                temp->data.get_book_id() == s_id) {
              found = true;
              if (temp->data.issue_book()) {
                record_issue(r.get_user_id(), s_id);
                save_books();
                cout << "\nBook issued successfully!" << endl;
                cout << "Remaining stock: ";
                temp->data.display_book();
              } else {
                cout << "\nBook is out of stock." << endl;
              }
              break;
            }
            temp = temp->next;
          }
          if (!found) {
            cout << "\nBook not found in your library." << endl;
          }
          break;
        }
        case 5: {
          if (s == "" || s == "Invalid User or Password") {
            cout << "Please login first." << endl;
            break;
          }

          cout << "\nEnter Book ID to return: ";
          getline(cin >> ws, s_id);

          node *temp = head;
          bool found = false;

          while (temp != NULL) {
            if (temp->data.get_library_id() == s &&
                temp->data.get_book_id() == s_id) {
              found = true;
              break;
            }

            temp = temp->next;
          }

          if (!found) {
            cout << "Book not found in your library." << endl;
            break;
          }

          if (remove_issue(r.get_user_id(), s_id)) {
            temp->data.return_book();
            save_books();

            cout << "\nBook returned successfully!" << endl;
            cout << "Updated stock: ";
            temp->data.display_book();
          } else {
            cout << "You have not issued this book." << endl;
          }

          break;
        }
        case 6:
          s = "";
          cout << "Logged out successfully." << endl;
          break;
        default:
          cout << "\nInvalid Choice" << endl;
        }
      } while (a != 6);
      break;
    }
    case 3:
      break;
    default:
      cout << "Invalid Choice " << endl;
      break;
    }
  } while (c != 3);
}