#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "mymap.h"
#include "myrandom.h"


TEST(mymap, empty_map) {
    mymap<int,int> empty_map;
    EXPECT_EQ(empty_map.Size(), 0);
}

TEST(mymap, empty_getsize) {
    mymap<int,int> empty_map;
    EXPECT_EQ(empty_map.Size(), 0);
}

TEST(mymap, put_temp) {
    mymap<int,int> map;
    int arr[] = {50, 33, 22, 11, 25, 3, 66};
    for (int i = 0; i < 7; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 7);
}

TEST(mymap, put_perfect) {
    mymap<int,int> map;
    int arr[] = {50, 33, 89, 41, 7, 91, 66};
    for (int i = 0; i < 7; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 7);
}

TEST(mymap, put_int) {
    mymap<int,int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 3);
}

TEST(mymap, put_double) {
    mymap<double,double> map;
    double arr[] = {2.1, 1.5, 3.8};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 3);
}

TEST(mymap, put_string) {
    mymap<string,string> map;
    string arr[] = {"aaa","bbb","ccc"};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 3);
}

TEST(mymap, put_char) {
    mymap<char,char> map;
    char arr[] = {'a','b','c'};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 3);
}

TEST(mymap, put_mixtype) {
    mymap<int,char> map;
    char arr[] = {'a','b','c'};
    int arr2[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr2[i]);
    }
    EXPECT_EQ(map.Size(), 3);
}

TEST(mymap, put_repeated) {
    mymap<int,int> map;
    map.put(1, 1);
    for (int i = 0; i < 7; i++) {
     map.put(2, 2);
    }
    EXPECT_EQ(map.Size(), 2);
}

TEST(mymap, get_int) {
    mymap<int,int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.get(1), 1);
    EXPECT_EQ(map.get(2), 2);
    EXPECT_EQ(map.get(3), 3);
}

TEST(mymap, get_double) {
    mymap<double,double> map;
    double arr[] = {2.1, 1.5, 3.8};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.get(2.1), 2.1);
    EXPECT_EQ(map.get(1.5), 1.5);
    EXPECT_EQ(map.get(3.8), 3.8);
}

TEST(mymap, get_string) {
    mymap<string,string> map;
    string arr[] = {"aaa","bbb","ccc"};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.get("aaa"), "aaa");
    EXPECT_EQ(map.get("bbb"), "bbb");
    EXPECT_EQ(map.get("ccc"), "ccc");
}

TEST(mymap, get_char) {
    mymap<char,char> map;
    char arr[] = {'a','b','c'};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.get('a'), 'a');
    EXPECT_EQ(map.get('b'), 'b');
    EXPECT_EQ(map.get('c'), 'c');
}

TEST(mymap, get_mixtype) {
    mymap<int,char> map;
    char arr[] = {'a','b','c'};
    int arr2[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr2[i]);
    }
    EXPECT_EQ(map.get('a'), 2);
    EXPECT_EQ(map.get('b'), 1);
    EXPECT_EQ(map.get('c'), 3);

}

TEST(mymap, stress_put) {
    mymap<int,int> map;
    int n = 100000;
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,10000);  // given
        int val = randomInteger(0,10000);
        map.put(key, val);
    }
    EXPECT_EQ(map.Size(), 9999);
}


