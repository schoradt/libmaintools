/*
 * maintools - small c++ library for application development.
 * Copyright (C)2004 Sven Schoradt
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Contact by Mail via <sven@dex.de>.
 * 
 */

/**
 * @file
 *
 * Test für den Argumenthandler
 *
 * @author Sven Schoradt
 */

#include <iostream>

#include "maintools.h"

int main(int argc, char ** argv) {
  std::cout << "maintools test case #1 - arguments test" << std::endl;

  std::cout << std::endl << "with --test=name you set the paramname for testing." << std::endl;

  std::cout << "testing creation ... ";
  arguments args(argc, argv);

  if(args.bad()) {
    std::cerr << "error: " << args.error() << std::endl;

    std::cout << "FAIL" << std::endl;

    return 1;


  } else {
    std::cout << "DONE" << std::endl;

  }

  std::cout << "testing progname ... ";

  std::cout << "progname is " << args.program() << " ";

  std::cout << "DONE" << std::endl;

  std::string test_name;

  if(args.get("test", test_name, "param")) {
    std::cout << "testing has ... ";

    if(args.has(test_name)) {
      std::cout << "parameter " << test_name << " is set ";

    } else {
      std::cout << "parameter " << test_name << " is not set ";

    }
    std::cout << "DONE" << std::endl;

    std::cout << "testing getter ... " << std::endl;

    int i;
    std::string str;
    bool b;
    float f;

    if(args.get(test_name, i)) {
      std::cout << "    parameter " << test_name << " as int = " << i << std::endl;
    }

    if(args.get(test_name, str)) {
      std::cout << "    parameter " << test_name << " as string = " << str << std::endl;
    }

    if(args.get(test_name, b)) {
      std::cout << "    parameter " << test_name << " as bool = " << b << std::endl;
    }

    if(args.get(test_name, f)) {
      std::cout << "    parameter " << test_name << " as float = " << f << std::endl;
    }

    std::cout << "DONE" << std::endl;
  
  }

  std::cout << "testing non option part 1 ... ";

  std::cout << "number of non options found " << args.count_noptions() << std::endl;

  for(int i = 0; i < args.count_noptions(); i++) {
    std::string no_str;

    if(args.get_noption(i, no_str)) {
      std::cout << "    non option (string)" << i << ": " << no_str << " ";

    }

    int no_int;

    if(args.get_noption(i, no_int)) {
      std::cout << "non option (int)" << i << ": " << no_int << " ";

    }

    float no_float;

    if(args.get_noption(i, no_float)) {
      std::cout << "non option (float)" << i << ": " << no_float << " ";

    }

    std::cout << std::endl;

  };

  std::cout << "DONE" << std::endl;

  std::cout << "testing non option part 2 ... ";

  std::cout << "number of non options found " << args.count_noptions() << std::endl;

  arguments::non_option_iterator it;

  for(it = args.no_begin(); it != args.no_end(); it++) {
    std::string no_str = *it;

    std::cout << "    non option : " << no_str << " " << std::endl;

  };

  std::cout << "DONE" << std::endl;

  return 0;
};
