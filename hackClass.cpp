/*
Pointerlar ile sinifin private uyelerinin degerini degistirme
*/


#include <iostream>

class Myobj {
    private:
        int data;
    public:
        Myobj(int data) {
            this->data = data;
        }

        void print() { std::cout<<data<<std::endl; }
};

int main() {
    Myobj obj(5);
    obj.print();
    int *ptr = (int*)(&obj); // sinifin adresini int tipinden bi pointera atiyoruz
    *ptr = 100; // pointerin degerini degistirdigimizde gosterdigi adreste otomatik olarak degisiyo :)
    obj.print();
	*ptr = 1500;
	obj.print();

	return 0;
}
