//
// Created by mati on 10/29/19.
//

#include <iostream>
#include "testLib2.h"

using namespace std;

extern "C" void TestLib2::execute() {
    printf("TestLib2::execute: Hello World!! \n");
}