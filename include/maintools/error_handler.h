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

#ifndef DEX_MAINTOOLS_ERROR_HANDLER_H
#define DEX_MAINTOOLS_ERROR_HANDLER_H

#include <string>

/**
 * @file
 *
 * Fehlerhandling für die im Projekt entstehenden Klassen.
 *
 * @author Sven Schoradt
 */

/**
 *
 * @class error_handler
 *
 * Stellt das Fehlermanagementinterface für alle Dienste des Projekts zur 
 * Verfügung. Die Klasse ist somit Basis aller Dienstklassen.
 */

class error_handler {
 public:
  /**
   * Konstruktor, initialisiere Handler.
   */
  error_handler()
    :flag_error(),
     string_error() 
  {
  };


  /**
   * Kopiere einen Errorhandler, für die Kopiermechanismen der abgeleiteten Objekte wichtig.
   */
  error_handler(error_handler& source)
    :flag_error(source.flag_error),
     string_error(source.string_error)
    {
      set_good();
    };

  /**
   * Destruktor, tut bis jetzt nichts.
   */
  virtual ~error_handler() {};


  /**
   * Liefert eine Beschreibung des letzten Fehlers. Diese Beschreibungen werden 
   * nicht zurückgesetzt, für die Fehlererkennung verwende man error_handler::bad().
   */
  std::string error() { return string_error; };

  /**
   * Gibt Aufschluss auf den Zustand des Objektes.
   *
   * Das Objekt wird zu Beginn jedes Methodenaufrufes wieder in einen
   * 'guten' Zustand versetzt.
   */
  bool bad() { return flag_error; };


 private:
  bool flag_error; // error reporting flag
  std::string string_error; // last error string, is once set and never reseted
 protected:
  void set_error(std::string msg) {
    string_error = msg;
    flag_error = true;
  };

  void set_good() {
    flag_error = false;
  };
};

#endif
