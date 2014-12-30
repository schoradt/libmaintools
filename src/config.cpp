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
#include <cstdlib>

#include "maintools/config.h"

/**
 * @file
 *
 * Implementation der Config-Klasse.
 *
 * @author Sven Schoradt
 */

/**
 * Erstellt ein leeres Konfigobjekt, in das mittels open_file dann daten geladen 
 * werden können.
 */
config::config():config_section(), v_sections() {
  // noop soon
};

/**
 * Erstellt ein Konfigurationsobjekt zu einem Programm. Hierzu werden die 
 * Dateien "/etc/prognamerc", "$(HOME)/.prognamerc" und ".prognamerc" eingelesen.
 */
config::config(std::string program):config_section(), v_sections() {
  // read config from file
  std::string filename;

  filename = "/etc/"+program+"rc";
  open_file(filename);
  
  filename = std::getenv("HOME");

  filename += "/."+program+"rc";
  open_file(filename);

  filename = "."+program+"rc";
  open_file(filename);
  
};

/**
 * Liest eine Datei in das Konfigurationsobjekt ein.
 */
void config::open_file(std::string filename, bool report_error) {
  if(! read_config(this, filename)) {
    if(report_error) {
      std::cerr << "An error occured between config processing ( file:" << filename << " )" << std::endl;

    }

  }

};

/**
 * Fügt dem Konfigurationsobjekt eine Sektion hinzu.
 */
void config::add_section(config_section * sec) {
  if(sec != NULL) {
    v_sections.push_back(sec);

    sec->root(this);

  }

};

/**
 * Liefert eine Sektion aus dem Konfigurationsobjekt.
 */
config_section& config::get_section(std::string name) {
  std::vector<config_section*>::iterator it;

  for(it=v_sections.begin(); it != v_sections.end(); ++it) {
    if((*it)->name() == name) {
      return (*(*it));
    }
  }

  config_section* empty = new config_section("");

  return (*empty);
};
