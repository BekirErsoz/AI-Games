#include <iostream>

int main() {
    int a, b, toplam;
    
    std::cout << "Birinci sayıyı girin: ";
    std::cin >> a;
    
    std::cout << "İkinci sayıyı girin: ";
    std::cin >> b;
    
    toplam = a + b;
    
    std::cout << "Toplam: " << toplam << std::endl;
    
    return 0;
}