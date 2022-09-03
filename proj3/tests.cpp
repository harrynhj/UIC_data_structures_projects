#include <iostream>
#include "barchartanimate.h"
#include <map>
using namespace std;


bool testBarDefaultConstructor() {
    Bar b;
    Bar c;
    if (b.getName() != "") {
        cout << "testBarDefaultConstructor: getName failed" << endl;
        return false;
    } else if (b.getValue() != 0) {
        cout << "testBarDefaultConstructor: getValue failed" << endl;
        return false;
    } else if (b.getCategory() != "") {
        cout << "testBarDefaultConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarDefaultConstructor2: all passed!" << endl;
    if (c.getName() != "") {
        cout << "testBarDefaultConstructor: getName failed" << endl;
        return false;
    } else if (c.getValue() != 0) {
        cout << "testBarDefaultConstructor: getValue failed" << endl;
        return false;
    } else if (c.getCategory() != "") {
        cout << "testBarDefaultConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarDefaultConstructor2: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
    Bar b("Chicago", 9234324, "US");
    Bar a("BeiJing", 9544324, "China");
    if (b.getName() != "Chicago") {
        cout << "testBarParamConstructor: getName failed" << endl;
        return false;
    } else if (b.getValue() != 9234324) {
        cout << "testBarParamConstructor: getValue failed" << endl;
        return false;
    } else if (b.getCategory() != "US") {
        cout << "testBarParamConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarParamConstructor1: all passed!" << endl;
    if (a.getName() != "BeiJing") {
        cout << "testBarParamConstructor: getName failed" << endl;
        return false;
    } else if (a.getValue() != 9544324) {
        cout << "testBarParamConstructor: getValue failed" << endl;
        return false;
    } else if (a.getCategory() != "China") {
        cout << "testBarParamConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarParamConstructor2: all passed!" << endl;
    return true;
}

bool testBarOperator1(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (a < b) {
        cout << "testBarOperator: operator< failed" << endl;
        return false;
    } else if (a < c) {
        cout << "testBarOperator: bar operator < failed" << endl;
        return false;
    }
    cout << "testBarOperator<: all passed twice!" << endl;
    return true;
}

bool testBarOperator2(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (a <= b) {
        cout << "testBarOperator: bar operator <= failed" << endl;
        return false;
    } else if (a <= c) {
        cout << "testBarOperator: bar operator <= failed" << endl;
        return false;
    }
    cout << "testBarOperator<=: all passed twice!" << endl;
    return true;
}

bool testBarOperator3(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (b >= a) {
        cout << "testBarOperator: bar operator >= failed" << endl;
        return false;
    } else if (c >= a) {
        cout << "testBarOperator: bar operator >= failed" << endl;
        return false;
    }
    cout << "testBarOperator>=: all passed twice!" << endl;
    return true;
}

bool testBarOperator4(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (b > a) {
        cout << "testBarOperator: bar operator > failed" << endl;
        return false;
    } else if (c > a) {
        cout << "testBarOperator: bar operator > failed" << endl;
        return false;
    }
    cout << "testBarOperator>: all passed twice!" << endl;
    return true;
}

bool testBarGetName(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (a.getName() != "BeiJing") {
        cout << "testBarGetName: getName failed" << endl;
        return false;
    }
    cout << "testBarGetName1: all passed!" << endl;
    if (b.getName() != "Chicago") {
        cout << "testBarGetName: getName failed" << endl;
        return false;
    }
    cout << "testBarGetName2: all passed!" << endl;
    if (c.getName() != "ShangHai") {
        cout << "testBarGetName: getName failed" << endl;
        return false;
    }
    cout << "testBarGetName3: all passed!" << endl;
    return true;
}

bool testBarGetValue(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (a.getValue() != 9534324) {
        cout << "testBarGetValue: getValue failed" << endl;
        return false;
    }
    cout << "testBarGetValue1: all passed!" << endl;
    if (b.getValue() != 9234324) {
        cout << "testBarGetValue: getValue failed" << endl;
        return false;
    }
    cout << "testBarGetValue2: all passed!" << endl;
    if (c.getValue() != 9134324) {
        cout << "testBarGetValue: getValue failed" << endl;
        return false;
    }
    cout << "testBarGetValue3: all passed!" << endl;
    return true;
}

bool testBarGetCategory(){
    Bar a("BeiJing", 9534324, "China");
    Bar b("Chicago", 9234324, "US");
    Bar c("ShangHai", 9134324, "China");
    if (a.getCategory() != "China") {
        cout << "testBarGetCategory: getCategory failed" << endl;
        return false;
    }
    cout << "testBarGetCategory1: all passed!" << endl;
    if (b.getCategory() != "US") {
        cout << "testBarGetCategory: getCategory failed" << endl;
        return false;
    }
    cout << "testBarGetCategory2: all passed!" << endl;
    if (c.getCategory() != "China") {
        cout << "testBarGetCategory: getCategory failed" << endl;
        return false;
    }
    cout << "testBarGetCategory3: all passed!" << endl;
    return true;
}

bool  testBarChartDefaultConstructor() {
    BarChart b;
    BarChart c;
    if (b.getFrame() != "") {
        cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
        return false;
    } else if (b.getSize() != 0) {
        cout << "testBarChartDefaultConstructor: getSize failed" << endl;
        return false;
    }
    cout << "testBarChartDefaultConstructor1: all passed!" << endl;
    if (c.getFrame() != "") {
        cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
        return false;
    } else if (c.getSize() != 0) {
        cout << "testBarChartDefaultConstructor: getSize failed" << endl;
        return false;
    }
    cout << "testBarChartDefaultConstructor2: all passed!" << endl;
    return true;
}

bool testBarChartWithCap() {
    BarChart b(10);
    BarChart c(20);
    b.addBar("BeiJing", 9534324, "China");
    c.addBar("Chicago", 9234324, "US");
    c.addBar("Chicago", 9234324, "US");
    if (b.getSize() != 1) {
        cout << "testBarChartWithCap: failed" << endl;
        return false;
    }
    cout << "testBarChartWithCap1: all passed!" << endl;
    if (c.getSize() != 2) {
        cout << "testBarChartWithCap: failed" << endl;
        return false;
    }
    cout << "testBarChartWithCap2: all passed!" << endl;
    return true;
}

bool testBarChartGetSize() {
    BarChart b(10);
    BarChart c(20);
    b.addBar("BeiJing", 9534324, "China");
    c.addBar("Chicago", 9234324, "US");
    c.addBar("Chicago", 9234324, "US");
    if (b.getSize() != 1) {
        cout << "testBarCHartGetSize: failed" << endl;
        return false;
    }
    cout << "testBarCHartGetSize1: all passed!" << endl;
    if (c.getSize() != 2) {
        cout << "testBarCHartGetSize: failed" << endl;
        return false;
    }
    cout << "testBarCHartGetSize2: all passed!" << endl;
    return true;
}

bool testBarChartCopy(){
    BarChart b(10);
    BarChart c;
    BarChart d;
    c = BarChart(b);
    if (b.getSize() != c.getSize()) {
        cout << "testBarChartCopy: copy failed" << endl;
        return false;
    }
    d = BarChart(b);
    if (d.getSize() != b.getSize()) {
        cout << "testBarChartCopy: copy failed" << endl;
        return false;
    }
    cout << "testBarChartCopy: all passed!" << endl;
    return true;
}

bool testBarChartClear() {
    BarChart b(10);
    BarChart c(20);
    b.addBar("BeiJing", 9534324, "China");
    c.addBar("Chicago", 9234324, "US");
    b.clear();
    c.clear();
    if (b.getFrame() != "") {
        cout << "testBarChartClear: BarChartClear failed" << endl;
        return false;
    } else if (b.getSize() != 0) {
        cout << "testBarChartClear: BarChartClear failed" << endl;
        return false;
    }
    cout << "testBarChartClear1: all passed!" << endl;
    if (c.getFrame() != "") {
        cout << "testBarChartClear: BarChartClear failed" << endl;
        return false;
    } else if (c.getSize() != 0) {
        cout << "testBarChartClear: BarChartClear failed" << endl;
        return false;
    }
    cout << "testBarChartClear2: all passed!" << endl;
    return true;
}

bool testBarChartSetFrame() {
    BarChart b(10);
    BarChart c(20);
    b.setFrame("1");
    c.setFrame("2");
    if (b.getFrame() != "1") {
        cout << "testBarChartSetFrame: setFrame failed" << endl;
        return false;
    }
    cout << "testBarChartSetFrame1: all passed!" << endl;
    if (c.getFrame() != "2") {
        cout << "testBarChartSetFrame: setFrame failed" << endl;
        return false;
    }
    b.clear();
    c.clear();
    cout << "testBarChartSetFrame2: all passed!" << endl;
    return true;
}

bool testBarChartCopyOp() {
    BarChart b(10);
    b.addBar("BeiJing", 9534324, "China");
    b.addBar("Chicago", 9234324, "US");
    BarChart c(20);
    c.addBar("BeiJing", 9534324, "China");
    BarChart bCopy(b);
    BarChart cCopy(c);
    if (bCopy.getSize() != 2) {
        cout << "testBarCHartCopy: BarChartCopy failed" << endl;
        return false;
    }
    cout << "testBarChartCopy1: all passed!" << endl;
    if (cCopy.getSize() != 1) {
        cout << "testBarCHartCopy: BarChartCopy failed" << endl;
        return false;
    }
    cout << "testBarChartCopy2: all passed!" << endl;
    return true;
}

bool testBarChartBracketOperator() {
    BarChart b(10);
    b.addBar("BeiJing", 9534324, "China");
    b.addBar("Chicago", 9234324, "US");
    if (b[0].getName() != "BeiJing") {
        cout << "testBarChartBracketOperator: Operator [] failed" << endl;
        return false;
    }
    cout << "testBarChartBracketOperator1: all passed!" << endl;
    if(b[1].getName() != "Chicago") {
        cout << "testBarChartBracketOperator: Operator [] failed" << endl;
        return false;
    }
    cout << "testBarChartBracketOperator2: all passed!" << endl;
    return true;
}

bool testBarChartEqualOperator() {
    BarChart b(10);
    b.addBar("BeiJing", 9534324, "China");
    BarChart c(20);
    c.addBar("BeiJing", 9534324, "China");
    BarChart a(10);
    a.addBar("BeiJing", 9534324, "China");
    BarChart d(20);
    d.addBar("BeiJing", 9534324, "China");
    c = b;
    a = d;

    if (c[0].getName() != "BeiJing") {
        cout << "testBarChartEqualOperator: Operator = failed" << endl;
        return false;
    }
    cout << "testBarChartEqualOperator1: all passed!" << endl;
    if (a[0].getName() != "BeiJing") {
        cout << "testBarChartEqualOperator: Operator = failed" << endl;
        return false;
    }
    cout << "testBarChartEqualOperator2: all passed!" << endl;
    return true;
}

bool testBarChartDump() {
    BarChart b(10);
    b.setFrame("1950");
    b.addBar("BeiJing", 9534324, "China");
    b.addBar("Chicago", 9234324, "US");
    b.dump(cout);
    BarChart c(10);
    c.setFrame("1960");
    c.addBar("BeiJing", 9534324, "China");
    c.dump(cout);
    cout << "testBarChartDump: all passed twice!" << endl;
    return true;
}

bool testBarChartGraph() {
    BarChart b(10);
    b.setFrame("1950");
    b.addBar("Paris", 9534324, "France");
    b.addBar("Chicago", 9234324, "US");
    b.addBar("HongKong", 7234324, "China");
    string red("\033[1;36m");
    string blue("\033[1;33m");
    map<string, string> colorMap;
    colorMap["US"] = RED;
    colorMap["France"] = BLUE;
    cout << "1st test" << endl;
    b.graph(cout, colorMap, 3);
    cout << "2nd test" << endl;
    b.graph(cout, colorMap, 2);
    cout << "testBarChartDump: all passed twice!" << endl;
    return true;
}

bool testBarChartAnimateDefaultConstructor() {
    string title1 = "title1";
    string title2 = "title2";
    string xlabel1 = "xlabel1";
    string xlabel2 = "xlabel2";
    string source1 = "source1";
    string source2 = "source2";
    BarChartAnimate a(title1, xlabel1, source1);
    BarChartAnimate b(title2, xlabel2, source2);
    if (a.getSize() != 0) {
        cout << "testBarChartAnimateDefaultConstructor: default constructor failed" << endl;
        return false;
    }
    cout << "testBarChartAnimateDefaultConstructor1: all passed!" << endl;
    if (b.getSize() != 0) {
        cout << "testBarChartAnimateDefaultConstructor: default constructor failed" << endl;
        return false;
    }
    cout << "testBarChartAnimateDefaultConstructor2: all passed!" << endl;
    return true;
}

bool testAddFrame_animate(){
    string tmp;
    cout << "input something to start test: ";
    cin >> tmp;
    string title = "title";
    string xlabel = "xlabel";
    string source = "source";
    string filename = "cities.txt";
    ifstream inFile(filename);
    getline(inFile, title);
    getline(inFile, title);
    getline(inFile, title);
    BarChartAnimate a(title, xlabel, source);
    a.addFrame(inFile);
    a.animate(cout,12,1);
    a.addFrame(inFile);
    a.animate(cout,5,1);
    cout << "testAddFrame_animate: Please check output to determine" << endl;
    inFile.close();
    return true;
}




int main() {
    testBarDefaultConstructor();
    testBarParamConstructor();
    testBarOperator1();
    testBarOperator2();
    testBarOperator3();
    testBarOperator4();
    testBarGetName();
    testBarGetValue();
    testBarGetCategory();
    testBarChartGetSize();
    testBarChartDefaultConstructor();
    testBarChartWithCap();
    testBarChartClear();
    testBarChartSetFrame();
    testBarChartCopy();
    testBarChartCopyOp();
    testBarChartBracketOperator();
    testBarChartEqualOperator();
    testBarChartDump();
    testBarChartGraph();
    testBarChartAnimateDefaultConstructor();
    testAddFrame_animate();
    return 0;
}