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

#ifndef DEX_MAINTOOLS_H
#define DEX_MAINTOOLS_H

#include "maintools/arguments.h"
#include "maintools/config.h"

/**
 * @file
 *
 * Einstiegspunkt in das Interface der Bibliothek.
 * Es werden Faktory-Funktionen für die Teilbereiche der Bibliothek angeboten.
 *
 * @author Sven Schoradt
 */

/**
 * @class maintools
 *
 * Klasse zur Sammlung der Fabrikmethoden für das Bibliotheksinterface.
 * Die meisten Funktionen implementieren das Singleton-Pattern.
 */

class maintools {
public:
  static arguments& get_arguments(int argc, char** argv);
  static config& get_config(std::string filename);
private:
};


#endif
