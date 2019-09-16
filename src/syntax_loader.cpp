#include "syntax_loader.h"
using namespace cppc;

void SyntaxLoader::parse(std::istream& is)
{

	std::string cname = "";
	bool is_no_rules = false;

	std::string cline;
	while(std::getline(is, cline))
	{
		if(cline.size()) {
			if(cline[0] != '\t') {
			}
			else{
				parse_rule(std::istringstream(cline));
			}
		}
		++i_line;
	}

}


Syntax SyntaxLoader::new_syntax(std::string name)
{
	if(syntax.count(name)) put_error("Syntax name already used");
	return get_syntax(name);
}


Syntax SyntaxLoader::get_syntax(std::string name)
{
	if(!syntax.count(name)) {
		return syntax[name] = Syntax(new SyntaxBase(name));
	}
	return syntax[name];
}


Syntax SyntaxLoader::parse_syntax(std::istream& is)
{
	std::string cword;
	is >> cword;

	Syntax syntax;

	if(cword == "[") {
		syntax = parse_syntax_opt(is);
	}
	else if(cword == "]") {
		put_error("Invalid optional finish");
	}
	else{
		syntax = get_syntax(cword);
	}

	if(!is.eof()) {
		return new SyntaxPair(syntax, parse_rule(is, is_opt));
	}

	return syntax;
}

Syntax SyntaxLoader::parse_syntax_opt(std::istream& is)
{
	std::string cword;
	is >> cword;

	Syntax syntax;

	if(cword == "[") {
		put_error("Invalid optional start");
		syntax = parse_syntax_opt(is);
	}
	else if(cword == "]") {
		
	}
	else {
		syntax = get_syntax(cword);
	}

	if(!is.eof()) {
		auto p = new SyntaxPair(syntax, parse_rule(is, is_opt));
		if(is_opt) return new SyntaxOpt(p);
		return p;
	}

	return syntax;
}
