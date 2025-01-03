//#include"AVLTree.hpp"
//#include<iostream>
//#include<fstream>
//#include<string>
//using namespace std;
//
//
//class myData {
//private:
//    string ip;
//    string date;
//    string time;
//    string zone;
//    string cik;
//    string acc;
//    string doc;
//    string code;
//    string filesize;
//    string idx;
//    string norefer;
//    string noagent;
//    string find;
//    string crawler;
//    string browser;
//public:
//    myData() {
//        ip = " ";
//        date = " ";
//        time = " ";
//        zone = " ";
//        cik = " ";
//        acc = " ";
//        doc = " ";
//        code = " ";
//        filesize = " ";
//        idx = " ";
//        norefer = " ";
//        noagent = " ";
//        find = " ";
//        crawler = " ";
//        browser = " ";
//    }
//    void setip(string i) {
//        ip = i;
//    }
//    void setdate(string d) {
//        date = d;
//    }
//    void settime(string t) {
//        time = t;
//    }
//    void setzone(string z) {
//        zone = z;
//    }
//    void setcik(string c) {
//        cik = c;
//    }
//    void setacc(string a) {
//        acc = a;
//    }
//    void setdoc(string d) {
//        doc = d;
//    }
//    void setcode(string c) {
//        code = c;
//    }
//    void setfilesize(string f) {
//        filesize = f;
//    }
//    void setidx(string i) {
//        idx = i;
//    }
//    void setnorefer(string rf) {
//        norefer = rf;
//    }
//    void setnoagent(string ag) {
//        noagent = ag;
//    }
//    void setfind(string f) {
//        find = f;
//    }
//    void setcrawler(string c) {
//        crawler = c;
//    }
//    void setbrowser(string b) {
//        browser = b;
//    }
//    string getip() {
//        return ip;
//    }
//    string getdate() {
//        return date;
//    }
//    string gettime() {
//        return time;
//    }
//    string getzone() {
//        return zone;
//    }
//    string getcik() {
//        return cik;
//    }
//    string getacc() {
//        return acc;
//    }
//    string getdoc() {
//        return doc;
//    }
//    string getcode() {
//        return code;
//    }
//    string getfilesize() {
//        return filesize;
//    }
//    string getidx() {
//        return idx;
//    }
//    string getnorefer() {
//        return norefer;
//    }
//    string getnoagent() {
//        return noagent;
//    }
//    string getfind() {
//        return find;
//    }
//    string getcrawler() {
//        return crawler;
//    }
//    string getbrowser() {
//        return browser;
//    }
//
//    bool operator > (const myData& other) {
//        if ((this->date, this->time) > (other.date, other.time)) {
//            true;
//        }
//        return false;
//    }
//
//    bool operator <(const myData& other) {
//        if ((this->date, this->time) < (other.date, other.time)) {
//            return true;
//        }
//        return false;
//    }
//    friend ostream& operator << (ostream& os, const myData& other) {
//        os << other.ip;
//        return os;
//    }
//    ~myData() {};
//};
//
////EXTERNAL INDEX
//int EXTindex = -1;//started from -1 bcs we will increment the index first so we want it to start from zero
//
////FUNCTION TO OPEN THE FILE 
//myData fileopener(string filename) {
//    myData arr[1000];
//    ifstream infile;
//    try
//    {
//        infile.open(filename);//trying to open the file
//        if (infile.fail()) {
//            throw "file does not exist";//error message if file doesnt exist
//        }
//    }
//    catch (const char* e)
//    {
//        cerr << e << endl;//displaying the error message 
//    }
//    string ip;
//    string date;
//    string time;
//    string zone;
//    string cik;
//    string acc;
//    string doc;
//    string code;
//    string filesize;
//    string idx;
//    string norefer;
//    string noagent;
//    string find;
//    string crawler;
//    string browser;
//
//
//    int index = 0;
//    while (getline(infile, ip)) {//looping while there are still values to obtain
//        getline(infile, ip, ',');//setting the ip,date,time variables to those from the file
//        getline(infile, date, ',');
//        getline(infile, time, ',');
//        getline(infile, zone, ',');
//        getline(infile, cik, ',');
//        getline(infile, acc, ',');
//        getline(infile, doc, ',');
//        getline(infile, code, ',');
//        getline(infile, filesize, ',');
//        getline(infile, idx, ',');
//        getline(infile, norefer, ',');
//        getline(infile, noagent, ',');
//        getline(infile, find, ',');
//        getline(infile, crawler, ',');
//        getline(infile, browser, ',');
//
//        myData d;//creating an object for each row from the adt i created 
//        d.setip(ip);//setting the values
//        d.setdate(date);
//        d.settime(time);
//        d.setzone(zone);
//        d.setcik(cik);
//        d.setacc(acc);
//        d.setdoc(doc);
//        d.setcode(code);
//        d.setfilesize(filesize);
//        d.setidx(idx);
//        d.setnorefer(norefer);
//        d.setnoagent(noagent);
//        d.setfind(find);
//        d.setcrawler(crawler);
//        d.setbrowser(browser);
//
//
//        if (index == 1000) {
//            break;
//        }
//        arr[index] = d;//we put every object created into an array 
//        index++;
//
//
//        //cout << "ip: " << ip << endl;
//        //cout << "date: " << date << endl;
//        //cout << "time: " << time << endl;
//        //cout << "zone: " << zone << endl;
//        //cout << "filesize: " << filesize << endl;
//    }
//    infile.close();//closing the file
//
//    //reading the element from the array one by one 
//    EXTindex++;
//    return arr[EXTindex];
//
//
//
//}
//
////THE HASH FUNCTION 
//unsigned int hash1(const string& key, int tableSize) {
//    unsigned int hashVal = 0;
//    for (char ch : key) hashVal = 37 * hashVal + ch;
//    return hashVal % tableSize;
//}
//
////FUNCTION TO READ IPs ONLY
//
//int EXTindex2 = -1;
//string readIP(string filename) {
//    string IP[1000];//made it 1000 just for testing
//    ifstream infile;
//    try
//    {
//        infile.open(filename);//trying to open the file
//        if (infile.fail()) {
//            throw "file does not exist";//error message if file doesnt exist
//        }
//    }
//    catch (const char* e)
//    {
//        cerr << e << endl;//displaying the error message 
//    }
//    string ip;
//    int index = 0;
//    while (getline(infile, ip)) {//looping while there are still values to obtain
//        getline(infile, ip, ',');//setting the ip,date,time variables to those from the file
//
//        if (index == 1000) {
//            break;
//        }
//        IP[index] = ip;
//        index++;
//    }
//    infile.close();//closing the file
//
//    //reading the element from the array one by one 
//    EXTindex2++;
//    return IP[EXTindex2];
//}
//
//int main() {
//    //CHECKING THAT THE ARRAY IDEA TO STORE THE OBJECT WORKS
// /*   for (int i = 0;i < 1000;i++) {
//        cout << "WE ARE AT INDEX: " << i << endl;
//        cout << fileopener("log20170630.csv") << endl;
//
//    }*/
//
//    AVLTree<myData>* hashtable[31]; 
//
//    //initializing the array pointers 
//    for (int i = 0;i < 31;i++) {
//        hashtable[i] = new AVLTree<myData>;
//    }
//
//    int hashval;
//    hashval = hash1(readIP("log20170630.csv"), 31);//calculating the hashvalue of the ip
//    if (hashtable[hashval] == NULL) {//if index is still empty then we wilk create a tree and insert in it
//        AVLTree<myData> t;
//        //here and in the else tried to create an object from mydata but couldnt set it values so 
//        //adjusted the read file function to return the object it just created 
//        t.insert(fileopener("log20170630.csv"));//inserting the object by calling the function that returns object it just inserted
//    }
//    else {//if index already has a tree created we will just create an object and insert it 
//        hashtable[hashval]->insert(fileopener("log20170630.csv"));//inserting at the tree in that index directly if tree exists
//    }
//
//    //displaying hashtable
//    cout << "HASH TABLE CONTENTS:" << endl;
//    for (int i = 0;i < 31;i++) {
//        cout << "HASH INDEX: " << i << endl;
//        hashtable[i]->traverse();
//    }
//}
//
//
