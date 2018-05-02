/*-------------------------------------------------------
 | CS 372: Software Construction                        |
 | Pair Programming: String Calculator                  |
 | Due Date: 2/12/18                                    |
 | File: CalculatorTests.cpp                            |
 | Written By: Thatcher Lane, Collin Lasley,            |
 | Description: Unit tests for String Calculator        |
 ------------------------------------------------------*/

#include "catch2.h"

#include "StringCalculator.h"

#include <sstream>


int ParseString(std::string inputStr)
{
    char delim = ',';
    if (inputStr[0] == '/' && inputStr[1] == '/') {
        delim = inputStr[2];
        inputStr = inputStr.substr(3, inputStr.length());
    }
    
    if (inputStr.empty())
        return 0;
    else if (inputStr.find_first_not_of("0123456789") == std::string::npos)
        return std::stoi(inputStr);
    else if (inputStr.find_first_of("-") != std::string::npos)
        throw "Exception.";
    
    else if(inputStr.find(',') != std::string::npos) {
        std::stringstream ss(inputStr);
        
        std::vector<int> individualNumbers;
        
        while(ss.good())
        {
            std::string temp;
            getline(ss,temp,',');
            int tempInt = std::stoi(temp);
            if(tempInt < 1000) {
                individualNumbers.push_back(tempInt);
            }
        }
        
        int sum = 0;
        for(const auto & n : individualNumbers)
        {
            sum += n;
        }
        
        return sum;
        
    }else if (inputStr.find('\n') != std::string::npos){
        std::stringstream ss(inputStr);
        
        std::vector<int> individualNumbers;
        
        while(ss.good())
        {
            std::string temp;
            getline(ss,temp,'\n');
            int tempInt = std::stoi(temp);
            if(tempInt < 1000) {
                individualNumbers.push_back(tempInt);
            }
        }
        
        int sum = 0;
        for(const auto & n : individualNumbers)
        {
            sum += n;
        }
        
        return sum;
    }else{
        std::stringstream ss(inputStr);
        
        std::vector<int> individualNumbers;
        
        while(ss.good())
        {
            std::string temp;
            getline(ss,temp,delim);
            int tempInt = std::stoi(temp);
            if(tempInt < 1000) {
                individualNumbers.push_back(tempInt);
            }
        }
        
        int sum = 0;
        for(const auto & n : individualNumbers)
        {
            sum += n;
        }
        
        return sum;
    }
    
}

TEST_CASE( "The Empty String Returns 0", "[StringEval]" ) {
    
    REQUIRE(ParseString("") == 0);
}

TEST_CASE( "A single int returns its value", "[StringEval]" ) {
    
    REQUIRE(ParseString("5") == 5);
    REQUIRE(ParseString("25") == 25);
}

TEST_CASE("Takes two ints, comma delimited and return their sum", "[StringEval]" ) {
    REQUIRE(ParseString("1,2") == 3);
    REQUIRE(ParseString("2,3") == 5);
}

TEST_CASE("Takes two ints, new line delimited and returns their sum", "[StringEval]" ) {
    REQUIRE(ParseString("1 \n 2") == 3);
}

TEST_CASE("Takes three ints, new line OR comma delimited, and returns their sum", "[StringEval]" ) {
    REQUIRE(ParseString("1,5,7") == 13);
    REQUIRE(ParseString("1\n5\n7") == 13);
}

TEST_CASE("Negative numbers throw an exception", "[StringEval]" ) {
    REQUIRE_THROWS(ParseString("-5"));
    REQUIRE_THROWS(ParseString("-4,12"));
}


TEST_CASE("Ignores numbers larger than 1000", "[StringEval}" ) {
    REQUIRE(ParseString("1,2,1000") == 3);
    REQUIRE(ParseString("1,5,1000") == 6);
}

TEST_CASE("Custom delimiter", "[StringEval}" ) {
    REQUIRE(ParseString("//$5$18") == 23);
    REQUIRE(ParseString("//(1(2(3") == 6);
}

