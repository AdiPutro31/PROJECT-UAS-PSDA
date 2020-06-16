#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef struct Node
{
    int data;
    Node *kiri;
    Node *kanan;
};

Node *pohon = NULL;
//FUNGSI TAMBAH BILANGAN
void tambah (Node **root, int databaru)
{
       
    if ((*root)==NULL)
       {
        Node *baru;
        baru = new Node;
        baru->data=databaru;
        baru->kiri=NULL;
        baru->kanan=NULL;
        (*root) = baru;
        (*root) -> kiri = NULL;
        (*root) -> kanan = NULL;
        printf("DATA BERTAMBAH");
       }
    else if (databaru<(*root)->data)
              tambah(&(*root)->kiri,databaru);
    else if (databaru>(*root)->data)
        tambah(&(*root)->kanan,databaru);
    else if (databaru==(*root)->data)
        printf("DATA SUDAH ADA");
}

//FUNGSI TAMPIL PRE-ORDER
void preOrder(Node *root)
{
    if(root!=NULL)
    {
        if(root->data!=NULL)
        {
            printf("%d ",root->data);
        }
        preOrder(root->kiri);
        preOrder(root->kanan);
    }
}

//FUNGSI TAMPIL IN-ORDER
void inOrder(Node *root)
{
       if(root!=NULL)
       {
           inOrder(root->kiri);
           if(root->data!=NULL)
           {
               printf("%d ",root->data);
           }
           inOrder(root->kanan);
        }
}

//FUNGSI TAMPIL POST-ORDER
void postOrder(Node *root)
{
       if(root!=NULL)
       {
         postOrder(root->kiri);
         postOrder(root->kanan);
         if(root->data!=NULL)
         {
            printf("%d ",root->data);
         }
       }
}

//FUNGSI CARI BILANGAN
void search(Node **root, int cari)
{
    if((*root) == NULL)
    {
        printf("TIDAK DITEMUKAN");
    }
    else if(cari < (*root)->data)
        search(&(*root)->kiri,cari);
    else if(cari > (*root)->data)
        search(&(*root)->kanan,cari);
    else if(cari == (*root)->data)
        printf("DITEMUKAN");
}

//FUNGSI CARI KEDALAMAN
int height(Node *root)
{
       if(root == NULL)
              return -1;
       else{
              int u = height(root->kiri);
        int v = height(root->kanan);
        if(u > v)
          return u + 1;
        else
          return v + 1;
       }
}


//FUNGSI HAPUS BILANGAN
void hapus(Node **root, int del)
{
       Node *curr;
       Node *parent;
       Node *temp;
       curr = (*root);

       bool flag = false;
  
       while(curr != NULL)
       {
              if(curr->data == del)
              {
                     flag = true;
                     //cout<<"DITEMUKAN";
                      break;
              }
              else
              {
                  parent = curr;
                  if(del>curr->data)
                     curr = curr->kanan;
                  else
                     curr = curr->kiri;
              }
       }

    if(!flag)
    {
        cout<<"TIDAK DITEMUKAN. PENGHAPUSAN BATAL"<<endl;
        return;
    }

       if(height(pohon) == 0)
       {
              if( curr->kiri== NULL && curr->kanan == NULL)
              {
                     (*root) = NULL;
                    
                     return;
              }
       }
       else if(height(pohon) > 0)
       {
              if( curr->kiri== NULL && curr->kanan == NULL)
              {
                     if(parent->kiri == curr)
                     {
                           parent->kiri = NULL;
                           delete curr;
                     }
                     else 
                     {
                           parent->kanan = NULL;
                           delete curr;
                     }

                     return;
              }

              if((curr->kiri == NULL && curr->kanan != NULL)|| (curr->kiri != NULL && curr->kanan == NULL))
              {
                     if(curr->kiri == NULL && curr->kanan != NULL)
                     {
                           if(parent->kiri == curr)
                           {
                              parent->kiri = curr->kanan;
                              delete curr;
                              curr=NULL;
                         }
                         else if(parent->kanan == curr)
                         {
                              parent->kanan = curr->kanan; 
                              delete curr;
                              curr=NULL;
                         }else
						 {
							  temp=*root;						 	
                         	  (*root)=(*root)->kanan;
                         	  delete temp;
                         	  temp=NULL;

						 }
                     }
                  else 
                  {
                           if(parent->kiri == curr)
                           {
                                  parent->kiri = curr->kiri; 
                                  delete curr;
                                  curr=NULL;
                           }
                           else if(parent->kanan == curr) 
                           {
                               parent->kanan = curr->kiri; 
                               delete curr;
                               curr=NULL;
                            }else{
							  temp=*root;						 	
                         	  (*root)=(*root)->kiri;
                         	  delete temp;
                         	  temp=NULL;                         	
							}
                   }
                   return;
              }


              
              if (curr->kiri != NULL && curr->kanan != NULL)
              {
                     Node* bantu;
                     bantu = curr->kanan;

                     if((bantu->kiri == NULL) && (bantu->kanan == NULL))
                     {
                           
                           curr = bantu;
                           delete bantu;
                           curr->kanan = NULL;
                     }
                     else 
                     {
                        
                           if(curr->kanan->kiri != NULL)
                           {
                                  
                                  Node* bantu2;
                                  Node* bantu3; 
                                  bantu3 = curr->kanan;         
                                  bantu2 = curr->kanan->kiri; 
                                  while(bantu2->kiri != NULL)
                                  {
                                         bantu3 = bantu2;
                                         bantu2 = bantu2->kiri;
                                  }
                                  curr->data = bantu2->data;
                                  delete bantu2;
                                  bantu3->kiri = NULL;
                        }
                        else 
                        {
                              Node* tmp;
                              tmp = curr->kanan;
                              curr->data = tmp->data;
                              curr->kanan = tmp->kanan;
                              delete tmp;
                              tmp=NULL;
                        }

                     }
                     return;
              }
       }
}