TEST(mymap, toString_int) {
    mymap<int,int> map;
    int arr[] = {5, 3, 13,10,2,8,17,1};
    for (int i = 0; i < 8; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\nkey: 5 value: 5\nkey: 8 value: 8\nkey: 10 value: 10\nkey: 13 value: 13\nkey: 17 value: 17\n";

    EXPECT_EQ(sol, map.toString());
}

TEST(mymap, toString_string) {
    mymap<string,string> map;
    string arr[] = {"aaa","bbb","ccc","ddd","eee","fff","ggg","hhh"};
    for (int i = 0; i < 8; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: aaa value: aaa\nkey: bbb value: bbb\nkey: ccc value: ccc\nkey: ddd value: ddd\nkey: eee value: eee\nkey: fff value: fff\nkey: ggg value: ggg\nkey: hhh value: hhh\n";

    EXPECT_EQ(sol, map.toString());
}

TEST(mymap, toString_char) {
    mymap<char,char> map;
    char arr[] = {'a','b','c','d','e','f','g','h'};
    for (int i = 0; i < 8; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: a value: a\nkey: b value: b\nkey: c value: c\nkey: d value: d\nkey: e value: e\nkey: f value: f\nkey: g value: g\nkey: h value: h\n";
    EXPECT_EQ(sol, map.toString());
}

TEST(mymap, toString_double) {
    mymap<double,double> map;
    double arr[] = {3.3, 1.1, 2.2};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: 1.1 value: 1.1\nkey: 2.2 value: 2.2\nkey: 3.3 value: 3.3\n";

    EXPECT_EQ(sol, map.toString());
}

TEST(mymap, bracket_op_int) {
    mymap<int,int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map[1], 1);
    EXPECT_EQ(map[2], 2);
    EXPECT_EQ(map[3], 3);
}

TEST(mymap, bracket_op_double) {
    mymap<double,double> map;
    double arr[] = {2.1, 1.5, 3.8};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map[2.1], 2.1);
    EXPECT_EQ(map[1.5], 1.5);
    EXPECT_EQ(map[3.8], 3.8);
}

TEST(mymap, bracket_op_string) {
    mymap<string,string> map;
    string arr[] = {"aaa","bbb","ccc"};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map["aaa"], "aaa");
    EXPECT_EQ(map["bbb"], "bbb");
    EXPECT_EQ(map["ccc"], "ccc");
}

TEST(mymap, bracket_op_char) {
    mymap<char,char> map;
    char arr[] = {'a','b','c'};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map['a'], 'a');
    EXPECT_EQ(map['b'], 'b');
    EXPECT_EQ(map['c'], 'c');
}

TEST(mymap, bracket_op_mixtype) {
    mymap<int,char> map;
    char arr[] = {'a','b','c'};
    int arr2[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
     map.put(arr2[i], arr[i]);
    }
    EXPECT_EQ(map[2], 'a');
    EXPECT_EQ(map[1], 'b');
    EXPECT_EQ(map[3], 'c');
}


TEST(mymap, put_same_key) {
    mymap<int,int> map;
    map.put(2, 2);
    map.put(4, 5);
    map.put(2, 3);
    EXPECT_EQ(map.Size(), 2);
}

TEST(mymap, get_invalid_key) {
    mymap<int,int> map;
    map.put(2, 2);
    EXPECT_EQ(map.get(3), 0);
}

TEST(mymap, braket_op_invalid_key) {
    mymap<int,int> map;
    map.put(2, 2);
    EXPECT_EQ(map[3], 0);
}

TEST(mymap, contain_int) {
    mymap<int,int> map;
    int n = 100000;
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,10000);  // given
        int val = randomInteger(0,10000);
        map.put(key, val);
    }
    map.put(6324, 6324);
    EXPECT_TRUE(map.contains(6324));
    EXPECT_FALSE(map.contains(99999));
}

TEST(mymap, contain_double) {
    mymap<double,double> map;
    double arr[] = {2.1, 1.5, 3.8};
    for (int i = 0; i < 3; i++) {
     map.put(arr[i], arr[i]);
    }
    EXPECT_TRUE(map.contains(1.5));
    EXPECT_FALSE(map.contains(4.8));
}

TEST(mymap, contain_string) {
    mymap<string,string> map;
    string arr[] = {"aaa","bbb","ccc"};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    EXPECT_TRUE(map.contains("aaa"));
    EXPECT_FALSE(map.contains("ddd"));
}

TEST(mymap, contain_char) {
    mymap<char,char> map;
    char arr[] = {'a','b','c'};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    EXPECT_TRUE(map.contains('a'));
    EXPECT_FALSE(map.contains('d'));
}

TEST(mymap, Milestone1_Everything) {
    // test to compare with C++ map
    mymap<int, int> mapMine;
    map<int,int> mapSol;
    int n = 1000000;  // # of elements inserted
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,10000);  // given
        int val = randomInteger(0,10000);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
	 // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
}


TEST (mymap, foreach_int) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
}

TEST (mymap, foreach_double) {
    mymap<double, double> map;
    double arr[] = {2.1, 1.6, 3.9};
    double order[] = {1.6, 2.1, 3.9};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
}

