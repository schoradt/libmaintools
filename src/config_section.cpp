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
 * ConfigSection Implementation
 *
 * @author Sven Schoradt
 */

#include "maintools/config_section.h"

/**
 * Konstruktor, erzeugt eine Konfigurationsabteilung unter dem 
 * angegebenen Namen.
 * Es wird der enthaltenen Fehlermanager initialisiert.
 */
config_section::config_section(std::string name)
  :error_handler(),
   s_name(name)
{
  // noop this time
};

/**
 * Destruktor. Bisher ungenutzt.
 */
config_section::~config_section() {
  // noop this time
};

/**
 * Setzt und liefert den Namen der Sektion.
 */
std::string config_section::name(std::string name) {
  set_good();

  if(name != "") {
    s_name.assign(name);
  }

  return s_name;
};

/**
 * Fügt ein Schlüssel Wert Paar der Sektion hinzu. Bei leerem Schlüssel wird ein
 * Fehler ausgelöst.
 */
void config_section::set(std::string key, std::string value) {
  set_good();

  if(key == "") {
    set_error("Leerer Schlüssel an set übergeben");

    return;

  }

  std::map<std::string, std::vector<std::string> >::iterator it;

  it = m_config_items.find(key);

  if(it != m_config_items.end()) {
    // apend the value to the item vector
    ((*it).second).push_back(value);
  } else {
    std::vector<std::string> item;
    item.push_back(value);

    m_config_items[key] = item;
  }
};

/**
 * Liefert den Wert zu einem Schlüssel. Sind zu einem Schlüssel mehrere
 * Werte vorhanden so wird der letzte verzeichnete zurückgeliefert.
 *
 * Wird der gesuchte Schlüssel in der Sektion gefunden, wird sein Wert 
 * zurückgeliefert. Wird er nicht gefunden so wird im darüberligenden 
 * Scope weitergesucht.
 */
const std::string config_section::get(std::string key) {
  if(key == "") return "";

  std::map<std::string, std::vector<std::string> >::iterator it;

  it = m_config_items.find(key);

  if(it != m_config_items.end()) {
    // return the last value
    return (*it).second.back();

  } else {
    if(root()) {
      return root()->get(key);

    } else {
      return "";

    }
  }

};

/**
 * Liefert eine Werteliste. Es wird zu einem Schlüssel eine Liste von Werten
 * die in der Reihenfolge ihres hinzufügens vorliegen, zurückgegeben.
 *
 * Falls der Schlüssel nicht gefunden wird wird im darüberliegenden Scope weitergesucht.
 */
const std::vector<std::string> config_section::get_list(std::string key) {
  if(key == "") {
    std::vector<std::string> empty;

    return empty;
  }

  std::map<std::string, std::vector<std::string> >::iterator it;

  it = m_config_items.find(key);

  if(it != m_config_items.end()) {
    // return the last value
    return (*it).second;

  } else {
    if(root()) {
      return root()->get_list(key);

    } else {
      std::vector<std::string> empty;

      return empty;

    }

  }

};

/**
 * Setzt und liefert den Vaterknoten einer Sektion.
 */
config_section * config_section::root(config_section * set) {
  if(set != NULL) {
    father = set;

  }

  return father;

};