int findMax()
{
		Node* curr = pohon;
		while(curr->kanan!=NULL)
		{
				curr=curr->kanan;
		}
		return curr->data;
}

int findMin()
{
		Node* curr = pohon;
		while(curr->kiri!=NULL)
		{
				curr=curr->kiri;
		}
		return curr->data;
}

//FUNGSI MAIN
int main()
{
    char pil;
    int del,cari;
    while (true)
    {
        system("cls"); 
        int data;
        printf("\t#PROGRAM BINARY SEARCH TREE PADA C++#");
        printf("\n\t=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=");
        printf("\nPILIHAN");
        printf("\n=+=+=+=\n");
        printf("[1] INSERT BILANGAN BARU\n");
        printf("[2] TAMPIL PRE-ORDER\n");
        printf("[3] TAMPIL IN-ORDER\n");
        printf("[4] TAMPIL POST-ORDER\n");
        printf("[5] HAPUS BILANGAN\n");
        printf("[6] RESET BILANGAN\n");
        printf("[7] CARI BILANGAN\n");
        printf("[8] CARI BILANGAN TERBESAR\n");
        printf("[9] CARI BILANGAN TERKECIL\n");
        printf("[X] KELUAR\n");
        printf("TENTUKAN PILIHAN : ");
        scanf("%c",&pil);
        fflush(stdin); 
        switch(pil)
        {
            //PILIHAN '1'
            case '1':
                     printf("\nINPUT : ");
                     printf("\n-------");
                     printf("\nMASUKKAN BILANGAN: ");
                     scanf("%d", &data);
                     tambah(&pohon,data);
                     _getch();
                      break;

             //PILIHAN '2'
              case '2':
                     printf("\nOUTPUT PRE ORDER : ");
                     printf("\n------------------\n");
                     if(pohon!=NULL)
                           preOrder(pohon);
                     else
                           printf("BELUM ADA BILANGAN");
                    
                     _getch();
                     break;
                    
              //PILIHAN '3'
              case '3':
                     printf("\nOUTPUT IN ORDER : ");
                     printf("\n------------------\n");
                     if(pohon!=NULL)
                           inOrder(pohon);
                     else
                           printf("BELUM ADA BILANGAN");
                    
                     _getch();
                     break;

             //PILIHAN '4'
              case '4':
                     printf("\nOUTPUT POST ORDER : ");
                     printf("\n------------------\n");
                     if(pohon!=NULL)
                           postOrder(pohon);
                     else
                           printf("BELUM ADA BILANGAN");

                     _getch();
                     break;
                  
              //PILIHAN '5'
              case '5':
                     if(pohon!=NULL)
                     {
                           printf("\nSEBELUM NODE DIHAPUS : ");
                           printf("\n---------------------- ");
                           printf("\nPRE ORDER  : ");
                           preOrder(pohon); //panggil fungsi
                           printf("\nIN ORDER   : ");
                           inOrder(pohon); //panggil fungsi
                           printf("\nPOST ORDER : ");
                           postOrder(pohon); //panggil fungsi
                           printf("\n\nPENGHAPUSAN DATA : ");
                           printf("\n------------------\n");
                           printf("MASUKKAN BILANGAN YANG AKAN DIHAPUS: ");
                           scanf("%d", &del);
                        
                           hapus(&pohon, del);
                           printf("\n\nSETELAH NODE DIHAPUS : ");
                           printf("\n---------------------- ");
                           printf("\nPRE ORDER  : ");
                           preOrder(pohon); //panggil fungsi
                           printf("\nIN ORDER   : ");
                           inOrder(pohon); //panggil fungsi
                           printf("\nPOST ORDER : ");
                           postOrder(pohon); //panggil fungsi
                     }
                     else
                           printf("\nBELUM ADA BILANGAN");

                     _getch();
                     break;

             //PILIHAN '6'
              case '6':
                     pohon=NULL;
                     printf("\nPENGOSONGAN ELEMEN ");
                     printf("\n------------------");
                     printf("\nBILANGAN SUDAH DIRESET");
                      
                     _getch();
                     break;

              //PILIHAN '7'
              case '7':
                     printf("\nOUTPUT -> UNTUK MENGECEK APAKAH BILANGAN TERDAPAT PADA TREE");
                     printf("\n------");
                     if(pohon!=NULL)
                     {
                           printf("\nPRE ORDER  : ");
                           preOrder(pohon); //panggil fungsi
                           printf("\nIN ORDER   : ");
                           inOrder(pohon); //panggil fungsi
                           printf("\nPOST ORDER : ");
                           postOrder(pohon); //panggil fungsi
                           printf("\n\nPENCARIAN BILANGAN");
                           printf("\n--------------");
                           printf("\nMASUKKAN BILANGAN YANG INGIN DICARI: ");
                           scanf("%d", &cari);
                           search(&pohon, cari);
                     }
                     else
                           printf("\nBELUM ADA BILANGAN");

                     _getch();
                     break;
                     
              //PILIHAN '8'       
              case '8':
              		cout<<"\nBILANGAN TERBESAR PADA TREE ADALAH :"<<findMax();
              		_getch();
              		break;
              		
              //PILIHAN '9'		
              case '9':
              		cout<<"\nBILANGAN TERKECIL PADA TREE ADALAH :"<<findMin(); 
					_getch(); 
					break;      
					
			  //PILIHAN 'X'		     	
              case 'X'|'x':
                     exit(0);
                     break;
              }
       }
}