TEST (mymap, foreach_char) {
    mymap<char, char> map;
    char arr[] = {'b', 'a', 'c'};
    char order[] = {'a', 'b', 'c'};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
}

TEST (mymap, foreach_string) {
    mymap<string, string> map;
    string arr[] = {"bbb", "aaa", "ccc"};
    string order[] = {"aaa", "bbb", "ccc"};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
}

TEST (mymap, double_equal_op_int) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_TRUE(order[i++] == key);
    }
}

TEST (mymap, double_equal_op_double) {
    mymap<double, double> map;
    double arr[] = {2.1, 1.6, 3.9};
    double order[] = {1.6, 2.1, 3.9};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_TRUE(order[i++] == key);
    }
}

TEST (mymap, double_equal_op_char) {
    mymap<char, char> map;
    char arr[] = {'b', 'a', 'c'};
    char order[] = {'a', 'b', 'c'};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_TRUE(order[i++] == key);
    }
}

TEST (mymap, double_equal_op_string) {
    mymap<string, string> map;
    string arr[] = {"bbb", "aaa", "ccc"};
    string order[] = {"aaa", "bbb", "ccc"};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_TRUE(order[i++] == key);
    }
}

TEST (mymap, ms3_everything){
   mymap<int, int> test;
   map<int, int> correct;
   for(int i = 0; i < 10000; i++) {
	// randomize key and val
	int k = randomInteger(0,10000);
	int v = randomInteger(0,10000);
	test.put(k, v);
	correct[k] = v;
   }
   stringstream ss("");
   for (int key : test) {
      // it does work like this
      ss << "key: " << key <<
         " value: " << test[key]
         << endl;
   }
   // loop should be in order
   EXPECT_EQ(test.toString(),
      ss.str());
}


TEST (mymap, clear_int) {
    mymap<int, int> map;
    int arr[] = {50, 33, 22, 11, 25, 3, 66};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST (mymap, clear_double) {
    mymap<double, double> map;
    double arr[] = {50.1, 33.2, 22.3, 11.4, 25.5, 3.6, 66.7};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST (mymap, clear_char) {
    mymap<char, char> map;
    char arr[] = {'b', 'a', 'c', 'd', 'e', 'f', 'g'};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST (mymap, clear_string) {
    mymap<string, string> map;
    string arr[] = {"bbb", "aaa", "ccc", "ddd", "eee", "fff", "ggg"};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST (mymap, clear_empty) {
    mymap<int, int> map;
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST (mymap, copy_int) {
    mymap<int, int> map;
    int arr[] = {50, 33, 22, 11, 25, 3, 66};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<int, int> map2(map);
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get(50), 50);
    EXPECT_EQ(map2.get(33), 33);
    EXPECT_EQ(map2.get(22), 22);
    EXPECT_EQ(map2.get(11), 11);
    EXPECT_EQ(map2.get(25), 25);
    EXPECT_EQ(map2.get(3), 3);
    EXPECT_EQ(map2.get(66), 66);
}

TEST (mymap, copy_double) {
    mymap<double, double> map;
    double arr[] = {50.1, 33.2, 22.3, 11.4, 25.5, 3.6, 66.7};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<double, double> map2(map);
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get(50.1), 50.1);
    EXPECT_EQ(map2.get(33.2), 33.2);
    EXPECT_EQ(map2.get(22.3), 22.3);
    EXPECT_EQ(map2.get(11.4), 11.4);
    EXPECT_EQ(map2.get(25.5), 25.5);
    EXPECT_EQ(map2.get(3.6), 3.6);
    EXPECT_EQ(map2.get(66.7), 66.7);
}

TEST (mymap, copy_char) {
    mymap<char, char> map;
    char arr[] = {'b', 'a', 'c', 'd', 'e', 'f', 'g'};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<char, char> map2(map);
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get('b'), 'b');
    EXPECT_EQ(map2.get('a'), 'a');
    EXPECT_EQ(map2.get('c'), 'c');
    EXPECT_EQ(map2.get('d'), 'd');
    EXPECT_EQ(map2.get('e'), 'e');
    EXPECT_EQ(map2.get('f'), 'f');
    EXPECT_EQ(map2.get('g'), 'g');
}

TEST (mymap, copy_string) {
    mymap<string, string> map;
    string arr[] = {"bbb", "aaa", "ccc", "ddd", "eee", "fff", "ggg"};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<string, string> map2(map);
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get("bbb"), "bbb");
    EXPECT_EQ(map2.get("aaa"), "aaa");
    EXPECT_EQ(map2.get("ccc"), "ccc");
    EXPECT_EQ(map2.get("ddd"), "ddd");
    EXPECT_EQ(map2.get("eee"), "eee");
    EXPECT_EQ(map2.get("fff"), "fff");
    EXPECT_EQ(map2.get("ggg"), "ggg");
}

TEST (mymap, copy_empty) {
    mymap<int, int> map;
    mymap<int, int> map2(map);
    EXPECT_EQ(map2.Size(), 0);
}

TEST (mymap, copy_op_int) {
    mymap<int, int> map;
    int arr[] = {50, 33, 22, 11, 25, 3, 66};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<int, int> map2 = map;
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get(50), 50);
    EXPECT_EQ(map2.get(33), 33);
    EXPECT_EQ(map2.get(22), 22);
    EXPECT_EQ(map2.get(11), 11);
    EXPECT_EQ(map2.get(25), 25);
    EXPECT_EQ(map2.get(3), 3);
    EXPECT_EQ(map2.get(66), 66);
}

