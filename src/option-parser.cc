#include "option-parser.hh"

#include <string>
#include <vector>
#include <iostream>

OptionParser::OptionParser(int argc, char **argv)
    : argc_(argc),
      argv_(argv),
      error_(false),
      pgn_(false),
      file_(""),
      player1_(""),
      player2_("")
{}

OptionParser::~OptionParser()
{}

bool OptionParser::parse()
{
    std::string token;
    for (int i(1); i < this->argc_; ++i)
    {
        if (this->error_)
            return false;

        token = std::string(this->argv_[i]);

        if (token.find("--") == 0)
            this->parsePlayer(token);
        else if (token.find(".so", token.length() - 4) != std::string::npos)
            this->libs_.push_back(token);
        else if (token.find(".pgn", token.length() - 5) != std::string::npos
            && i == this->argc_ - 1)
        {
            if (this->player1_ !=  "" || this->player2_ != "")
                return false;
            else
            {
               this->file_ = token;
               this->pgn_ = true;
            }
        }
        else
            return false;
    }
    if ((this->player1_ == "" || this->player2_ == "") && this->pgn_ == false)
        this->error_ = true;



    return !(this->error_);
}

bool OptionParser::isPgn()
{
    return this->pgn_;
}

std::string OptionParser::getFile()
{
    return this->file_;
}

void OptionParser::parsePlayer(std::string token)
{
    token = token.substr(2);
    std::string player;
    std::string::size_type count = token.find('=');
    if (count != std::string::npos)
    {
        player = token.substr(count + 1);
        if (player == "human"
            || player.find(".so", player.length() - 4) != std::string::npos)
        {
            if (token.substr(0, count) == "player-white")
            {
                if (this->player1_ == "")
                    this->player1_ = player;
                else
                    this->error_ = true;
            }
            else if (token.substr(0, count) == "player-black")
            {
                if (this->player2_ == "")
                    this->player2_ = player;
                else
                    this->error_ = true;
            }
            else
                this->error_ = true;
        }
        else
            this->error_ = true;
    }
    else
        this->error_ = true;
}

void OptionParser::print()
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "Options : " << std::endl;
    std::cout << "Is PGN ?\t" << std::boolalpha << this->isPgn() << std::endl;
    std::cout << "List of libs :" << std::endl;
    for (std::string st : this->libs_)
    {
        std::cout << "\t" << st << std::endl;
    }
    std::cout << "PGN file :\t" << this->file_ << std::endl;
    std::cout << "PLayer white:\t" << this->player1_ << std::endl;
    std::cout << "PLayer black:\t" << this->player2_ << std::endl;
}