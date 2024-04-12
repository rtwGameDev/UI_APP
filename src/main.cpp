#include "homePage.h"
#include <iostream>
using namespace std;
int main() {
    auto ui = homePage::create();

    ui->run();
    cout << 1;
    return 0;
}