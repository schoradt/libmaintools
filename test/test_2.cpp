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
 * Test für den Konfigurationshandler.
 *
 * @author Sven Schoradt
 */

#include <iostream>

#include "maintools.h"

int main(int argc, char * argv[]) {

  std::cout << "test 2 - config class whith file ..." << std::endl;

  arguments args(argc, argv);

  std::string filename;

  if(args.count_noptions() == 1) {
    args.get_noption(0, filename);

    std::cout << "filename: " << filename << std::endl;

  } else {
    std::cerr << "you must give a config file" << std::endl;
    std::cerr << "call test_2.t filaneme " << std::endl;

    return 0;
  }

  // create config
  config conf(args.program());

  conf.open_file(filename);

  if(conf.get_section("test1").name() == "test1") {
    std::cout << "    get_section OK" << std::endl;

  } else {
    std::cout << "    get_section FAIL" << std::endl;

  }

  config_section sec1 = conf.get_section("test1");

  if(sec1.get("karte") == "blau") {
    std::cout << "    get 1 OK" << std::endl;

  } else {
    std::cout << "    get 1 FAIL" << std::endl;

  }

  if(sec1.get("herz") == "rot") {
    std::cout << "    get 2 OK" << std::endl;

  } else {
    std::cout << "    get 2 FAIL" << std::endl;

  }
  
 
  return 0;

};
