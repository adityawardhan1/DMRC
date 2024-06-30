
#include <bits/stdc++.h>
#include <fstream>

#define ll long long
#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

map<string, ll> M;
char color[200][200] = {'\0'};
string station[200];
map<string, string> tourm;

class comparedis {
  public:
    bool operator()(pair<ll, ll> &p, pair<ll, ll> &q) {
        return (p.se > q.se);
    }
};

vector<pair<ll, ll>> v[100010];
ll N;


void insertCardInfo(ll cid, ll amt) {
    ofstream fout;
    fout.open("paisa.txt", ios::app);
    if (!fout) {
        cout << "Error opening file.\n";
        return;
    }
    fout << cid << " " << amt << endl;
    fout.close();
}

void issueNewCard() {
    ofstream fout;
    fout.open("paisa.txt", ios::app);
    if (!fout) {
        cout << "Error opening file.\n";
        return;
    }

    ll cid, amount;
    cout << "Enter new card ID: ";
    cin >> cid;
    cout << "Enter initial amount for the new card: ";
    cin >> amount;

    fout << cid << " " << amount << endl;
    fout.close();

    cout << "New card issued successfully!\n";
}


void ascii_welcome() {
    cout << "=========================================" << endl;
    cout << "           Welcome to Metro Guide        " << endl;
    cout << "=========================================" << endl;
    cout << "  DDDD   M   M   RRRR    CCCCCCC         " << endl;
    cout << "  D   D  MM MM   R   R   C               " << endl;
    cout << "  D   D  M M M   RRRR    C              " << endl;
    cout << "  D   D  M   M   R  R    C               " << endl;
    cout << "  DDDD   M   M   R   R   CCCCCCC          " << endl;
    cout << "=========================================" << endl;
}

void ascii_card_recharge() {
    cout << "=========================================" << endl;
    cout << "          Smart Card Recharge            " << endl;
    cout << "=========================================" << endl;
}

void recharge() {
    fstream f;
    ll amt, ini, cid, fin, x;
    ll c_id, amount;
    f.open("paisa.txt", ios::in | ios::out);
    if (!f)
        cout << "File Not Found\n";
    f.seekg(0, ios::beg);
    cout << endl;
    ascii_card_recharge();
    cout << "Enter Card ID\n";
    cin >> c_id;
    cout << "Enter Amount to Recharge\n";
    cin >> amount;
    f.clear();

    bool found = false;
    while (f >> cid >> amt) {
        if (cid == c_id) {
            found = true;
            x = amt + amount;
            f.seekp(-1 * sizeof(long long), ios::cur);
            f << x;
            cout << "Recharge Successful!\n";
            cout << "\nCard ID: " << cid << endl;
            cout << "Initial Balance: " << amt << endl;
            cout << "Recharge Amount: " << amount << endl;
            cout << "Total Balance: " << x << endl;
            break;
        }
    }

    if (!found) {
        cout << "Card ID not found\n";
    }

    f.close();
}

void gettour() {
    ifstream fin;
    string s1, s2;
    fin.open("tourplace.txt", ios::in);
    if (!fin)
        cout << "File Not Found\n";
    fin.seekg(0);
    fin.clear();
    while (getline(fin, s1) && getline(fin, s2)) {
        tourm[s1] = s2;
    }
    fin.close();
}

void disp(ll src, ll dest, ll par[]) {
    stack<ll> st;
    st.push(dest);
    ll i = dest;
    while (par[i] != -1) {
        i = par[i];
        st.push(i);
    }

    char col = '\0';
    while (!st.empty()) {
        ll x = st.top();
        st.pop();
        cout << station[x];
        if (!st.empty()) {
            ll y = st.top();
            if (col == '\0') {
                col = color[x][y];
            } else if (col != color[x][y]) {
                cout << " - Change to ";
                switch (color[x][y]) {
                    case 'b':
                        cout << "blue line";
                        break;
                    case 'y':
                        cout << "yellow line";
                        break;
                    case 'o':
                        cout << "orange line";
                        break;
                    case 'g':
                        cout << "green line";
                        break;
                    case 'r':
                        cout << "red line";
                        break;
                    case 'v':
                        cout << "violet line";
                        break;
                    default:
                        cout << "unknown line";
                        break;
                }
                cout << endl;
                col = color[x][y];
            } else {
                cout << " -> ";
            }
        }
    }
    cout << endl;
}

