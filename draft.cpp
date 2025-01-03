//#include<iostream>
//#include<string>
//#include"AVLTree.hpp"
//using namespace std;
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
//        if ((this->date,this->time) > (other.date,other.time)) {
//            true;
//        }
//        return false;
//    }
//
//    bool operator <(const myData& other) {
//        if ((this->date,this->time) < (other.date,other.time)) {
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
//unsigned int hash1(const string& key, int tableSize) {
//	unsigned int hashVal = 0;
//	for (char ch : key) hashVal = 37 * hashVal + ch;
//	return hashVal % tableSize;
//}
//
//int main() {
//    AVLTree<myData>* hashtable[20]; //= (AVLTree<myData>*)calloc(20, sizeof(AVLTree<myData>));
//
//    for (int i = 0;i < 20;i++) {
//        hashtable[i] = new AVLTree<myData>;
//    }
//
//    
//    for (int i = 0;i < 20;i++) {
//        if (hashtable[i] == NULL) {//if index is still empty then we wilk create a tree and insert in it
//            AVLTree<myData> t;
//            myData d;//creating an object for each row from the adt i created 
//            //        d.setip(ip);//setting the values
//            //        d.setdate(date);
//            //        d.settime(time);
//            //        d.setzone(zone);
//            //        d.setcik(cik);
//            //        d.setacc(acc);
//            //        d.setdoc(doc);
//            //        d.setcode(code);
//            //        d.setfilesize(filesize);
//            //        d.setidx(idx);
//            //        d.setnorefer(norefer);
//            //        d.setnoagent(noagent);
//            //        d.setfind(find);
//            //        d.setcrawler(crawler);
//            //        d.setbrowser(browser);
//            t.insert(d);
//        }
//        else {//if index already has a tree created we will just create an object and insert 
//            myData d;//creating an object for each row from the adt i created 
//            //        d.setip(ip);//setting the values
//            //        d.setdate(date);
//            //        d.settime(time);
//            //        d.setzone(zone);
//            //        d.setcik(cik);
//            //        d.setacc(acc);
//            //        d.setdoc(doc);
//            //        d.setcode(code);
//            //        d.setfilesize(filesize);
//            //        d.setidx(idx);
//            //        d.setnorefer(norefer);
//            //        d.setnoagent(noagent);
//            //        d.setfind(find);
//            //        d.setcrawler(crawler);
//            //        d.setbrowser(browser);
//            hashtable[i]->insert(d);
//        }
//    }
//	//TESTING THE HASH FUNCTION
//	string word;
//	string hashtable[20];
//	int hashval;
//	for (int i = 0;i < 4;i++) {
//		cout << "enter word:" << endl;
//		cin >> word;
//		hashval = hash1(word, 20);
//		hashtable[hashval] = word;
//	}
//	cout << "HASH TABLE CONTENTS:" << endl;
//	for (int i = 0;i < 20;i++) {
//		cout << hashtable[i] << endl;
//	}
//
//	//DRAFT OF LOGIC 
//	//inside loop of reading the file call the hash function for the ip
//	// address if not already hashed in the table then create an AVL tree for this index and start
//	// creating objects and inserting them into this tree
//	//if tree already exists for this index just create the object and insert it into the tree
//	//by date and time which are already implemented in the overloaded operator of the class 
//	//of the data we insert into the AVLtree from the previous assignment 
//	// 
//	// NOT SURE OF THE REHASHING PART
//    //also we wanna calculate the load factor so we will create a counter for each new index ip is inserted 
//	//into and calculate the lamda each time by lamda=counter/tablesize and check if the load factor
//	//exceeded a specific threshold or not if yes then we must rehash by expanding table size 
//	//by double or more (next prime number) and use a new hashfunction to rehash all indexes 
//
//}
