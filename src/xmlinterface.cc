#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

/* -- Adjust if necessary. -- */
#include "ai.hh"
#include "color.hh"
#include "move.hh"
#include "piece-type.hh"
#include "position.hh"
/* -------------------------- */

extern "C" { void* ai_create(int color); }

using namespace std;
using namespace boost;
using namespace boost::property_tree;

const ptree& empty_ptree()
{
  static ptree t;
  return t;
}

string piece_name(PieceType t)
{
  switch (t)
  {
    case KING: return "king";
    case QUEEN: return "queen";
    case ROOK: return "rook";
    case BISHOP: return "bishop";
    case KNIGHT: return "knight";
    case PAWN: return "pawn";
    case NONE: return "none";
  }

  return "none";
}

PieceType piece_type(string s)
{
  if (s == "KING") return KING;
  else if (s == "QUEEN") return QUEEN;
  else if (s == "ROOK") return ROOK;
  else if (s == "BISHOP") return BISHOP;
  else if (s == "KNIGHT") return KNIGHT;
  else if (s == "PAWN") return PAWN;
  else return NONE;
}

extern "C"
{
  void* ai_create_wrapped(int color)
  {
    Ai* ai = static_cast<Ai*>(ai_create(color));
    return ai;
  }

  const char* move_get_xml(void* handle)
  {
    static char* ret = NULL;
    Ai* ai = (Ai*) handle;
    Move move = ai->move_get();
    Position s = move.start_get();
    Position e = move.end_get();

    stringstream stream;
    cout << "Promotion: " << move.promotion_get() << endl;
    stream << "<move>";
    stream << "<start c=\"" << s.file_get() << "\" r=\"" << s.rank_get() << "\"/>";
    stream << "<end c=\"" << e.file_get() << "\" r=\"" << e.rank_get() << "\"/>";
    stream << "<promotion type=\"" << piece_name(move.promotion_get()) << "\"/>";
    stream << "</move>";
    string str = stream.str();

    free(ret);
    ret = static_cast<char*>(malloc(sizeof(char) * str.size() + 1));
    memcpy(ret, str.c_str(), str.size() + 1);
    printf("move: %s\n", ret);

    return ret;
  }

  void last_opponent_move_set_xml(void* handle, const char* moveXML)
  {
    Ai* ai = (Ai*) handle;
    ptree tree;
    string xml(moveXML);
    istringstream stream(xml);
    read_xml(stream, tree);
    const ptree& move = tree.get_child("move", empty_ptree());
    int sc = 0, sr = 0, ec = 0, er = 0;
    string prom;

    for (const ptree::value_type& item : move)
    {
      if (item.first == "start")
      {
        sc = item.second.get_child("<xmlattr>").get<int>("c");
        sr = item.second.get_child("<xmlattr>").get<int>("r");
      }
      else if (item.first == "end")
      {
        ec = item.second.get_child("<xmlattr>").get<int>("c");
        er = item.second.get_child("<xmlattr>").get<int>("r");
      }
      else if (item.first == "promotion")
      {
        prom = item.second.get_child("<xmlattr>").get<string>("type");
      }
    }

    Position s(static_cast<Position::File>(sc), static_cast<Position::Rank>(sr));
    Position e(static_cast<Position::File>(ec), static_cast<Position::Rank>(er));
    Move m(s, e, piece_type(prom));
    ai->last_opponent_move_set(m);
  }
}
