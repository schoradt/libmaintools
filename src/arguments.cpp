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

#include "maintools/arguments.h"

/**
 * @file
 *
 * Implementaion des Argumenthandlers. Es werden hier nur die Funktionen
 * implementiert, die nicht als Template implementiert sind.
 *
 * @author Sven Schoradt
 */

/**
 * Erzeuge einen leeren Argumenthandler.
 */
arguments::arguments()
  :error_handler(),
   m_arguments(),
   v_non_options(),
   s_progname() 
{

};

/**
 * Erzeuge einen Argumenthandler aus argv und argc.
 */
arguments::arguments(int argc, char** argv)
  :error_handler(),
   m_arguments(),
   v_non_options(),
   s_progname(argv[0]) 
{
  // clean program name
  int index = s_progname.find_last_of('/');

  if(index != std::string::npos) {
    s_progname = s_progname.substr(index+1);

  }

  std::string arg_string;
  std::string look_ahead;
  // start at 1 to skip programm name
  for(int i = 1; i < argc; i++) {
    // init strings for current argument section
    std::string arg_string = argv[i];

    // prepare look_ahead for spaced arguments
    if(i+1 < argc) {
      look_ahead = argv[i+1];

    } else {
      look_ahead = "";

    }

    // some tests
    if(arg_string[0] != '-') {
      // no argument - non-option
      v_non_options.push_back(arg_string);

    } else if(arg_string == "--") {
      // register the rest of the arguments as non-options
      for(i++; i < argc; i++) {
        arg_string = argv[i];

        v_non_options.push_back(arg_string);
      }

    } else {
      // is an argument - I hope
      bool b_short = false;

      if(arg_string[1] == '-') {
        // long argument
        arg_string.erase(0,2);

      } else {
        // short argument
        arg_string.erase(0,1);
        b_short = true;

      }

      std::string name = "";
      std::string value = "";

      // looking for = or :
      std::string::size_type eq_index = arg_string.find('=');

      if(eq_index == std::string::npos) {
        eq_index = arg_string.find(':');

      }

      if(eq_index != std::string::npos) {
        name = arg_string.substr(0, eq_index);

        arg_string.erase(0, eq_index+1);

        value = arg_string;
      } else {
        name = arg_string;

        // looking for spaced values - only for long options
        if(!b_short && look_ahead != "" && look_ahead.size() > 0 && look_ahead[0] != '-') {
          value = look_ahead;
          i++;

        }

      }


      if(b_short && name.size() > 1) {
        // compressed short flags, ignore value
        while(name != "") {
	  std::string short_name(name, 0, 1);
	  std::string short_value("");

          name.erase(0,1);

          m_arguments[short_name] = make_pair(false, short_value);

        }

      } else {

        if(value != "") {
          m_arguments[name] = make_pair(true, value);

        } else {
          m_arguments[name] = make_pair(false, value);

        }

      }

    }

  }
  
};

/**
 * Erzeuge einen Argumenthandler als Kopie eines anderen.
 */
arguments::arguments(arguments& source)
  : error_handler(source),
    m_arguments(source.m_arguments),
    v_non_options(source.v_non_options),
    s_progname(source.s_progname)
{

};

/**
 * Zerstöre den Argumenthandler.
 *
 * Nichts zu tuen bis jetzt, aber man weiss ja nie.
 */
arguments::~arguments() {};

/**
 * Prüft ob ein Argument gesetzt ist. Für Flags, d.h. Argumente ohne Wert die 
 * einzigste Möglichkeit der Abfrage.
 */
bool arguments::has(std::string name) {
  set_good();

  if(m_arguments.find(name) != m_arguments.end()) {
    return true;

  }

  return false;
};

/**
 * Liefert die Anzahl der Nicht-Argumente.
 */
int arguments::count_noptions() {

  return (int)v_non_options.size();

};

/**
 * Liefert den Namen des Programmes. Dieser wird aus argv[0] ermittelt.
 */
std::string arguments::program() {
  return s_progname;
};
