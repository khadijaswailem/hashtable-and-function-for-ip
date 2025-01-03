#include"AVLTree.hpp"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;


class myData {
private:
    string ip;
    string date;
    string time;
    string zone;
    string cik;
    string acc;
    string doc;
    string code;
    string filesize;
    string idx;
    string norefer;
    string noagent;
    string find;
    string crawler;
    string browser;
public:
    myData() {
        ip = " ";
        date = " ";
        time = " ";
        zone = " ";
        cik = " ";
        acc = " ";
        doc = " ";
        code = " ";
        filesize = " ";
        idx = " ";
        norefer = " ";
        noagent = " ";
        find = " ";
        crawler = " ";
        browser = " ";
    }
    void setip(string i) {
        ip = i;
    }
    void setdate(string d) {
        date = d;
    }
    void settime(string t) {
        time = t;
    }
    void setzone(string z) {
        zone = z;
    }
    void setcik(string c) {
        cik = c;
    }
    void setacc(string a) {
        acc = a;
    }
    void setdoc(string d) {
        doc = d;
    }
    void setcode(string c) {
        code = c;
    }
    void setfilesize(string f) {
        filesize = f;
    }
    void setidx(string i) {
        idx = i;
    }
    void setnorefer(string rf) {
        norefer = rf;
    }
    void setnoagent(string ag) {
        noagent = ag;
    }
    void setfind(string f) {
        find = f;
    }
    void setcrawler(string c) {
        crawler = c;
    }
    void setbrowser(string b) {
        browser = b;
    }
    string getip() {
        return ip;
    }
    string getdate() {
        return date;
    }
    string gettime() {
        return time;
    }
    string getzone() {
        return zone;
    }
    string getcik() {
        return cik;
    }
    string getacc() {
        return acc;
    }
    string getdoc() {
        return doc;
    }
    string getcode() {
        return code;
    }
    string getfilesize() {
        return filesize;
    }
    string getidx() {
        return idx;
    }
    string getnorefer() {
        return norefer;
    }
    string getnoagent() {
        return noagent;
    }
    string getfind() {
        return find;
    }
    string getcrawler() {
        return crawler;
    }
    string getbrowser() {
        return browser;
    }

    bool operator > (const myData& other) {
        if (this->date>other.date) {
            return true;
        }
        else if ((this->date == other.date) and (this->time>other.time)) {//added a new case just incase 
            return true;
        }
        return false;
    }
    
    
    bool operator <(const myData& other) {
        if (this->date< other.date)  {
            return true;
        }
        else if ((this->date == other.date) and (this->time < other.time)) {
            return true;
        }
        return false;
    }

    bool operator == (const myData& other) {//overloaded this for the rangesearch in the BST class
        if ((this->date, this->time) == (other.date, other.time)) {
            return true;
        }
        return false;
    }

    friend ostream& operator << (ostream& os, const myData& other) {
        os << other.ip<<" "<<other.date << " " << other.time;//to see the ip and date a time 
        return os;
    }
    ~myData() {};
};


//FUNCTION TO OPEN THE FILE 
void fileopener(string filename, myData arr[], string IP[]) {
    ifstream infile;
    try
    {
        infile.open(filename);//trying to open the file
        if (infile.fail()) {
            throw "file does not exist";//error message if file doesnt exist
        }
    }
    catch (const char* e)
    {
        cerr << e << endl;//displaying the error message 
    }
    string ip;
    string date;
    string time;
    string zone;
    string cik;
    string acc;
    string doc;
    string code;
    string filesize;
    string idx;
    string norefer;
    string noagent;
    string find;
    string crawler;
    string browser;


    int index = 0;
    
    while (getline(infile, ip)) {//looping while there are still values to obtain
        getline(infile, ip, ',');//setting the ip,date,time variables to those from the file
        getline(infile, date, ',');
        getline(infile, time, ',');
        getline(infile, zone, ',');
        getline(infile, cik, ',');
        getline(infile, acc, ',');
        getline(infile, doc, ',');
        getline(infile, code, ',');
        getline(infile, filesize, ',');
        getline(infile, idx, ',');
        getline(infile, norefer, ',');
        getline(infile, noagent, ',');
        getline(infile, find, ',');
        getline(infile, crawler, ',');
        getline(infile, browser, ',');

        myData d;//creating an object for each row from the adt i created 
        d.setip(ip);//setting the values
        d.setdate(date);
        d.settime(time);
        d.setzone(zone);
        d.setcik(cik);
        d.setacc(acc);
        d.setdoc(doc);
        d.setcode(code);
        d.setfilesize(filesize);
        d.setidx(idx);
        d.setnorefer(norefer);
        d.setnoagent(noagent);
        d.setfind(find);
        d.setcrawler(crawler);
        d.setbrowser(browser);


        if (index == 1000) {//only reading 1000 for testing 
            break;
        }
        arr[index] = d;//we put every object created into an array 
        IP[index] = ip;//putting the IP only in an array 
        index++;

       /* cout << "ip: " << ip << endl;
        cout << "date: " << date << endl;
        cout << "time: " << time << endl;*/
        //cout << "zone: " << zone << endl;
        //cout << "filesize: " << filesize << endl;
    }
    infile.close();//closing the file


}

