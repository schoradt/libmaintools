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

#ifndef DEX_MAINTOOLS_ARGUMENTS_H
#define DEX_MAINTOOLS_ARGUMENTS_H

#include <map>
#include <vector>
#include <utility>
#include <string>

#include "maintools/utility.h"
#include "maintools/error_handler.h"

/**
 * @file
 *
 * Verwalte die Kommandozeilenargumente eines Programmes.
 *
 * @author Sven Schoradt
 */


/**
 *
 * @class arguments
 *
 * Klasse zum Verwalten von Kommandozeilenargumenten.
 *
 * Es wird eine POSIX-konforme implementation des Argumenthandlings angestrebt.
 * Es werden einbuchstabige Argumente als '-p' und mehrbuchstabige Argumente als 
 * '--param' akzeptiert. Werte werden mittels '=' oder mittels Lehrzeichen getrennt 
 * angegeben, wobei bei Lehrzeichengetrenntem Wert der Wert nicht mit einem '-'
 * beginnen darf.
 * Non-Options, das sind Teile der Argumentkette, die nicht mit '-' beginnen werden gierig
 * an die Optionen als Werte gebunden. Um dies zu verhindern muss der Nutzer nach der 
 * letzten OPtion '--' angeben. Danach werden alle folgenden Teile der Argumentkette als 
 * Non-Options betrachtet.
 */

class arguments:public error_handler {
public:
  arguments();
  arguments(int argc, char** argv);
  arguments(arguments& source);

  ~arguments();

  /**
   * Liefert den Wert eines Arguments. Es kann ein Default-Wert angegeben werden.
   */
  template<class A,class B> bool get(std::string name, A& value, B& default_value)
  {
    set_good();

    if(m_arguments.find(name) != m_arguments.end()) {
      if(m_arguments[name].first) {
        return convert(m_arguments[name].second, value);

      } 

    }

    return convert(default_value, value);

  };

  /**
   * Liefert den Wert eines Argumentes.
   */
  template<class A> bool get(std::string name, A& value)
  {
    set_good();

    if(m_arguments.find(name) != m_arguments.end()) {
      if(m_arguments[name].first) {
        return convert(m_arguments[name].second, value);

      }

    }

    return false;

  };

  bool has(std::string name);

  int count_noptions();

  /**
   * Liefert die i-te Non-Option.
   */
  template<class A> bool get_noption(int i, A& value) {
    set_good();

    if(i < count_noptions()) {
      return convert(v_non_options[i], value);
    }

    return false;
  }

  std::string program();

  /**
   * Iterator Typ für das iterieren über die vorhandenen non-options.
   */
  typedef std::vector<std::string>::iterator non_option_iterator;

  /**
   * Liefert einen Iterator der auf den Start der Liste von Non-Options verweist.
   */
  non_option_iterator no_begin() { return v_non_options.begin(); };

  /**
   * Liefert einen Iterator der das Ende der Non-OPtions markiert.
   */
  non_option_iterator no_end() { return v_non_options.end(); };
  
private:
  std::map<std::string, std::pair<bool, std::string> > m_arguments;

  std::vector<std::string> v_non_options;

  std::string s_progname;

};


#endif
