#include<iostream>
#include<cstdlib>
#include<string>
#include<Windows.h>
#include<time.h>

using namespace std;

/*
DAFTAR NAMA ANGGOTA:
ALBERTUS HERONIUS / 2101690042
CHRISTIAN WINATA / 2101707642
DAVID LIOIS / 2101628096
MILLINOV ADMIRAL / 2101675804
*/

/*
idenya yaitu; dengan menggunakan linked list dan class, 
saya membuat dua kumpulan data (book) yang berisikan data inisiasi random yang sama, 
kemudian di dalam menu akan diberikan 2 pilihan (search dengan BST atau sequence search), 
setiap search selesai, akan ditampilkan durasi search masing masing
*/

//using BST
//untuk yang BST, saya menggunakan class
class Book
{
private:
 struct book
 {
  book* left;
  book* right;
  int id;
  string name;
 };
 book* root;
public:
 Book()
 {
  root = NULL;
 }
 bool isEmpty() const { return root==NULL; }
 void print_inorder();
 void inorder(book*);
 void insert(int id, string name);
 bool search(int id);
};

//function untuk tambah buku (BST)
void Book::insert(int idTemp, string nameTemp)
{
 book* b = new book;
 book* parent;
 b->id = idTemp;
 b->name = nameTemp;
 b->left = NULL;
 b->right = NULL;
 parent = NULL;
 if(isEmpty()) root = b;
 else
 {
  book* curr;
  curr = root;
  while(curr)
  {
   parent = curr;
   if(b->id > curr->id) curr = curr->right;
   else curr = curr->left;
  }

  if(b->id < parent->id)
   parent->left = b;
  else
   parent->right = b;
 }
}

//function untuk search buku (BST)
bool Book::search(int idTemp)
{
 bool found = false;
 if(isEmpty())
 {
  cout<<" No Book! "<<endl;
  return false;
 }
 book* curr;
 book* parent;
 curr = root;
 parent = (book*)NULL;
 while(curr != NULL)
 {
  if(curr->id == idTemp)
  {
   found = true;
   break;
  }
  else
  {
   parent = curr;
   if(idTemp>curr->id) curr = curr->right;
   else curr = curr->left;
  }
 }

 if(!found)
 {
  cout<<" Book not found! "<<endl;
 }
 else
 {
  cout<<" Book found! "<<endl;
 }

 return found;
}

//function untuk view daftar buku (BST)
void Book::print_inorder()
{
 inorder(root);
}

//view daftar buku (BST)
void Book::inorder(book* p)
{
 if(p != NULL)
 {
  if(p->left) inorder(p->left);
   cout<<p->id<<" "<<p->name<<endl;
  if(p->right) inorder(p->right);
 }
 else return;
}

//using linked list
//dibuat struct baru (clone) untuk linked list
struct book2{
 int id2;
 char name2[100];
 book2* next;
 book2* prev;
}*curr, *head, *tail = NULL;

//tambah buku dalam linked list
void pushBook2(int id2, char name2[]){
 curr = (struct book2*) malloc (sizeof(book2));
 curr->id2 = id2;
 strcpy(curr->name2,name2);

 if(head == NULL){
  head = curr;
  tail = curr;
  curr->next = curr->prev = NULL;
 }

 else{
  tail->next = curr;
  curr->prev = tail;
  tail = curr;
  tail->next = NULL;
 }
}

//view book dalam linked list
void viewBook2(){
 curr = head;
 while(curr!=NULL){
  printf("%d %s \n", curr->id2, curr->name2);
  curr = curr->next;
 }
}

//search book dalam linked list
void searchBook2(int searchTemp2){
 curr = head;
 int ctr = 0;

 if(curr == NULL){
  printf("No book");
 }
 else{

  while(curr!=NULL){
   if(curr->id2 == searchTemp2){
    ctr=1;
    printf("Book found");
    break;
   }
   else{
    curr=curr->next;
   }
  }

  if(ctr==0){
   printf("Book not found");
  }

 }

}

