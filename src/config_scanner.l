%{
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
 * Scanner für Konfigurationsdateien.
 * 
 * @author Sven Schoradt
 */

#include "maintools/config.h"

#include <iostream>
#include <string>

#include <cstdio>

config * conf = 0;

config_section * sec = 0;

%}

%%
<<EOF>> { return 1; }
[ \t\n] ; // ignore whitespace, tabs and newlines
#.*\n    ; // ignore Comments line by line
.*[:space:]*=[:space:]*.* { 
                            std::string kv(yytext); 

                            int pos;
                            pos = kv.find_first_of("=");
                            std::string key = kv.substr(0,pos);
                            std::string value = kv.substr(pos+1);

                            pos = key.find_first_not_of(" ");
                            key.erase(0,pos);
                            pos = key.find_last_not_of(" ");
                            key.erase(pos+1);
                            pos = value.find_first_not_of(" ");
                            value.erase(0,pos);
                            pos = value.find_last_not_of(" ");
                            value.erase(pos+1);

                            if(sec) {
                              sec->set(key,value);

                            } else {
                              conf->set(key, value);

                            }
                          }
^<[a-z0-9_-]+> { 
                 std::string section(yytext);

                 int pos;

                 pos = section.find_first_of("<");
                 section.erase(0,pos+1);
                 pos = section.find_last_of(">");
                 section.erase(pos);

                 sec = new config_section(section);
                 conf->add_section(sec); 
               }
. { std::cerr << "Unerlaubtes Zeichen" << yytext << std::endl; return 0; }
%%

int yywrap() {
  return 1;
}

int read_config(config * inconf, std::string filename) {
  conf = inconf;

  if(! conf) return 0;

  std::cout << "Reading config " << filename << std::endl;

  yyin = fopen(filename.c_str(), "r+");

  int mode = 0;

  if(yyin) {

    mode = yylex();

    fclose(yyin);

  }

  return mode;

}