TEST (mymap, copy_op_double) {
    mymap<double, double> map;
    double arr[] = {50.1, 33.2, 22.3, 11.4, 25.5, 3.6, 66.7};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<double, double> map2 = map;
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get(50.1), 50.1);
    EXPECT_EQ(map2.get(33.2), 33.2);
    EXPECT_EQ(map2.get(22.3), 22.3);
    EXPECT_EQ(map2.get(11.4), 11.4);
    EXPECT_EQ(map2.get(25.5), 25.5);
    EXPECT_EQ(map2.get(3.6), 3.6);
    EXPECT_EQ(map2.get(66.7), 66.7);
}

TEST (mymap, copy_op_char) {
    mymap<char, char> map;
    char arr[] = {'b', 'a', 'c', 'd', 'e', 'f', 'g'};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<char, char> map2 = map;
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get('b'), 'b');
    EXPECT_EQ(map2.get('a'), 'a');
    EXPECT_EQ(map2.get('c'), 'c');
    EXPECT_EQ(map2.get('d'), 'd');
    EXPECT_EQ(map2.get('e'), 'e');
    EXPECT_EQ(map2.get('f'), 'f');
    EXPECT_EQ(map2.get('g'), 'g');
}

TEST (mymap, copy_op_string) {
    mymap<string, string> map;
    string arr[] = {"bbb", "aaa", "ccc", "ddd", "eee", "fff", "ggg"};
    for (int i = 0; i < 7; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<string, string> map2 = map;
    EXPECT_EQ(map2.Size(), 7);
    EXPECT_EQ(map2.get("bbb"), "bbb");
    EXPECT_EQ(map2.get("aaa"), "aaa");
    EXPECT_EQ(map2.get("ccc"), "ccc");
    EXPECT_EQ(map2.get("ddd"), "ddd");
    EXPECT_EQ(map2.get("eee"), "eee");
    EXPECT_EQ(map2.get("fff"), "fff");
    EXPECT_EQ(map2.get("ggg"), "ggg");
}

TEST (mymap, copy_op_empty) {
    mymap<int, int> map;
    mymap<int, int> map2 = map;
    EXPECT_EQ(map2.Size(), 0);
}

TEST (mymap, check_balance_int) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    EXPECT_EQ(map.checkBalance(), sol);
}

