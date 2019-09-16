#include <unordered_set>
#include <string>
#include <vector>
#include <istream>
#include <memory>

namespace cppc {

	class SyntaxBase;
	class Syntax;

	class SyntaxBase {
	protected:
		SyntaxBase();
	};

	class Syntax : public std::shared_ptr<SyntaxBase> {
	public:

	};


	class SyntaxOpt : public SyntaxBase {
	private:
		Syntax syntax;

	public:
		SyntaxOpt(Syntax syntax) : syntax(syntax) {}
	};


	class SyntaxPair : public SyntaxBase {
	private:
		Syntax syntax_1, syntax_2;

	public:
		SyntaxPair(Syntax syntax_1, Syntax syntax_2)
			: syntax_1(syntax_1), syntax_2(syntax_2) {};
	};


	class SyntaxOR : public SyntaxBase {
	private:
		Syntax syntax_1, syntax_2;

	public:
		SyntaxOR(Syntax syntax_1, Syntax syntax_2)
			: syntax_1(syntax_1), syntax_2(syntax_2) {};
	};


	class SyntaxString : public SyntaxBase {
	public:
		std::string str;
	};


	class SyntaxLoader {
	public:
		using Syntaxes = std::unordered_set<Syntax>;

		SyntaxLoader(std::istream& is);
		
		struct Log {
			size_t i_line;
			size_t i_char;
			bool is_error;
			std::string message;
		};

	private:
		void parse(std::istream& is);
		Syntax parse_syntax    (std::istream& is, char end);
		Syntax parse_syntax_opt(std::istream& is, char end);
		
		Syntax new_syntax(std::string name);
		Syntax get_syntax(std::string name);

		void put_warning(std::string);
		void put_error(std::string);

		Syntaxes syntax;

		std::vector<Log> logs;
		size_t i_line = 0;
		size_t i_char = 0;

	};

}
