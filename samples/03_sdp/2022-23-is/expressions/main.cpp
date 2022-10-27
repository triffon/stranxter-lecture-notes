#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"

#include <string>
#include <iostream>
#include <cassert>

#include "tokenizer.h"
#include "evaluator.h"


TEST_CASE("Basic Tokenizer Test")
{

    std::stringstream expr ("123*(11+20)");

    Token t;

    std::vector<Token> expected = {{Token::NUMBER,0,123},
                                   {Token::OPERATOR,'*',0},
                                   {Token::OPEN_PAR,'(',0},
                                   {Token::NUMBER,0,11},
                                   {Token::OPERATOR,'+',0},
                                   {Token::NUMBER,0,20},
                                   {Token::CLOSE_PAR,')',0}};

    for (Token expectedToken:expected)
    {
        Token in;
        expr >> in;
        CHECK(in.type==expectedToken.type);
        CHECK(in.value==expectedToken.value);
        CHECK(in.symbol==expectedToken.symbol);
    }

}

TEST_CASE("Extended Tokenizer Test")
{

    std::stringstream expr ("123  \n\n\n\r\r\t"
                            "  *      (\n"
                            "11\n"
                            "+20)\n\n\n");

    Token t;

    std::vector<Token> expected = {{Token::NUMBER,0,123},
                                {Token::OPERATOR,'*',0},
                                {Token::OPEN_PAR,'(',0},
                                {Token::NUMBER,0,11},
                                {Token::OPERATOR,'+',0},
                                {Token::NUMBER,0,20},
                                {Token::CLOSE_PAR,')',0}};

    for (Token expectedToken:expected)
    {
        Token in;
        expr >> in;
        CHECK(in.type==expectedToken.type);
        CHECK(in.value==expectedToken.value);
        CHECK(in.symbol==expectedToken.symbol);
    }

}

TEST_CASE ("Eval test")
{
    std::vector<std::pair<std::string,int>> tests = 
                {{"1",1},
                 {"(1+2)",3},
                 {"((1+10)*(3+4))",77},
                 {"(1+(9+1))",11}};

    for (std::pair<std::string,int> test : tests)
    {
        std::stringstream s(test.first);
        CHECK(evaluate(s) == test.second);
    }
    
}

int main()
{
       
    doctest::Context().run();
    return 0;
}



