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

#ifndef DEX_MAINTOOLS_CONFIG_H
#define DEX_MAINTOOLS_CONFIG_H

#include "maintools/config_section.h"

/**
 * @file
 *
 * Konfiguration eines Programmes.
 *
 * @author Sven Schoradt
 */

/**
 * @class config
 *
 * Die Klasse repräsentiert die Konfigurationsdatei eines Programmes.
 * Diese kann aus mehreren Sektionen, gekennzeichnet durch '\<name\>', 
 * bestehen. Im globalen Kontext und in jeder Sektion werden Schlüssel-Wert
 * Paare mittels 'Schlüssel=Wert' abgelegt. Kommentare sind mittels '#' möglich.
 */
class config:public config_section {
public:
  config();

  config(std::string program);

  void open_file(std::string filename, bool report_error = true);

  void add_section(config_section * sec);

  config_section& get_section(std::string name);

private:
  std::vector<config_section*> v_sections;
  
};

/**
 * Verweis auf die Scannerfunktion zum Einlesen des Konfigurationsdateiinhalts.
 */
extern int read_config(config * inconf, std::string filename);

#endif
