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

#include <iostream>

#include "maintools/config.h"

/**
 * @file
 *
 * Implementation der Config-Klasse.
 *
 * @author Sven Schoradt
 */


config::config():config_section(), v_sections() {
  // noop soon
};

config::config(std::string filename):config_section(), v_sections() {
  // read config from file
  if(! read_config(this, filename)) {
    std::cerr << "An error occured between config processing" << std::endl;
  }
};

void config::add_section(config_section * sec) {
  if(sec != NULL) {
    v_sections.push_back(sec);

    sec->root(this);

  }

};

config_section& config::get_section(std::string name) {
  std::vector<config_section*>::iterator it;

  for(it=v_sections.begin(); it != v_sections.end(); it++) {
    if((*it)->name() == name) {
      return (*(*it));
    }
  }

  config_section empty("empty");

  return empty;
};