//THE HASH FUNCTION 
unsigned int hash1(const string& key, int tableSize) {
    unsigned int hashVal = 0;
    for (char ch : key) hashVal = 37 * hashVal + ch;//chose 37 after testing with other prime constants
    return hashVal % tableSize;//to make sure hashval would be within table size bounds
}

//PUT THIS HERE SO IT CAN BE SEEN EVERYWHERE 
AVLTree<myData>* hashtable[31];//initialzing an array for the hashtable of prime size 31

//FUNCTION TO SEARCH FOR A SPECIFIC IP ADDRESS WITHIN RANGE OF DATE AND TIME
AVLNode<myData>* IPsearch(string lowdate, string lowtime, string highdate, string hightime, string key) {
    
    int hashval = hash1(key, 31);//calculating the hashvalue
    AVLNode<myData>* n = hashtable[hashval]->getRoot();//getting root of the tree
    if (hashtable[hashval]->contains(n->getItem()) == false) {//checking if ip exists or not in tree at specific hash index
        return NULL;
    }
    return hashtable[hashval]->rangeSearch(lowdate, lowtime, highdate, hightime, key,n);//calling the search with the tree at the index of teh hashvalue
    
}



int main() {
    //CHECKING THAT THE ARRAY IDEA TO STORE THE OBJECT WORKS
 /*   for (int i = 0;i < 1000;i++) {
        cout << "WE ARE AT INDEX: " << i << endl;
        cout << fileopener("log20170630.csv") << endl;

    }*/


    //array that stores the ip addresses 
    string IP[1000];//made it 1000 just for testing

    //array that stores the weblogs
    myData arr[1000];

    //arrays passed by reference and filled inside the function 
    fileopener("log20170630.csv", arr,IP);

    //initializing the array pointers 
    for (int i = 0;i < 31;i++) {
        hashtable[i] = NULL;
    }

    int hashval;
    for (int i = 0;i < 1000;i++) {//1000 just for testing (when running the whole file would loop on the number of rows in the file by previously counting in the while loop of reading file contents
        hashval = hash1(IP[i], 31);//calculating the hashvalue of the ip by reading it from the IP array
        if (hashtable[hashval] == NULL) {//if index is still empty then we will create a tree and insert in it
            hashtable[hashval] = new AVLTree<myData> ;
            //here and in the else tried to create an object from mydata but couldnt set it values so 
            //adjusted the read file function to return the object it just created 
            hashtable[hashval]->insert(arr[i]);//inserting the object by the index of the array taht stores the objects 
        }
        else {//if index already has a tree created we will just create an object and insert it 
            hashtable[hashval]->insert(arr[i]);//inserting at the tree in that index directly if tree exists
        }
    }
    
    //TESTING THE IP SEARCH
    cout << "Key found at memory address: " << IPsearch("2017-06-03", "00:00:00", "2017-06-30", "00:00:03", "107.23.85.jfd")<<endl; 
   

    //TRYING TO TEST IF IP ISNT IN THE TREE CASE 
    cout << "Key not found. " << IPsearch("2017-06-30", "00:00:00", "2017-06-30", "00:00:03", "107.23.85.jfx")<<endl;
   

    //displaying hashtable
    cout << "HASH TABLE CONTENTS:" << endl;
    for (int i = 0;i < 31;i++) {
        if (hashtable[i] == NULL) {
            cout << "No tree at index: " << i << endl;//error message 
            continue;//just incase a hash index didnt have a tree in it because no ip got hashed to it
            //should continue normally/skip this iteration 
        }
        cout << "HASH INDEX: " << i << endl;
        hashtable[i]->traverse(hashtable[i]->getRoot());//passed the root of the tree at the specific hash index were at so that the function doesnt set the default value to n and then return NULL 
    }

   
}


