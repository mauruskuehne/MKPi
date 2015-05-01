//
//  StringFunctionsTest.cpp
//  MKPi
//
//  Created by Maurus Kühne on 01.05.15.
//  Copyright (c) 2015 Maurus Kühne. All rights reserved.
//

#include <stdio.h>
#include "catch.hpp"
#include "StringFunctions.h"

TEST_CASE( "strlen", "[StringFunctions]" ) {
  
  REQUIRE(Strings::strlen("012345") == 6);
  REQUIRE(Strings::strlen("") == 0);
}


TEST_CASE( "strcmp", "[StringFunctions]" ) {
  
  REQUIRE(Strings::strcmp("first", "second") == 0);
  REQUIRE(Strings::strcmp("","") == 1);
  
  REQUIRE(Strings::strcmp("hello","hello") == 1);
}