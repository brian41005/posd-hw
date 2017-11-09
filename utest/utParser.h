#ifndef UTPARSER_H
#define UTPARSER_H

#include "../include/parser.h"
#include "../include/scanner.h"


TEST(Parser, createTerm_Var){
    Scanner scanner("X");
    Parser parser(scanner);
    ASSERT_EQ("X", parser.createTerm()->symbol());    
}

TEST(Parser, createTerm_Num){
  Scanner scanner("123");
  Parser parser(scanner);
  ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST(Parser, createTerm_Atom)
{
  Scanner scanner("tom");
  Parser parser(scanner);
  ASSERT_EQ("tom", parser.createTerm()->symbol());
}

TEST(Parser, createArgs)
{
  Scanner scanner("1, X, tom");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("1", terms[0]->symbol());
  ASSERT_EQ("X", terms[1]->symbol());
  ASSERT_EQ("tom", terms[2]->symbol());
}

TEST(Parser, createArgs_two)
{
  Scanner scanner("1, X");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("1", terms[0]->symbol());
  ASSERT_EQ("X", terms[1]->symbol());
}

TEST(Parser, createArgs_one)
{
  Scanner scanner("1");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("1", terms[0]->symbol());
}

TEST(Parser, createTerms)
{
  Scanner scanner("s(1, X, tom)");
  Parser parser(scanner);
  ASSERT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}

// Given there is string: "point(1, X, z(1,2,3))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z(1,2,3))".
TEST(Parser, parseStructOfStruct) {
    Scanner scanner("point(1, X, z(1,2,3))");
    Parser parser(scanner);
    ASSERT_EQ("point(1, X, z(1, 2, 3))", parser.createTerm()->symbol());
    
}

// Given there is string: "s(s(s(s(1))))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "s(s(s(s(1))))".
TEST(Parser, parseStructOfStructAllTheWay) {
    Scanner scanner("s(s(s(s(1))))");
    Parser parser(scanner);
    ASSERT_EQ("s(s(s(s(1))))", parser.createTerm()->symbol());
    
}

// Given there is string: "point(1, X, z)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z)".
TEST(Parser, parseStructThreeArgs) {
    Scanner scanner("point(1, X, z)");
    Parser parser(scanner);
    ASSERT_EQ("point(1, X, z)", parser.createTerm()->symbol());
 
}

// Given there is string: "_date" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Variable.
// And #symbol() of Variable should return "_date".
TEST(Parser, parseVar) {
    Scanner scanner("_date");
    Parser parser(scanner);
    ASSERT_EQ("_date", parser.createTerm()->symbol());

}

// Given there is string: "point()" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point()".
TEST(Parser, parseStructNoArg) {
    Scanner scanner("point()");
    Parser parser(scanner);
    ASSERT_EQ("point()", parser.createTerm()->symbol());
}

// Given there is string: "   [   ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[]".
TEST(Parser, parseListEmpty) {
    Scanner scanner("   [   ]");
    Parser parser(scanner);
    ASSERT_EQ("[]", parser.createTerm()->symbol());
}

// Given there is string: "   [  [1], [] ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], []]".
TEST(Parser, parseListOfLists) {
    Scanner scanner("   [  [1], [] ]");
    Parser parser(scanner);
    ASSERT_EQ("[[1], []]", parser.createTerm()->symbol());
}

// Given there is string: "point(11)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11)".
TEST(Parser, parseStructOneArg) {
    Scanner scanner("point(11)");
    Parser parser(scanner);
    ASSERT_EQ("point(11)", parser.createTerm()->symbol());
}

// Given there is string: "point(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11, 12)".
TEST(Parser, parseStructTwoArgs) {
    Scanner scanner("point(11,12)");
    Parser parser(scanner);
    ASSERT_EQ("point(11, 12)", parser.createTerm()->symbol());
}

// Given there is string: "   [  [1], [], s(s(1)) ]   " in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], [], s(s(1))]".
TEST(Parser, parseListOfListsAndStruct) {
    Scanner scanner("   [  [1], [], s(s(1)) ]   ");
    Parser parser(scanner);
    ASSERT_EQ("[[1], [], s(s(1))]", parser.createTerm()->symbol());
}

// Given there is string: "   [1, 2]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[1, 2]".
TEST(Parser, parseList) {
    Scanner scanner("   [1, 2]");
    Parser parser(scanner);
    ASSERT_EQ("[1, 2]", parser.createTerm()->symbol());
}

// Given there is string: "...(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "...(11, 12)".
TEST(Parser, parseStructDOTSTwoArgs) {
    Scanner scanner("...(11,12)");
    Parser parser(scanner);
    ASSERT_EQ("...(11, 12)", parser.createTerm()->symbol());
}

// Given there is string: ".(2,.(1,[]))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(2, .(1, []))"
// And the first term should be number: "2", the second term should be another Strcut: ".(1, [])".
TEST(Parser, ListAsStruct2) {
    Scanner scanner(".(2,.(1,[]))");
    Parser parser(scanner);
    Struct *s = dynamic_cast<Struct *>(parser.createTerm());
    ASSERT_EQ(2, s->arity());
    ASSERT_EQ(".(2, .(1, []))", s->symbol());
    ASSERT_EQ("2", s->args(0)->symbol());
    ASSERT_EQ(".(1, [])", s->args(1)->symbol());
}

// Given there is string: ".(1,[])" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(1, [])".
// And the first term should be number: "1", the second term should be another List: "[]".
TEST(Parser, ListAsStruct) {
    Scanner scanner(".(1,[])");
    Parser parser(scanner);
    Struct *s = dynamic_cast<Struct *>(parser.createTerm());
    ASSERT_EQ(2, s->arity());
    ASSERT_EQ(".(1, [])", s->symbol());
    ASSERT_EQ("1", s->args(0)->symbol());
    ASSERT_EQ("[]", s->args(1)->symbol());
}

// Given there is not string in scanner.
// When parser parses all terms via scanner.
// Then it should return nothing.
TEST(Parser, listOfTermsEmpty) {
    Scanner scanner;
    Parser parser(scanner);
    ASSERT_EQ(nullptr, parser.createTerm());
}

// Given there is string: "[1,2)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a string: "unexpected token" as exception.
TEST(Parser, illegal1) {
    Scanner scanner("[1,2)");
    Parser parser(scanner);
    try{
        parser.createTerm();
    }catch(string s){
        EXPECT_EQ("unexpected token", s);
    }
}
    
// Given there is string: " 12345,  tom" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "tom".
TEST(Parser, listOfTermsTwo) {
    Scanner scanner(" 12345,  tom");
    Parser parser(scanner);
    vector<Term *> args = parser.getArgs();
    ASSERT_EQ("12345", args[0]->symbol());
    ASSERT_EQ("tom", args[1]->symbol());
}




// Given there is string: " 12345,  67" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "67".
TEST(Parser, listOfTermsTwoNumbers) {
    Scanner scanner(" 12345,  67");
    Parser parser(scanner);
    vector<Term *> args = parser.getArgs();    
    ASSERT_EQ("12345", args[0]->symbol());
    ASSERT_EQ("67", args[1]->symbol());

}

// Given there is string: "s(s(s(s(1)))), b(1,2,3)" in scanner.
// When parser parses all terms via scanner.
// Then it should return two Struct.
// And #symbol() of the first Strcut should return "s(s(s(s(1))))".
// And #symbol() of the second Strcut should return "b(1, 2, 3)".
TEST(ParserTest, parseStructOfStructAllTheWay2) {
    Scanner scanner("s(s(s(s(1)))), b(1,2,3)");
    Parser parser(scanner);
    vector<Term *> args = parser.getArgs();        
    ASSERT_EQ("s(s(s(s(1))))", args[0]->symbol());
    ASSERT_EQ("b(1, 2, 3)", args[1]->symbol());
}

// Given there is string: " 12345,  tom,   Date" in scanner.
// When parser parses all terms via scanner.
// Then it should return three terms: "12345", "tom" and "Date".
TEST(ParserTest, listOfTermsThree) {
    Scanner scanner(" 12345,  tom,   Date");
    Parser parser(scanner);
    vector<Term *> args = parser.getArgs();            
    ASSERT_EQ("12345", args[0]->symbol());
    ASSERT_EQ("tom", args[1]->symbol());
    ASSERT_EQ("Date", args[2]->symbol());
}

/*
TEST(ParserTest, parseStructOfStructAllTheWay3) {
    Scanner scanner("s(s(s(s(1)))), b(1,2,3), tom, X, 12.222");
    Parser parser(scanner);
    ASSERT_EQ("s(s(s(s(1))))", parser.createTerm()->symbol());
    ASSERT_EQ(nullptr, parser.createTerm());
    ASSERT_EQ("b(1, 2, 3)", parser.createTerm()->symbol());
    ASSERT_EQ(nullptr, parser.createTerm());
    ASSERT_EQ("tom", parser.createTerm()->symbol());
    ASSERT_EQ(nullptr, parser.createTerm());
    ASSERT_EQ("X", parser.createTerm()->symbol());
    ASSERT_EQ(nullptr, parser.createTerm());
    ASSERT_EQ("12.222", parser.createTerm()->symbol());
    ASSERT_EQ(nullptr, parser.createTerm());
    
}
*/
#endif