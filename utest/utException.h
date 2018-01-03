#include "../include/scanner.h"
#include "../include/parser.h"

TEST(ShellException, exception_OnlyVariable) {
    Scanner s("X.");  // this is our wrong expression.
    Parser p(s);
    try {
        p.buildExpression();  // according to your implementation.
        FAIL()
            << "It should throw an exception: X does never get assignment";  // fail if not exception is thrown.
    } catch (std::string& msg) {
        ASSERT_EQ("X does never get assignment",
                  msg);  // it should throw an exception like this.
    }
}


TEST(ShellException, exceptionMissingPeriodToken) {
    Scanner s("X=1");
    Parser p(s);
    try {
        p.buildExpression();
        FAIL() << "It should throw an exception: Missing token '.'";
    } catch (std::string& msg) {
        ASSERT_EQ("Missing token '.'", msg);
    }
}

TEST(ShellException, exception_UnexpectedDisjTokenBeforePeriod) {
    Scanner s("X;.");
    Parser p(s);
    try {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unexpected ';' before '.'";
    } catch (std::string& msg) {
        ASSERT_EQ("Unexpected ';' before '.'", msg);
    }
}

TEST(ShellException, exception_UnexpectedConjTokenBeforePeriod1) {
    Scanner s("X,.");
    Parser p(s);
    try {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unexpected ',' before '.'";
    } catch (std::string& msg) {
        ASSERT_EQ("Unexpected ',' before '.'", msg);
    }
}

TEST(ShellException, exception_UnexpectedConjTokenBeforePeriod2) {
    Scanner s("X=1,.");
    Parser p(s);
    try {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unbalanced operator";
    } catch (std::string& msg) {
        ASSERT_EQ("Unexpected ',' before '.'", msg);
    }
}

TEST(ShellException, exception_UnbalancedOperator1) {
    Scanner s("X = match(tom, marry;)");
    Parser p(s);
    try {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unbalanced operator";
    } catch (std::string& msg) {
        ASSERT_EQ("Unbalanced operator", msg);
    }
}

TEST(ShellException, exception_UnbalancedOperator2) {
    Scanner s("X = [tom, marry ;]");
    Parser p(s);
    try {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unbalanced operator";
    } catch (std::string& msg) {
        ASSERT_EQ("Unbalanced operator", msg);
    }
}