void bfs(ll src, ll dest) {
    bool vis[100010] = {false};
    ll par[100010];
    for (ll i = 0; i < N; i++)
        par[i] = -1;

    queue<ll> q;
    q.push(src);
    vis[src] = true;

    while (!q.empty()) {
        ll x = q.front();
        q.pop();
        ll vsz = v[x].size();
        for (ll i = 0; i < vsz; i++) {
            ll y = v[x][i].fi;
            if (!vis[y]) {
                par[y] = x;
                vis[y] = true;
                q.push(y);
            }
        }
        v[x].clear();
    }

    disp(src, dest, par);
}

void dijkstra(ll src, ll dest) {
    bool vis[100010] = {false};
    ll dist[100010], par[100010];
    for (ll i = 0; i < N; i++) {
        dist[i] = LLONG_MAX;
        par[i] = -1;
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, comparedis> pq;
    pq.push(mp(src, 0));
    dist[src] = 0;
    vis[src] = true;

    while (!pq.empty()) {
        pair<ll, ll> k = pq.top();
        pq.pop();
        ll x = k.fi;
        ll vsz = v[x].size();
        for (ll i = 0; i < vsz; i++) {
            ll y = v[x][i].fi;
            ll w = v[x][i].se;
            if (dist[x] + w < dist[y]) {
                par[y] = x;
                dist[y] = dist[x] + w;
            }
            if (!vis[y]) {
                vis[y] = true;
                pq.push(mp(y, dist[y]));
            }
        }
        v[x].clear();
    }

    disp(src, dest, par);
}

void consmap() {
    ifstream fin;
    string s;
    fin.open("list.txt", ios::in);
    ll l = 0;
    fin.seekg(0);
    fin.clear();
    while (getline(fin, s)) {
        M[s] = l;
        station[l] = s;
        l++;
    }
    N = l - 1;
    fin.close();
}

void addedge(char fname[], ll w) {
    ifstream fin;
    string s;
    ll x, y;
    fin.open(fname, ios::in);
    fin.seekg(0);
    getline(fin, s);
    x = M[s];
    char c = fname[0];
    fin.clear();
    while (getline(fin, s)) {
        y = M[s];
        v[x].pb(mp(y, w));
        v[y].pb(mp(x, w));
        color[x][y] = c;
        color[y][x] = c;
        x = y;
    }
    fin.close();
}

/*void consgraph() {
    addedge("blueline.txt", 0);
    addedge("yellowline.txt", 0);
    addedge("redline.txt", 0);
    addedge("greenline.txt", 0);
    addedge("violetline.txt", 0);
    addedge("bluext.txt", 0);
    addedge("orangeline.txt", 1);
}*/

int main() {
    ascii_welcome();
    string source, destination;
    ll src, dest, choice, dec;
    char ch;

    gettour();
    consmap();

    do {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nMain Menu:\n";
        cout << "1. Route between two stations\n";
        cout << "2. Nearest metro station to a tourist place\n";
        cout << "3. Recharge your Smart Card\n";
        cout << "4. Issue New Smart Card\n";
        cin >> dec;

        switch (dec) {
            case 1:
                do {
                   // consgraph();
                    cout << "Enter the source station\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, source);
                    cout << "Enter the destination station\n";
                    getline(cin, destination);

                    if (M.find(source) == M.end() || M.find(destination) == M.end()) {
                        cout << "Invalid station names. Please try again.\n";
                        continue;
                    }

                    src = M[source];
                    dest = M[destination];

                    cout << "Select a path:\n";
                    cout << "1. Most economical path\n";
                    cout << "2. Shortest path\n";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            dijkstra(src, dest);
                            break;
                        case 2:
                            bfs(src, dest);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }

                    cout << "Do you wish to check for any other station (Y/N)?\n";
                    cin >> ch;
                } while (tolower(ch) == 'y');
                break;

            case 2:
                do {
                    string place;
                    cout << "Enter a tourist place\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, place); // Clear any buffer

                    if (tourm.find(place) == tourm.end()) {
                        cout << "Tourist place not found. Please try again.\n";
                        continue;
                    }

                    string nearest_station = tourm[place];
                    cout << "Nearest metro station: " << nearest_station << endl;

                    cout << "Do you wish to check for another place (Y/N)?\n";
                    cin >> ch;
                } while (tolower(ch) == 'y');
                break;

            case 3:
                do {
                    recharge();
                    cout << "Do you wish to recharge another smart card (Y/N)?\n";
                    cin >> ch;
                } while (tolower(ch) == 'y');
                break;

            case 4:
                issueNewCard();
                break;

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }

        cout << "Do you wish to go back to the main menu (Y/N)?\n";
        cin >> ch;
    } while (tolower(ch) == 'y');

    cout << "Thank you for using Metro Guide! Have a great day!\n";
    return 0;
}
