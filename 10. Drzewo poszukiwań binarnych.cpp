#include <iostream>

using namespace std;

template <class T>
class TreeNode{
    public:
        TreeNode<T>* lewed;
        int poziom;
        TreeNode<T>* prawed;
        T value;
        TreeNode(T val);
        void zmniejszP(){
            poziom--;
            if(lewed != nullptr) lewed-> zmniejszP();
            if(prawed != nullptr) prawed-> zmniejszP();
        }
};

template <class T> TreeNode<T>::TreeNode(T val)
: value(val), lewed(nullptr), prawed(nullptr), poziom(0){}

template <class T>
class Tree{
    public:
        TreeNode<T>* first;
        Tree(): first(nullptr){}
        void dodaj(T value);
        void usun(T value, TreeNode<T>* start);
        int getnajdlsciezke(TreeNode<T>* node);
        int getnajkrsciezke(TreeNode<T>* node);
        void wyswietlPre(TreeNode<T>* node);
        void wyswietlPost(TreeNode<T>* node);
        void wyswietlIn(TreeNode<T>* node);
        int dlsciezka = 0;
        int krsciezka = -1;
};

template <class T> void Tree<T>::dodaj(T value){
    if(first == nullptr){
        first = new TreeNode<T>(value);
        first->poziom = 0;
        return;
    }
    TreeNode<T>* obc = first, *dziecko;
    while(obc){
        if(value >= obc->value){ 
            dziecko = obc->lewed;
            if(dziecko == nullptr){
                obc->lewed = new TreeNode<T>(value);
                obc->lewed->poziom = obc->poziom+1;
                return;
            }    
        }
        if(value < obc->value){ 
            dziecko = obc->prawed;
            if(dziecko == nullptr){
                obc->prawed = new TreeNode<T>(value);
                obc->prawed->poziom = obc->poziom+1;
                return;
            }    
        }
        obc = dziecko;
    }
}

template <class T> void Tree<T>::usun(T value, TreeNode<T>* start = nullptr){
    if(first == nullptr) return;
    if(first->value == value and start == nullptr){
        while(first->value == value){
            if(first->lewed == nullptr and first->prawed == nullptr){
                first = nullptr;
                return;
            }else if(first->lewed == nullptr and first->prawed != nullptr){
                first = first->prawed;
                return;
            }else if(first->lewed != nullptr and first->prawed == nullptr){
                first = first->lewed;
                continue;
            }else{
                TreeNode<T>* next = first;
                TreeNode<T>* nextd = first->lewed;
                while(nextd->prawed){
                    next = nextd;
                    nextd = nextd->prawed;
                }
                first->value = nextd->value;
                usun(nextd->value, next);
            }
        }

    }
   
    if(start == nullptr) start = first;
    TreeNode<T>* obc = start, *dziecko = nullptr;
    while(obc){
        if(value >= obc->value){ 
            dziecko = obc->lewed;
            if(dziecko == nullptr) return;
            if(value == dziecko->value){
                if(dziecko->lewed == nullptr and dziecko->prawed == nullptr){
                    obc->lewed = nullptr;
                    return;
                }else if(dziecko->lewed == nullptr and dziecko->prawed != nullptr){
                    obc->lewed = dziecko->prawed;
                    obc->lewed->zmniejszP();
                    return;
                }else if(dziecko->lewed!= nullptr and dziecko->prawed == nullptr){
                    obc->lewed = dziecko->lewed;
                    obc->lewed->zmniejszP();
                    continue;
                }else{
                    TreeNode<T>* next = obc;
                    TreeNode<T>* nextd = obc->lewed;
                    while(nextd->prawed){
                        next = nextd;
                        nextd = nextd->prawed;
                    }
                    (obc->lewed)->value = nextd->value;
                    usun(nextd->value, next);
                }
            }          
        }
        if(value < obc->value){ 
            dziecko = obc->prawed;
            if(dziecko == nullptr){
                return;
            } 
            if(value == dziecko->value){
                if(dziecko->lewed == nullptr and dziecko->prawed == nullptr){
                    obc->prawed = nullptr;
                    return;
                }else if(dziecko->lewed == nullptr and dziecko->prawed != nullptr){
                    obc->prawed = dziecko->prawed;
                    obc->prawed->zmniejszP();
                    return;
                }else if(dziecko->lewed != nullptr and dziecko->prawed == nullptr){
                    obc->prawed = dziecko->lewed;
                    obc->prawed->zmniejszP();
                    continue;
                }else{
                    TreeNode<T>* next = obc;
                    TreeNode<T>* nextd = obc->lewed;
                    while(nextd->prawed){
                        next = nextd;
                        nextd = nextd->prawed;
                    }
                    (obc->lewed)->value = nextd->value;
                    usun(nextd->value, next);
                }
            }             
        }
        obc = dziecko;
    }
}

template <class T> void Tree<T>::wyswietlPre(TreeNode<T>* node){
    if(node == nullptr) return;
    cout<<node->value<<" ";
    wyswietlPre(node->lewed);
    wyswietlPre(node->prawed);
}
template <class T> void Tree<T>::wyswietlPost(TreeNode<T>* node){
    if(node == nullptr) return;
    wyswietlPost(node->lewed);
    wyswietlPost(node->prawed);
    cout<<node->value<<" ";
}
template <class T> void Tree<T>::wyswietlIn(TreeNode<T>* node){
    if(node == nullptr) return;
    wyswietlIn(node->lewed);
    cout<<node->value<<" ";
    wyswietlIn(node->prawed);
}
template <class T> int Tree<T>::getnajdlsciezke(TreeNode<T>* node){
    if(node == nullptr) return 0;
    if(node->poziom > dlsciezka) dlsciezka = node->poziom;
    getnajdlsciezke(node->lewed);
    getnajdlsciezke(node->prawed);
    return dlsciezka;
}
template <class T> int Tree<T>::getnajkrsciezke(TreeNode<T>* node){
    if(node == nullptr) return 0;
    if(krsciezka != -1 and node->poziom > krsciezka) return -1;
    if((node->poziom < krsciezka or krsciezka == -1) and (node->lewed == nullptr and node->prawed == nullptr)) krsciezka = node->poziom;
    getnajkrsciezke(node->lewed);
    getnajkrsciezke(node->prawed);
    return krsciezka;
}
int main()
{
    Tree<double> drzewo;
    int k;
    cin>>k;
    double value;
    for(k; k > 0; k--){
        cin>>value;
        drzewo.dodaj(value);
    }

    int l;
    cin>>l;
    for(l; l > 0; l--){
        cin>>value;
        drzewo.usun(value);
    }
    int m;
    cin>>m;
    switch(m){
        case 0:
            drzewo.wyswietlPre(drzewo.first);
        break;
        case 1:
            drzewo.wyswietlIn(drzewo.first);
        break;  
        case 2:
            drzewo.wyswietlPost(drzewo.first);
        break;
    }
    cout<<drzewo.getnajdlsciezke(drzewo.first)<<" ";
    cout<<drzewo.getnajkrsciezke(drzewo.first);
    return 1;
}