TEST (mymap, check_balance_double) {
    mymap<double, double> map;
    double arr[] = {2.2, 1.1, 3.3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: 2.2, nL: 1, nR: 1\nkey: 1.1, nL: 0, nR: 0\nkey: 3.3, nL: 0, nR: 0\n";
    EXPECT_EQ(map.checkBalance(), sol);
}

TEST (mymap, check_balance_char) {
    mymap<char, char> map;
    char arr[] = {'b', 'a', 'c'};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: b, nL: 1, nR: 1\nkey: a, nL: 0, nR: 0\nkey: c, nL: 0, nR: 0\n";
    EXPECT_EQ(map.checkBalance(), sol);
}

TEST (mymap, check_balance_string) {
    mymap<string, string> map;
    string arr[] = {"bbb", "aaa", "ccc"};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    string sol = "key: bbb, nL: 1, nR: 1\nkey: aaa, nL: 0, nR: 0\nkey: ccc, nL: 0, nR: 0\n";
    EXPECT_EQ(map.checkBalance(), sol);
}

TEST (mymap, check_balance_empty) {
    mymap<int, int> map;
    string sol = "";
    EXPECT_EQ(map.checkBalance(), sol);
}

TEST (mymap, tovector_int) {
    mymap<int,int> m;
    vector<pair<int,int>> v;
    int arr[] = {2,1,3};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
        v.push_back(make_pair(i+1,i+1));
    }
    ASSERT_EQ(m.toVector(), v);
}

TEST (mymap, tovector_double) {
    mymap<double,double> m;
    vector<pair<double,double>> v;
    double arr[] = {2.2,1.1,3.3};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    v.push_back(make_pair(1.1,1.1));
    v.push_back(make_pair(2.2,2.2));
    v.push_back(make_pair(3.3,3.3));
    ASSERT_EQ(m.toVector(), v);
}

TEST (mymap, tovector_char) {
    mymap<char,char> m;
    vector<pair<char,char>> v;
    char arr[] = {'b','a','c'};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    v.push_back(make_pair('a','a'));
    v.push_back(make_pair('b','b'));
    v.push_back(make_pair('c','c'));
    ASSERT_EQ(m.toVector(), v);
}

TEST (mymap, tovector_string) {
    mymap<string,string> m;
    vector<pair<string,string>> v;
    string arr[] = {"bbb","aaa","ccc"};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    v.push_back(make_pair("aaa","aaa"));
    v.push_back(make_pair("bbb","bbb"));
    v.push_back(make_pair("ccc","ccc"));
    ASSERT_EQ(m.toVector(), v);
}

TEST (mymap, tovector_empty) {
    mymap<int,int> m;
    vector<pair<int,int>> v;
    ASSERT_EQ(m.toVector(), v);
}

TEST (mymap, balance_int) {
    mymap<int,int> m;
    int arr[] = {1,2,3};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    EXPECT_EQ(m.checkBalance(), sol);
} 

TEST (mymap, balance_double) {
    mymap<double,double> m;
    double arr[] = {1.1,2.2,3.3};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 2.2, nL: 1, nR: 1\nkey: 1.1, nL: 0, nR: 0\nkey: 3.3, nL: 0, nR: 0\n";
    EXPECT_EQ(m.checkBalance(), sol);
} 

TEST (mymap, balance_char) {
    mymap<char,char> m;
    char arr[] = {'a','b','c'};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: b, nL: 1, nR: 1\nkey: a, nL: 0, nR: 0\nkey: c, nL: 0, nR: 0\n";
    EXPECT_EQ(m.checkBalance(), sol);
} 

TEST (mymap, balance_string) {
    mymap<string,string> m;
    string arr[] = {"aaa","bbb","ccc"};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: bbb, nL: 1, nR: 1\nkey: aaa, nL: 0, nR: 0\nkey: ccc, nL: 0, nR: 0\n";
    EXPECT_EQ(m.checkBalance(), sol);
} 

TEST (mymap, balance_small_tree) {
    mymap<int,int> m;
    int arr[] = {99,98,97,96,95,94,100,101,102,103,104};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 100, nL: 6, nR: 4\nkey: 96, nL: 2, nR: 3\nkey: 94, nL: 0, nR: 1\n";
    sol +="key: 95, nL: 0, nR: 0\nkey: 98, nL: 1, nR: 1\nkey: 97, nL: 0, nR: 0\nkey: 99, nL: 0, nR: 0\n";
    sol +="key: 102, nL: 1, nR: 2\nkey: 101, nL: 0, nR: 0\nkey: 103, nL: 0, nR: 1\nkey: 104, nL: 0, nR: 0\n";
    EXPECT_EQ(m.checkBalance(), sol);
} 

