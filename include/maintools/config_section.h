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

#ifndef DEX_MAINTOOLS_CONFIG_SECTION_H
#define DEX_MAINTOOLS_CONFIG_SECTION_H

#include <string>
#include <map>
#include <vector>

#include "maintools/error_handler.h"

/**
 * @file
 *
 * Benamster Teil der Konfigurationsdatei.
 *
 * @author Sven Schoradt
 */

/**
 * @class config_section
 *
 * Eine Sektion in der Konfigdatei. Bietet das Abfrageinterface für 
 * Konfigurationsschlüssel ect.
 */

class config_section:public error_handler {
public:
  config_section(std::string name = "");

  ~config_section();

  std::string name(std::string name = "");

  void set(std::string key, std::string value);

  const std::string get(std::string key);

  const std::vector<std::string> get_list(std::string key);

  config_section * root(config_section * set = NULL);
  
private:
  std::string s_name;
  std::map<std::string, std::vector<std::string> > m_config_items;

  config_section * father;

};

#endif