int main()
{
 Book b;
 int ch;
 int tmp,tmp1;
 string temp;

 int arr[1000];

 srand(time(NULL));

 //langkah di bawah dilakukan untuk mendapatkan data awal (book ID) yang random, dipilih angka 1 sampai 1000

 //inisiasi untuk arr[i] yang berisi angka 1 sampai 1000
 for(int i=0;i<1000;i++){
  arr[i] = i+1;
 }

 //angka yang ada di dalam arr[i] akan di acak-acak (ditukar-tukar)
 for(int i = 0;i<1000;i++){
  int temp = arr[i];
  int ranIdx = rand()%1000;
  arr[i] = arr[ranIdx];
  arr[ranIdx] = temp;
 }
 //dengan cara ini, tidak akan ada nilai yang sama (tiap arr[i] memiliki nilai yang unik) dan teracak

 //insert angka random yang ada di dalam array ke dalam tree dan linked list

 for(int i=0;i<1000;i++){
  b.insert(arr[i], "a");
  pushBook2(arr[i], "a");
  //"a" hanyalah nama book yang seharusnya tidak ada hubungan dengan tree yang terbentuk, 
 //karena tree untuk buku dibuat berdasarkan ID nya
 }

  //inisiasi data type untuk menghitung waktu
  LARGE_INTEGER frequency, frequency2; 
  LARGE_INTEGER t1, t2, t3, t4; 
  double elapsedTime, elapsedTime2;

 do
 {
  //menu
  cout<<endl<<endl;
  cout<<"           Operations          "<<endl;
  cout<<" ----------------------------- "<<endl;
  cout<<" 1. Insert Book "<<endl;
  cout<<" 2. View Book List "<<endl;
  cout<<" 3. Search "<<endl;
  cout<<" 4. Search linked list"<<endl;
  cout<<" 5. Exit "<<endl;
  cout<<" Enter your choice : ";
  cin>>ch;
  switch(ch)
  {
   case 1 : 
    cout<<" Enter book ID to be inserted : ";
    cin>>tmp;
    cin.clear(); cin.sync();

    cout<<" Enter book name to be inserted :";
    getline(cin, temp);
    cin.clear(); cin.sync();

    char temp2[100];
    strcpy(temp2, temp.c_str());

    b.insert(tmp, temp);
    pushBook2(tmp, temp2);

    break;

   case 2 : 
    cout<<endl;
    cout<<"VIEW LIST:"<<endl<<endl;
    cout<<" Binary Search Tree "<<endl;
    cout<<"--------------------"<<endl;

    b.print_inorder();

    cout<<endl<<endl;
    cout<<"     Linked-List "<<endl;
    cout<<"--------------------"<<endl<<endl;

    viewBook2();

    break;
   
   case 3:
    cout<<" Enter book ID to be searched : ";

    cin>>tmp;
    cin.clear(); cin.sync();
	
	//mulai record waktu BST-nya
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t1);

    cout<<" Using BST:"<<endl;

	//memanggil function search buku yang ada di tree 
    b.search(tmp);

    cout<<endl;

	//record waktu BST selesai
    QueryPerformanceCounter(&t2);

	//durasi Binary search didapat dari waktu selesai dikurang waktu awal (mulai)
    elapsedTime = (float) (t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
    cout<<elapsedTime
     <<" sec"<<endl;
	//menampilkan hasil dalam milisecond (0,00... sec)

    cout<<endl<<endl;
   
    break;

   case 4:
    cout<<" Enter book ID to be searched : ";

    cin>>tmp;
    cin.clear(); cin.sync();

    cout<<"------------------------"<<endl<<endl;

	//mulai record waktunya search linked list (sequence search)
    QueryPerformanceFrequency(&frequency2);
    QueryPerformanceCounter(&t3);

    cout<<" Using Sequential Search Linked List:"<<endl;
    
	//memanggil function search buku yang ada di linked-list
    searchBook2(tmp);

    cout<<endl;

	//record waktu sequence search selesai
    QueryPerformanceCounter(&t4);

	//durasi sequence search didapat dari waktu selesai dikurang waktu awal (mulai)
    elapsedTime2 = (float)(t4.QuadPart - t3.QuadPart) / frequency2.QuadPart;
    cout<<elapsedTime2
     <<" sec"<<endl;
	//menampilkan hasil dalam milisecond (0,00... sec)

    cout<<endl<<endl;
   
    break;

   }
 }while(ch!=5);

 cin.get();
 return 0;
}

//2101690042

/* 
NOTE:
Hasil waktu yang di-search menggunakan BST dan Sequence Search Linked List selalu berbeda-beda,
dan sering kali Sequence Search Linked List lebih cepat (mungkin karena datanya yang masih sedikit) dari pada BST,
sehingga masih diperlukan perbaikan di dalam cara menghitung durasi waktunya ataupun menginisiasi data awalnya. 
Terima kasih. 
*/